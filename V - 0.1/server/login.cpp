//system libs
#include <iostream>
#include <string>
#include <windows.h>


//custom libs
#include "login.h"
#include "Animations.h"
#include "Classes.h"


//defines
#define FOREGROUND_LIGHTER_BLUE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)

//namespaces
using namespace std;


//function declarations
void Loading_Login_Animation_Function(const int totalProgress, const std::string& loadingText, const int delay);
void clearLineToCursor();


//object creted for User 
User user;




// Validation logic function
bool validateLogin(const string& username, const string& password) {
    // Valid credentials
    return (user.username == "admin" && user.password == "pass");
}




//login function
void lpg(){
	
	int counts=3;
	do{
     //Set_Console_Color(FOREGROUND_BLUE, FOREGROUND_INTENSITY);
    // Username input
    cout << "Username: ";
    //Set_Console_Color(FOREGROUND_LIGHTER_BLUE, 0);
    cin >> user.username;

    // Password input
    //Set_Console_Color(FOREGROUND_BLUE, FOREGROUND_INTENSITY);
    cout << "Password: ";
    // Set_Console_Color(FOREGROUND_LIGHTER_BLUE, 0);
    cin >> user.password;



    // Check credentials
    if (validateLogin(user.username, user.password)) {
    	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
        cout << endl <<"Login successful. Welcome " << user.username << "!" << endl<<endl<<endl<<endl<<endl<<endl<<endl;
        Set_Console_Color(DEFAULT_COLOR, 0);
        Loading_Components_Animation();
        clearLineToCursor();
        Initialising_Programm_Animation();
        //clearLineToCursor();
        //Preparing_To_Launch();
        Sleep(3000);
        Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
         cout<<"\n\n\nProgram ready!"<<endl<<endl<<endl<<endl;
         Sleep(1000);
         Set_Console_Color(DEFAULT_COLOR, 0);
        cout<<"Press ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"enter";Set_Console_Color(DEFAULT_COLOR, 0);cout<<" to launch SafeSocket: ";
        getchar();
        while(getchar()!='\n'){
        	
		}
        break;
    } else {
    	Set_Console_Color(FOREGROUND_RED, FOREGROUND_INTENSITY);
        cout << endl << "Login failed. Invalid username or password." << endl;
        counts--;
        if(counts==0){
        	cout<<"INTRUDER DETECTED exiting programm.....";
        	exit(0);
		}
        cout<<"\nWARNING(!)";cout<< counts<<" more attempts until you get flaged as INTRUDER.\n";
        Set_Console_Color(DEFAULT_COLOR, 0);
        // Further actions after failed login will be added here!!!!!!!!!!!!!!!
    }
}while(true);
}





//login page function for optic functionalities
void loginpage() {
    string login_choice;
    int count=3;
   //Set_Console_Color(FOREGROUND_BLUE, FOREGROUND_INTENSITY);
cout<<"Welcome to SafeSocket\n\nEnter 'Log' to login to your existing account or 'Sup' to create a new one:  ";
while(true){

cin>>login_choice;
if(login_choice=="Log"){
	cout<<"\nPlease Login bellow: \n\n\n";
	lpg();
	break;
}else if(login_choice=="Sup"){
	cout<<"Enter your credentials to create a new account with them bellow: \n\n\n";
	system("cls");
	user.get_credentials();
	string entered_username, entered_password;
    bool logged_in = false;
    cout<<"Please login bellow: \n\n\n";
    while (!logged_in) {
        cout << "Enter username: ";
        cin >> entered_username;
        cout << "Enter password: ";
        cin >> entered_password;
        
        if (user.check_credentials(entered_username, entered_password)) {
            cout << "Credentials are correct." << endl;
            logged_in = true;
            	Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
        cout << endl <<"Login successful. Welcome " << user.username << "!" << endl<<endl<<endl<<endl<<endl<<endl<<endl;
        Set_Console_Color(DEFAULT_COLOR, 0);
        Loading_Components_Animation();
        clearLineToCursor();
        Initialising_Programm_Animation();
        //clearLineToCursor();
        Sleep(3000);
        //Preparing_To_Launch_Animation();
        Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);
        cout<<"\n\n\nProgram ready!"<<endl<<endl<<endl<<endl;
        Sleep(1000);
        Set_Console_Color(DEFAULT_COLOR, 0);
        cout<<"Press ";Set_Console_Color(FOREGROUND_GREEN, FOREGROUND_INTENSITY);cout<<"enter";Set_Console_Color(DEFAULT_COLOR, 0);cout<<" to launch SafeSocket: ";
        getchar();
        while(getchar()!='\n'){
        	
		}
        break;
            
        } else {
        	Set_Console_Color(FOREGROUND_RED, FOREGROUND_INTENSITY);
            cout << "Incorrect username or password. Please try again: " << endl;
            count--;
            if(count==0){
            	cout<<"INTRUDER DETECTED, exiting program with 0 return value......";
            	exit(0);
			}
            cout<<"\nYou have "<<count<<" more attempts before you get flaged as INTRUFER.\n\n";
            Set_Console_Color(DEFAULT_COLOR, 0);
        }
    }
    
	break;
}else{
	cout<<"Invalid choice please enter ( Log | Sup ):  ";
    
}
}

}


//animations need to move from here to Animations.h and .cpp IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Loading_Login_Animation_Function(const int totalProgress, const std::string& loadingText, const int delay) {
    for (int progress = 0; progress <= totalProgress; ++progress) {
        cout << "\r" << loadingText << "[";
        for (int i = 0; i < totalProgress; ++i) {
            if (i < progress)
                cout << "="; // Fill the progress with =
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
//animations need to move from here to Animations.h and .cpp IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Loading_Components_Animation() {
    string loadingText = "Loading Components ";
    const int totalProgress = 50; // Total length of the progress bar
    const int delay = 60; // Delay between each step in milliseconds
    Loading_Login_Animation_Function(totalProgress, loadingText, delay);
    Sleep(1400);
}
//animations need to move from here to Animations.h and .cpp IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void Initialising_Programm_Animation() {
    string loadingText = "Initialising Programm ";
    const int totalProgress = 50; // Total length of the progress bar
    const int delay = 5; // Delay between each step in milliseconds
    Loading_Login_Animation_Function(totalProgress, loadingText, delay);
}

//animations need to move from here to Animations.h and .cpp IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void clearLineToCursor() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD cursorPos = csbi.dwCursorPosition;
    int lineLength = cursorPos.X + 1; // Adding 1 to account for zero-based indexing
    cout << "\r" << string(lineLength, ' ');
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos); // Restore cursor position
}


