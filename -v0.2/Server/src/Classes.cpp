/* 
  This project is developed in C++, an object-oriented programming language.
  The use of classes and objects enhances the security of the code,
  ensuring that data and functionalities are kept private and modular in the whole project.
 
  This module contains the implementations of all server-side functionalities.
  It includes the definitions and functionalities of classes as declared in the "Classes.h" file.
 */
 
 //system libs 
 #include <windows.h>
 #include <limits>   // Include the <limits> header for numeric_limits
#include <stdexcept> 
 
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

//adding functionality to the public string get_credentials function from Classes.h
string Socket_Parameters::get_ip(){

    do{
    	Set_Console_Color(FOREGROUND_YELLOW, 0);
    	system("cls");
		cout<<"\n\n1. Enter Server's IP address:  ";
		Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); //change color for user input to light green
	cin >> ip;

    if (isValidIpAddress(ip)) {
        cout << "Valid IP address\n";
    } else {
    	Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Invalid IP address\n";
        getchar();
       Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout<<"\nPress Enter to try again: ";
        while(getchar()!='\n'){};
    }
}while(isValidIpAddress(ip)==false);
	
	return ip;   //return string (ip) that later gets changed to const char* to be able to have usage in socket functionalities
}

Socket_Parameters soc;



////adding functionality to the public int  get_PortNumber function from Classes.h
int Socket_Parameters::get_PortNumber(){
	cout<<"\n2. Define the Port number (between 0 and 65535) to listen from :  ";
	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY); //change color for user input as usual
while (true) {
        
        
        try {
            if (!(cin >> PortNumber)) {
                throw invalid_argument("Invalid input: not a number.");
            }

            if (PortNumber < 0 || PortNumber > 65535) {
                throw out_of_range("Input out of range.");
            }

            // If we reach here, PortNumber is valid
            break; // Exit the loop if valid input
        }
        catch (const invalid_argument& e) {
            cerr << e.what() << " Please enter a valid number.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        catch (const out_of_range& e) {
            cerr << e.what() << " Please enter a number between 0 and 65535.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "Valid port number entered: " << PortNumber << endl;
	
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
while (true) {
     
        
        try {
            cin >> Timeout;

            if (cin.fail()) {
                throw runtime_error("Invalid input: not a number.");
            }

            // Additional validation if needed (e.g., range checks)
            // For example:
            // if (Timeout < 0 || Timeout > 100) {
            //     throw runtime_error("Timeout value out of range.");
            // }

            // If input is valid, break out of the loop
            break;
        }
        catch (const runtime_error& e) {
            cerr << e.what() << " Please enter a valid number.\n";
            cin.clear();    // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard input buffer
        }
    }

    cout << "Valid timeout value entered: " << Timeout << endl;
	
	return Timeout;   //return also intager valuew inputed by the user
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
