//windows.h icluded for WORD type of data frojm windows
#include <windows.h>

//namespace usage for includison later
using namespace std;


//function decflarations
void Set_Console_Color(WORD foreground, WORD background);

void SetConsoleFont(int fontSize);









void Loading_Login_Animation_Function(const int totalProgress, const string& loadingText, const int delay);

void Loading_Components_Animation();

void Initialising_Programm_Animation();

void Preparing_To_Launch_Animation();

void clearLineToCursor();
