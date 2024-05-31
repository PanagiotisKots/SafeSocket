//system libs
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>

//custom libs
#include "Sockets.h"
#include "Animations.h"
#include "Classes.h"



//defines
#define FOREGROUND_LIGHTER_BLUE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)


//namespace standard
using namespace std;

//function declarations
void Loading_Login_Animation_Function(const int totalProgress, const std::string& loadingText, const int delay);
void clearLineToCursor();
void Loading_Components_Animation();
void Initialising_Programm_Animation();
void Preparing_To_Launch_Animation();
void Troubleshooting(string trouble_text);
void ContactSupport();
void UserHelpMod();


//object creation
Sup login;

Sup sup;//bad practicen  need fixes and calibrations!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


Connection_Parameters con_par;

// Validation logic function
bool validateLogin(const Sup& sup, const string& username, const string& password) {
    // Valid credentials
    return (username == sup.uname && password == sup.pass);
}







//login page function for optic functionalities
void loginpage() {
    
    
cout<<"Welcome to SafeSocket\n\nPlease login:\n\n\n\n";

do{

string username,password;

username = login.get_uname();

password = login.get_pass();
    



    // Check credentials
    if (validateLogin(sup,username, password)) {
    	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
        cout << endl <<"Login successful. Welcome " << username << "!" << endl<<endl<<endl<<endl<<endl<<endl<<endl;
         Set_Console_Color(	DEFAULT_COLOR, 0);
        //Loading_Components_Animation();
        clearLineToCursor();
        Initialising_Programm_Animation();
        clearLineToCursor();
        Preparing_To_Launch_Animation();
        break;
    } else {
    	Set_Console_Color(FOREGROUND_RED, FOREGROUND_INTENSITY);
        cout << endl << "Login failed. Invalid username or password." << endl;
        Set_Console_Color(	DEFAULT_COLOR, 0);
        // Further actions after failed login can be added here
    }
}while(true);
}




//animative function (NEED TO MOVE TO ANIMATIONS.CPP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
void Loading_Login_Animation_Function(const int totalProgress, const string& loadingText, const int delay) {
    for (int progress = 0; progress <= totalProgress; ++progress) {
        cout << "\r" << loadingText << "[";
        for (int i = 0; i < totalProgress; ++i) {
            if (i < progress)
                cout << "="; // Fill the progress
            else
                cout << " "; // Empty space
        }
        cout << "] " << (progress * 100 / totalProgress) << "%"; // Display percentage
        cout.flush();

        if (progress == totalProgress / 3 || progress == 2 * totalProgress / 3)
            Sleep(delay * 2); // Pause in the middle and near the end
        else if (progress < totalProgress / 3)
            Sleep(delay * 2); // Slower speed for the first third
        else if (progress > 2 * totalProgress / 3)
            Sleep(delay / 2); // Accelerated speed for the last third
        else
            Sleep(delay); // Normal speed for the middle third
    }
}

void Loading_Components_Animation() {
    string loadingText = "Loading Components ";
    const int totalProgress = 60; // Total length of the progress bar
    const int delay = 30; // Delay between each step in milliseconds
    Loading_Login_Animation_Function(totalProgress, loadingText, delay);
    Sleep(1400);
}

void Initialising_Programm_Animation() {
    string loadingText = "Initialising Programm ";
    const int totalProgress = 60; // Total length of the progress bar
    const int delay = 5; // Delay between each step in milliseconds
    Loading_Login_Animation_Function(totalProgress, loadingText, delay);
}

void Preparing_To_Launch_Animation() {
    string loadingText = "Preparing to Launch ";
    const int totalProgress = 60; // Total length of the progress bar
    const int delay = 140; // Delay between each step in milliseconds
    Loading_Login_Animation_Function(totalProgress, loadingText, delay);
    Sleep(1000);
    cout << endl << "Programm ready!" << endl;
    Sleep(3000);
     Set_Console_Color(	FOREGROUND_GREEN, FOREGROUND_INTENSITY);
    cout<<"\n\n\nPress Enter to launch SafeSocket: ";
    getchar();
    while(getchar()!='\n'){
	}
}


void clearLineToCursor() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD cursorPos = csbi.dwCursorPosition;
    int lineLength = cursorPos.X + 1; // Adding 1 to account for zero-based indexing
    cout << "\r" << string(lineLength, ' ');
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos); // Restore cursor position
}










//function about user simple server-client connection choice 1st choice from main menu
int ChoiceOne(){
	
	system("cls");   //clears screen
	
	//variables 
	int PortNumber,Timeout;
	bool Encryption = false;
	char Encryption_Input;
	string Server_ip;
	
	//option setting menu
	Server_ip =  con_par.get_ip();
	PortNumber = con_par.get_port();
	Encryption = con_par.get_enc();
	 
	
		
	
	
    Connection_One(Server_ip, PortNumber);  //send parameters and call the function to start connection to socket
	
	return 0;
} 





//multiple client connection    
//need to add errror imput and crashes handling

/*
int ChoiceTwo(){
	
	system("cls");
	
	//variables 
	int PortNumber,Timeout,Max_Client_Num;
	bool Encryption = false;
	char Encryption_Input;
	
	cout<<"1. Enter the port number to listen for incoming connnections: ";
	cin>>PortNumber;
	
	cout<<"2. Do you want to use the AES encryption for Advanced Security? [Y/N]";
	cin>>Encryption_Input;
	
	//bool handling
	if(Encryption_Input=='Y'){
		Encryption = true;
	
	}else if (Encryption_Input=='N'){
		Encryption = false;
		//add cerrr handling 
	}else{
		
		// Invalid input
        std::cout << "Invalid input. Defaulting to no encryption.\n";
	}
	
	cout<<"3. Enter maximum number of connected clients: ";
	cin>>Max_Client_Num;
	
	cout<<"4. Define client connection waiting timeout: ";
	cin>>Timeout;
	
	cout<<"\nwaiting for client/s to connect...";//add animation
	
	
	 //MultipleClients(PortNumber,Max_Client_Num,Timeout);
	
	
	return 0;

	
}

*/



/*
int ChoiceThree() {
    system("cls"); 

    // variables
    int PortNumber, Timeout, MaxConnections, BufferSize;
    string Encryption, Compression;
    char Encryption_Input, Compression_Input;
    string IPAddress, Protocol, DataFormat, EncryptionMethod; // New variable for custom IP address, protocol, data format, and encryption method

    // Get user input for custom connection settings
    cout << "\n\nCustom Connection Settings:\n";
    cout << "1. Enter the IP Address to connect to: ";
    cin >> IPAddress;
    cout << endl;

    cout << "2. Enter the Port number to listen for incoming connections: ";
    cin >> PortNumber;
    cout << endl;

    cout << "3. Enter the protocol (TCP/UDP): ";
    cin >> Protocol;
    cout << endl;

    cout << "4. Do you want to use encryption for Advanced Security? [Y/N]";
    cin >> Encryption_Input;
    cout << endl;

    // String handling for encryption
    if (Encryption_Input == 'Y' || Encryption_Input == 'y') {
        Encryption = "Yes";
        cout << "Choose Encryption Method (AES/RSA/SHA-256): ";
        cin >> EncryptionMethod;
        cout << endl;
    } else if (Encryption_Input == 'N' || Encryption_Input == 'n') {
        Encryption = "No";
    } else {
        cout << "Invalid input. Defaulting to no encryption.\n";
        Encryption = "No";
    }

    cout << "5. Do you want to use compression for data transfer? [Y/N]";
    cin >> Compression_Input;
    cout << endl;

    // String handling for compression
    if (Compression_Input == 'Y' || Compression_Input == 'y') {
        Compression = "Yes";
    } else if (Compression_Input == 'N' || Compression_Input == 'n') {
        Compression = "No";
    } else {
        cout << "Invalid input. Defaulting to no compression.\n";
        Compression = "No";
    }

    cout << "6. Enter waiting timeout for client connection (in seconds): ";
    cin >> Timeout;
    cout << endl;

    cout << "7. Enter the maximum number of connections allowed: ";
    cin >> MaxConnections;
    cout << endl;

    cout << "8. Enter the buffer size for data transfer (in bytes): ";
    cin >> BufferSize;
    cout << endl;

    cout << "9. Enter the format of data (JSON/XML/Custom): ";
    cin >> DataFormat;
    cout << endl;

system("cls");
    // Display the custom connection settings
    cout << "\nCustom Connection Settings:\n";
    cout << "IP Address: " << IPAddress << endl;
    cout << "Port Number: " << PortNumber << endl;
    cout << "Protocol: " << Protocol << endl;
    cout << "Encryption: " << Encryption << endl;
    if (Encryption == "Yes") {
        cout << "Encryption Method: " << EncryptionMethod << endl;
    }
    cout << "Compression: " << Compression << endl;
    cout << "Timeout: " << Timeout << " seconds" << endl;
    cout << "Max Connections: " << MaxConnections << endl;
    cout << "Buffer Size: " << BufferSize << " bytes" << endl;
    cout << "Data Format: " << DataFormat << endl;


//do you wish to change smthing ..............

    // Call your custom connection function with string parameters
    //Server_Custom_Connection(PortNumber, Timeout, MaxConnections, BufferSize, IPAddress, Protocol, Encryption, Compression);

 custom_made_con_f();

    return 0; 
}


*/






// Function to display help/instructions
int ChoiceFour(){
	
	while(true){ //infinite loop
	
    system("cls");//clear screen
    
    //help menu
    Set_Console_Color(FOREGROUND_RED, 0);
    cout << "Help/Instruction Menu:\n\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "1.";Set_Console_Color(FOREGROUND_RED, 0);cout<<" How to use this program.\n";
      Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "2.";  Set_Console_Color(FOREGROUND_RED, 0);cout<<" Troubleshooting bugs/issues.\n";
      Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "3.";  Set_Console_Color(FOREGROUND_RED, 0);cout<<" Contact us.\n";
      Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "4.";  Set_Console_Color(FOREGROUND_RED, 0);cout<<" Return to main menu.\n";
    int choice;
      Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "\n\nEnter your choice: ";
      Set_Console_Color(FOREGROUND_RED, 0);
    cin >> choice;
    
    

    if(choice==1){
    	UserHelpMod();//call UserHelpMod function from bellow
	}
	else if(choice ==2){
		system("cls");  //clear screen
		string bugmessage;
		  Set_Console_Color(FOREGROUND_YELLOW, 0);
		cout<<"SafeSocket Troubleshooting page:";  Set_Console_Color(FOREGROUND_RED, 0);cout<<"\n\n\nPlease submit the isue/bug you found here to help us solve it: ";
		  Set_Console_Color(DEFAULT_COLOR, 0);
		cin>>bugmessage;
		Troubleshooting(bugmessage);//call troublshooting function sending as parameter the entered message by the user
		       //to email address or report it in guithub repository where program is uploadeds	
	}
	else if(choice==3){
		ContactSupport();//prints info and gives extra details
	}
	else if(choice==4){
		return 0;//fix return to main menu bug
		
		
	}
    
}
    return 0;//end of function
}



//add legitimate email - github sending functionality
void Troubleshooting(string trouble_text){
	
	  Set_Console_Color(FOREGROUND_YELLOW, 0);
	cout<<"\n\nIssue sent , thank you for informing us....\n\nfeel free to reoport this or any other isues to our Github repository:";Set_Console_Color(FOREGROUND_RED, 0);cout<<" https://github.com/PanagiotisKots/SafeSocket ";
	
	Set_Console_Color(DEFAULT_COLOR, 0);
	//wait for enter from user
	cout<<"\n\nPress enter to go back: ";
	getchar();
	while(getchar()!='\n'){
	}
}

//add gotoxy box here and to all the menus if possdible
void ContactSupport(){
	system("cls");//clear screen
	string choice;
	  Set_Console_Color(FOREGROUND_YELLOW, 0);
	  //suppoort menu displayal with color manipulations
	cout<<"Contact Support Options: \n\n";
	  Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"1.";  Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Email:";  Set_Console_Color(FOREGROUND_RED, 0);cout<<" pkotsorgios654@gmail.com\n";
	cout<<"2.";  Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Github:";  Set_Console_Color(FOREGROUND_RED, 0);cout<<" https://github.com/PanagiotisKots/SafeSocket\n";
	cout<<"3.";  Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Our Website:";  Set_Console_Color(FOREGROUND_RED, 0);cout<<" update coming soon!!!\n\n";
	  Set_Console_Color(FOREGROUND_YELLOW, 0);
	cout<<"You can also send a message to us directly through SafeScocket.\n";
	cout<<"Enter";  Set_Console_Color(FOREGROUND_RED, 0);cout<<" 'direct'";  Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" to send us message or";   Set_Console_Color(FOREGROUND_RED, 0);cout<<" 'exit'";  Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" to exit Contact Support menu: ";
	Set_Console_Color(FOREGROUND_RED, 0);
	cin>>choice;
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	//user inpuit handling
	if(choice=="direct"){
		string direct_message;
		cout<<"Enter message here:  ";
		  Set_Console_Color(DEFAULT_COLOR, 0);
		cin>>direct_message;
		//send it to us via safesocket server...
		Set_Console_Color(FOREGROUND_YELLOW, 0);
		cout<<"Thank you for the feedback, we will answer as soon as possible: \n\n";
		Set_Console_Color(DEFAULT_COLOR, 0);
		//wait for enter from user
		cout<<"press enter to exit: ";
		//fix spacing error with getline character
		getchar();
		
		while(getchar()!='\n'){
		}
		
	}else if(choice=="exit"){
		//exit function
		Set_Console_Color(FOREGROUND_RED, 0);
		cout<<"Exiting Contact Suppport menu.";
		Sleep(2000);//add loading dots animations
	}
	
	
}










//make these private using classes and all etc......

string UserHelp(){
	
	system("cls");
	  Set_Console_Color(FOREGROUND_YELLOW, 0);
	//Make it morre advanced 
	string helpMessage = 
    "We are very sorry but this help sector is not yed available in the pre release version of the programm!!!\nit will be soon.";
	

	return helpMessage;
	
}

//function that dusplayes the message of UserHelp in animative format
void UserHelpMod(){
	
	string o = UserHelp();
	for(int i=0; i<o.length(); i++){
		Sleep(25);
		cout<<o[i];
	}
	Set_Console_Color(DEFAULT_COLOR, 0);
		cout<<"\n\nPress enter to return: ";
	getchar();
	while(getchar()!='\n'){
	}
}










Sup lg;//not correct 

//fix this one for good!!!!!!!!!!!!!!!!!!!!
void choiceFive(){
	
	system("cls");
	int user_choice;
	Set_Console_Color(DEFAULT_COLOR, 0);
	cout<<"\n\nSafeSocket Settings menu(!)."<<endl<<endl<<endl<<endl;
	cout<<"Sttings:\n\n"<<"1. Change Default Credentials\n";
	cout<<"2. exit\n\n\n";
	cout<<"Enter your choice: ";
	cin>>user_choice;
	
	
	switch(user_choice){
		case 1:
			system("cls");
			cout<<"Enter Current credentials for authentication: \n\n";
			cout<<"Username: ";
			cin>>lg.uname;
			cout<<"Password: ";
			cin>>lg.pass;
			
			
		  // Check credentials
    if (validateLogin(sup,lg.uname, lg.pass)) {
    	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
        cout << endl <<"Authentication successful. Good job " << lg.uname << "!" << endl<<endl<<endl<<endl;
        cout<<"Enter new credentials bellow: \n\n";
        cout<<"Enter new username: ";
        cin>>lg.uname;
        cout<<"Enter new password: ";
        cin>>lg.pass;
        
        
        cout<<"\n\nUsername: "<<lg.uname<<" Pass: "<<lg.pass;
        
        
        sup.uname=lg.uname;
        cout<<sup.uname;
        
        getchar();
        while(getchar()!='\n'){
		}
	}
	else{
		Set_Console_Color(FOREGROUND_RED, FOREGROUND_INTENSITY);
        cout << endl << "Login failed. Invalid username or password." << endl;
        Set_Console_Color(	DEFAULT_COLOR, 0);
        getchar();
        while(getchar()!='\n'){
		}
	}
	
}
}
