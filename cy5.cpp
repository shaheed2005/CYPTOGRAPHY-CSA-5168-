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

int is_valid_a(int a) {
    return gcd(a, 26) == 1;
}

char encrypt_char(int a, int b, char p) {
    if (p >= 'A' && p <= 'Z') {
        return (char)(((a * (p - 'A') + b) % 26) + 'A');
    }
    return p;  
}

void encrypt_text(int a, int b, const char *plaintext, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = encrypt_char(a, b, plaintext[i]);
    }
    ciphertext[strlen(plaintext)] = '\0';  
}

int main() {
    int a, b;
    char plaintext[100];
    char ciphertext[100];

    printf("Enter values for a (must be coprime to 26) and b (0-25): ");
    scanf("%d %d", &a, &b);

    if (!is_valid_a(a)) {
        printf("Invalid value for a. It must be coprime to 26.\n");
        return 1;
    }
    if (b < 0 || b > 25) {
        printf("Invalid value for b. It must be between 0 and 25.\n");
        return 1;
    }

    printf("Enter plaintext (uppercase letters only): ");
    scanf("%s", plaintext);

    encrypt_text(a, b, plaintext, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

