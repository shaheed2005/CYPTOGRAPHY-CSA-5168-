#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 100

int main() {
    char plaintext[MAX_TEXT_SIZE], key[MAX_TEXT_SIZE], ciphertext[MAX_TEXT_SIZE];
    int keyLen, textLen, i, keyIndex = 0;
    char ch;
    
    
    printf("Enter the plaintext (letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    
    printf("Enter the key (letters only): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    keyLen = strlen(key);
    textLen = strlen(plaintext);

    
    for (i = 0; i < textLen; i++) {
        ch = plaintext[i];
        if (isalpha(ch)) {
            char keyChar = toupper(key[keyIndex % keyLen]); 
            int shift = keyChar - 'A'; 
            if (isupper(ch)) {
                ciphertext[i] = (ch - 'A' + shift) % 26 + 'A';
            } else if (islower(ch)) {
                ciphertext[i] = (ch - 'a' + shift) % 26 + 'a';
            }
            keyIndex++; 
        } else {
            ciphertext[i] = ch; 
        }
    }
    ciphertext[textLen] = '\0'; 
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
