#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>

void encrypt(char *plaintext, int *key, int len) {
    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = 'A' + (plaintext[i] - 'A' + key[i]) % 26;
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = 'a' + (plaintext[i] - 'a' + key[i]) % 26;
        }
    }
}

int main() {
    char plaintext[100];
    int key[100];
    int len;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    len = strlen(plaintext);
    srand(time(NULL));
    for (int i = 0; i < len; i++) {
        key[i] = rand() % 26;
    }

    encrypt(plaintext, key, len);
    printf("Encrypted text: %s", plaintext);
    
    return 0;
}

