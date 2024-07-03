#ifndef UTILS_H
#define UTILS_H

//namespace for string data type usage
using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>



//function definitions about socket programming side of the project
int Server_Listen(int PortNumber, int Timeout, const char* IPAddress);



int Server_Custom_Connection(const char* IPAddress, int PortNumber, int timeout, string protocol, char encryption, string encryption_type, char compression, int BufferSize );
 
bool isValidIpAddress(const string& ip);

void handle_receive(SOCKET clientSocket);

void handle_send(SOCKET clientSocket);


//multiple ones
struct ClientInfo {//make it class
    SOCKET socket;
    string ip;
    int port;
};


string getHostName();
string getPcName();
void handle_client(SOCKET clientSocket, int clientIndex, vector<ClientInfo>& channels);
void listen_for_clients(vector<ClientInfo>& channels);
void display_menu(const vector<ClientInfo>& channels);
void client_communication(SOCKET clientSocket);
COORD getCursorPosition();
void gotoxy(int x, int y);
void clearLastInputLine();
int MultipleConnHandlF();

#endif
