/* 
  This project is developed in C++, an object-oriented programming language.
  The use of classes and objects enhances the security of the code,
  ensuring that data and functionalities are kept private and modular in the whole project.
 
  This module contains the implementations of all server-side functionalities.
  It includes the definitions and functionalities of classes as declared in the "Classes.h" file.
 */
 
 //system libs 
 #include <windows.h>
 
 
 //custom made libraries
#include "classes.h"
#include "cstdlib"
#include "Utils.h"
#include "Animations.h"


//module definitions
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_SEA_BLUE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

//namespace standard usage for simplicity
using namespace std;


//adding functionality to the public void get_credentials function from Classes.h
void User::get_credentials() {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
}


//adding functionality to the public bool check_credentials function from Classes.h
bool User::check_credentials(const string& entered_username, const string& entered_password) {
    return username == entered_username && password == entered_password; //shdl return boolean values
}







//adding functionality to the public string get_credentials function from Classes.h
string Socket_Parameters::get_ip(){
	cout<<"\n\n1. Enter Server's IP address:  ";
		Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); //change color for user input to light green
	cin>>ip;
	
	
	return ip;   //return string (ip) that later gets changed to const char* to be able to have usage in socket functionalities
}



////adding functionality to the public int  get_PortNumber function from Classes.h
int Socket_Parameters::get_PortNumber(){
	cout<<"\n2. Define the Port number to listen for incoming connections:  ";
	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); //change color for user input as usual
	cin>>PortNumber;
	cout<<endl;
	
	return PortNumber;   //return intager of port number valueu user entered
}





//for future usage
bool Socket_Parameters::get_Encryption(){
	
	cout<<"3. Do you want to use AES encryption for Advanced Security? [Y/N]:  ";
	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
	cin>>Encryption_Input;
	cout<<endl;
	
	//bool handling
	if(Encryption_Input=='Y'){
		return Encryption = true;
	
	}else if (Encryption_Input=='N'){
		return Encryption = false;
		//add cerrr handling 
	}else{
		Set_Console_Color(FOREGROUND_RED, 0);
		// Invalid input
        cout << "Invalid input. Defaulting to no encryption.\n";
	}
}





//functionality add to the int get_Timeout function from Classes.h
int Socket_Parameters::get_Timeout(){

	cout<<"4. Enter waiting for client connection Timeout:  ";
	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
	cin>>Timeout;
	cout<<endl;
	
	return Timeout;   //return also intager valuew inputed by the user
}














