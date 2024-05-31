#ifndef SOCKETS_H
#define SOCKETS_H

//namespace std for string variable usage
using namespace std;


//function declarations
int Connection_One(const string& ip_ad, int port_num);

void handle_receive(SOCKET clientSocket);

void handle_send(SOCKET clientSocket);

//int custom_made_con_f();


#endif
