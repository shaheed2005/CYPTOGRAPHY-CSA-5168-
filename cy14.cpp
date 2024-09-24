#include <stdio.h>
#include <string.h>

void encrypt(const char *plaintext, const int *key, int key_len, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        int shift = key[i % key_len];
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

void decrypt(const char *ciphertext, const int *key, int key_len, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        int shift = key[i % key_len];
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = (ciphertext[i] - 'a' - shift + 26) % 26 + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

void find_key(const char *ciphertext, const char *plaintext, int *key, int key_len) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z' && plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            key[i % key_len] = (ciphertext[i] - 'a' - (plaintext[i] - 'a') + 26) % 26;
        }
    }
}

int main() {
    char plaintext[] = "sendmoremoney";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[100];
    int key[100] = {0};

    encrypt(plaintext, key_stream, sizeof(key_stream) / sizeof(key_stream[0]), ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    char target_plaintext[] = "cashnotneeded";
    find_key(ciphertext, target_plaintext, key, sizeof(key_stream) / sizeof(key_stream[0]));
    
    printf("Key for decryption: ");
    for (int i = 0; i < sizeof(key_stream) / sizeof(key_stream[0]); i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    char decrypted[100];
    decrypt(ciphertext, key, sizeof(key_stream) / sizeof(key_stream[0]), decrypted);
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}

