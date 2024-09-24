#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

void calculate_frequency(const char *ciphertext, double frequency[ALPHABET_SIZE]) {
    int letter_count[ALPHABET_SIZE] = {0};
    int total_letters = 0;

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            letter_count[ciphertext[i] - 'a']++;
            total_letters++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i] = (double)letter_count[i] / total_letters * 100.0;
    }
}

void decrypt_with_shift(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int compare_frequencies(const void *a, const void *b) {
    return (*(double *)b - *(double *)a);
}

void generate_possible_plaintexts(const char *ciphertext, int top_n) {
    char plaintext[100];
    double frequencies[ALPHABET_SIZE];
    double expected_freq[ALPHABET_SIZE] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
                                            0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
                                            2.758, 0.978, 2.360, 0.150, 1.929, 0.074};

    calculate_frequency(ciphertext, frequencies);

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt_with_shift(ciphertext, shift, plaintext);
        double score = 0;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            score += abs(frequencies[i] - expected_freq[i]);
        }

        printf("Shift %d: %s (Score: %.2f)\n", shift, plaintext, score);
    }
}

int main() {
    char ciphertext[100];
    int top_n;

    printf("Enter ciphertext (lowercase letters only): ");
    scanf("%s", ciphertext);
    printf("How many top possible plaintexts to display? ");
    scanf("%d", &top_n);

    generate_possible_plaintexts(ciphertext, top_n);

    return 0;
}

