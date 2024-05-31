//System libraries
#include <iostream>


//custom libraries
#include "Animations.h"


//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)


//namespaces
using namespace std;

//logo prrinting function
void PrintLogo(){
	
	/*This is the main current logo of the application,
	and same goes for botjh server and client.It contains ascii art
	and also some color changes in the console text with manipulative windows functions.
	It will be enhanced soon after 1st official updaqte-release*/
	
//LOGO
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
cout<<endl<<"Github: https://github.com/Panagio";Set_Console_Color(FOREGROUND_RED, 0);cout<<"tisKots/SafeSocket";   //developer's github repo
}




