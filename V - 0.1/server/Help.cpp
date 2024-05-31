//system libraries
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>

//namespaces
using namespace std;

//make these private using classes and all etc......(to add extra security to the programm)

//function that contains the help message
string UserHelp(){
	
	system("cls");   //clears screen
	
	//message for user helpi
	string help = "We are very sorry but this sector is not yet available in the pre-release version of the program\n"
	"it will be included at its first official release though!";
	
	return help;   //returns the message in string format
	
}

//function that handles the string returned from the above function
void UserHelpMod(){
	
	string o = UserHelp();  //save the returned string in o variabvle
	
	//loop that printd each letter of the string with some duration between each loop iteration
	for(int i=0; i<o.length(); i++){
		Sleep(25);
		cout<<o[i];
	}
	
	//wait for user to press enter
	cout<<"\n\nPress Enter to return to homepage: ";
	getchar();
	while(getchar()!='\n'){
		
	}
	
}
