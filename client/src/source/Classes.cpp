//system libs
#include <iostream>

//custom libs
#include "Classes.h"
#include "Animations.h"




//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


//adding functionality to the public void get_credentials function from Classes.h
void User::get_credentials() {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
}




User::User(){
	username = "admin";
	password = "pass";
}

User usr;

void User::Change_usrnm(){
	
	cout<<"Enter ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"new";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" username:\n\nUsername: ";//add additional security layer of enter the curent ones
	Set_Console_Color(FOREGROUND_RED, 0);
	cin>>username;
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	
}

void User::Change_passw(){
	cout<<"\n\nEnter ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"new ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"password:\n\nPassword: ";
	Set_Console_Color(FOREGROUND_RED, 0);
	cin>>password;
	Set_Console_Color(FOREGROUND_YELLOW, 0);
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




















string Color::get_color(){

	
	cin>>color;
	
	return color;
}




WORD Color::handle_Foreground(){
	
	if (color == "RED") {
        foreground = FOREGROUND_RED;
    } else if (color == "BLUE") {
        foreground = FOREGROUND_BLUE;
    } else if (color == "GREEN") {
        foreground = FOREGROUND_GREEN;
    } else {
        cerr << "Not supported color format. Press Enter to try again: ";
        getchar();  // Clear input buffer
        while (getchar() != '\n') {
            // Clear remaining input buffer
        }
        cerr<<"exiting.....";
    }
    return foreground;
}



WORD Color::handle_intensity(){
	
	
	 cout << "Enter ";Set_Console_Color(FOREGROUND_YELLOW, FOREGROUND_INTENSITY);cout<<"1 ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"for color intensity or 0 for none: ";
     cin >> temp;
    
      if (temp == 1) {
        background == FOREGROUND_INTENSITY;  // Set intensity flag if temp is 1
    } else if (temp == 0) {
        cerr << "Not supported intensity format. Press Enter to try again: ";
        getchar();  // Clear input buffer
        while (getchar() != '\n') {
            // Clear remaining input buffer
        }
        cerr<<"error...";
    }
    return background;
}
   

void Color::Print_Color(){
	 Set_Console_Color(foreground, background);
	 
	
}



Color::Color(){
	foreground = FOREGROUND_YELLOW;
	background = 0;
	
	
}




Color c;
Color co;





string Color2::get_color2(){

	
	cin>>color;
	
	return color;
}




WORD Color2::handle_Foreground2(){
	
	if (color == "RED") {
        foreground = FOREGROUND_RED;
    } else if (color == "BLUE") {
        foreground = FOREGROUND_BLUE;
    } else if (color == "GREEN") {
        foreground = FOREGROUND_GREEN;
    } else {
        cerr << "Not supported color format. Press Enter to try again: ";
        getchar();  // Clear input buffer
        while (getchar() != '\n') {
            // Clear remaining input buffer
        }
        cerr<<"exiting.....";
    }
    return foreground;
}



WORD Color2::handle_intensity2(){
	
	 cout << "Enter 1 for color intensity or 0 for none: ";
     cin >> temp;
    
      if (temp == 1) {
        background == FOREGROUND_INTENSITY;  // Set intensity flag if temp is 1
    } else if (temp == 0) {
        cerr << "Not supported intensity format. Press Enter to try again: ";
        getchar();  // Clear input buffer
        while (getchar() != '\n') {
            // Clear remaining input buffer
        }
        cerr<<"error...";
    }
    return background;
}
   

void Color2::Print_Color2(){
	 Set_Console_Color(foreground, background);
	 
	
}



Color2::Color2(){
	foreground = FOREGROUND_RED;
	background = 0;
	
	
}


Color2 col;

