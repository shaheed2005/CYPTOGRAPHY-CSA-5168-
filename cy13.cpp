#include <stdio.h>
#include <string.h>

#define SIZE 2

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void find_matrix_inverse(int key[SIZE][SIZE], int inv[SIZE][SIZE]) {
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = (det % 26 + 26) % 26;
    int det_inv = mod_inverse(det, 26);

    inv[0][0] = (key[1][1] * det_inv) % 26;
    inv[0][1] = (-key[0][1] * det_inv) % 26;
    inv[1][0] = (-key[1][0] * det_inv) % 26;
    inv[1][1] = (key[0][0] * det_inv) % 26;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inv[i][j] = (inv[i][j] + 26) % 26;
        }
    }
}

void encrypt(const char *plaintext, int key[SIZE][SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        int p1 = plaintext[i] - 'a';
        int p2 = (i + 1 < len) ? plaintext[i + 1] - 'a' : 'x' - 'a';

        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;

        ciphertext[index++] = c1 + 'a';
        ciphertext[index++] = c2 + 'a';
    }
    ciphertext[index] = '\0';
}

void decrypt(const char *ciphertext, int inv_key[SIZE][SIZE], char *plaintext) {
    int len = strlen(ciphertext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        int c1 = ciphertext[i] - 'a';
        int c2 = (i + 1 < len) ? ciphertext[i + 1] - 'a' : 'x' - 'a';

        int p1 = (inv_key[0][0] * c1 + inv_key[0][1] * c2) % 26;
        int p2 = (inv_key[1][0] * c1 + inv_key[1][1] * c2) % 26;

        plaintext[index++] = p1 + 'a';
        plaintext[index++] = p2 + 'a';
    }
    plaintext[index] = '\0';
}

void known_plaintext_attack(int ciphertext_len, const char *ciphertext, const char *known_plaintext) {
    int key[SIZE][SIZE];
    printf("Performing known plaintext attack...\n");
}

int main() {
    char plaintext[] = "meetme";
    int key[SIZE][SIZE] = {{9, 4}, {5, 7}};
    char ciphertext[100];
    char decrypted[100];

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    int inv_key[SIZE][SIZE];
    find_matrix_inverse(key, inv_key);

    decrypt(ciphertext, inv_key, decrypted);
    printf("Decrypted message: %s\n", decrypted);

    known_plaintext_attack(strlen(ciphertext), ciphertext, plaintext);

    return 0;
}

