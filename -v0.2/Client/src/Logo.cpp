
#include <iostream>
#include <windows.h>
#include "Animations.h"
#include "Classes.h"
using namespace std;
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

//logo prrinting function
void PrintLogo(){
	
	//logo of the application
	
	
	/*This is the main current logo of the application,
	and same goes for botjh server and client.It contains ascii art
	and also some color changes in the console text with manipulative windows functions.
	It will be enhanced soon after 1st official release*/
	
//LOGO with color text manipulative functions
c.Print_Color();
cout<<" ____         __      ____             ";col.Print_Color2();cout<<"_        _                "<<endl;
c.Print_Color();
cout<<"/ ___|  __ _ / _| ___/ ___";col.Print_Color2();cout<<"|  ___   ___| | _____| |_     _"<<endl;
c.Print_Color();
cout<<"\\___ \\ / _` | |_ / _ \\___ \\";col.Print_Color2();cout<<" / _ \\ / _| |/ / _ \\ __|  _| |_ _| |_"<<endl;
c.Print_Color();
cout<<" ___) | (_| |  _|  __/___) |";col.Print_Color2();cout<<" (_) | (__|   <  __/ |_  |_   _|_   _|"<<endl;
c.Print_Color();
cout<<"|____/ \\__,_|_|  \\___|____/ \\___";col.Print_Color2();cout<<"/ \\___|_|\\_\\___|\\__|   |_|   |_| "<<endl;
c.Print_Color();
cout<<endl<<"Github: https://github.com/Panagio";col.Print_Color2();cout<<"tisKots/SafeSocket";
}


