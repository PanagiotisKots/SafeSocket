//System libraries
#include <iostream>


//custom libraries
#include "Animations.h"
#include "Classes.h"
#include "Settings.h"


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
cout<<endl<<"Github: https://github.com/Panagio";col.Print_Color2();cout<<"tisKots/SafeSocket";   //developer's github repo
}




