#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int main() {
    char plaintext[100], ciphertext[100];
    char key[ALPHABET_SIZE + 1] = "QWERTYUIOPASDFGHJKLZXCVBNM";  
    char mapping[ALPHABET_SIZE];
    int i, j;

   
    if (strlen(key) != ALPHABET_SIZE) {
        printf("Key must be exactly 26 characters long.\n");
        return 1;
    }

   
    for (i = 0; i < ALPHABET_SIZE; i++) {
        mapping[i] = key[i];
    }

    
    printf("Enter the plaintext message (uppercase letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  
    
    i = 0;
    while (plaintext[i] != '\0') {
        char ch = plaintext[i];
        if (ch >= 'A' && ch <= 'Z') {
            ciphertext[i] = mapping[ch - 'A'];
        } else if (ch >= 'a' && ch <= 'z') {
            ciphertext[i] = mapping[ch - 'a'] + ('a' - 'A');
        } else {
            ciphertext[i] = ch;  
        }
        i++;
    }
    ciphertext[i] = '\0';  
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
