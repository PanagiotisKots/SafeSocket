#include <iostream>
#include <string>

using namespace std;

// Function to encrypt with caesar cipher
string encrypt(string message, int shift) {
    string result;
    for (char character : message) {
        if (isalpha(character)) {
            char shifted = character + shift;
            if (isupper(character)) {
                if (shifted > 'Z') {
                    shifted -= 26;
                } else if (shifted < 'A') {
                    shifted += 26;
                }
            } else {
                if (shifted > 'z') {
                    shifted -= 26;
                } else if (shifted < 'a') {
                    shifted += 26;
                }
            }
            result += shifted;
        } else {
            result += character;
        }
    }
    return result;
}

// Function to decrypt a message encrypted with the Caesar cipher
string decrypt(string message, int shift) {
	
	//same but with negative encryption
    return encrypt(message, -shift);
}



//the same way add aes to the project()from wincrypt
