#ifndef CLASSES_H
#define CLASSES_H

/*
  This file contains all the class declarations for the server-side modules of the entire project.
  The classes are organized into private, protected, and public sections to ensure proper construction.
 */


// system libraries
#include <iostream>
#include <string>

using namespace std;   //namespace usage for simplisity and string data type acceptance 



//User class for sugn-up or login   
class User {
	//fix this with default with and constructors protected etc...
	
//public values(!!!!!make them private , use inheritance and secure them better also have as default credentials using constructor!!!!!!!!!!!)FIX IT!!!!!!!!!
public:
    string username;
    string password;
    
    //functions that accept and chech credentials of user
    void get_credentials();
    bool check_credentials(const string& entered_username, const string& entered_password);
};




//Socket_Parameters class declarataion
class Socket_Parameters{
	
	//private values
	private:
		string ip;
		int PortNumber;
		bool Encryption = false;
		char Encryption_Input;
	    int Timeout;
	
	//public values (mostly functions that handle the private ones)
	public:
		string get_ip();
		int get_PortNumber();
		bool get_Encryption();
		char get_Encryption_Input();
		int get_Timeout();
};


//ADD CLASS TO DISPLAY THE CLIENTS FULL DETAILOS SUCHJ AS IP, PORT, CHANEL, DEVICE INFO, HARDWARE INFO ETC.....

#endif

