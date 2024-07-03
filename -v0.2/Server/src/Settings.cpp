#include <iostream>
#include <windows.h>

#include "Settings.h"
#include "Animations.h"
#include <windows.h>

#include "Classes.h"


#define FOREGROUND_YELLOW 0x0006 // Yellow text color



using namespace std;



//add extra modules like setting.h 

//function that changes username 
void Change_Uname(){
	usr.Change_usrnm();
	

}

//same goes here + make them string form to return changed credentials into string formats
void Change_Pass(){

usr.Change_passw();
cout<<"\nUsername & Password updated ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"succesfully. \n\n";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"\n\nPress Enter to continue: ";
	getchar();
	while(getchar()!='\n'){
	}
}


//this will change logo colors add option of color 1 and then color 2 and make them return them and with #direktivves make the colors be like these ones returned numbers 1-2-3-4-5etc...
int Change_Logo_Color1(){
	


    cout<<"----------------\n";
    Set_Console_Color(FOREGROUND_RED, 0);
	cout << "[+] Color 1 set: \n";
	Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout<<"----------------\n\n\n";

    cout<<"Enter color {";Set_Console_Color(FOREGROUND_RED, 0);cout<<"RED";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<", ";Set_Console_Color(FOREGROUND_BLUE, 0);cout<<"BLUE";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<",";Set_Console_Color(FOREGROUND_GREEN, 0);cout<<" GREEN";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"}: ";

	
	c.get_color();
	c.handle_Foreground();
	c.handle_intensity();
	c.Print_Color();

    cout<<"[+] Color1 Changed\n\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    

    
  

    return 0;
}





void Change_Logo_Color2(){
	  cout<<"----------------\n";
    Set_Console_Color(FOREGROUND_RED, 0);
	cout << "[+] Color 2 set: \n";
	Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout<<"----------------\n\n\n";

    cout<<"Enter color {";Set_Console_Color(FOREGROUND_RED, 0);cout<<"RED";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<", ";Set_Console_Color(FOREGROUND_BLUE, 0);cout<<"BLUE";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<",";Set_Console_Color(FOREGROUND_GREEN, 0);cout<<" GREEN";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"}: ";

	
	col.get_color2();
	col.handle_Foreground2();
	col.handle_intensity2();
	col.Print_Color2();
	
	cout<<"[+] Color2 Changed\n\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout<<"Press Enter to continue: ";

    getchar();
    while(getchar()!='\n'){
	}

	
}






















//prints menu of settings and handles the rest
int Settings_Menu(){
	
		int exitcode = 0;
	
	system("cls");
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	cout<<"------------\n";Set_Console_Color(FOREGROUND_RED, 0);cout<<"[+] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Settings\n------------\n\n\n";
	cout<<"-------------------\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"=> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Setting's Menu:\n-------------------\n\n";
	cout<<"---------------------------------------\n";
	
	cout<<"| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"1. Change Logo Colors";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"               |\n";
	cout<<"---------------------------------------\n";
	cout<<"| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"2. Change Default Credentials";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"       |\n";
	cout<<"---------------------------------------\n";
	cout<<"| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"3. Add Default Connection Parameters";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
	cout<<"---------------------------------------\n";
	cout<<"| ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"4. Exit Settings Menu               ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"|\n";
	cout<<"---------------------------------------\n\n";
	
	string choice;
	
	cout<<"Enter your choice: ";
	
	
	
	cin>>choice;
	
	if(choice=="1"){
		system("cls");
		Change_Logo_Color1();
		Change_Logo_Color2();
		return exitcode;
		
		
	}else if(choice=="2"){
		system("cls");
		Change_Uname();
		 Change_Pass();
		 return exitcode;
		 	
		
	}else if(choice=="3"){
		Add_Default_prices();
		cout<<"(!) Option not yet available. Under construction!!!";
		cout<<"\nPres enter to continue: ";
	    getchar();
	    while(getchar()!='\n'){
		}
		return exitcode;
			
	}if(choice=="4"){
		cout<<"Exiting";
		Loading_dots();
	exitcode = 1;
		return exitcode;
		
	}
	else{
		cout<<"Invalid Choicee. Press Enter to try again: ";
		getchar();
		while(getchar()!='\n'){
		}
			return exitcode;
	}
}
	




//using constructor, it will add default prices top server , ip, port encryptionj etc.....
void Add_Default_prices(){
	
	
}

