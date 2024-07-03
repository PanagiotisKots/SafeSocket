//system libs
#include <iostream>
#include <windows.h>


//namespaces 
using namespace std;

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
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    // Set the console font using SetCurrentConsoleFontEx
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
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


