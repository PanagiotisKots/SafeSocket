//system libs
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <stdexcept> // For std::logic_error
#include <limits>
#include <vector>



//custom libs
#include "Sockets.h"
#include "Animations.h"
#include "Classes.h"
#include "Login.h"
#include "Utils.h"


#define FOREGROUND_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE)

//namespace standard
using namespace std;

//function declarations
void Troubleshooting(string trouble_text);
void ContactSupport();
void UserHelpMod();







Connection_Parameters con_par;











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



int ChoiceTwo(){
	
	system("cls");
	
	//add information gathering before calling the connection function from sockets.cpp
	
	MultipleServersConF();
	
	
	return 0;

	
}






int ChoiceThree() {
    system("cls"); 

    
    //add menus and input from user etc/////////////..............
    
    
 ScanConnF();

    return 0; 
}









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
  
    
    

    if(choice==1){
    	UserHelpMod();//call UserHelpMod function from bellow
	}
	else if(choice ==2){
			vector<std::string> bug_messages;
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
	else if(choice==3){
		ContactSupport();//prints info and gives extra details
	}
	else if(choice==4){
		return 0;//fix return to main menu bug
		
		
	}
    
}
    return 0;//end of function
}



void Troubleshooting(const std::vector<std::string>& trouble_texts) {
  for (const auto& text : trouble_texts) {
    // Process each string in the vector, for example, print them
    std::cout << "Message: " << text << std::endl;
    // Add more processing logic here as needed
}

//add legit email or github posting bug sending - reporting functionality
Set_Console_Color(FOREGROUND_YELLOW, 0);   //change console color to YELLOW
cout<<"\n\n\nIssue ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"sent";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<" , thank you for informing us....\n\nfeel ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"free ";Set_Console_Color(FOREGROUND_YELLOW, 0);cout<<"to report this or any other isues to our ";Set_Console_Color(FOREGROUND_PURPLE, 0);cout<<"Github repository:";Set_Console_Color(FOREGROUND_RED, 0);cout<<" https://github.com/PanagiotisKots/SafeSocket ";
Set_Console_Color(FOREGROUND_RED, FOREGROUND_INTENSITY);
cout<<"\n\nPress ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"enter";Set_Console_Color(FOREGROUND_RED, FOREGROUND_INTENSITY);cout<<" to continue:  ";

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
		string direct_message[50];
		cout<<"Enter message here (q to terminate message):  ";
		  Set_Console_Color(DEFAULT_COLOR, 0);
		  for(int i=0; i<50; i++){
		  	cin>>direct_message[i];
		  	if(direct_message[i]=="q"){
		  		break;
			  }
		  }
		cout<<endl<<endl;
		cout<<"Message: ";
		for(int i=0; i<50; i++){
			cout<<direct_message[i]<<" ";
			if(direct_message[i]=="\0"){
				break;
			}
		}
		
		Set_Console_Color(FOREGROUND_YELLOW, 0);
		cout<<endl<<"Thank you for the feedback, we will answer as soon as possible: \n\n";
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
		cout<<"Exiting Contact Suppport menu";
		for(int i=0; i<5; i++){
			cout<<".";
			Sleep(300);//add loading dots animations
		}
	
	}
	
	
}










//make these private using classes and all etc......

string UserHelp(){
	
	system("cls");
	  Set_Console_Color(FOREGROUND_YELLOW, 0);
	//Make it morre advanced 
		//message for user helpi
	string help = "*********************************************************************************\n"
                  "[+]  SafeSocket++ - Version 0.2\n"
                  "*********************************************************************************\n\n\n"
                  "[+] Overview\n\n"
                  "SafeSocket++ is a sophisticated Windows application designed to facilitate secure and efficient socket-based communication between servers and clients. \n"
				  "Whether you're managing network infrastructures, developing networked applications, or ensuring secure data transmission, SafeSocket++ provides the \n"
				  "tools and features necessary to streamline operations and enhance security.\n\n"
                  "From establishing reliable connections to implementing advanced encryption methods, SafeSocket++ empowers users with intuitive controls and robust \n"
				  "capabilities to manage network interactions effectively. This version represents a significant upgrade in both functionality and security, \n"
				  "making it an indispensable tool for professionals and enthusiasts alike.\n\n"
                  "[+] New Features\n\n" 
                  "Version 0.2 introduces several groundbreaking features:\n"
                  "* Cipher Encryption inside the communication channel: Safeguards sensitive data by encrypting communication channels, \n"
				  "ensuring confidentiality and integrity throughout transmissions.\n"
                  "* Settings option in the main menu for better user control of the program: Allows customization of various \n"
				  "aspects of SafeSocket++, enhancing flexibility and user experience.\n"
                  "* Enhanced safety and error handling, including crash safety: Implements robust protocols to handle errors gracefully \n"
				  "and prevent crashes, ensuring uninterrupted operation under varying conditions.\n"
                  "* Ability to handle multiple connections to servers: Supports simultaneous connections from multiple servers, \n"
				  "optimizing resource management and scalability in network environments.\n\n"
                  "[+] How It Can Help\n\n"
                  "SafeSocket++ - Version 0.2 offers significant benefits:\n"
                  "- **Enhanced Security**: By integrating cipher encryption, SafeSocket++ protects sensitive data from unauthorized access, \n"
				  "ensuring secure communications over networks.\n"
                  "- **Improved Efficiency**: The ability to manage multiple server connections and customizable settings streamlines network operations, \n"
				  "boosting efficiency in managing network resources.\n"
                  "- **Reliability and Stability**: With enhanced error handling and crash safety features, SafeSocket++ maintains stability even \n"
				  "under challenging network conditions, minimizing downtime and ensuring continuous operation.\n"
                  "- **Learning and Development**: Ideal for both beginners and advanced users, SafeSocket++ serves as a learning tool \n"
				  "for understanding network programming concepts and implementing robust solutions in C++.\n\n"
                  "Whether you're securing critical data transmissions, optimizing network perform ance, or expanding your knowledge of network programming, \n"
				  "SafeSocket++ - Version 0.2 equips you with the tools and capabilities to achieve your goals effectively and securely.\n\n\n\n"
                  "[+] How To use:\n\n"
                  "From the main menu Choose option 1 to connect your machine(client) , to another one (server) and open a chat room untill someone exits.\n"
                  "You will be redirected to a page where the programm will ask to fil in some details for the connection to take as parameters.\n"
                  "At first, you have to enter your machines IP ADDRESS (ipconfig in cmd) ex. 192.168.1.8 , then you will have to enter the port number for the connection,\n"
                  "ex. 4040((!)Dont go very low in port numbers), then if you want to have encryption in the channel while communicating where you enter Y for Yes and N for NO.\n"
                  "When a server is already loistening, for clients, you will automatically get redirected to the live session of the chat betwen the 2 machines\n"
                  "and you can freelly start sending and recieving messages.\n\n"
                  "In the same way, you can choose the multiple connection which has some extra features but with the ssme logic as the single one. (!)You will have to be able to know how to handle\n"
                  "multiple server conns at the same time though.\n\n\n"
                  "[+] Stay Tuned\n\n\n"
                  "In SafeSocket's++ Github repo the code will keep getting better and better and new versions with more functionalities and options are gonna be posted soon. \nHope you enjoy!!!\n\nHappy Coding fellow programmers :)";
	
	

	return help;
	
}

//function that dusplayes the message of UserHelp in animative format
void UserHelpMod(){
	
	string o = UserHelp();
	for(int i=0; i<o.length(); i++){
		Sleep(5);
		cout<<o[i];
	}
	Set_Console_Color(DEFAULT_COLOR, 0);
		cout<<"\n\nPress enter to return: ";
	getchar();
	while(getchar()!='\n'){
	}
}
