//system libs
#include <iostream>

//custom libs
#include "Classes.h"
#include "Animations.h"




//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


//function functionalities from Classes.h for login and sput
string Sup::get_uname(){
	
	 // Username input
    cout << "Username: ";
    cin >> uname;
	
	return uname;
}


string Sup::get_pass(){
	
	// Password input
    cout << "Password: ";
    cin >> pass;
	
	return pass;
}



Sup::Sup(){
	
	uname = "admin";
	pass = "pass";
}










//adding functionaliti to the network class functiojns
string Connection_Parameters::get_ip(){
Set_Console_Color(	FOREGROUND_YELLOW, 0);
	cout<<"1. Enter Server's IP to connect with: ";
	Set_Console_Color(	FOREGROUND_RED, 0);
	cin>>ip_addr;
	
	return ip_addr;
}



int Connection_Parameters::get_port(){
	Set_Console_Color(	FOREGROUND_YELLOW, 0);
	cout<<"\n\n2. Enter port number to connect with Server: ";
		Set_Console_Color(	FOREGROUND_RED, 0);
	cin>>port;
	cout<<endl;
	return port;
}


bool Connection_Parameters::get_enc(){
	char encryptionn;
	Set_Console_Color(	FOREGROUND_YELLOW, 0);
	cout<<"3. Do you want to use AES encryption for Advanced Security? [Y/N]";
	Set_Console_Color(	FOREGROUND_RED, 0);
	cin>>encryptionn;
	cout<<endl;
	//bool handling
	if(encryptionn=='Y'){
		encryption = true;
	
	}else if (encryptionn=='N'){
		encryption = false;
		//add cerrr handling 
	}else{
		Set_Console_Color(	FOREGROUND_RED, 0);
		// Invalid input
        cout << "Invalid input. Defaulting to no encryption.\n";
	}
		Set_Console_Color(	FOREGROUND_YELLOW, 0);
		
	cout<<endl;
	
	return encryption;
}

