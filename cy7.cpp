#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256

void analyze_frequency(const char *ciphertext, int frequency[ALPHABET_SIZE]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        frequency[(unsigned char)ciphertext[i]]++;
    }
}

void print_frequency(int frequency[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("Character '%c': %d\n", i, frequency[i]);
        }
    }
}

void decrypt(const char *ciphertext, char *plaintext, char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = key[(unsigned char)ciphertext[i]];
    }
}

int main() {
    const char *ciphertext = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                             " (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                             " ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
                             " (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";

    int frequency[ALPHABET_SIZE] = {0};
    analyze_frequency(ciphertext, frequency);
    print_frequency(frequency);

    char key[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = (char)i;
    }

    key['5'] = 'E';
    key['3'] = 'T';
    key['8'] = 'H';
    key['0'] = 'O';
    key['1'] = 'A';
    key['2'] = 'R';
    key['6'] = 'N';

    char plaintext[1000];
    decrypt(ciphertext, plaintext, key);
    plaintext[strlen(ciphertext)] = '\0';

    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

