//system libraries
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <stdio.h>
#include <thread>
#include <string>
#include <vector>
#include <atomic>
#include <mutex>

#include <fstream>


//custom libraries
#include "Animations.h"
#include "Encryption.h"

//pragmas directives
#pragma comment(lib, "ws2_32.lib") // Winsock library
#pragma warning(disable:4996)





#define PORT 4041
#define BUFFER_SIZE 2048


//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_SEA_BLUE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define DEFAULT_BUFLEN 4096

#include <fstream>
#define BUFFER_SIZE 2048
//namespaces
using namespace std;


void error(const char *msg) {
    perror(msg);
    exit(1);
}




void handle_File_recieve(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE];
    std::ofstream file("received_example.jpg", std::ios::binary);
    if (!file.is_open()) {
        error("Failed to open file");
        return;
    }

    int bytesReceived;
    do {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            file.write(buffer, bytesReceived);
        } else if (bytesReceived == 0) {
            std::cout << "Connection closed by peer" << std::endl;
        } else {
            error("Recv failed");
        }
    } while (bytesReceived > 0);

    if (bytesReceived < 0) {
        error("Recv failed");
    } else {
        std::cout << "File transfer complete" << std::endl;
        file.close(); // Ensure file is closed
    }
}

void handle_receive(SOCKET clientSocket) {
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int bytesRecv;

    while (true) {
        bytesRecv = recv(clientSocket, recvbuf, recvbuflen, 0);
        if (bytesRecv > 0) {
            recvbuf[bytesRecv] = '\0'; // Null-terminate the received string
            std::string decrypted_message = decrypt(recvbuf, 2);

            if (decrypted_message == "SendFile") {
                handle_File_recieve(clientSocket);
            } else {
                std::cout << "Server: " << decrypted_message << std::endl;
            }
        } else if (bytesRecv == 0) {
            std::cout << "Connection closed by server" << std::endl;
            break;
        } else {
            std::cout << "recv() failed: " << WSAGetLastError() << std::endl;
            break;
        }
    }
}







//function that handles the sending of messages to the server
void handle_send(SOCKET clientSocket) {
    string sendbuf;
     //infinite loop
    while (true) {
        // Send data to server
        Set_Console_Color(FOREGROUND_ORANGE, 0);
        cout << "Client: ";
        Set_Console_Color(DEFAULT_COLOR, 0);
        //message input
        getline(cin, sendbuf);
        if(sendbuf == "q"){
        	// Clean up and close the socket
          closesocket(clientSocket);
          WSACleanup();
          break;
		}
        string encrypted_message = encrypt(sendbuf, 2);
        int bytesSent = send(clientSocket, encrypted_message.c_str(), (int)encrypted_message.length(), 0);
        if (bytesSent == SOCKET_ERROR) {
        	Set_Console_Color(FOREGROUND_RED, 0);
        	//error occured
            cout << "send() failed: " << WSAGetLastError() << endl;
            break;
        }
    }
}




















//first connection (simple one)
int Connection_One(const string& ip_ad, int port_num) {
    // Initialize WSA
    WSADATA wsaData;
    int wsaerr;
    
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
    		Set_Console_Color(FOREGROUND_RED, 0);
    		//error occured
        cout << "The Winsock dll not found!" << endl;
        return 1;
    } else { Set_Console_Color(FOREGROUND_ORANGE, 0);
        cout << "The Winsock dll";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<" found" << endl;
         Set_Console_Color(FOREGROUND_ORANGE, 0);
        cout << "The status: ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout << wsaData.szSystemStatus << endl;
    }

    // Create a socket
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
    	Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    } else { Set_Console_Color(FOREGROUND_ORANGE, 0);
        cout << "socket() is ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"OK!" << endl;
    }

    // Specify server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip_ad.c_str()); // Convert string to const char*
    serverAddr.sin_port = htons(port_num); 
    // Connect to server
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
    		Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Failed to connect: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    } else {
    	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
        cout << "Connected"; Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<" to server!" << endl;
    }

//wait for user to press enter
cout<<"Press enter to continue to channel: ";
getchar();
while(getchar()!='\n'){
}
    system("cls");//clear screen
    Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
    cout<<"Client's ";
	Set_Console_Color(DEFAULT_COLOR, 0);
    cout<<"Chat room ";	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"open";	Set_Console_Color(DEFAULT_COLOR, 0);cout<<" and";	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<" running\n\n\n\n";
    // Create threads for sending and receiving
    thread recvThread(handle_receive, clientSocket);
    thread sendThread(handle_send, clientSocket);
    

    // Wait for threads to finish
    recvThread.join();
    sendThread.join();
  

    // Clean up and close the socket
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}











void get_file_from_server(){




    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("WSAStartup failed");
    }

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        error("Socket creation failed");
    }

    // Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.8"); // Use the appropriate IP address
    serverAddr.sin_port = htons(PORT);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        error("Connect failed");
    }

    std::cout << "Connected to server" << std::endl;

    // Open the file to write
    std::ofstream file("received_example.jpg", std::ios::binary);
    if (!file.is_open()) {
        error("Failed to open file");
    }

    // Receive data from server and write to file
    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        file.write(buffer, bytesReceived);
    }

    if (bytesReceived == SOCKET_ERROR) {
        error("Recv failed");
    }

    std::cout << "File transfer complete" << std::endl;

    // Clean up
    file.close();
    closesocket(clientSocket);
    WSACleanup();

    
}












void clientThread(const std::string& server_ip, const std::string& server_port, int server_index) {
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return;
    }

    struct addrinfo* result = nullptr;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return;
    }

    // Attempt to connect to the first address returned by getaddrinfo
    SOCKET ConnectSocket = INVALID_SOCKET;
    for (auto ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        // Connect to server
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        std::cerr << "Unable to connect to server!" << std::endl;
        WSACleanup();
        return;
    }

    // Communication loop
    const int recvbuflen = 512;
    char recvbuf[recvbuflen];
    std::string sendbuf;

    while (true) {
        // Receive data from server
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            std::cout << "Received from server[" << server_index << "]: " << std::string(recvbuf, iResult) << std::endl;
        } else if (iResult == 0) {
            std::cout << "Connection closed by server[" << server_index << "]." << std::endl;
            break;
        } else {
            std::cerr << "Recv failed with error: " << WSAGetLastError() << std::endl;
            break;
        }

        // Send data to server
        std::cout << "Enter message to send (or type 'quit' to terminate): ";
        std::getline(std::cin, sendbuf);

        if (sendbuf == "quit") {
            break;
        }

        iResult = send(ConnectSocket, sendbuf.c_str(), (int)sendbuf.length(), 0);
        if (iResult == SOCKET_ERROR) {
            std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    // Shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "Shutdown failed with error: " << WSAGetLastError() << std::endl;
    }

    // Cleanup
    closesocket(ConnectSocket);
    WSACleanup();
}













//bug!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int MultipleServersConF(){
	// Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }

    std::vector<std::pair<std::string, std::string>> servers;
       
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    // Example: Prompt user to enter servers
    std::cout << "Enter ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"IP ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"address and ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"port";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" of servers (enter 'done' to finish):\n";
    std::string server_ip, server_port;
    while (true) {
    	Set_Console_Color(FOREGROUND_YELLOW, 0);
        std::cout << "Server IP: ";
        
        Set_Console_Color(FOREGROUND_RED, 0);
        std::getline(std::cin, server_ip);
        if (server_ip == "done") break;

Set_Console_Color(FOREGROUND_YELLOW, 0);
        std::cout << "Server port: ";
		Set_Console_Color(FOREGROUND_RED, 0);
        std::getline(std::cin, server_port);

        servers.emplace_back(server_ip, server_port);
        
    }

    // Start a client thread for each server
    std::vector<std::thread> threads;
    for (int i = 0; i < servers.size(); ++i) {
        threads.emplace_back(clientThread, servers[i].first, servers[i].second, i);
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Cleanup Winsock
    WSACleanup();
}

























//Random connection ones...........


//ADD MORE INFO ABPOUT CVLIERNTS OPRN P[ORTS TO CONNECT TO...............


const int START_PORT = 1;
const int END_PORT = 65535;
const std::string BASE_IP = "192.168.1."; // Change this base IP to match your subnet

std::mutex coutMutex;
std::atomic<bool> connectionMade(false);

void scanPorts(const std::string& ipAddress) {
   WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService;
    int result;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "WSAStartup failed: " << result << std::endl;
        return;
    }

    for (int port = START_PORT; port <= END_PORT; ++port) {
        // Check if a connection has already been made
        if (connectionMade.load()) {
            break;
        }

        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Scanning IP " << ipAddress << " on port " << port << "..." << std::endl;
        }

        // Create a socket for connecting to the server
        ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (ConnectSocket == INVALID_SOCKET) {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        // Set up the sockaddr structure
        clientService.sin_family = AF_INET;
        clientService.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        clientService.sin_port = htons(port);

        // Attempt to connect to the server
        result = connect(ConnectSocket, (struct sockaddr*)&clientService, sizeof(clientService));
        if (result == SOCKET_ERROR) {
            // Unable to connect, continue scanning
            closesocket(ConnectSocket);
            continue;
        } else {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "IP " << ipAddress << " Port " << port << " is open. Do you want to connect? (y/n): ";
            char response;
            std::cin >> response;
            if (response == 'y' || response == 'Y') {
                std::cout << "Connected to IP " << ipAddress << " Port " << port << std::endl;
                connectionMade.store(true);
                system("cls"); // clear screen
                Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
                std::cout << "Client's ";
                Set_Console_Color(7, 0); // DEFAULT_COLOR
                std::cout << "Chat room ";
                Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
                std::cout << "open";
                Set_Console_Color(7, 0);
                std::cout << " and";
                Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
                std::cout << " running\n\n\n\n";
                Set_Console_Color(7, 0);

                // Create threads for sending and receiving
                std::thread recvThread(handle_receive, ConnectSocket);
                std::thread sendThread(handle_send, ConnectSocket);

                // Wait for threads to finish
                recvThread.join();
                sendThread.join();
            }
            // Close the socket after use
            closesocket(ConnectSocket);
        }
    }

    // Cleanup
    WSACleanup();
}
//BUG!!!!!!!!!!!!!!!!!!!






int ScanConnF(){
	  std::vector<std::thread> threads;

    // Scan IPs in the range of BASE_IP.1 to BASE_IP.255
    for (int i = 1; i <= 255; ++i) {
        std::string ipAddress = BASE_IP + std::to_string(i);
        threads.emplace_back(scanPorts, ipAddress);
    }

    for (auto& thread : threads) {
        thread.join();
    }
    
    
    
    
    
}


















/*
//port forwarded code
#include <iostream>
#include <thread>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 3030

void receive_messages(SOCKET sock) {
    char buffer[1024] = {0};
    int valread;
    while ((valread = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        std::cout << "Received: " << buffer << std::endl;
        memset(buffer, 0, sizeof(buffer));
    }
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation error" << std::endl;
        WSACleanup();
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Replace "FRIEND_PUBLIC_IP" with your friend's actual public IP address
    if (inet_pton(AF_INET, "FRIEND_PUBLIC_IP", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    std::thread(receive_messages, sock).detach();

    std::string message;
    while (true) {
        std::getline(std::cin, message);
        send(sock, message.c_str(), message.size(), 0);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
*/

