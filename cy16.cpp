#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

double expected_freq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.929, 0.074
};

void calculate_frequency(const char *text, double *frequency) {
    int letter_count[ALPHABET_SIZE] = {0};
    int total_letters = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            letter_count[text[i] - 'a']++;
            total_letters++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i] = (total_letters > 0) ? (double)letter_count[i] / total_letters * 100.0 : 0.0;
    }
}

void decrypt_with_key(const char *ciphertext, const char *key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = 'a' + (key[ciphertext[i] - 'a'] - 'a' + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

double score_plaintext(const char *plaintext) {
    double score = 0;
    double text_freq[ALPHABET_SIZE] = {0};
    calculate_frequency(plaintext, text_freq);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += fabs(text_freq[i] - expected_freq[i]);
    }

    return score;
}

void generate_keys(char keys[][ALPHABET_SIZE + 1], int *key_count) {
    char base_key[ALPHABET_SIZE + 1] = "abcdefghijklmnopqrstuvwxyz";
    int used[ALPHABET_SIZE] = {0};

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        used[i] = 0;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = i; j < ALPHABET_SIZE; j++) {
            if (i != j) {
                char temp = base_key[i];
                base_key[i] = base_key[j];
                base_key[j] = temp;

                strcpy(keys[*key_count], base_key);
                (*key_count)++;

                temp = base_key[i];
                base_key[i] = base_key[j];
                base_key[j] = temp;
            }
        }
    }
}

void frequency_attack(const char *ciphertext, int top_n) {
    char keys[100][ALPHABET_SIZE + 1];
    int key_count = 0;
    double scores[100];
    char decrypted[100][100];

    generate_keys(keys, &key_count);

    for (int i = 0; i < key_count; i++) {
        decrypt_with_key(ciphertext, keys[i], decrypted[i]);
        scores[i] = score_plaintext(decrypted[i]);
    }

    for (int i = 0; i < key_count - 1; i++) {
        for (int j = 0; j < key_count - i - 1; j++) {
            if (scores[j] > scores[j + 1]) {
                double temp_score = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp_score;

                char temp_text[100];
                strcpy(temp_text, decrypted[j]);
                strcpy(decrypted[j], decrypted[j + 1]);
                strcpy(decrypted[j + 1], temp_text);
            }
        }
    }

    printf("Top %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n && i < key_count; i++) {
        printf("Plaintext: %s (Score: %.2f)\n", decrypted[i], scores[i]);
    }
}

int main() {
    char ciphertext[100];
    int top_n;

    printf("Enter ciphertext (lowercase letters only): ");
    scanf("%s", ciphertext);
    printf("How many top possible plaintexts to display? ");
    scanf("%d", &top_n);

    frequency_attack(ciphertext, top_n);

    return 0;
}

