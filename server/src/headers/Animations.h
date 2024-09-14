#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <windows.h> 
/***************************************************************
windows.h inluded here is needed for the WORD data type 
which is a windows one mentioned inside the original windows lib
****************************************************************/

using namespace std;

//function declarations for other modules that require these function's usage
void SetConsoleFont(int fontSize);

void Set_Console_Color(WORD foreground, WORD background);

void Loading_dots();






void Loading_Login_Animation_Function(const int totalProgress, const string& loadingText, const int delay);

void Loading_Components_Animation();

void Initialising_Programm_Animation();

void Preparing_To_Launch_Animation();

void clearLineToCursor();
#endif
