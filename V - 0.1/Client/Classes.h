#ifndef CLASSES_H
#define CLASSES_H

//for string datatype
using namespace std;


//class for Signup           //BAD PREACTICE !!!!!!!!!!!!!!!!!
class Sup{
	
	public://fix this by adding inheritance and make it protected!!!!!!!!!!!!!!!!!!!!
	string uname;
	string pass;
	
	
	public:
		Sup();
		string get_uname();
		string get_pass();
	
};




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


#endif


