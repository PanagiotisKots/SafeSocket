//system libs
#include <iostream>

//custom libs
#include "Utils.h"
#include "Animations.h"
#include "Settings.h"
#include "Logo.h"


//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

#include <stdexcept> // For std::logic_error
//namespaces 
using namespace std;




#include <limits>


//function that displays the logo and homepage menu
void homepage(){
	
	system("cls");   //clear screen using system windows functiion
	
	//logo display with console color manipulations
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"Welcome ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to:\n\n\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"--- CLIENT SIDE OF ---\n";
	c.Print_Color();
	cout<<"************************";col.Print_Color2();	cout<<"******************************************"<<endl;
	
	PrintLogo();   //calling the logo printing function containing logo with color mods
		
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
	
	
	//main menu options display with console color manipulations
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"Main";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Menu:\n\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"1.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Connect to server."<<endl;
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"2.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Connect to multiple servers.\n";Set_Console_Color(FOREGROUND_RED, 0);
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"3.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Random Connection\n";Set_Console_Color(FOREGROUND_RED, 0);;
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"4.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" -Help\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"5.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Settings\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"6.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Exit\n"<<endl;
	
	
	int choice;
	Set_Console_Color(FOREGROUND_ORANGE, 0);  //set console color to ORANGE from defined colors
	
	//program naviugation based on main menu user choice
	cout<<"\nEnter your choice: ";
	Set_Console_Color(FOREGROUND_RED, 0);
	
while (true) {
        try {
           
            std::cin >> choice;

            // Check if the input operation failed (e.g., non-integer input)
            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
                throw std::logic_error("Invalid input: not an integer");
            } else {
                break; // Exit the loop if input is valid
            }
        } catch (const std::logic_error& e) {
            std::cerr << "Caught a logic error: " << e.what() << std::endl;
        }
    }

    std::cout << "You entered: " << choice << std::endl;
	
	//user input controll and navigation
	if(choice==1){
		ChoiceOne();//if user enters 1 we call the ChoiceOne() function to establish a connection
	}
	else if(choice==2){ //not ready yet
		ChoiceTwo();
		
	cout<<endl<<"Press enter to return to main menu: ";
	getchar();
	while(getchar()!='\n'){
	}
	}
	else if(choice==3){  //not ready yet
	    ChoiceThree();
	    
		cout<<endl<<"Press enter to return to main menu: ";
		getchar();
	while(getchar()!='\n'){
	}
	}
	else if(choice==4){//help menu option
		ChoiceFour();
	
	}else if(choice==5){
	Settings_Menu();

	
	
	}else if(choice==6){//if user enters 5 the program should exit 
	#include "Sockets.h"
	get_file_from_server();
		exit(0);
	}
	
	
	
	
}
