#ifndef UTILS_H
#define UTILS_H

//namespace for string data type usage
using namespace std;

//function definitions about socket programming side of the project
int Server_Listen(int PortNumber, int Timeout, const char* IPAddress);

int MultipleClients(int portNumber, int maxClients, int waitTime);

int Server_Custom_Connection(int PortNumber,int Timeout, int max_clients, int buffer_size, string IPAddress, string connection_type, string encryption, string compression);

bool IsValidIPAddress(const string& ipAddress);

void handle_receive(SOCKET clientSocket);

void handle_send(SOCKET clientSocket);

#endif
