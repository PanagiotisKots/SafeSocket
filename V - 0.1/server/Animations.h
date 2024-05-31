#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <windows.h> 
/***************************************************************
windows.h inluded here is needed for the WORD data type 
which is a windows one mentioned inside the original windows lib
****************************************************************/


//function declarations for other modules that require these function's usage
void SetConsoleFont(int fontSize);

void Set_Console_Color(WORD foreground, WORD background);

#endif
