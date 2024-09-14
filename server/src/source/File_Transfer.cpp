#include <iostream>
#include <fstream>
#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 4041
#define BUFFER_SIZE 2048

using namespace std;


void error(const char *msg) {
    perror(msg);
    exit(1);
}


void Send_file_to_client(){



    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error("WSAStartup failed");
    }

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        error("Socket creation failed");
    }

    // Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        error("Bind failed");
    }

    // Listen to incoming connections
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        error("Listen failed");
    }

    std::cout << "Waiting for incoming connections..." << std::endl;

    // Accept an incoming connection
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
    if (clientSocket == INVALID_SOCKET) {
        error("Accept failed");
    }

    std::cout << "Connection accepted" << std::endl;

    // Open the file to send
    std::ifstream file("test.jpg", std::ios::binary);
    if (!file.is_open()) {
        error("Failed to open file");
    }

    // Read from file and send to client
    int bytesRead;
    do {
        file.read(buffer, sizeof(buffer));
        bytesRead = static_cast<int>(file.gcount());
        if (bytesRead > 0) {
            int bytesSent = send(clientSocket, buffer, bytesRead, 0);
            if (bytesSent == SOCKET_ERROR) {
                error("Send failed");
            }
        }
    } while (bytesRead > 0);

    std::cout << "File transfer complete" << std::endl;

    // Clean up
    file.close();
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

  
}

//ADD MULTIPLE FILE SENDING FUNCTIONALITY KLPKLPKLP.......

