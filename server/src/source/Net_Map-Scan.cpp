#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime> // for rand() and srand()
#include <winsock2.h> // For Winsock functions
#include <windows.h> // for Sleep()
#include <iomanip> // for std::setw

#include <ws2tcpip.h> // For inet_ntop
#include <iphlpapi.h> // For IP Helper API functions
#include <icmpapi.h> // For ICMP API functions

#pragma comment(lib, "ws2_32.lib") // Link with Winsock library
#pragma comment(lib, "iphlpapi.lib") // Link with IP Helper API library
#pragma comment(lib, "icmp.lib") // Link with ICMP library


int mais() {
    WSADATA wsa;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    SOCKET sock;
    int i, start, end, err;
    char hostname[100];
    struct sockaddr_in sa;
    int ret;
    DWORD timeout = 1000; // Timeout in milliseconds

    printf("Enter hostname or IP: ");
    scanf("%s", hostname);

    printf("Enter start port number: ");
    scanf("%d", &start);

    printf("Enter end port number: ");
    scanf("%d", &end);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the hostname
    ret = getaddrinfo(hostname, NULL, &hints, &result);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(ret));
        WSACleanup();
        return 2;
    }

    // Loop through all addresses returned by getaddrinfo
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        if (ptr->ai_family == AF_INET) {
            memcpy(&sa, ptr->ai_addr, sizeof(struct sockaddr_in));
            break;
        }
    }

    if (ptr == NULL) {
        fprintf(stderr, "No valid address found.\n");
        freeaddrinfo(result);
        WSACleanup();
        return 3;
    }

    // Print the IP address being scanned
    printf("Scanning ports on %s (%s):\n", hostname, inet_ntoa(sa.sin_addr));

    sa.sin_family = AF_INET;

    srand((unsigned int)time(NULL)); // Initialize random seed

    for (i = start; i <= end; i++) {
        sa.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (sock == INVALID_SOCKET) {
            fprintf(stderr, "socket creation failed\n");
            WSACleanup();
            return 4;
        }

        // Set receive timeout
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

        err = connect(sock, (struct sockaddr *)&sa, sizeof(sa));

        if (err == SOCKET_ERROR) {
            int error_code = WSAGetLastError();
            if (error_code == WSAETIMEDOUT) {
                // Port is likely open but filtered
                printf("Port %i is open (filtered)\n", i);
            } else if (error_code == WSAECONNREFUSED) {
                // Port is closed
                // printf("Port %i is closed\n", i); // Commented out for silent mode
            } else {
                // Other errors
                fprintf(stderr, "Error connecting to port %i: %d\n", i, error_code);
            }
        } else {
            // Successfully connected (port is open)
            printf("Port %i is open\n", i);
        }

        closesocket(sock);

        // Randomize delay between 10 to 50 milliseconds
        Sleep(10 + rand() % 41);
    }

    freeaddrinfo(result);
    WSACleanup();
    return 0;
}











void pingSweep(const std::string& subnet, int start, int end) {
    HANDLE hIcmpFile;
    unsigned long ipaddr = INADDR_NONE;
    DWORD dwRetVal = 0;
    char sendData[] = "PingSweepData";
    LPVOID replyBuffer = nullptr;
    DWORD replySize = 0;

    replySize = sizeof(ICMP_ECHO_REPLY) + sizeof(sendData);
    replyBuffer = (VOID*)malloc(replySize);
    if (replyBuffer == nullptr) {
        std::cerr << "Unable to allocate memory" << std::endl;
        return;
    }

    hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Unable to open handle" << std::endl;
        free(replyBuffer);
        return;
    }

    for (int i = start; i <= end; ++i) {
        std::string ip = subnet + std::to_string(i);
        ipaddr = inet_addr(ip.c_str());
        if (ipaddr == INADDR_NONE) {
            std::cerr << "Invalid IP address: " << ip << std::endl;
            continue;
        }

        dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, sendData, sizeof(sendData), 
                                NULL, replyBuffer, replySize, 1000);
        if (dwRetVal != 0) {
            PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)replyBuffer;
            struct in_addr replyAddr;
            replyAddr.S_un.S_addr = pEchoReply->Address;
            std::cout << "Reply from " << ip << ": bytes=" << pEchoReply->DataSize 
                      << " time=" << pEchoReply->RoundTripTime << "ms TTL=" 
                      << (int)pEchoReply->Options.Ttl << std::endl;
        } else {
            //std::cout << "Request timed out for " << ip << std::endl;
        }
    }

    IcmpCloseHandle(hIcmpFile);
    free(replyBuffer);
}

int ping_sweep_f() {
    std::string subnet = "192.168.1.";
    int start = 1;
    int end = 254;

    std::cout << "Starting ping sweep on subnet " << subnet << std::endl;
    pingSweep(subnet, start, end);

    return 0;
}















void traceroute(const std::string& targetIp, int maxHops = 30) {
    HANDLE hIcmpFile;
    unsigned long ipaddr = INADDR_NONE;
    DWORD dwRetVal = 0;
    char sendData[] = "TracerouteData";
    LPVOID replyBuffer = nullptr;
    DWORD replySize = 0;

    replySize = sizeof(ICMP_ECHO_REPLY) + sizeof(sendData);
    replyBuffer = (VOID*)malloc(replySize);
    if (replyBuffer == nullptr) {
        std::cerr << "Unable to allocate memory" << std::endl;
        return;
    }

    hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Unable to open handle" << std::endl;
        free(replyBuffer);
        return;
    }

    ipaddr = inet_addr(targetIp.c_str());
    if (ipaddr == INADDR_NONE) {
        std::cerr << "Invalid IP address: " << targetIp << std::endl;
        IcmpCloseHandle(hIcmpFile);
        free(replyBuffer);
        return;
    }

    for (int ttl = 1; ttl <= maxHops; ++ttl) {
        DWORD dwOptionsLength = sizeof(IP_OPTION_INFORMATION);
        IP_OPTION_INFORMATION options = {0};
        options.Ttl = ttl;

        auto start = std::chrono::high_resolution_clock::now();

        dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, sendData, sizeof(sendData), 
                                &options, replyBuffer, replySize, 1000);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (dwRetVal != 0) {
            PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)replyBuffer;
            struct in_addr replyAddr;
            replyAddr.S_un.S_addr = pEchoReply->Address;

            std::cout << std::setw(2) << ttl << "  " 
                      << inet_ntoa(replyAddr) << "  " 
                      << duration << " ms" << std::endl;

            if (pEchoReply->Status == IP_SUCCESS) {
                std::cout << "Trace complete." << std::endl;
                break;
            }
        } else {
            std::cout << std::setw(2) << ttl << "  *  Request timed out." << std::endl;
        }
    }

    IcmpCloseHandle(hIcmpFile);
    free(replyBuffer);
}

int tracerouting() {
    std::string targetIp = "192.168.1.5";  // Google DNS for example
    int maxHops = 30;

    std::cout << "Traceroute to " << targetIp << " with max hops " << maxHops << std::endl;
    traceroute(targetIp, maxHops);

    return 0;
}

































// Define an alternative for inet_ntop if not available (e.g., older Windows SDKs)
const char* inet_ntop(int af, const void* src, char* dst, socklen_t size) {
    if (af == AF_INET) {
        struct sockaddr_in in;
        memset(&in, 0, sizeof(in));
        in.sin_family = AF_INET;
        memcpy(&in.sin_addr, src, sizeof(struct in_addr));
        strcpy(dst, inet_ntoa(in.sin_addr));
        return dst;
    }
    return NULL;
}

// Function to check if Windows Firewall is enabled
bool isFirewallEnabled() {
    HKEY hKey;
    DWORD dwValue;
    DWORD dwSize = sizeof(DWORD);
    LONG lStatus;

    // Open the Windows Firewall key
    lStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                           "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile",
                           0,
                           KEY_READ,
                           &hKey);

    if (lStatus == ERROR_SUCCESS) {
        // Query the value of EnableFirewall
        lStatus = RegQueryValueEx(hKey,
                                  "EnableFirewall",
                                  NULL,
                                  NULL,
                                  (LPBYTE)&dwValue,
                                  &dwSize);

        RegCloseKey(hKey);

        if (lStatus == ERROR_SUCCESS && dwValue == 1) {
            return true; // Firewall enabled
        }
    }

    return false; // Firewall disabled or error
}

// Function to display IP configuration information
void displayIPConfiguration() {
    ULONG ulSize = 0;
    DWORD dwRetVal = 0;

    // Allocate memory for IP_ADAPTER_INFO structure
    IP_ADAPTER_INFO* pAdapterInfo = NULL;
    ULONG outBufLen = sizeof(IP_ADAPTER_INFO);

    // Make initial call to GetAdaptersInfo to get the necessary size
    dwRetVal = GetAdaptersInfo(pAdapterInfo, &outBufLen);
    if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(outBufLen);
        if (pAdapterInfo == NULL) {
            std::cerr << "Memory allocation failed for IP_ADAPTER_INFO" << std::endl;
            return;
        }
    }

    // Call GetAdaptersInfo again to get actual data
    dwRetVal = GetAdaptersInfo(pAdapterInfo, &outBufLen);
    if (dwRetVal != ERROR_SUCCESS) {
        std::cerr << "GetAdaptersInfo failed with error: " << dwRetVal << std::endl;
        if (pAdapterInfo) {
            free(pAdapterInfo);
        }
        return;
    }

    // Iterate through the list of adapters
    for (IP_ADAPTER_INFO* pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next) {
        // Print adapter name and description
        std::cout << "Adapter Name: " << pAdapter->AdapterName << std::endl;
        std::cout << "Adapter Description: " << pAdapter->Description << std::endl;

        // Print IP addresses
        std::cout << "IP Address(es): ";
        IP_ADDR_STRING* pIpAddress = &(pAdapter->IpAddressList);
        while (pIpAddress) {
            std::cout << pIpAddress->IpAddress.String << " ";
            pIpAddress = pIpAddress->Next;
        }
        std::cout << std::endl;
    }

    // Free memory allocated by GetAdaptersInfo
    if (pAdapterInfo) {
        free(pAdapterInfo);
    }
}

// Function to display active TCP connections
void displayActiveConnections() {
    PMIB_TCPTABLE_OWNER_PID pTcpTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    // Make initial call to GetTcpTable to get the necessary size into dwSize
    dwRetVal = GetExtendedTcpTable(NULL, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
    if (dwRetVal != ERROR_INSUFFICIENT_BUFFER) {
        std::cerr << "GetExtendedTcpTable failed with error: " << dwRetVal << std::endl;
        return;
    }

    // Allocate memory for the TCP table structure
    pTcpTable = (PMIB_TCPTABLE_OWNER_PID)malloc(dwSize);
    if (pTcpTable == NULL) {
        std::cerr << "Memory allocation failed for MIB_TCPTABLE_OWNER_PID" << std::endl;
        return;
    }

    // Make second call to GetExtendedTcpTable to get actual data
    dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
    if (dwRetVal != NO_ERROR) {
        std::cerr << "GetExtendedTcpTable failed with error: " << dwRetVal << std::endl;
        free(pTcpTable);
        return;
    }

    // Print active TCP connections
    std::cout << "Active TCP Connections:" << std::endl;
    std::cout << std::setw(5) << "PID" << std::setw(25) << "Local Address" << std::setw(25) << "Remote Address" << std::setw(10) << "State" << std::endl;
    for (DWORD i = 0; i < pTcpTable->dwNumEntries; i++) {
        DWORD dwLocalAddr = pTcpTable->table[i].dwLocalAddr;
        DWORD dwLocalPort = ntohs((u_short)pTcpTable->table[i].dwLocalPort);
        DWORD dwRemoteAddr = pTcpTable->table[i].dwRemoteAddr;
        DWORD dwRemotePort = ntohs((u_short)pTcpTable->table[i].dwRemotePort);
        DWORD dwState = pTcpTable->table[i].dwState;
        DWORD dwOwningPid = pTcpTable->table[i].dwOwningPid;

        // Convert addresses and ports to readable format
        char szLocalAddr[INET_ADDRSTRLEN];
        char szRemoteAddr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &dwLocalAddr, szLocalAddr, sizeof(szLocalAddr));
        inet_ntop(AF_INET, &dwRemoteAddr, szRemoteAddr, sizeof(szRemoteAddr));

        // Print connection details
        std::cout << std::setw(5) << dwOwningPid << std::setw(25) << szLocalAddr << ":" << dwLocalPort
                  << std::setw(25) << szRemoteAddr << ":" << dwRemotePort
                  << std::setw(10) << dwState << std::endl;
    }

    // Free memory allocated for TCP table
    if (pTcpTable) {
        free(pTcpTable);
    }
}

int arpa() {
    // Check and display firewall status
    if (isFirewallEnabled()) {
        std::cout << "Windows Firewall is enabled." << std::endl;
    } else {
        std::cout << "Windows Firewall is disabled." << std::endl;
    }

    // Display IP configuration information
    std::cout << std::endl << "IP Configuration:" << std::endl;
    displayIPConfiguration();

    // Display active TCP connections
    std::cout << std::endl << "Active Connections:" << std::endl;
    displayActiveConnections();

getchar();
while(getchar()!='\n'){
}
    return 0;
}









































// Function to scan a specific port on an IP address
void scanPort(const char* ipAddress, int port) {
    WSADATA wsaData;
    SOCKET sock;
    sockaddr_in server;
    int connResult;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed. Error Code : " << WSAGetLastError() << std::endl;
        return;
    }

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Could not create socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress);
    server.sin_port = htons(port);

    connResult = connect(sock, (struct sockaddr*)&server, sizeof(server));
    if (connResult == SOCKET_ERROR) {
        // Port closed or unreachable
        // std::cerr << "Port " << port << " closed on " << ipAddress << std::endl;
    } else {
        // Port open
        std::cout << "Port " << port << " open on " << ipAddress << std::endl;
        // Perform vulnerability checks or further actions here (placeholder)
        // Example: Perform basic vulnerability check (for demonstration)
        if (port == 80) {
            std::cout << "Possible vulnerability: HTTP service exposed" << std::endl;
        }
        if (port == 22) {
            std::cout << "Possible vulnerability: SSH service exposed" << std::endl;
        }
    }

    closesocket(sock);
    WSACleanup();
}

// Function to scan a range of IP addresses for a specific port
void scanIPRange(const std::string& baseIp, int start, int end, int port) {
    std::vector<std::thread> threads;
    std::mutex mtx;

    for (int i = start; i <= end; ++i) {
        std::string ip = baseIp + std::to_string(i);
        threads.emplace_back([&mtx, ip, port]() {
            scanPort(ip.c_str(), port);

            std::lock_guard<std::mutex> lock(mtx);
        });
    }

    for (auto& t : threads) {
        t.join();
    }
}

int vuln() {
    const std::string baseIp = "192.168.1.";
    const int start = 1;
    const int end = 10;  // Example range (adjust as needed)
    const int port = 80; // Example port to scan (HTTP)

    scanIPRange(baseIp, start, end, port);

getchar();
while(getchar()!='\n'){
}
    return 0;
}















































std::mutex print_mutex;

// Function to get MAC address from IP using ARP
std::string getMacFromIP(const std::string& ipAddress) {
    ULONG macAddr[2];
    ULONG macAddrLen = 6;
    IPAddr destIP;
    char macAddress[18];

    destIP = inet_addr(ipAddress.c_str());
    if (SendARP(destIP, 0, macAddr, &macAddrLen) == NO_ERROR) {
        snprintf(macAddress, sizeof(macAddress), "%02X:%02X:%02X:%02X:%02X:%02X",
            macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
        return std::string(macAddress);
    }

    return "Unknown";
}

// Function to perform a ping sweep to discover live hosts
std::vector<std::string> discoverHosts(const std::string& baseIp, int start, int end) {
    std::vector<std::string> hosts;

    for (int i = start; i <= end; ++i) {
        std::string ip = baseIp + std::to_string(i);

        HANDLE hIcmpFile;
        DWORD dwRetVal = 0;
        char SendData[32] = "Data Buffer";
        LPVOID ReplyBuffer = NULL;
        DWORD ReplySize = 0;

        hIcmpFile = IcmpCreateFile();
        ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
        ReplyBuffer = (VOID*)malloc(ReplySize);
        dwRetVal = IcmpSendEcho(hIcmpFile, inet_addr(ip.c_str()), SendData, sizeof(SendData),
            NULL, ReplyBuffer, ReplySize, 1000);

        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
        struct in_addr ReplyAddr;
        ReplyAddr.S_un.S_addr = pEchoReply->Address;

        if (dwRetVal != 0) {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "Host " << ip << " is alive." << std::endl;
            hosts.push_back(ip);
        }

        free(ReplyBuffer);
        CloseHandle(hIcmpFile);
    }

    return hosts;
}

// Function to perform port scanning on a specific IP address
void scanPorts(const std::string& ipAddress) {
    for (int port = 1; port <= 80; ++port) {
        SOCKET sock;
        sockaddr_in addr;
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
            return;
        }

        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET) {
            std::cerr << "Socket creation failed" << std::endl;
            WSACleanup();
            return;
        }

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        addr.sin_port = htons(port);

        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR) {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "Port " << port << " open on " << ipAddress << std::endl;
        }

        closesocket(sock);
        WSACleanup();
    }
}

// Function to retrieve hostname from IP address
std::string getHostName(const std::string& ipAddress) {
    struct sockaddr_in sa;
    char hostname[NI_MAXHOST] = "";

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    if (getnameinfo((struct sockaddr*)&sa, sizeof sa, hostname, NI_MAXHOST, NULL, 0, 0) == 0) {
        return std::string(hostname);
    } else {
        return "Unknown";
    }
}

// Function to retrieve device name (if available)
std::string getDeviceName(const std::string& ipAddress) {
    // Implement logic to get device name based on IP address (e.g., from DHCP logs, network inventory)
    return "Unknown";
}

// Function to perform basic OS detection based on open ports (for demonstration purposes)
std::string detectOS(const std::string& ipAddress) {
    // Implement logic to detect OS based on open ports (e.g., common ports associated with specific OS)
    return "Unknown";
}

// Function to print detailed information about each host
void printHostDetails(const std::string& ipAddress) {
    std::string macAddress = getMacFromIP(ipAddress);
    std::string hostName = getHostName(ipAddress);
    std::string deviceName = getDeviceName(ipAddress);
    std::string os = detectOS(ipAddress);

    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << "IP Address: " << ipAddress << std::endl;
    std::cout << "MAC Address: " << macAddress << std::endl;
    std::cout << "Hostname: " << hostName << std::endl;
    std::cout << "Device Name: " << deviceName << std::endl;
    std::cout << "OS: " << os << std::endl;
    std::cout << std::endl;
}

// Function to perform full network scan
int fullp() {
    const std::string baseIp = "192.168.1.";
    const int start = 1;
    const int end = 10;  // Example range (adjust as needed)

    // Discover live hosts in the network range
    std::vector<std::string> liveHosts = discoverHosts(baseIp, start, end);

    // Perform detailed scanning and print information for each host
    for (const auto& ip : liveHosts) {
        printHostDetails(ip);
        scanPorts(ip); // Perform port scanning
    }

    return 0;
}


