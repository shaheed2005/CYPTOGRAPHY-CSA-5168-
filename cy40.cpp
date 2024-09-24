#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000
#define TOP_N 10

double letter_frequency[ALPHABET_SIZE] = {
    0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061,
    0.070, 0.001, 0.010, 0.040, 0.024, 0.067, 0.075, 0.019,
    0.000, 0.060, 0.063, 0.091, 0.028, 0.010, 0.025, 0.002,
    0.020, 0.000
};

void frequency_analysis(char *text, double *freq) {
    int total = 0;
    for (int i = 0; text[i]; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            freq[text[i] - 'A']++;
            total++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            freq[text[i] - 'a']++;
            total++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] /= total;
    }
}

double score_frequencies(double *freq) {
    double score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (freq[i] - letter_frequency[i]) * (freq[i] - letter_frequency[i]);
    }
    return score;
}

void decrypt_and_score(char *ciphertext, char *key, double *results, char possible_plaintexts[TOP_N][MAX_TEXT_LENGTH]) {
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        double freq[ALPHABET_SIZE] = {0};
        char decrypted[MAX_TEXT_LENGTH];
        for (int i = 0; ciphertext[i]; i++) {
            if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                decrypted[i] = (ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
            } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                decrypted[i] = (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
            } else {
                decrypted[i] = ciphertext[i];
            }
        }
        decrypted[strlen(ciphertext)] = '\0';
        frequency_analysis(decrypted, freq);
        double score = score_frequencies(freq);
        if (score < results[TOP_N - 1]) {
            results[TOP_N - 1] = score;
            strcpy(possible_plaintexts[TOP_N - 1], decrypted);
            for (int j = TOP_N - 1; j > 0 && results[j] < results[j - 1]; j--) {
                double temp_score = results[j];
                results[j] = results[j - 1];
                results[j - 1] = temp_score;

                char temp_text[MAX_TEXT_LENGTH];
                strcpy(temp_text, possible_plaintexts[j]);
                strcpy(possible_plaintexts[j], possible_plaintexts[j - 1]);
                strcpy(possible_plaintexts[j - 1], temp_text);
            }
        }
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    double results[TOP_N] = {1e6};
    char possible_plaintexts[TOP_N][MAX_TEXT_LENGTH];

    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    decrypt_and_score(ciphertext, "", results, possible_plaintexts);

    for (int i = 0; i < TOP_N; i++) {
        printf("Possible plaintext %d: %s, Score: %f\n", i + 1, possible_plaintexts[i], results[i]);
    }

    return 0;
}

