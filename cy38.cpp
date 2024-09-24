#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2

void multiply_matrices(int a[SIZE][SIZE], int b[SIZE][1], int result[SIZE][1]) {
    for (int i = 0; i < SIZE; i++) {
        result[i][0] = 0;
        for (int k = 0; k < SIZE; k++) {
            result[i][0] += a[i][k] * b[k][0];
        }
        result[i][0] %= 26;
    }
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void inverse_matrix(int matrix[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    det = (det + 26) % 26;
    int inv_det = mod_inverse(det, 26);
    if (inv_det == -1) return;

    inverse[0][0] = (matrix[1][1] * inv_det) % 26;
    inverse[0][1] = (-matrix[0][1] * inv_det + 26) % 26;
    inverse[1][0] = (-matrix[1][0] * inv_det + 26) % 26;
    inverse[1][1] = (matrix[0][0] * inv_det) % 26;
}

void encrypt(char *plaintext, int key[SIZE][SIZE], char *ciphertext) {
    int block[SIZE][1];
    for (int i = 0; plaintext[i]; i += SIZE) {
        for (int j = 0; j < SIZE; j++) {
            if (plaintext[i + j] == '\0') break;
            block[j][0] = plaintext[i + j] - 'A';
        }
        int result[SIZE][1];
        multiply_matrices(key, block, result);
        for (int j = 0; j < SIZE; j++) {
            ciphertext[i + j] = result[j][0] + 'A';
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(char *ciphertext, int key[SIZE][SIZE], char *plaintext) {
    int inv_key[SIZE][SIZE];
    inverse_matrix(key, inv_key);
    int block[SIZE][1];
    for (int i = 0; ciphertext[i]; i += SIZE) {
        for (int j = 0; j < SIZE; j++) {
            if (ciphertext[i + j] == '\0') break;
            block[j][0] = ciphertext[i + j] - 'A';
        }
        int result[SIZE][1];
        multiply_matrices(inv_key, block, result);
        for (int j = 0; j < SIZE; j++) {
            plaintext[i + j] = result[j][0] + 'A';
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    int key[SIZE][SIZE] = {{6, 24}, {1, 13}};

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    char decrypted[100];
    decrypt(ciphertext, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

