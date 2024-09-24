#include <stdio.h>
#include <stdlib.h>

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

int main() {
    unsigned long long a, q, xAlice, xBob, A, B, keyAlice, keyBob;

    printf("Enter public base (a): ");
    scanf("%llu", &a);
    printf("Enter prime modulus (q): ");
    scanf("%llu", &q);
    printf("Enter Alice's secret number (x): ");
    scanf("%llu", &xAlice);
    printf("Enter Bob's secret number (x): ");
    scanf("%llu", &xBob);

    A = modExp(a, xAlice, q);
    B = modExp(a, xBob, q);

    keyAlice = modExp(B, xAlice, q);
    keyBob = modExp(A, xBob, q);

    printf("Alice sends A = %llu\n", A);
    printf("Bob sends B = %llu\n", B);
    printf("Alice's computed key: %llu\n", keyAlice);
    printf("Bob's computed key: %llu\n", keyBob);

    return 0;
}

