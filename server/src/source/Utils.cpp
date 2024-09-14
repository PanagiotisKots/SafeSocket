//system libs
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <mutex>
#include <sstream>
#include <chrono>  // For chrono functions
#include <algorithm>
#include <ctime>



//c libs
#include <stdio.h>
#include <stdlib.h> // For getenv function
#include <windows.h>
#include <iphlpapi.h>


//pragmas (direktives)
#pragma comment(lib, "ws2_32.lib") // Winsock library
// Disable compiler warning C4996 message for the code bellow
#pragma warning(disable:4996)      

//defines
#define MAX_CLIENTS 1000
#define DEFAULT_BUFLEN 4096
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_SEA_BLUE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


//namespaces
using namespace std;



//custom libs
#include "Animations.h"
#include "Encryption.h"
#include "Utils.h"



//ADD IT IN ALL THE CON FUNCTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!
bool isValidIpAddress(const std::string& ip) {
    std::istringstream iss(ip);
    std::string segment;
    int num;
    char delim;

    for (int i = 0; i < 4; ++i) {
        if (!(iss >> num)) {
            return false;
        }
        if (i < 3) {
            if (!(iss >> delim) || delim != '.') {
                return false;
            }
        }
        if (num < 0 || num > 255) {
            return false;
        }
    }

    return true;
}







//function that handles the recieved packets from client
void handle_receive(SOCKET clientSocket) {
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int bytesRecv;

     //infinite loop
    while (true) {
        // Receive data from client
        bytesRecv = recv(clientSocket, recvbuf, recvbuflen, 0);
        
        //checking
        if (bytesRecv > 0) {
            recvbuf[bytesRecv] = '\0'; // Null-terminate the received message
            Set_Console_Color(FOREGROUND_YELLOW, 0);
            //dislayal in servers screen
            string decrypted_message =  decrypt( recvbuf, 2);
            cout << "Client: " ;Set_Console_Color(DEFAULT_COLOR, 0);cout<< decrypted_message << endl;
        } else if (bytesRecv == 0) {
        	//if no message sent
        	Set_Console_Color(FOREGROUND_RED, 0);
            cout << "Connection closing..." << endl;
            break;
        } else {
        	//some error occured
        		Set_Console_Color(FOREGROUND_RED, 0);
            cout << "recv() failed: " << WSAGetLastError() << endl;
            break;
        }
    }
}


#define BUFFER_SIZE 2048
#include <fstream>

void handle_send(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE];
    std::string sendbuf;

    while (true) {
        // Prompt user input
        Set_Console_Color(FOREGROUND_RED, 0);
        std::cout << "Server: ";
        Set_Console_Color(DEFAULT_COLOR, 0);
        std::getline(std::cin, sendbuf);

        // Encrypt the message before sending
        std::string encrypted_message = Caesar_Encrypt(sendbuf, 2);

        // Send encrypted message to client
        int bytesSent = send(clientSocket, encrypted_message.c_str(), static_cast<int>(encrypted_message.length()), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cout << "send() failed: " << WSAGetLastError() << std::endl;
            break;
        }

        // Check if the command is to send a file
        if (sendbuf == "SendFile") {
            // Open the file to send
            std::ifstream file("test.jpg", std::ios::binary);
            
            if (!file.is_open()) {
                error("Failed to open file");
                continue; // Continue to prompt for input
            }

            // Read from file and send to client
            while (file.read(buffer, sizeof(buffer)).gcount() > 0) {
                int bytesRead = file.gcount();
                bytesSent = send(clientSocket, buffer, bytesRead, 0);
                if (bytesSent == SOCKET_ERROR) {
                    error("Send failed");
                    break; // Exit loop on send error
                }
            }

            std::cout << "File transfer complete" << std::endl;

            // Clean up
            file.close();
        }
    }
}









//function for 1st choice connection and communication
int Server_Listen(int PortNumber, int Timeout, const char* IPAddress) {
 //  Initialize WSA variables
    WSADATA wsaData; //windows socket api
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    if (wsaerr != 0) {
    		Set_Console_Color(FOREGROUND_RED, 0);
        cout << "The Winsock dll not found!" << endl;//some error occured          
        return 0;
    } else {
    	//success message display
        cout << "The Winsock dll";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<" found" << endl;
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "The status:     ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout << wsaData.szSystemStatus << endl;
    }

    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
    	//error creating socket
    	Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Error at socket():" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    } else {
    	//succesfulls socket creation
    	Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "socket is       ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"OK" << endl;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(IPAddress);
    service.sin_port = htons(PortNumber);
    
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
    	Set_Console_Color(FOREGROUND_RED, 0);
    	//error occured
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    } else {
    	//succesfull
    	Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "bind() is       ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"OK!" << endl;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
    	Set_Console_Color(FOREGROUND_RED, 0);
    	//erroro ccured
        cout << "listen(): Error listening on socket: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    } else {
    	//success
    	Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "listen() is     ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"OK!\n\nListening for incoming connections...";
        
    }

    timeval timeout;
    timeout.tv_sec = Timeout;
    timeout.tv_usec = 0;

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(serverSocket, &readSet);

    int result = select(0, &readSet, NULL, NULL, &timeout);
    if (result == SOCKET_ERROR) {
    	Set_Console_Color(FOREGROUND_RED, 0);
    	//error ocured
        cout << "select() failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    } else if (result == 0) {
    	Set_Console_Color(FOREGROUND_RED, 0);
    	//timeout happened ()timer reachee limit
        cout << "Timeout reached. No incoming connections." << endl;
        WSACleanup();
        return 0;
    }

    SOCKET acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET) {
    	Set_Console_Color(FOREGROUND_RED, 0);
    	//error happened
        cout << "accept failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    } else {
    	Set_Console_Color(FOREGROUND_YELLOW, 0);
    	//everything went well
        cout << "accept() is     ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"OK!" << endl;
    }

system("cls");//clear screen
Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
cout<<"Server's ";
Set_Console_Color(DEFAULT_COLOR, 0);
cout<<"Chat room ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"open";Set_Console_Color(DEFAULT_COLOR, 0);cout<<" and";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<" running \n\n\n\n\n";//(port, ip of server and client connected etc....)



    // Create threads for sending and receiving
    thread recvThread(handle_receive, acceptSocket);
    thread sendThread(handle_send, acceptSocket);

    // Wait for threads to finish
    recvThread.join();
    sendThread.join();

    // Clean up
    closesocket(acceptSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}





















//multiple ones (CONNECTIONS MULTIPLE CLIENTS!!!!!!!!!!!!!!!!!!!!!!)

void gotoxy(int x, int y);


mutex channels_mutex;
stringstream messageBuffer; // Buffer to store messages
bool stopListener = false;  // Flag to control listener loop


string getHostName() {
    char hostname[256];
    DWORD size = sizeof(hostname);
    if (!GetComputerNameA(hostname, &size)) {
        cout << "Error getting computer name." << endl;
        return "";
    }
    return string(hostname);
}

string getPcName() {
    char username[256];
    DWORD username_size = sizeof(username);
    if (!GetUserNameA(username, &username_size)) {
        printf("Error getting username.\n");
        return "";
    }

    return string(username);
}

// Function to handle client connections
void handle_client(SOCKET clientSocket, int clientIndex, vector<ClientInfo>& channels) {
    sockaddr_in clientAddr;
    int addrSize = sizeof(clientAddr);
    getpeername(clientSocket, (sockaddr*)&clientAddr, &addrSize);
    string clientIp = inet_ntoa(clientAddr.sin_addr);
    int clientPort = ntohs(clientAddr.sin_port);

    // Prepare message for buffer
    stringstream ss;
    Set_Console_Color(FOREGROUND_RED, 0);
    ss << "\n[+] ";Set_Console_Color(FOREGROUND_YELLOW, 0);ss<<"Client  [";Set_Console_Color(FOREGROUND_RED, 0);ss << clientIndex;Set_Console_Color(FOREGROUND_YELLOW, 0);ss << "]  connected on port:  [";Set_Console_Color(FOREGROUND_RED, 0);ss << 12345 + clientIndex;Set_Console_Color(FOREGROUND_YELLOW, 0);ss << "]  with IP:  [";Set_Console_Color(FOREGROUND_RED, 0); ss<< clientIp;Set_Console_Color(FOREGROUND_YELLOW, 0);ss <<"]"<< endl;
 
    // Add client info to channels vector
    {
        lock_guard<mutex> lock(channels_mutex);
        channels.push_back({clientSocket, clientIp, 12345 + clientIndex});
    }

    // Store message in buffer
    {
        lock_guard<mutex> lock(channels_mutex);
        messageBuffer << ss.str();
    }

    // Echo server logic (example)
    char buffer[4096];
    int bytesReceived;
    while (true) {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            // Prepare disconnection message for buffer
            stringstream ss_disconnect;
            ss_disconnect << "[+] Client  [" << clientIndex << "]  disconnected" << endl;

            // Store disconnection message in buffer
            {
                lock_guard<mutex> lock(channels_mutex);
                messageBuffer << ss_disconnect.str();
            }

            break;
        }

        // Append client index to message
        string message = "Client " + to_string(clientIndex) + ": " + string(buffer, bytesReceived);

        // Echo back to the client
        send(clientSocket, message.c_str(), message.size(), 0);
    }

    // Remove client socket from channels vector
    {
        lock_guard<mutex> lock(channels_mutex);
        auto it = std::find_if(channels.begin(), channels.end(), [clientSocket](const ClientInfo& info) {
            return info.socket == clientSocket;
        });
        if (it != channels.end()) {
            channels.erase(it);
        }
    }
    closesocket(clientSocket);
}

// Function to listen on ports for incoming connections
void listen_for_clients(vector<ClientInfo>& channels) {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cout << "WSAStartup failed with error: " << iResult << endl;
        return;
    }

    int port = 12345; // Starting port number for clients

    while (!stopListener) {
        SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET) {
            cout << "socket failed with error: " << WSAGetLastError() << endl;
            continue;
        }

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);

        if (bind(listenSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
            closesocket(listenSocket);
            cout << "bind failed with error: " << WSAGetLastError() << endl;
            continue;
        }

        if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
            cout << "listen failed with error: " << WSAGetLastError() << endl;
            closesocket(listenSocket);
            continue;
        }

        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            cout << "accept failed with error: " << WSAGetLastError() << endl;
            closesocket(listenSocket);
            continue;
        }

        closesocket(listenSocket);

        // Handle client in a separate thread
        thread clientThread(handle_client, clientSocket, port - 12345, ref(channels));
        clientThread.detach(); // Detach thread to allow it to run independently

        ++port; // Move to the next port for the next client
    }

    WSACleanup();
}

void display_menu(const vector<ClientInfo>& channels) {
	int index = 20;
    string o = getHostName();
    string p = getPcName();
    lock_guard<mutex> lock(channels_mutex);
    cout<<"----------------------"<<endl;
    Set_Console_Color(FOREGROUND_RED, 0);
    cout << "[+] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Connected clients:\n";
    cout<<"----------------------"<<endl;
    for (size_t i = 0; i < channels.size(); ++i) {
    	
    	gotoxy(0,index);
        cout << "[+] Client  [";Set_Console_Color(FOREGROUND_RED, 0);cout << i;Set_Console_Color(FOREGROUND_YELLOW, 0);cout << "]  connected from IP  [";Set_Console_Color(FOREGROUND_RED, 0);cout << channels[i].ip;Set_Console_Color(FOREGROUND_YELLOW, 0);cout << "]  and  PORT  [";Set_Console_Color(FOREGROUND_RED, 0);cout << channels[i].port ;Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"]   with  Hostname  [";Set_Console_Color(FOREGROUND_RED, 0);cout<<o;Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"]  and  Name   [";Set_Console_Color(FOREGROUND_RED, 0);cout<<p;Set_Console_Color(FOREGROUND_YELLOW, 0);cout <<"]\n\n"<< endl;
        index++;
	}
}

void client_communication(SOCKET clientSocket) {
    char buffer[4096];
    string message;

    cout << "You are now communicating with the client. Type ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"'exit' ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to return to the main menu.\n";
    while (true) {
        cout << "> ";
        getline(cin, message);

        if (message == "exit") {
            break;
        }

        send(clientSocket, message.c_str(), message.size(), 0);
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            cout << "Client disconnected" << endl;
            break;
        }

        cout << "Received: " << string(buffer, bytesReceived) << endl;
    }
}



// Function to get the current cursor position (x, y)
COORD getCursorPosition() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}

// Function to set cursor position at specified x, y coordinates
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to clear the last input line dynamically
void clearLastInputLine() {

    COORD currentPos = getCursorPosition();

    // Determine the beginning of the last input line (assuming user input starts from row 0)
    int lastInputLineY = currentPos.Y;
    int secondLastInputLineY = lastInputLineY - 1;

    // Clear the second last input line if it exists
    if (secondLastInputLineY >= 0) {
        gotoxy(0, secondLastInputLineY);
        for (int i = 0; i < 80; ++i) { // Assuming a standard console width of 80 columns
            std::cout << ' ';
        }
    }

    // Clear the last input line
    gotoxy(0, lastInputLineY);
    for (int i = 0; i < 80; ++i) { // Assuming a standard console width of 80 columns
        std::cout << ' ';
    }

    // Move cursor back to the beginning of the last input line
    gotoxy(0, lastInputLineY);
}






int MultipleConnHandlF(){
	vector<ClientInfo> channels;
    string choice;

    // Start the listener thread once
    thread listenerThread(listen_for_clients, ref(channels));
    listenerThread.detach();

    // Ensure "listening on port" messages are printed before displaying the menu
    this_thread::sleep_for(chrono::seconds(1));

    while (true) {
        system("cls");
        // Main menu display
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout<<"---------------"<<endl;
        Set_Console_Color(FOREGROUND_RED, 0);
        cout<<"[+] Welcome to: \n";
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout<<"---------------"<<endl;
        cout<<"------------------------------------------"<<endl;
        Set_Console_Color(FOREGROUND_RED, 0);
        cout<<"[+] SafeSocket's Multiple Connection Board \n";
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout<<"------------------------------------------";
        Set_Console_Color(FOREGROUND_RED, 0);
        cout << "\n\n\n[+] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Menu:\n\n";
        
        cout<<"-------------------------------------\n";
        cout << "| 1.";Set_Console_Color(FOREGROUND_RED, 0);cout<<" Listener details               ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout<<"-------------------------------------\n";
        cout << "| 2. ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"Connected clients information  ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout<<"-------------------------------------\n";
        cout << "\n\nEnter your choice (or type ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"'exit' ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"quit";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"): \n\n> ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the input buffer

        if (choice == "exit") {
            stopListener = true;
            break;
        }

        if (choice == "1") {
           string opt;
		    system("cls");
		    cout<<"-----------------------"<<endl;Set_Console_Color(FOREGROUND_RED, 0);
            cout << "[+] Live Listener Room:\n";
            Set_Console_Color(FOREGROUND_YELLOW, 0);
            cout<<"-----------------------"<<endl;
            cout<<"\nPress ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"'-1' ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to refresh OR ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"'exit' ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to exit\n";
            while (true) {
                // Print any new messages from buffer
                {
                    lock_guard<mutex> lock(channels_mutex);
                    if (!messageBuffer.str().empty()) {
                        cout << messageBuffer.str();
                        messageBuffer.str(""); // Clear buffer after printing
                    }
                }
                this_thread::sleep_for(chrono::milliseconds(100)); // Small delay before checking again
            cin>>opt;
            if(opt=="-1"){
            	cout<<"Refreshing";
            	for(int i=0; i<5; i++){
            		cout<<".";
            		Sleep(500);
				}
			}
            clearLastInputLine();
            if(opt=="exit"){
            	cout<<"Exiting";
            	for(int i=0; i<5; i++){
            		cout<<".";
            		Sleep(500);
				}
            	break;
			}
			}
        } if (choice == "2") {
    system("cls");
Set_Console_Color(FOREGROUND_RED, 0);
    cout << "\n\n[+] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"OPTIONS:\n\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "-----------------------------------------------------------\n";
    cout << "| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] <ClientIndex> to start communicating.               ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
    cout << "-----------------------------------------------------------\n";
    cout << "| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] <-1> to refresh.                                    ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
    cout << "-----------------------------------------------------------\n";
    cout << "| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] <exit> to return to main menu.                      ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
    cout << "-----------------------------------------------------------\n";
    cout << "| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] <Info[Client_index]> to view advanced information.  ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
    //add mass messaging to all clients connected option!!!!!!!!!!!!!!!!!!
    cout << "-----------------------------------------------------------\n\n";

    // Display client information initially
    display_menu(channels);

    while (true) {
        cout << "\n\n>";
        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the input buffer

        if (choice == "exit") {
        	cout<<"exiting";
			for(int i=0; i<5; i++){
				cout<<'.';
				Sleep(100);
			}
            break; // Exit the Option 2 menu loop and return to main menu
        }
        
        if (choice == "-1") {
            
            string o = "Refreshing";
            cout<<o;
            for(int i=0; i<5; i++){
            	cout<<".";
            	Sleep(250);
			}
			system("cls");
            // Display the menu options again after clearing the screen
          Set_Console_Color(FOREGROUND_RED, 0);
    cout << "\n\n[+] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"OPTIONS:\n\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "-----------------------------------------------------------\n";
    cout << "| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] <ClientIndex> to start communicating.               ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
    cout << "-----------------------------------------------------------\n";
    cout << "| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] <-1> to refresh.                                    ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
    cout << "-----------------------------------------------------------\n";
    cout << "| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] <exit> to return to main menu.                      ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
    cout << "-----------------------------------------------------------\n";
    cout << "| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] <Info[Client_index]> to view advanced information.  ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
    //add mass messaging to all clients connected
    cout << "-----------------------------------------------------------\n\n";
            display_menu(channels); // Display client information again
            continue; // Continue to prompt for input in the Option 2 menu
        }

     
        
    
// Handle the case where the user selects a specific client to communicate with
       
        //add if here...
        int clientIndex = stoi(choice);
        if (clientIndex < 0 || clientIndex >= channels.size()) {
            cout << "Invalid client index.\n";
            continue;
        }

        system("cls");
        client_communication(channels[clientIndex].socket);
        display_menu(channels); // After communication, display the menu and client information again
    }
}

    }

    return 0;
}
























int Server_Custom_Connection(const char* IPAddress, int PortNumber, int Timeout, string protocol, char encryption, string encryption_type, char compression, int BufferSize) {
    // Initialize WSA variables
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    if (wsaerr != 0) {
        Set_Console_Color(FOREGROUND_RED, 0);
        cout << "The Winsock dll not found!" << endl;        
        return 0;
    } else {
        cout << "The Winsock dll"; Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); cout << " found" << endl;
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "The status:     "; Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); cout << wsaData.szSystemStatus << endl;
    }

    // Determine socket type based on protocol
    int socketType = (protocol == "TCP") ? SOCK_STREAM : SOCK_DGRAM;
    int protocolType = (protocol == "TCP") ? IPPROTO_TCP : IPPROTO_UDP;

    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, socketType, protocolType);
    if (serverSocket == INVALID_SOCKET) {
        Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Error at socket():" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    } else {
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "socket is       "; Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); cout << "OK" << endl;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(IPAddress);
    service.sin_port = htons(PortNumber);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        Set_Console_Color(FOREGROUND_RED, 0);
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    } else {
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "bind() is       "; Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); cout << "OK!" << endl;
    }

    if (protocol == "TCP" && listen(serverSocket, 1) == SOCKET_ERROR) {
        Set_Console_Color(FOREGROUND_RED, 0);
        cout << "listen(): Error listening on socket: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    } else if (protocol == "TCP") {
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "listen() is     "; Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); cout << "OK!\n\nListening for incoming connections...";
    }

    timeval timeout;
    timeout.tv_sec = Timeout;
    timeout.tv_usec = 0;

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(serverSocket, &readSet);

    int result = select(0, &readSet, NULL, NULL, &timeout);
    if (result == SOCKET_ERROR) {
        Set_Console_Color(FOREGROUND_RED, 0);
        cout << "select() failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    } else if (result == 0) {
        Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Timeout reached. No incoming connections." << endl;
        WSACleanup();
        return 0;
    }

    SOCKET acceptSocket;
    if (protocol == "TCP") {
        acceptSocket = accept(serverSocket, NULL, NULL);
        if (acceptSocket == INVALID_SOCKET) {
            Set_Console_Color(FOREGROUND_RED, 0);
            cout << "accept failed: " << WSAGetLastError() << endl;
            closesocket(serverSocket);
            WSACleanup();
            return -1;
        } else {
            Set_Console_Color(FOREGROUND_YELLOW, 0);
            cout << "accept() is     "; Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); cout << "OK!" << endl;
        }
    } else { // UDP does not require accept
        acceptSocket = serverSocket;
    }

    system("cls");
    Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
    cout << "[+] Server's Custom ";
    Set_Console_Color(DEFAULT_COLOR, 0);
    cout << "Chat room "; Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); cout << "Open"; Set_Console_Color(DEFAULT_COLOR, 0); cout << " and"; Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); cout << " Running \n\n\n\n\n";

    // Handle encryption
    if (encryption == 'Y' || encryption == 'y') {
        cout << "Encryption type: " << encryption_type << endl;
        // Placeholder for setting up encryption
    }

    // Handle compression
    if (compression == 'Y' || compression == 'y') {
        cout << "Compression enabled." << endl;
        // Placeholder for setting up compression
    }

    // Set socket buffer size
    setsockopt(acceptSocket, SOL_SOCKET, SO_RCVBUF, (char*)&BufferSize, sizeof(BufferSize));
    setsockopt(acceptSocket, SOL_SOCKET, SO_SNDBUF, (char*)&BufferSize, sizeof(BufferSize));

    if (protocol == "TCP") {
        // Create threads for sending and receiving
        thread recvThread(handle_receive, acceptSocket);
        thread sendThread(handle_send, acceptSocket);

        // Wait for threads to finish
        recvThread.join();
        sendThread.join();
    } else { // UDP
        char* recvBuffer = new char[BufferSize];
        char* sendBuffer = new char[BufferSize];

        sockaddr_in client;
        int clientLen = sizeof(client);

        while (true) {
            // Receive data
            int bytesReceived = recvfrom(acceptSocket, recvBuffer, BufferSize, 0, (sockaddr*)&client, &clientLen);
            if (bytesReceived == SOCKET_ERROR) {
                Set_Console_Color(FOREGROUND_RED, 0);
                cout << "recvfrom() failed: " << WSAGetLastError() << endl;
                break;
            }

            // Placeholder for processing received data
            // Encrypt, decompress if needed

            // Send data back
            int bytesSent = sendto(acceptSocket, sendBuffer, bytesReceived, 0, (sockaddr*)&client, clientLen);
            if (bytesSent == SOCKET_ERROR) {
                Set_Console_Color(FOREGROUND_RED, 0);
                cout << "sendto() failed: " << WSAGetLastError() << endl;
                break;
            }

            // Placeholder for preparing data to send
            // Compress, encrypt if needed
        }

        delete[] recvBuffer;
        delete[] sendBuffer;
    }

    // Clean up
    closesocket(acceptSocket);
    closesocket(serverSocket);
    WSACleanup();
}





























void Full_Scale_Conn(){
	
	cout<<"******************************\n";
	cout<<"Full Scale Connection Option!\n";
    cout<<"******************************\n\n\n";
	
	cout<<"Enter <-Sound> to send voice message to client\n";
	cout<<"Enter <-Scr_Share> to share your screen\n";
	cout<<"Text messages are allowed any time\n";
	cout<<"Enter <-Stop> <-Sound or -Scr_Share> to stop\n\n\n";
	
	
	
	
	
}












