#ifndef UTILS_H
#define UTILS_H


#include "Classes.h"

//namespoace standard for string data type usage
using namespace std;

//function declarations
bool validateLogin(const Sup& sup, const string& username, const string& password);//fix this

void loginpage();

void Loading_Login_Animation_Function(const int totalProgress, const string& loadingText, const int delay);

void Loading_Components_Animation() ;

void Initialising_Programm_Animation();

void Preparing_To_Launch_Animation();

void clearLineToCursor();

int ChoiceOne();

int ChoiceTwo();

int ChoiceThree();

int ChoiceFour();

void Troubleshooting(string trouble_text);

void ContactSupport();

string UserHelp();

void UserHelpMod();

void choiceFive();

#endif
