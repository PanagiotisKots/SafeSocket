//system libraries
#include <iostream>
#include <cstdlib> 
#include <windows.h>

//custom made libs
#include "Utils.h"
#include "Help.h"
#include "Animations.h"
#include "Classes.h"


//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


//namespace standard for code simplicity
using namespace std;                                                   


//function defionitions
void Troubleshooting(string trouble_text);                               
void ContactSupport();







//Function that handles user inputs and parameters for simple connection ( Choice 1 from main menu )
int ChoiceOne(){
	
	system("cls");   //clear screen system function
	
	Socket_Parameters sock;   //create object from Classes.h of class Socket_Parameters to sock
	
	
	//simple connnection parameter setting menu 
	
	Set_Console_Color(FOREGROUND_YELLOW, 0);   //console color change to yellow
	
	string ip_adr = sock.get_ip();   //get ip from user input with classes function
	
	Set_Console_Color(FOREGROUND_YELLOW, 0);   //console color change to yellow
	
	int port = sock.get_PortNumber();     //get port number from pivate class by user input(same way as ip)
	
	Set_Console_Color(FOREGROUND_YELLOW, 0);   //console color change to yellow
	
	bool crypt = sock.get_Encryption();   //get boolean for of encryption from user and return true or false value for future usage

    Set_Console_Color(FOREGROUND_YELLOW, 0);   //console color change to yellow

	int time_out = sock.get_Timeout();   //gets user input price for waiting time to connect ....same way as ip port etc......
	
	
	
	/* Convert string to const char* using c_str() for it to be able 
	to be accepted in the Server_Listen function that can only take const char* as a 
	parameter because of windows socket programming limitations
	*/
    const char* cString = ip_adr.c_str(); //make the conversion of string to const char* and send it as a parameter instead of string bellow
    
    
	/*call the single connection function from utils.cpp, sending as parameters the private elements
	{port number, timeout and ip address which has transormed to cString}*/
	Server_Listen(port, time_out, cString);
	
	return 0;  //return 0 when function reaches end
} 





//multiple client connection    


//NOT YET AVAILABLE, STILL UNDER CONSTRUCTION!!!!!!!!!!!!!!!!
//need to add errror imput and crashes handling
/*int ChoiceTwo(){
	
	system("cls");
	
	//variables 
	int PortNumber,Timeout,Max_Client_Num;
	bool Encryption = false;
	char Encryption_Input;
	
	cout<<"1. Enter the port number to listen for incoming connnections: ";
	cin>>PortNumber;
	
	cout<<"2. Do you want to use the AES encryption for Advanced Security? [Y/N]";
	cin>>Encryption_Input;
	
	//bool handling
	if(Encryption_Input=='Y'){
		Encryption = true;
	
	}else if (Encryption_Input=='N'){
		Encryption = false;
		//add cerrr handling 
	}else{
		
		// Invalid input
        cout << "Invalid input. Defaulting to no encryption.\n";
	}
	
	cout<<"3. Enter maximum number of connected clients: ";
	cin>>Max_Client_Num;
	
	cout<<"4. Define client connection waiting timeout: ";
	cin>>Timeout;
	
	cout<<"\nwaiting for client/s to connect...";//add animation
	
	
	 MultipleClients(PortNumber,Max_Client_Num,Timeout);
	
	
	return 0;

	
}
*/




//NOT YET AVAILABLE, STILL UNDER CONSTRUCTION!!!!!!!!!!!!
/*
int ChoiceThree() {
    system("cls"); 

    // variables
    int PortNumber, Timeout, MaxConnections, BufferSize;
    string Encryption, Compression;
    char Encryption_Input, Compression_Input;
    string IPAddress, Protocol, DataFormat, EncryptionMethod; // New variable for custom IP address, protocol, data format, and encryption method

    // Get user input for custom connection settings
    cout << "\n\nCustom Connection Settings:\n";
    cout << "1. Enter the IP Address to connect to: ";
    cin >> IPAddress;
    cout << endl;

    cout << "2. Enter the Port number to listen for incoming connections: ";
    cin >> PortNumber;
    cout << endl;

    cout << "3. Enter the protocol (TCP/UDP): ";
    cin >> Protocol;
    cout << endl;

    cout << "4. Do you want to use encryption for Advanced Security? [Y/N]";
    cin >> Encryption_Input;
    cout << endl;

    // String handling for encryption
    if (Encryption_Input == 'Y' || Encryption_Input == 'y') {
        Encryption = "Yes";
        cout << "Choose Encryption Method (AES/RSA/SHA-256): ";
        cin >> EncryptionMethod;
        cout << endl;
    } else if (Encryption_Input == 'N' || Encryption_Input == 'n') {
        Encryption = "No";
    } else {
        cout << "Invalid input. Defaulting to no encryption.\n";
        Encryption = "No";
    }

    cout << "5. Do you want to use compression for data transfer? [Y/N]";
    cin >> Compression_Input;
    cout << endl;

    // String handling for compression
    if (Compression_Input == 'Y' || Compression_Input == 'y') {
        Compression = "Yes";
    } else if (Compression_Input == 'N' || Compression_Input == 'n') {
        Compression = "No";
    } else {
        cout << "Invalid input. Defaulting to no compression.\n";
        Compression = "No";
    }

    cout << "6. Enter waiting timeout for client connection (in seconds): ";
    cin >> Timeout;
    cout << endl;

    cout << "7. Enter the maximum number of connections allowed: ";
    cin >> MaxConnections;
    cout << endl;

    cout << "8. Enter the buffer size for data transfer (in bytes): ";
    cin >> BufferSize;
    cout << endl;

    cout << "9. Enter the format of data (JSON/XML/Custom): ";
    cin >> DataFormat;
    cout << endl;

system("cls");
    // Display the custom connection settings
    cout << "\nCustom Connection Settings:\n";
    cout << "IP Address: " << IPAddress << endl;
    cout << "Port Number: " << PortNumber << endl;
    cout << "Protocol: " << Protocol << endl;
    cout << "Encryption: " << Encryption << endl;
    if (Encryption == "Yes") {
        cout << "Encryption Method: " << EncryptionMethod << endl;
    }
    cout << "Compression: " << Compression << endl;
    cout << "Timeout: " << Timeout << " seconds" << endl;
    cout << "Max Connections: " << MaxConnections << endl;
    cout << "Buffer Size: " << BufferSize << " bytes" << endl;
    cout << "Data Format: " << DataFormat << endl;


//do you wish to change smthing ..............

    // Call your custom connection function with string parameters
    Server_Custom_Connection(PortNumber, Timeout, MaxConnections, BufferSize, IPAddress, Protocol, Encryption, Compression);

    return 0; 
}
*/








// Function to display help/instructions ( Choice 4 from main menu )
int ChoiceFour(){
	
	while(true){
	
    system("cls");   //clear screen system function
    
    //Choice 4 Secopndary menu display and user input about choice acceptance
    Set_Console_Color(FOREGROUND_YELLOW, 0);   
    cout << "(!)";Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<" Help/Instruction Menu:\n\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "1. "; Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<"How to use this program.\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "2.";Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<" Troubleshooting bugs/issues.\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "3. "; Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<"Contact us.\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "4.";Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<" Return to main menu.\n\n";
    int choice;
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "Enter your choice: ";
    Set_Console_Color(FOREGROUND_ORANGE, 0);
    cin >> choice;   //acceptyy user input for choice from the menu above to navigate to coresponding choice
    
    
    //If user enters 1 
    if(choice==1){
    	Set_Console_Color(DEFAULT_COLOR, 0);   //reser to default color ( in this modules defines )
    	UserHelpMod();   //call function to display helping message to user
	}
	//id user enters 2 
	else if(choice ==2){
		string bugmessage;//MAKE IT ARRAY OF STRINGS INSTEAD OF A SINGLE ONE TO ALLOW MULTIPLE ENTERS OF USER.....!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		system("cls");   //clear screen 
		Set_Console_Color(FOREGROUND_YELLOW,0);   //set console color to YELLOW
		cout<<"SafeSocket Troubleshooting page:\n\n\nPlease submit the isue/bug you found here to help us solve it:   ";
		Set_Console_Color(FOREGROUND_RED, 0);   //set it to red 
		cin>>bugmessage;   //accept input of user message in form of string
		Troubleshooting(bugmessage);   //call function sending as parameter user input in string form ***(change it to array of strings)***
		/*  add functionalities in this function to either 
		email address or report it in guithub repository 
		where program is uploaded!!!!!!!!!!!!	*/
	}
	//if user enters 3 
	else if(choice==3){
		ContactSupport();   //call contact support function
	}
	//if user enters 4 
	else if(choice==4){
		//return to main menu
		break;
		
		
	}
}
    
    return 0;
}



//function that helps user troubleshoot a bug or issue 
void Troubleshooting(string trouble_text){
	
	
	//add legit email or github posting bug sending - reporting functionality
	Set_Console_Color(FOREGROUND_YELLOW, 0);   //change console color to YELLOW
	cout<<"\n\n\nIssue sent , thank you for informing us....\n\nfeel free to reoport this or any other isues to our Github repository:";Set_Console_Color(FOREGROUND_RED, 0);cout<<" https://github.com/PanagiotisKots/SafeSocket ";
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	cout<<"\n\nPress enter to continue:  ";
	getchar();
	while(getchar()!='\n'){
	}
	Set_Console_Color(DEFAULT_COLOR, 0);   //make it again default color
}



//function that helps user to contact support 
void ContactSupport(){
	
	//add gotoxy box here and to all the menus in next update
	
	system("cls");   //clear console screen
	string choice;
	Set_Console_Color(FOREGROUND_YELLOW, 0);    //initialise copnsole color to YELLOW
	cout<<"Contact Support Options: \n\n";
	Set_Console_Color(FOREGROUND_RED, 0);   //make it red
	
	/*Secondary menu display of creators contact info and 
	more in different colors matching programs theme*/
	cout<<"1.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Email: ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"pkotsorgios654@gmail.com\n";
	
	cout<<"2.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Github: ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"https://github.com/PanagiotisKots/SafeSocket\n";
	
	cout<<"3.";	Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Our Website: (gonna be updated soon!!!)\n\n";
	cout<<"You can also send a message to us directly through SafeScocket.\n";
	cout<<"Enter ";	Set_Console_Color(FOREGROUND_RED, 0);cout<<"'direct'";	Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" to send us message or";	Set_Console_Color(FOREGROUND_RED, 0);cout<<" 'exit'";	Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" to exit Contact Support menu: ";
		Set_Console_Color(FOREGROUND_RED, 0);
	cin>>choice;   //input taken from usrr 
		Set_Console_Color(FOREGROUND_YELLOW, 0); //change color again to YELLOW
		
		//Choiuce handling
	if(choice=="direct"){
		string direct_message;//needs to become array of strings
		cout<<"Enter message here:  ";//add functionality from troubleshootiung to send email or github direct ......
			Set_Console_Color(FOREGROUND_RED, 0);
		cin>>direct_message;
			Set_Console_Color(FOREGROUND_YELLOW, 0);
		//or send it to us via safesocket server in the very future.....
		cout<<"Thank you for the feedback, we will answer as soon as possible: \n\n";
		cout<<"press enter to exit: ";
		//fix spacing error with getline character   (BUG DETECTED!!!!!!!!!!!)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		getchar();//function to get chasracter from user
	
		while(getchar()!='\n'){   //loop untill the takes one is '\n' (ENTER)
		}
		//if user enters exit as menu choice then exit page return to previous one 
	}else if(choice=="exit"){
			Set_Console_Color(FOREGROUND_RED, 0);
		cout<<"Exiting Contact Suppport menu."; 
		Sleep(2000);//add loading dots anmtns
	}
	
	
}















