#include <iostream>
#include<windows.h>

using namespace std;

#include "Animations.h"
#include "Classes.h"
#include"Login.h"






//object creted for User 
User user;




// Validation logic function
bool validateLogin(const string& username, const string& password) {
    // Valid credentials
    return (user.username == usr.username && user.password == usr.password);
}




//login function
void lpg(){
	
	int counts=3;
	do{
     //Set_Console_Color(FOREGROUND_BLUE, FOREGROUND_INTENSITY);
    // Username input
    cout << "Username: ";
    //Set_Console_Color(FOREGROUND_LIGHTER_BLUE, 0);
    cin >> usr.username;

    // Password input
    //Set_Console_Color(FOREGROUND_BLUE, FOREGROUND_INTENSITY);
    cout << "Password: ";
    // Set_Console_Color(FOREGROUND_LIGHTER_BLUE, 0);
    cin >> usr.password;



    // Check credentials
    if (validateLogin(usr.username, usr.password)) {
    	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
        cout << endl <<"Login successful. Welcome " << usr.username << "!" << endl<<endl<<endl<<endl<<endl<<endl<<endl;
        Set_Console_Color(DEFAULT_COLOR, 0);
        Loading_Components_Animation();
        clearLineToCursor();
        Initialising_Programm_Animation();
        //clearLineToCursor();
        //Preparing_To_Launch();
        Sleep(3000);
        Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
         cout<<"\n\n\nProgram ready!"<<endl<<endl<<endl<<endl;
         Sleep(1000);
         Set_Console_Color(DEFAULT_COLOR, 0);
        cout<<"Press ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"enter";Set_Console_Color(DEFAULT_COLOR, 0);cout<<" to launch SafeSocket: ";
        getchar();
        while(getchar()!='\n'){
        	
		}
        break;
    } else {
    	Set_Console_Color(FOREGROUND_RED, FOREGROUND_INTENSITY);
        cout << endl << "Login failed. Invalid username or password." << endl;
        counts--;
        if(counts==0){
        	cout<<"INTRUDER DETECTED exiting programm.....";
        	exit(0);
		}
        cout<<"\nWARNING(!)";cout<< counts<<" more attempts until you get flaged as INTRUDER.\n";
        Set_Console_Color(DEFAULT_COLOR, 0);
        // Further actions after failed login will be added here!!!!!!!!!!!!!!!
    }
}while(true);
}





//login page function for optic functionalities
void loginpage() {
    string login_choice;
    int count=3;
   //Set_Console_Color(FOREGROUND_BLUE, FOREGROUND_INTENSITY);
cout<<"[+] Welcome to SafeSocket\n\n[+]Enter Credentials to enter the application.\n\n\n";



	lpg();

            Set_Console_Color(DEFAULT_COLOR, 0);
        
}




