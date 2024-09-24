
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5
#define MAX_TEXT_SIZE 100

int main() {
    char key[MAX_TEXT_SIZE], plaintext[MAX_TEXT_SIZE], preparedText[MAX_TEXT_SIZE], ciphertext[MAX_TEXT_SIZE];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    int i, j, k = 0, len;
    char ch;
    int r1, r2, c1, c2;
    int used[26] = {0};

   
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 
    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; 
        if (isalpha(ch) && !used[ch - 'A']) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            ch = 'A' + i;
            if (ch == 'J') ch = 'I'; 
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = ch;
            k++;
        }
    }

    
    printf("Enter the plaintext (letters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    k = 0;
    len = strlen(plaintext);
    for (i = 0; i < len; i++) {
        ch = toupper(plaintext[i]);
        if (isalpha(ch)) {
            if (ch == 'J') ch = 'I'; 
            preparedText[k++] = ch;
        }
    }
    if (k % 2 != 0) {
        preparedText[k++] = 'X'; 
    }
    preparedText[k] = '\0';

    
    len = strlen(preparedText);
    for (i = 0; i < len; i += 2) {
        char a = preparedText[i];
        char b = preparedText[i + 1];

        
        for (r1 = 0; r1 < MATRIX_SIZE; r1++) {
            for (c1 = 0; c1 < MATRIX_SIZE; c1++) {
                if (matrix[r1][c1] == a) break;
            }
            if (c1 < MATRIX_SIZE) break;
        }
        for (r2 = 0; r2 < MATRIX_SIZE; r2++) {
            for (c2 = 0; c2 < MATRIX_SIZE; c2++) {
                if (matrix[r2][c2] == b) break;
            }
            if (c2 < MATRIX_SIZE) break;
        }

        
        if (r1 == r2) { 
            ciphertext[i] = matrix[r1][(c1 + 1) % MATRIX_SIZE];
            ciphertext[i + 1] = matrix[r2][(c2 + 1) % MATRIX_SIZE];
        } else if (c1 == c2) {
            ciphertext[i] = matrix[(r1 + 1) % MATRIX_SIZE][c1];
            ciphertext[i + 1] = matrix[(r2 + 1) % MATRIX_SIZE][c2];
        } else { 
            ciphertext[i] = matrix[r1][c2];
            ciphertext[i + 1] = matrix[r2][c1];
        }
    }
    ciphertext[len] = '\0';

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}

