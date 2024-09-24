#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void create_matrix(const char *keyword, char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    int k = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            if (ch == 'J') {
                ch = 'I';
            }
            used[ch - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            if (ch == 'J') continue;
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
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

void decrypt_playfair(const char *ciphertext, char *plaintext, char matrix[SIZE][SIZE]) {
    int len = strlen(ciphertext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];

        int row1, col1, row2, col2;
        find_position(a, &row1, &col1, matrix);
        find_position(b, &row2, &col2, matrix);

        if (row1 == row2) {
            plaintext[index++] = matrix[row1][(col1 + SIZE - 1) % SIZE];
            plaintext[index++] = matrix[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            plaintext[index++] = matrix[(row1 + SIZE - 1) % SIZE][col1];
            plaintext[index++] = matrix[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            plaintext[index++] = matrix[row1][col2];
            plaintext[index++] = matrix[row2][col1];
        }
    }
    plaintext[index] = '\0';
}

int main() {
    const char *keyword = "PLAYFAIR"; 
    char matrix[SIZE][SIZE];
    create_matrix(keyword, matrix);

    const char *ciphertext = "KXJEYUREBEZWEHEWRYTUBEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[1000];

    decrypt_playfair(ciphertext, plaintext, matrix);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

