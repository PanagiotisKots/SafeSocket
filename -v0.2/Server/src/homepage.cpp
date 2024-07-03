//system libs
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <stdexcept>//used for exceptions
#include <cctype>
//custom libs
#include "Logo.h"
#include "Sockets.h"
#include "Help.h"
#include "Utils.h"
#include "Animations.h"
#include "Settings.h"
#include "Classes.h"

//DEFINES
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


//namespaces
using namespace std;





//function that displays the logo and homepage menu
void homepage(){
	
	
	system("cls");   //clear screen using system windows functiion
	
	//logo display with console color manipulations
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"Welcome ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to:\n\n\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"--- SERVER SIDE OF ---\n";
	c.Print_Color();
	cout<<"************************";col.Print_Color2();cout<<"******************************************"<<endl;
	
		PrintLogo();   //calling the logo printing function
		
	cout<<endl;
	c.Print_Color();	
	//extra details added here
	cout<<"***********************************";col.Print_Color2();cout<<"*******************************"<<endl;
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"=> Developed by: [Kotsorgios Panagiotis].\n";
	cout<<"=> Utilizes: [AES] Advanced Encryption Protocol.";Set_Console_Color(FOREGROUND_RED, 0);cout<<"   (!) ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"not yet available\n";Set_Console_Color(FOREGROUND_RED, 0);
    cout<<"=> Windows system compatible.\n";
	cout<<"=> Fully written in C++ programming language."<<endl;
	cout<<"=> Active Contributors: [Kotsorgios Panagiotis]."<<endl<<endl<<endl;
	
	
	
	
	Set_Console_Color(FOREGROUND_RED, 0);
	//main menu options display with console color m,anipulations
	cout<<"Main";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Menu:\n\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"1.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Single server-client connection"<<endl;
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"2.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Multiple client connection\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"3.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Custom Made Connection\n";Set_Console_Color(FOREGROUND_RED, 0);
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"4.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Help\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"5.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Settings\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"6.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Exit\n\n";
	
	int choice;
	Set_Console_Color(FOREGROUND_ORANGE, 0);  //set console color to ORANGE from defined colors
	
	//program naviugation based on main menu user choice

	cout<<"\nEnter your choice: ";
	Set_Console_Color(FOREGROUND_RED, 0);
     
     //error occursion handfling
    try{
	cin>>choice;
	
	if(cin.fail()){
		throw logic_error("");
	}
	}catch(const logic_error& e){
		
		
		cout << "Not intager value given: " << e.what() << endl<<endl;
			Set_Console_Color(FOREGROUND_ORANGE, 0);
		cout<<"Press enter to continue: ";
		getchar();
		while(getchar()!='\n'){
		}

        // Clear the error state of std::cin
        cin.clear();
        // Ignore the rest of the line to discard invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	
	
	
	//if user enters 1 as option
	if(choice==1){
		ChoiceOne();   //call the choice 1 function
	}
	//if user enters 2
	else if(choice==2){
		//option not yet actiuve and avaiulable
		MultipleConnHandlF();
		Set_Console_Color(FOREGROUND_ORANGE, 0);
		cout<<"Press Enter to return to homepage: ";
		getchar();
		while(getchar()!='\n'){
		}
		//ChoiceTwo();
	}
	//if user enters 3
	else if(choice==3){
		//option not yet actiuve and avaiulable
		/*Set_Console_Color(FOREGROUND_RED, 0);
		cout<<"WARNING(!) Option Not yet available\n\n";
		Set_Console_Color(FOREGROUND_ORANGE, 0);
		cout<<"Press Enter to return to homepage: ";
		getchar();
		while(getchar()!='\n'){
		}**/
	    ChoiceThree();
	}
	//if user enters 4
	else if(choice==4){
		ChoiceFour();  //call the help function to displayb secondary menu
	
	}else if(choice==5){
		while(1){
		
		//call settings menu function
		int p = Settings_Menu();
	    if(p==1){
	    	break;
		}
	}
	}else if(choice==6){
		exit(0);//exits program returning 0 as exit value
		
	}
	
	
}
