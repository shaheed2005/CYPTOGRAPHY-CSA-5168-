#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generate_cipher_sequence(const char *keyword, char *cipher) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
    cipher[index] = '\0';
}

void encrypt(const char *plaintext, const char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = toupper(plaintext[i]);
        if (isalpha(ch)) {
            ciphertext[i] = cipher[ch - 'A'];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(const char *ciphertext, const char *cipher, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (cipher[j] == ch) {
                    plaintext[i] = 'A' + j;
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char keyword[100], cipher[ALPHABET_SIZE + 1];
    printf("Enter the keyword: ");
    scanf("%s", keyword);
    generate_cipher_sequence(keyword, cipher);

    char plaintext[100], ciphertext[100], decrypted[100];
    printf("Enter plaintext: ");
    scanf(" %[^\n]s", plaintext);

    encrypt(plaintext, cipher, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, cipher, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

