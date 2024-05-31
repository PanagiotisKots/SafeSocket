//system libraries
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <stdio.h>
#include <thread>

//custom libraries
#include "Animations.h"


//pragmas directives
#pragma comment(lib, "ws2_32.lib") // Winsock library
#pragma warning(disable:4996)




//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_SEA_BLUE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define DEFAULT_BUFLEN 4096


//namespaces
using namespace std;



//function that handles the recieval of messages from server
void handle_receive(SOCKET clientSocket) {
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int bytesRecv;

    //infinite loop
    while (true) {
        // Receive data from server
        bytesRecv = recv(clientSocket, recvbuf, recvbuflen, 0);
        //message handling
        if (bytesRecv > 0) {
            recvbuf[bytesRecv] = '\0'; // Null-terminate the received string
            Set_Console_Color(FOREGROUND_YELLOW, 0);
            //message print
            cout << "Server: ";Set_Console_Color(DEFAULT_COLOR, 0); cout<< recvbuf << endl;
        } else if (bytesRecv == 0) {
        	Set_Console_Color(FOREGROUND_RED, 0);
        	//error occures(not exactly)
            cout << "Connection closed by server" << endl;
            break;
        } else {
        	Set_Console_Color(FOREGROUND_RED, 0);
        	//error
            cout << "recv() failed: " << WSAGetLastError() << endl;
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
        int bytesSent = send(clientSocket, sendbuf.c_str(), (int)sendbuf.length(), 0);
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





//note ready yet, needs adjustments and bug fixes
/*
int custom_made_con_f(){
	WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        cout << "The Winsock dll not found!" << endl;
        return 1;
    } else {
        cout << "The Winsock dll found" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }

    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    } else {
        cout << "socket() is OK!" << endl;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.6");
    serverAddr.sin_port = htons(3031);

    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Failed to connect: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    } else {
        cout << "Connected to server!" << endl;
    }

    thread recvThread(handle_receive, clientSocket);
    thread sendThread(handle_send, clientSocket);

    recvThread.join();
    sendThread.join();

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

*/
