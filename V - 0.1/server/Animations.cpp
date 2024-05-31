/*This module contains all the animative like functions windows 
or not that are included in the current programm */

//system libs
#include <iostream>
#include <windows.h>


//namespaces
using namespace std;            //use namespace standard for better code readability and overall simplicity


/***************************************************************************
BOTH ANIMATIVE FUNCTIONS MENTIONED BELLOW {Set_Console_Color,SetConsoleFont} 
ARE FROM THE WINDOWS.H LIBRARY AND USE ALREADY
EXIOSTING WINDOWS FUNCTIUONS SPECIFICALLY FOIIR CONSOLE MANIPULATIVE ACTIONS.
****************************************************************************/



// Function to change the console text color by taking two parameters for it (console color manipulation)
void Set_Console_Color(WORD foreground, WORD background) {
    // Get the handle to the standard output device (console)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set the console text attributes (color) by combining foreground and background color values
    SetConsoleTextAttribute(hConsole, foreground | background);
}



//windows function for console text size manipultation
void SetConsoleFont(int fontSize){
	
    // Define a CONSOLE_FONT_INFOEX structure
    CONSOLE_FONT_INFOEX cfi;
    // Set the size of the structure
    cfi.cbSize = sizeof(cfi);
    // Set the font index to 0
    cfi.nFont = 0;
    // Set the width of each character in the font (0 for automatic)
    cfi.dwFontSize.X = 0;
    // Set the height of each character in the font (in pixels) based on the parameter
    cfi.dwFontSize.Y = fontSize;
    // Specify the font family (0 for default)
    cfi.FontFamily = FF_DONTCARE;
    // Specify the font weight (400 for normal)
    cfi.FontWeight = FW_NORMAL;
    // Copy the face name of the font to be used
    wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    // Set the console font using SetCurrentConsoleFontEx
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}



//add loading and texta nimations here from login pagfe
