//system libraries
#include <iostream>
#include <windows.h>

//custom made ones
#include "Utils.h"
#include "Menus.h"
#include "Animations.h"
#include "Login.h"
//namespaces
using namespace std;






//main function
int main(int argc, char** argv) {

	
	SetConsoleFont(20);          //sets console text size to 20
	
	loginpage();                 /*prints user login page logic and doews also credential validation before moving on to the
	                               //next module to enter the user to the programs main menu*/

	
	system("cls");               //clear screen system command execution
	
	SetConsoleFont(26);          //set text size to 24 after entering main menu for better displayal


   //main loop
   while(true){
	
	
	
                  
	homepage();                /*here we are gonna be keep looping endlessly by calling the main menu function
	                             ubtill the user enters a break statement somewhere in the following code and exits it.*/

}
	return 0;                  //end of programm
}
