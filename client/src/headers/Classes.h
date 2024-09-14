#ifndef CLASSES_H
#define CLASSES_H

//for string datatype
using namespace std;

#include <windows.h>



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




//class for networking 
class Connection_Parameters{
	
	string ip_addr;
	int port;
	bool encryption;
	//add more.....
	
	public:
		string get_ip();
		int get_port();
		bool get_enc();


    //add constructor with default prices and automatically get pc's ip in server side too......		
    
    
};


















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


