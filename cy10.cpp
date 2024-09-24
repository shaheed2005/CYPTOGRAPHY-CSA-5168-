#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void create_matrix(char matrix[SIZE][SIZE]) {
    char playfair_matrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    memcpy(matrix, playfair_matrix, sizeof(playfair_matrix));
}

void find_position(char ch, int *row, int *col, char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void preprocess_text(const char *input, char *output) {
    int index = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = toupper(input[i]);
        if (isalpha(ch)) {
            output[index++] = ch;
            if (i + 1 < strlen(input) && toupper(input[i + 1]) == ch) {
                output[index++] = 'X';
            }
        }
    }
    if (index % 2 != 0) {
        output[index++] = 'X';
    }
    output[index] = '\0';
}

void encrypt_playfair(const char *plaintext, char *ciphertext, char matrix[SIZE][SIZE]) {
    int index = 0;
    for (int i = 0; plaintext[i] != '\0'; i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];

        int row1, col1, row2, col2;
        find_position(a, &row1, &col1, matrix);
        find_position(b, &row2, &col2, matrix);

        if (row1 == row2) {
            ciphertext[index++] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[index++] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[index++] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[index++] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[index++] = matrix[row1][col2];
            ciphertext[index++] = matrix[row2][col1];
        }
    }
    ciphertext[index] = '\0';
}

int main() {
    char matrix[SIZE][SIZE];
    create_matrix(matrix);

    const char *message = "Must see you over Cadogan West. Coming at once.";
    char plaintext[1000];
    char ciphertext[1000];

    preprocess_text(message, plaintext);
    encrypt_playfair(plaintext, ciphertext, matrix);
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}

