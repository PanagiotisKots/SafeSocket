
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 3030

std::vector<SOCKET> clients;
std::mutex clients_mutex;

void handle_client(SOCKET client_socket) {
    char buffer[1024] = {0};
    int valread;
    while ((valread = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        std::cout << "Received: " << buffer << std::endl;

        // Send message to all clients except the sender
        clients_mutex.lock();
        for (SOCKET client : clients) {
            if (client != client_socket) {
                send(client, buffer, strlen(buffer), 0);
            }
        }
        clients_mutex.unlock();
        memset(buffer, 0, sizeof(buffer));
    }

    closesocket(client_socket);

    // Remove client from clients vector
    clients_mutex.lock();
    clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
    clients_mutex.unlock();
}

int maiss() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind to the port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen for connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "New connection" << std::endl;

        clients_mutex.lock();
        clients.push_back(new_socket);
        clients_mutex.unlock();

        std::thread(handle_client, new_socket).detach();
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}


