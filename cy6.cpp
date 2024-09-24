#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void break_affine_cipher(const char *ciphertext, char most_freq, char second_freq) {
    int freq1 = most_freq - 'A';
    int freq2 = second_freq - 'A';

    for (int a = 1; a < 26; a++) {
        if (gcd(a, 26) == 1) {
            for (int b = 0; b < 26; b++) {
                int inv_a = mod_inverse(a, 26);
                if (inv_a == -1) continue;

                int p1 = (inv_a * (freq1 - b + 26)) % 26;
                int p2 = (inv_a * (freq2 - b + 26)) % 26;

                if (p1 == p2) {
                    printf("Possible key: a = %d, b = %d\n", a, b);
                    for (int i = 0; ciphertext[i] != '\0'; i++) {
                        char c = ciphertext[i];
                        if (c >= 'A' && c <= 'Z') {
                            int p = (inv_a * (c - 'A' - b + 26)) % 26;
                            printf("%c", p + 'A');
                        } else {
                            printf("%c", c);
                        }
                    }
                    printf("\n");
                }
            }
        }
    }
}

int main() {
    char ciphertext[100];
    printf("Enter the ciphertext (uppercase letters only): ");
    scanf("%s", ciphertext);
    break_affine_cipher(ciphertext, 'B', 'U');
    return 0;
}

