#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long modExp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void encryptMessage(char *message, unsigned long long e, unsigned long long n) {
    for (int i = 0; message[i] != '\0'; i++) {
        int plaintext = message[i] - 'A';
        unsigned long long ciphertext = modExp(plaintext, e, n);
        printf("%llu ", ciphertext);
    }
    printf("\n");
}

int main() {
    unsigned long long e = 65537;
    unsigned long long n = 253521; 
    char message[] = "HELLO";

    encryptMessage(message, e, n);
    return 0;
}

