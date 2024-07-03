#ifndef SOCKETS_H
#define SOCKETS_H

//namespace std for string variable usage
using namespace std;


//function declarations
int Connection_One(const string& ip_ad, int port_num);

void handle_receive(SOCKET clientSocket);

void handle_send(SOCKET clientSocket);

//multiple connn


int MultipleServersConF();

void clientThread(const std::string& server_ip, const std::string& server_port, int server_index);



//custom made connnn



void scanPorts(const std::string& ipAddress);

int ScanConnF();
#endif
