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

public://??functions that return string format here to make them private
    string username;
    string password;
    
    //functions that accept and chech credentials of user
    void get_credentials();
    User();
    void Change_usrnm();
    void Change_passw();
    
};

extern User usr;




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






extern Socket_Parameters soc;



class Color{
	
	private:
		string color;
        int temp;
        WORD foreground;  // Initialize foreground color attribute
        WORD background;  // Initialize background color attribute (here assumed to be 0)
        
    public:
    	string get_color();
    	WORD handle_Foreground();
    	WORD handle_intensity();
    	void Print_Color();
    	Color();
	
	
};




class Color2{
	
	private:
		string color;
        int temp;
        WORD foreground;  // Initialize foreground color attribute
        WORD background;  // Initialize background color attribute (here assumed to be 0)
        
    public:
    	string get_color2();
    	WORD handle_Foreground2();
    	WORD handle_intensity2();
    	void Print_Color2();
    	Color2();
	
	
};





extern Color c;

extern Color co;


extern Color2 col;


#endif

