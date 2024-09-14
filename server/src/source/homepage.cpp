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
#include "Homepage.h"
#include "Remote_Access.h"
//#include "File_Transfer.h"
#include "Net_Map-Scan.h"
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
	
	
	cout<<"            Main";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Menu "<<endl;
	
	Set_Console_Color(FOREGROUND_RED, 0);
	
	cout<<"---------------------------------\n";
	cout<<"| [1]";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" LAN (private connections)";Set_Console_Color(FOREGROUND_RED, 0);cout<<" |"<<endl;
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"---------------------------------\n";
	cout<<"| [2]";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" WAN (public connections) ";Set_Console_Color(FOREGROUND_RED, 0);cout<<" |\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"---------------------------------\n";
	cout<<"| [3]";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Network Mapping/Scaning  ";Set_Console_Color(FOREGROUND_RED, 0);cout<<" |\n";Set_Console_Color(FOREGROUND_RED, 0);
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"---------------------------------\n";
	cout<<"| [4]";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Help                     ";Set_Console_Color(FOREGROUND_RED, 0);cout<<" |\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"---------------------------------\n";
	cout<<"| [5]";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Settings                 ";Set_Console_Color(FOREGROUND_RED, 0);cout<<" |\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"---------------------------------\n";
	cout<<"| [6]";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Remote Access and Controll";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|\n";
	cout<<"---------------------------------"<<endl;
	cout<<"| [7]";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Exit                     ";Set_Console_Color(FOREGROUND_RED, 0);cout<<" |\n";
		cout<<"---------------------------------"<<endl;
	Set_Console_Color(FOREGROUND_RED, 0);
		
		
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
		
		system("cls");
		cout<<"[+] Private / Local Connection Menu"<<endl<<endl;
		
	    Lan_Menu();
		
		
		
	}
	//if user enters 2
	else if(choice==2){
		
			
		
		
		Wan_Menu();
		//option not yet actiuve and avaiulable
	/*(	MultipleConnHandlF();
		Set_Console_Color(FOREGROUND_ORANGE, 0);
		cout<<"Press Enter to return to homepage: ";
		getchar();
		while(getchar()!='\n'){
		}
		
		*/
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
	 Net_Map();
	 getchar();
	 while(getchar()!='\n'){
	 }
	    
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
	//call remote access and controll functions(menu with remote shell and phoenix rat functionalities);
	General_Menu_F();
	
	}
	
	else if(choice==7){
		exit(0);//exits program returning 0 as exit value
		
	}
	
	
}








void Lan_Menu(){
	
	
	while(true){
	
	system("cls");
	
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"----------------------------------------------"<<endl;
	cout<<"| [1] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Single Server - Client Connection      ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"| "<<endl;
	cout<<"----------------------------------------------"<<endl;
	cout<<"| [2] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Multiple Client Connections            ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|"<<endl;
	cout<<"----------------------------------------------"<<endl;
	cout<<"| [3] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Custom Made Server - Client Connection ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|"<<endl;
	cout<<"----------------------------------------------"<<endl;
	cout<<"| [4] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Send File ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"                             |"<<endl;
	cout<<"----------------------------------------------"<<endl;
	
	cout<<"| [5] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Full Scale Connection (Audio included) ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|"<<endl;
	cout<<"----------------------------------------------"<<endl;

	cout<<"| [6] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"EXIT ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"                                  |"<<endl;
	cout<<"----------------------------------------------"<<endl;
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	
	
	//ADD EXIT OPTIONS EVERYWHERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	int o;
	cout<<"\nEnter choice: ";
	cin>>o;
	
	if(o==1){
		ChoiceOne(); 
	}else if(o==2){
		MultipleConnHandlF();
	}else if(o==3){
		ChoiceThree();
	}else if(o==4){
		Send_file_to_client();
	break;
	
	}else if(o==5){
		
		
		cout<<"(!) Option Not Yet Available, Will be on the next update.\n\n";
		cout<<"Press Entrrer to continue: ";
		getchar();
		while(getchar()!='\n'){
		}
	}
	else if(o==6){
		cout<<"Exitinng";
		for(int i=0; i<5; i++){
			cout<<".";
			Sleep(1000);
			
		}
		break;
	}
	
	else {
		cerr<<"Invalid Input";
		Sleep(1000);
		
	}
}
}








void Wan_Menu(){
	while(true){
	
	system("cls");
	
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"[+] PUBLIC / EXTERNAL Connection Menu"<<endl<<endl;
	cout<<"---------------------------------------------------------------------------------"<<endl;
	cout<<"| [1] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Single Server - Client Connection (Public / External)      ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"               | "<<endl;
	cout<<"---------------------------------------------------------------------------------"<<endl;
	cout<<"| [2] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Multiple Client Connections (Public / External)     ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"                      |"<<endl;
	cout<<"---------------------------------------------------------------------------------"<<endl;
	cout<<"| [3] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Custom Made Server - Client Connection  (Public / External)";Set_Console_Color(FOREGROUND_RED, 0);cout<<"               |"<<endl;
	cout<<"---------------------------------------------------------------------------------"<<endl;
	cout<<"| [4] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Full Scale Connection(Live Audio, Live Screensharing, Live File Transfers)";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|"<<endl;
	cout<<"---------------------------------------------------------------------------------"<<endl;
	cout<<"| [5] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"EXIT ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"                                                                     |"<<endl;
	cout<<"---------------------------------------------------------------------------------"<<endl;
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	
	
	//ADD EXIT OPTIONS EVERYWHERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	int o;
	cout<<"\nEnter choice: ";
	cin>>o;
	
	if(o==1){
		//add functions for public networking
			cout<<"(!) Option Not Yet Available, Will be on the next update.\n\n";
		cout<<"Press Entrrer to continue: ";
			getchar();
		while(getchar()!='\n'){
		}
	}else if(o==2){
		//add functions for public networking
			cout<<"(!) Option Not Yet Available, Will be on the next update.\n\n";
		cout<<"Press Entrrer to continue: ";
			getchar();
		while(getchar()!='\n'){
		}
	}else if(o==3){
	//add functions for public networking
		cout<<"(!) Option Not Yet Available, Will be on the next update.\n\n";
		cout<<"Press Entrrer to continue: ";
			getchar();
		while(getchar()!='\n'){
		}
	}else if(o==4){
			cout<<"(!) Option Not Yet Available, Will be on the next update.\n\n";
		cout<<"Press Entrrer to continue: ";
			getchar();
		while(getchar()!='\n'){
		}

	
	}
	else if(o==5){
	
	cout<<"Exiting";
	for(int i=0; i<5; i++){
		cout<<".";
		Sleep(1000);
	}
	break;
	}else {
		cerr<<"Invalid Input";
	}
}
}












void Net_Map(){
	while(true){
	
	system("cls");
	
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"[+] Network Scanning / Mapping  Menu"<<endl<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"| [1] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Ping Sweeping      ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"    | "<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"| [2] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Port Scanning     ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"     |"<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"| [3] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Traceroute";Set_Console_Color(FOREGROUND_RED, 0);cout<<"             |"<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"| [4] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"ARP Scanning ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"          |"<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"| [5] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Vulnerability Scanning ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|"<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"| [6] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Full Package Scan ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"     |"<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"| [7] ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"EXIT ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"                  |"<<endl;
	cout<<"------------------------------"<<endl;
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	
	

	
	int o;
	cout<<"\nEnter choice: ";
	cin>>o;
	if(o==1){
		ping_sweep_f();
	}
	if(o==2){
		 mais();
	}
	if(o==3){
		tracerouting();
		getchar();
		while(getchar()!='\n'){
		}
	}
	if(o==4){
		 arpa();
	}
	if(o==5){
		vuln();
	}
	if(o==6){
		fullp();
	}
	if(o==7){
		cout<<"Exiting";
		for(int i=0; i<5; i++){
			cout<<".";
			Sleep(1000);
		}
		break;
	}
	else{
		cout<<"Invalid input";
	}



}
}













//cout<<"Make the full scale connection function add to it file sending, audio transfer and screen sharing live in seperate window.\n";
		//cout<<"(!) This Connection, has also Live Audio transfer, Live file sending , Live etxt message exchange and also screensharing in gui form.";
	//ADD EXIT OPTIONS EVERYWHERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//add instructions to do port forwarding like to dfo this connrction firstly yo need ....... explain..... add option if yoj know .. or not .....
//add image profile to thefull scale comunicastion(standard one in the pop up indormation window where the screensharing will also be displayed)
