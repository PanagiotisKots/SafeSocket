#ifndef LOGIN_H
#define LOGIN_H


//namespace for string usage
using namespace std;

//function declarations
bool validateLogin(const string& username, const string& password);

void loginpage();

void Loading_Login_Animation_Function(const int totalProgress, const string& loadingText, const int delay);

void Loading_Components_Animation();

void Initialising_Programm_Animation();

void Preparing_To_Launch_Animation();

void clearLineToCursor();

void lpg();

#endif 
