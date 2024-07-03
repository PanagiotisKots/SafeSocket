//system libraries
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>


#include "Animations.h"
//namespaces
using namespace std;



//function that contains the help message
string UserHelp(){
	
	system("cls");   //clears screen
	
	//message for user helpi
	string help = "*********************************************************************************\n"
                  "[+]  SafeSocket++ - Version 0.2\n"
                  "*********************************************************************************\n\n\n"
                  "[+] Overview\n\n"
                  "SafeSocket++ is a sophisticated Windows application designed to facilitate secure and efficient socket-based communication between servers and clients. \n"
				  "Whether you're managing network infrastructures, developing networked applications, or ensuring secure data transmission, SafeSocket++ provides the \n"
				  "tools and features necessary to streamline operations and enhance security.\n\n"
                  "From establishing reliable connections to implementing advanced encryption methods, SafeSocket++ empowers users with intuitive controls and robust \n"
				  "capabilities to manage network interactions effectively. This version represents a significant upgrade in both functionality and security, \n"
				  "making it an indispensable tool for professionals and enthusiasts alike.\n\n"
                  "[+] New Features\n\n" 
                  "Version 0.2 introduces several groundbreaking features:\n"
                  "* Cipher Encryption inside the communication channel: Safeguards sensitive data by encrypting communication channels, \n"
				  "ensuring confidentiality and integrity throughout transmissions.\n"
                  "* Settings option in the main menu for better user control of the program: Allows customization of various \n"
				  "aspects of SafeSocket++, enhancing flexibility and user experience.\n"
                  "* Enhanced safety and error handling, including crash safety: Implements robust protocols to handle errors gracefully \n"
				  "and prevent crashes, ensuring uninterrupted operation under varying conditions.\n"
                  "* Ability to handle multiple connections from clients: Supports simultaneous connections from multiple clients, \n"
				  "optimizing resource management and scalability in network environments.\n\n"
                  "[+] How It Can Help\n\n"
                  "SafeSocket++ - Version 0.2 offers significant benefits:\n"
                  "- **Enhanced Security**: By integrating cipher encryption, SafeSocket++ protects sensitive data from unauthorized access, \n"
				  "ensuring secure communications over networks.\n"
                  "- **Improved Efficiency**: The ability to manage multiple client connections and customizable settings streamlines network operations, \n"
				  "boosting efficiency in managing network resources.\n"
                  "- **Reliability and Stability**: With enhanced error handling and crash safety features, SafeSocket++ maintains stability even \n"
				  "under challenging network conditions, minimizing downtime and ensuring continuous operation.\n"
                  "- **Learning and Development**: Ideal for both beginners and advanced users, SafeSocket++ serves as a learning tool \n"
				  "for understanding network programming concepts and implementing robust solutions in C++.\n\n"
                  "Whether you're securing critical data transmissions, optimizing network perform ance, or expanding your knowledge of network programming, \n"
				  "SafeSocket++ - Version 0.2 equips you with the tools and capabilities to achieve your goals effectively and securely.\n\n\n\n"
                  "[+] How To use:\n\n"
                  "From the main menu Choose option 1 to connect your machine(server) , to another one (client) and open a chat room untill someone exits.\n"
                  "You will be redirected to a page where the programm will ask to fil in some details for the connection to take as parameters.\n"
                  "At first, you have to enter your machines IP ADDRESS (ipconfig in cmd) ex. 192.168.1.8 , then you will have to enter the port number for the connection,\n"
                  "ex. 4040 (!)Dont go very low in port numbers, then if you want to have encryption in the channel while communicating where you enter Y for Yes and N for NO,\n"
                  "and finally a timeout to wait for clients to conect. When a client connects, you will automatically get redirected to the live session of the chat betwen the 2 machines\n"
                  "and you can freelly start sending and recieving messages.\n\n"
                  "In the same way, you can choose the multiple connection which has some extra features but with the ssme logic as the single one. (!)You will have to be able to know how to handle\n"
                  "multiple clients at the same time though.\n\n\n"
                  "[+] Stay Tuned\n\n\n"
                  "In SafeSocket's++ Github repo the code will keep getting better and better and new versions with more functionalities and options are gonna be posted soon. \nHope you enjoy!!!\n\nAnd if you are a fellow programmer: Happy Coding;";
	
	return help;   //returns the message in string format
	
}

//function that handles the string returned from the above function
void UserHelpMod(){
	
	string o = UserHelp();  //save the returned string in o variabvle
	 SetConsoleFont(20);
	//loop that printd each letter of the string with some duration between each loop iteration
	for(int i=0; i<o.length(); i++){
		Sleep(5);
		cout<<o[i];
	}
	
	//wait for user to press enter
	cout<<"\n\nPress Enter to return to homepage: ";
	getchar();
	while(getchar()!='\n'){
		
	}
		SetConsoleFont(28); 
	
}

