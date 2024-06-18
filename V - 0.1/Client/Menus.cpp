//system libs
#include <iostream>

//custom libs
#include "Utils.h"
#include "Animations.h"



//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


//namespaces 
using namespace std;


// function definitions
void PrintLogo();




//function that displays the logo and homepage menu
void homepage(){
	
	system("cls");   //clear screen using system windows functiion
	
	//logo display with console color manipulations
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"Welcome ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to:\n\n\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"--- CLIENT SIDE OF ---\n";
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	cout<<"************************";Set_Console_Color(FOREGROUND_RED, 0);cout<<"******************************************"<<endl;
	
	PrintLogo();   //calling the logo printing function containing logo with color mods
		
	cout<<endl;
	Set_Console_Color(FOREGROUND_YELLOW, 0);	
	//extra details added here
	cout<<"***********************************";Set_Console_Color(FOREGROUND_RED, 0);cout<<"*******************************"<<endl;
	cout<<"=> Developed by: [Kotsorgios Panagiotis].\n";
	cout<<"=> Utilizes: [AES] Advanced Encryption Protocol.";Set_Console_Color(FOREGROUND_RED, 0);cout<<"   (!) ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"not yet available\n";Set_Console_Color(FOREGROUND_RED, 0);
    cout<<"=> Windows system compatible.\n";
	cout<<"=> Fully written in C++ programming language."<<endl;
	cout<<"=> Active Contributors: [Kotsorgios Panagiotis]."<<endl<<endl<<endl;
	
	
	//main menu options display with console color manipulations
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"Main";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Menu:\n\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"1.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Connect to server."<<endl;
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"2.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Connect to multiple servers.";Set_Console_Color(FOREGROUND_RED, 0);cout<<"\t\t(!)";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Under Construction\n";Set_Console_Color(FOREGROUND_RED, 0);
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"3.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Custom Made Connection";Set_Console_Color(FOREGROUND_RED, 0);cout<<"\t\t(!)";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Under Construction\n";Set_Console_Color(FOREGROUND_RED, 0);
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"4.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" -Help\n";
	Set_Console_Color(FOREGROUND_RED, 0);
//	cout<<"5.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Settings\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"5.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Exit\n"<<endl;
	
	
	int choice;
	Set_Console_Color(FOREGROUND_ORANGE, 0);  //set console color to ORANGE from defined colors
	
	//program naviugation based on main menu user choice
	cout<<"\nEnter your choice: ";
	Set_Console_Color(FOREGROUND_RED, 0);
	cin>>choice;
	
	//user input controll and navigation
	if(choice==1){
		ChoiceOne();//if user enters 1 we call the ChoiceOne() function to establish a connection
	}
	else if(choice==2){ //not ready yet
		//ChoiceTwo();
		cout<<"We are sorry but thiw is a pre-release of the program and some of its functionalities\nare still under construction.These will be included in the official release of the programm!!!";
		 Set_Console_Color(	FOREGROUND_ORANGE, 0);
		 //wait for user to press enter
	cout<<endl<<"Press enter to return to main menu: ";
	getchar();
	while(getchar()!='\n'){
	}
	}
	else if(choice==3){  //not ready yet
	    //ChoiceThree();
	    Set_Console_Color(FOREGROUND_RED, 0);
	    cout<<"We are sorry but thiw is a pre-release of the program and some of its functionalities\nare still under construction.These will be included in the official release of the programm!!!.";
		 Set_Console_Color(	FOREGROUND_ORANGE, 0);
		 //wait for user to press enter
		cout<<endl<<"Press enter to return to main menu: ";
		getchar();
	while(getchar()!='\n'){
	}
	}
	else if(choice==4){//help menu option
		ChoiceFour();
	
	}else if(choice==5){
	exit(0);
	//choiceFive();
	
	
	}else if(choice==6){//if user enters 5 the program should exit 
		exit(0);
	}
	
	
	
	
}


//logo prrinting function
void PrintLogo(){
	
	//logo of the application
	
	
	/*This is the main current logo of the application,
	and same goes for botjh server and client.It contains ascii art
	and also some color changes in the console text with manipulative windows functions.
	It will be enhanced soon after 1st official release*/
	
//LOGO with color text manipulative functions
Set_Console_Color(FOREGROUND_YELLOW, 0);
cout<<" ____         __      ____             ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"_        _                "<<endl;
Set_Console_Color(FOREGROUND_YELLOW, 0);
cout<<"/ ___|  __ _ / _| ___/ ___";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|  ___   ___| | _____| |_     _"<<endl;
Set_Console_Color(FOREGROUND_YELLOW, 0);
cout<<"\\___ \\ / _` | |_ / _ \\___ \\";Set_Console_Color(FOREGROUND_RED, 0);cout<<" / _ \\ / _| |/ / _ \\ __|  _| |_ _| |_"<<endl;
Set_Console_Color(FOREGROUND_YELLOW, 0);
cout<<" ___) | (_| |  _|  __/___) |";Set_Console_Color(FOREGROUND_RED, 0);cout<<" (_) | (__|   <  __/ |_  |_   _|_   _|"<<endl;
Set_Console_Color(FOREGROUND_YELLOW, 0);
cout<<"|____/ \\__,_|_|  \\___|____/ \\___";Set_Console_Color(FOREGROUND_RED, 0);cout<<"/ \\___|_|\\_\\___|\\__|   |_|   |_| "<<endl;
Set_Console_Color(FOREGROUND_YELLOW, 0);
cout<<endl<<"Github: https://github.com/Panagio";Set_Console_Color(FOREGROUND_RED, 0);cout<<"tisKots/SafeSocket";
}


