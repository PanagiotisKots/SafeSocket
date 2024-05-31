//system libs
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <stdio.h>
#include <thread>
#include <vector>
#include <string>

//custom libs
#include "Animations.h"

//defines
#define MAX_CLIENTS 1000
#define DEFAULT_BUFLEN 4096
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_SEA_BLUE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


//pragmas (direktives)
#pragma comment(lib, "ws2_32.lib") // Winsock library
#pragma warning(disable:4996)      // Disable compiler warning C4996 message for the code bellow


//namespaces
using namespace std;





//ip structure check if correct or not
bool IsValidIPAddress(const string& ipAddress) {
	
	//add it to all of the functions 
    struct sockaddr_in sa;
    return inet_addr(ipAddress.c_str()) != INADDR_NONE;
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
            cout << "Client: " ;Set_Console_Color(DEFAULT_COLOR, 0);cout<< recvbuf << endl;
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



//function that handles packet sending to client
void handle_send(SOCKET clientSocket) {
    string sendbuf;
    //infinite loop
    while (true) {
        // Send data to client
        	Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Server: ";
        	Set_Console_Color(DEFAULT_COLOR, 0);
        getline(cin, sendbuf);
        int bytesSent = send(clientSocket, sendbuf.c_str(), (int)sendbuf.length(), 0);
        if (bytesSent == SOCKET_ERROR) {
            cout << "send() failed: " << WSAGetLastError() << endl;
            break;
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









/*
//needs calibrations not ready yet
SOCKET server_socket;
vector<string> history;

int MultipleClients(int portNumber, int maxClients, int waitTime) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "Failed to initialize Winsock. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cerr << "Could not create socket: " << WSAGetLastError() << endl;
        return 2;
    }

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portNumber);

    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cerr << "Bind failed with error code: " << WSAGetLastError() << endl;
        return 3;
    }

    listen(server_socket, maxClients);

    cout << "Server is waiting for incoming connections..." << endl;
    cout << "Please start one or more client-side apps." << endl;

    fd_set readfds;
    SOCKET client_socket[MAX_CLIENTS] = {};

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);

        for (int socketIndex = 0; socketIndex < maxClients; socketIndex++) {
            SOCKET s = client_socket[socketIndex];
            if (s > 0) {
                FD_SET(s, &readfds);
            }
        }

        timeval timeout;
        timeout.tv_sec = waitTime;
        timeout.tv_usec = 0;

        if (select(0, &readfds, NULL, NULL, &timeout) == SOCKET_ERROR) {
            cerr << "Select function call failed with error code: " << WSAGetLastError() << endl;
            return 4;
        }

        SOCKET new_socket;
        sockaddr_in address;
        int addrlen = sizeof(sockaddr_in);
        if (FD_ISSET(server_socket, &readfds)) {
            if ((new_socket = accept(server_socket, (sockaddr*)&address, &addrlen)) < 0) {
                perror("Accept function error");
                return 5;
            }

            for (const auto& msg : history) {
                cout << msg << endl;
                send(new_socket, msg.c_str(), msg.size(), 0);
            }

            printf("New connection, socket fd is %d, ip is: %s, port: %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            for (int i = 0; i < maxClients; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets at index %d\n", i);
                    break;
                }
            }
        }

        for (int socketIndex = 0; socketIndex < maxClients; socketIndex++) {
            SOCKET s = client_socket[socketIndex];
            if (FD_ISSET(s, &readfds)) {
                getpeername(s, (sockaddr*)&address, (int*)&addrlen);

                char client_message[DEFAULT_BUFLEN];
                int client_message_length = recv(s, client_message, DEFAULT_BUFLEN, 0);
                client_message[client_message_length] = '\0';

                string check_exit = client_message;
                if (check_exit == "off") {
                    cout << "Client #" << socketIndex << " is off" << endl;
                    client_socket[socketIndex] = 0;
                }

                string temp = client_message;
                history.push_back(temp);

                for (int i = 0; i < maxClients; i++) {
                    if (client_socket[i] != 0) {
                        send(client_socket[i], client_message, client_message_length, 0);
                    }
                }
            }
        }
    }

    WSACleanup();
    return 0;
}

*/










//add error handling to all of them for commong networking errors like ipo,port etc that might happen 

/*
//not ready yet , needs calibrartions!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int Server_Custom_Connection(int PortNumber,int Timeout, int max_clients, int buffer_size, string IPAddress, string connection_type, string encryption, string compression) {
// Initialize Winsock
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        cout << "WSAStartup failed: " << wsaerr << endl;
        return wsaerr;
    }

    SOCKET serverSocket;
    serverSocket = INVALID_SOCKET;
    if (connection_type == "TCP") {
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    } else if (connection_type == "UDP") {
        serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    } else {
        cout << "Invalid connection type!" << endl;
        WSACleanup();
        return -1;
    }

    if (serverSocket == INVALID_SOCKET) {
        cout << "Error creating socket: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(IPAddress.c_str());
    service.sin_port = htons(PortNumber);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    if (connection_type == "TCP") {
        if (listen(serverSocket, max_clients) == SOCKET_ERROR) {
            cout << "listen() failed: " << WSAGetLastError() << endl;
            closesocket(serverSocket);
            WSACleanup();
            return -1;
        }
    }

    cout << "Server is waiting for connections..." << endl;

    timeval timeout;
    timeout.tv_sec = Timeout;
    timeout.tv_usec = 0;

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(serverSocket, &readSet);

    int result = select(0, &readSet, NULL, NULL, &timeout);
    if (result == SOCKET_ERROR) {
        cout << "select() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    } else if (result == 0) {
        cout << "Timeout reached. No incoming connections." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    if (connection_type == "TCP") {
        SOCKET acceptSocket = accept(serverSocket, NULL, NULL);
        if (acceptSocket == INVALID_SOCKET) {
            cout << "accept() failed: " << WSAGetLastError() << endl;
            closesocket(serverSocket);
            WSACleanup();
            return -1;
        }
        cout << "accept() is OK!" << endl;

        thread recvThread(handle_receive, acceptSocket);
        thread sendThread(handle_send, acceptSocket);

        recvThread.join();
        sendThread.join();

        closesocket(acceptSocket);
    } else if (connection_type == "UDP") {
        cout << "UDP server is ready to receive data." << endl;

        // Handle UDP-specific logic here...
    }

    closesocket(serverSocket);
    WSACleanup();


    return 0;
}
*/






