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

void frequency_analysis(char *ciphertext, double *freq) {
    int total = 0;
    for (int i = 0; ciphertext[i]; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            freq[ciphertext[i] - 'A']++;
            total++;
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            freq[ciphertext[i] - 'a']++;
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

void decrypt_and_score(char *ciphertext, char *key, double *results, int *best_keys) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double freq[ALPHABET_SIZE] = {0};
        char decrypted[MAX_TEXT_LENGTH];
        for (int j = 0; ciphertext[j]; j++) {
            if (ciphertext[j] >= 'A' && ciphertext[j] <= 'Z') {
                decrypted[j] = (ciphertext[j] - 'A' - i + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
            } else if (ciphertext[j] >= 'a' && ciphertext[j] <= 'z') {
                decrypted[j] = (ciphertext[j] - 'a' - i + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
            } else {
                decrypted[j] = ciphertext[j];
            }
        }
        decrypted[strlen(ciphertext)] = '\0';
        frequency_analysis(decrypted, freq);
        double score = score_frequencies(freq);
        if (score < results[TOP_N - 1]) {
            results[TOP_N - 1] = score;
            best_keys[TOP_N - 1] = i;
            for (int k = TOP_N - 1; k > 0 && results[k] < results[k - 1]; k--) {
                double temp_score = results[k];
                results[k] = results[k - 1];
                results[k - 1] = temp_score;

                int temp_key = best_keys[k];
                best_keys[k] = best_keys[k - 1];
                best_keys[k - 1] = temp_key;
            }
        }
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    double results[TOP_N] = {1e6};
    int best_keys[TOP_N] = {0};

    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    
    decrypt_and_score(ciphertext, "", results, best_keys);

    for (int i = 0; i < TOP_N; i++) {
        printf("Possible key: %d, Score: %f\n", best_keys[i], results[i]);
    }

    return 0;
}

