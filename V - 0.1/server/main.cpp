//standard libs
#include <iostream> 
#include <windows.h>
#include <cstdio>

//custom libs
#include "homepage.h"
#include "login.h"
#include "homepage.h"
#include "Utils.h"
#include "Animations.h"

//defines 
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_SEA_BLUE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


//namespaces
using namespace std;                               //standard namespace use for code simplisity



//functionn declarations
void SetConsoleFont(int fontSize);                //declaration of function for console text size






//main function
int main(int argc, char** argv) {
    
    
  
	SetConsoleFont(22);                           //make text size bigger (windows function for console font size manipulation)
	
 	loginpage();                                  //login page function 
	

	SetConsoleFont(28);                           //modifying text size to 28
	
	
	while(true){                                  //main loop (keeps the main menu printed without exiting the programm)
	 
	homepage();                                   //home page and main menu functions (where the rest of the programm continues)
}
	
	return 0;                                     //return 0 when program ends
}











