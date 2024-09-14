//system libraries
#include <iostream>
#include <cstdlib> 
#include <windows.h>
#include <vector>
#include <stdexcept> // For std::logic_error
#include <limits>


//custom made libs
#include "Utils.h"
#include "Help.h"
#include "Animations.h"
#include "Classes.h"
#include "Sockets.h"


//defines
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE)

//namespace standard for code simplicity
using namespace std;                                                   


//function defionitions
void Troubleshooting(string trouble_text);                               
void ContactSupport();







//Function that handles user inputs and parameters for simple connection ( Choice 1 from main menu )
int ChoiceOne(){
	
	system("cls");   //clear screen system function
	
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	cout<<"-------------------------------------------\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"[+] Single Server - Client connection menu: "<<endl;
	Set_Console_Color(FOREGROUND_YELLOW, 0);
	cout<<"-------------------------------------------\n";
	
	//simple connnection parameter setting menu 
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"\n--------------------------------------------------\n";
	cout<<"| ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"1. ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Continue with default Connection parameters ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|\n";Set_Console_Color(FOREGROUND_RED, 0);	cout<<"--------------------------------------------------\n";Set_Console_Color(FOREGROUND_RED, 0);cout<<"| ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"2. ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Go with custom Connection parameters        ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"|\n";
	Set_Console_Color(FOREGROUND_RED, 0);
	cout<<"--------------------------------------------------\n\n\n";
	int choice;
	cin>>choice;
	
	if(choice==2){
		
	Set_Console_Color(FOREGROUND_YELLOW, 0);   //console color change to yellow
	
	string ip_adr = soc.get_ip();   //get ip from user input with classes function
	
	Set_Console_Color(FOREGROUND_YELLOW, 0);   //console color change to yellow
	
	int port = soc.get_PortNumber();     //get port number from pivate class by user input(same way as ip)
	
	Set_Console_Color(FOREGROUND_YELLOW, 0);   //console color change to yellow
	
	bool crypt = soc.get_Encryption();   //get boolean for of encryption from user and return true or false value for future usage

    Set_Console_Color(FOREGROUND_YELLOW, 0);   //console color change to yellow

	int time_out = soc.get_Timeout();   //gets user input price for waiting time to connect ....same way as ip port etc......
	
	
	
	/* Convert string to const char* using c_str() for it to be able 
	to be accepted in the Server_Listen function that can only take const char* as a 
	parameter because of windows socket programming limitations
	*/
    const char* cString = ip_adr.c_str(); //make the conversion of string to const char* and send it as a parameter instead of string bellow
    
    
	/*call the single connection function from utils.cpp, sending as parameters the private elements
	{port number, timeout and ip address which has transormed to cString}*/
	Server_Listen(port, time_out, cString);
	}
	else if(choice==1){
		cout<<"Option not yet avaiilable:";
		
		getchar();
		while(getchar()!='\n'){
			
			
		}
	}
	
	
	
	
	return 0;  //return 0 when function reaches end
} 





int ChoiceThree() {
    system("cls"); 

    // variables
    int PortNumber, Timeout, MaxConnections, BufferSize;
    string Encryption, Compression;
    char Encryption_Input, Compression_Input;
    string IPAddress, Protocol, DataFormat, EncryptionMethod; // New variable for custom IP address, protocol, data format, and encryption method

    // Get user input for custom connection settings
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "------------------------------------\n";
    Set_Console_Color(FOREGROUND_RED, 0);
    cout << "[+] Custom Connection Settings Menu:\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "------------------------------------\n\n\n";
    Set_Console_Color(FOREGROUND_RED, 0);
    
    cout << "1. ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Enter the IP Address of your server machine: ";
    Set_Console_Color(FOREGROUND_RED, 0);
    cin >> IPAddress;
    cout << endl;

Set_Console_Color(FOREGROUND_RED, 0);
    cout << "2. ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Enter the Port number to listen for incoming connections: ";
    Set_Console_Color(FOREGROUND_RED, 0);
    cin >> PortNumber;
    cout << endl;
    
Set_Console_Color(FOREGROUND_RED, 0);
    cout << "3. ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Enter the protocol you want to use (TCP/UDP): ";
    Set_Console_Color(FOREGROUND_RED, 0);
    cin >> Protocol;
    cout << endl;

Set_Console_Color(FOREGROUND_RED, 0);
    cout << "4. ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Do you want to use encryption for Advanced Security? [Y/N]";
    Set_Console_Color(FOREGROUND_RED, 0);
    cin >> Encryption_Input;
    cout << endl;
    



    // String handling for encryption
    if (Encryption_Input == 'Y' || Encryption_Input == 'y') {
        Encryption = "Yes";
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        cout << "Choose Encryption Method (";Set_Console_Color(FOREGROUND_BLUE, 0);cout<<"AES";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"/";Set_Console_Color(FOREGROUND_PURPLE, 0);cout<<"cipher";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"/";Set_Console_Color(FOREGROUND_RED, 0);cout<<"3pledes";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"): ";
        Set_Console_Color(FOREGROUND_RED, 0);
		cin >> EncryptionMethod;
        cout << endl;
    } else if (Encryption_Input == 'N' || Encryption_Input == 'n') {
        Encryption = "No";
    } else {
    	Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Invalid input. Defaulting to no encryption.\n";
        Set_Console_Color(FOREGROUND_YELLOW, 0);
        Encryption = "No";
    }
Set_Console_Color(FOREGROUND_RED, 0);
    cout << "5. ";Set_Console_Color(FOREGROUND_YELLOW	, 0);cout<<"Do you want to use compression for data transfer? [Y/N]";
    Set_Console_Color(FOREGROUND_RED, 0);
	cin >> Compression_Input;
    cout << endl;

    // String handling for compression
    if (Compression_Input == 'Y' || Compression_Input == 'y') {
        Compression = "Yes";
    } else if (Compression_Input == 'N' || Compression_Input == 'n') {
        Compression = "No";
    } else {
    	Set_Console_Color(FOREGROUND_RED, 0);
        cout << "Invalid input. Defaulting to no compression.\n";
        Set_Console_Color(FOREGROUND_YELLOW	, 0);
        Compression = "No";
    }

Set_Console_Color(FOREGROUND_RED, 0);
    cout << "6. ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Enter waiting timeout for client connection (in seconds): ";
    Set_Console_Color(FOREGROUND_RED, 0);
	cin >> Timeout;
    cout << endl;

    //cout << "7. Enter the maximum number of connections allowed: ";
    //cin >> MaxConnections;
    //cout << endl;

Set_Console_Color(FOREGROUND_RED, 0);
    cout << "7. ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Enter the buffer size for data transfer (in bytes): ";
    Set_Console_Color(FOREGROUND_RED, 0);
	cin >> BufferSize;
    cout << endl;

    //cout << "9. Enter the format of data (JSON/XML/Custom): ";
    //cin >> DataFormat;
    //cout << endl;


    // Display the custom connection settings
    cout << "---------------------------------\n";
    Set_Console_Color(FOREGROUND_RED, 0);
    cout << "[+] Custom Connection Parameters:\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "---------------------------------\n\n\n";
    
    Set_Console_Color(FOREGROUND_RED, 0);
    cout << "-> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"IP Address: ";Set_Console_Color(FOREGROUND_RED, 0);cout << IPAddress << endl;
    cout << "-> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Port Number: ";Set_Console_Color(FOREGROUND_RED, 0);cout << PortNumber << endl;
    cout << "-> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Protocol: " ;Set_Console_Color(FOREGROUND_RED, 0);cout<< Protocol << endl;
    cout << "-> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Encryption: " ;Set_Console_Color(FOREGROUND_RED, 0);cout<< Encryption << endl;
    if (Encryption == "Yes") {
        cout << "-> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Encryption Method: " ;Set_Console_Color(FOREGROUND_RED, 0);cout<< EncryptionMethod << endl;
    }
    cout << "-> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Compression: " ;Set_Console_Color(FOREGROUND_RED, 0);cout<< Compression << endl;
    cout << "-> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Timeout: " ;Set_Console_Color(FOREGROUND_RED, 0);cout<< Timeout << " seconds" << endl;
    //cout << "Max Connections: " << MaxConnections << endl;
    cout << "-> ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"Buffer Size: " ;Set_Console_Color(FOREGROUND_RED, 0);cout<< BufferSize << " bytes" << endl;
    //cout << "Data Format: " << DataFormat << endl;
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout<<"\nPress ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"Enter ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to enter communication channell: ";
getchar();
		while(getchar()!='\n'){
		}



    // Call your custom connection function with string parameters
    
    const char* myCStr = IPAddress.c_str();
    
    
     Server_Custom_Connection( myCStr,  PortNumber, Timeout,  Protocol,  Encryption_Input,  EncryptionMethod,  Compression_Input,  BufferSize );

    return 0; 
}





























// Function to display help/instructions ( Choice 4 from main menu )
int ChoiceFour(){
	
	while(true){
	
    system("cls");   //clear screen system function
    
    //Choice 4 Secopndary menu display and user input about choice acceptance
    Set_Console_Color(FOREGROUND_YELLOW, 0);   
    cout << "(!)";Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<" Help/Instruction Menu:\n\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "1. "; Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<"How to use this program.\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "2.";Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<" Troubleshooting bugs/issues.\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "3. "; Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<"Contact us.\n";
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "4.";Set_Console_Color(FOREGROUND_ORANGE, 0);cout<<" Return to main menu.\n\n";
    int choice;
    Set_Console_Color(FOREGROUND_YELLOW, 0);
    cout << "Enter your choice: ";
    Set_Console_Color(FOREGROUND_ORANGE, 0);
    

   // Loop until valid input is received
    while (true) {
        // Attempt to read an integer input
        cin >> choice;

        // Check if input operation failed (e.g., non-integer input)
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid integer." << endl;

            // Clear error flags and ignore incorrect input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Prompt user again for input
            cout << "Enter a choice: ";
        } else {
            // Input successful, break out of the loop
            break;
        }
    }

    // Process the valid input
    cout << "Valid choice entered: " << choice << endl;
  
    
    //If user enters 1 
    if(choice==1){
    	Set_Console_Color(DEFAULT_COLOR, 0);   //reser to default color ( in this modules defines )
    	UserHelpMod();   //call function to display helping message to user
	}
	//id user enters 2 
	else if(choice ==2){
		
		std::vector<std::string> bug_messages;
    std::string input;

    system("cls"); // Clear screen (platform-dependent)

    Set_Console_Color(14, 0); // Set console color to yellow (assuming 14 is yellow)
    std::cout << "SafeSocket Troubleshooting Page:\n\n";
    Set_Console_Color(12, 0); // Set console color to red (assuming 12 is red)
    std::cout << "Please submit the issue/bug you found here to help us solve it(q to quit):\n\n";

    Set_Console_Color(7, 0); // Reset console color to default (assuming 7 is white)

    while (true) {
        std::getline(std::cin, input);
        if (input == "q") {
        	Troubleshooting(bug_messages);
            break;
        }
        bug_messages.push_back(input); // Add the input string to the vector
    }


	}
	//if user enters 3 
	else if(choice==3){
		ContactSupport();   //call contact support function
	}
	//if user enters 4 
	else if(choice==4){
		cout<<"Exiting";
		Loading_dots();
		//return to main menu
		break;
		
		
	}
}
    
    return 0;
}




void Troubleshooting(const std::vector<std::string>& trouble_texts) {
  for (const auto& text : trouble_texts) {
    // Process each string in the vector, for example, print them
    std::cout << "Troubleshooting: " << text << std::endl;
    // Add more processing logic here as needed
}

//add legit email or github posting bug sending - reporting functionality
Set_Console_Color(FOREGROUND_YELLOW, 0);   //change console color to YELLOW
cout<<"\n\n\nIssue sent , thank you for informing us....\n\nfeel free to reoport this or any other isues to our Github repository:";Set_Console_Color(FOREGROUND_RED, 0);cout<<" https://github.com/PanagiotisKots/SafeSocket ";
Set_Console_Color(FOREGROUND_YELLOW, 0);
cout<<"\n\nPress enter to continue:  ";
getchar();
while(getchar()!='\n'){
}
}


//function that helps user to contact support 
void ContactSupport(){
	
	//add gotoxy box here and to all the menus in next update
	
	system("cls");   //clear console screen
	string choice;
	Set_Console_Color(FOREGROUND_YELLOW, 0);    //initialise copnsole color to YELLOW
	cout<<"Contact Support Options: \n\n";
	Set_Console_Color(FOREGROUND_RED, 0);   //make it red
	
	/*Secondary menu display of creators contact info and 
	more in different colors matching programs theme*/
	cout<<"1.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Email: ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"pkotsorgios654@gmail.com\n";
	
	cout<<"2.";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Github: ";Set_Console_Color(FOREGROUND_RED, 0);cout<<"https://github.com/PanagiotisKots/SafeSocket\n";
	
	cout<<"3.";	Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" Our Website: (gonna be updated soon!!!)\n\n";
	cout<<"You can also send a message to us directly through SafeScocket.\n";
	cout<<"Enter ";	Set_Console_Color(FOREGROUND_RED, 0);cout<<"'direct'";	Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" to send us message or";	Set_Console_Color(FOREGROUND_RED, 0);cout<<" 'exit'";	Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" to exit Contact Support menu: ";
		Set_Console_Color(FOREGROUND_RED, 0);
	cin>>choice;   //input taken from usrr 
		Set_Console_Color(FOREGROUND_YELLOW, 0); //change color again to YELLOW
		
		//Choiuce handling
	if(choice=="direct"){
		string direct_message;//needs to become array of strings
		cout<<"Enter message here:  ";//add functionality from troubleshootiung to send email or github direct ......
			Set_Console_Color(FOREGROUND_RED, 0);
		cin>>direct_message;
			Set_Console_Color(FOREGROUND_YELLOW, 0);
		
		cout<<"Thank you for the feedback, we will answer as soon as possible: \n\n";
		cout<<"press enter to exit: ";
		
		getchar();//function to get chasracter from user
	
		while(getchar()!='\n'){   //loop untill the takes one is '\n' (ENTER)
		}
		//if user enters exit as menu choice then exit page return to previous one 
	}else if(choice=="exit"){
        cout<<"Exiting";
		Loading_dots();
			Set_Console_Color(FOREGROUND_RED, 0);
	
	}
	
	
}
