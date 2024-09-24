#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long generateK(unsigned long long q) {
    return rand() % (q - 1) + 1;
}

void dsaSign(unsigned long long p, unsigned long long q, unsigned long long g, unsigned long long x, unsigned long long m, unsigned long long *r, unsigned long long *s) {
    unsigned long long k = generateK(q);
    *r = modExp(g, k, p) % q;
    *s = (modExp(k, q - 2, q) * (m + x * *r)) % q;
}

void rsaSign(unsigned long long e, unsigned long long d, unsigned long long n, unsigned long long m, unsigned long long *signature) {
    *signature = modExp(m, d, n);
}

int main() {
    srand(time(NULL));

    unsigned long long p = 23, q = 11, g = 5, x = 6, m = 15; 
    unsigned long long r1, s1, r2, s2;

    dsaSign(p, q, g, x, m, &r1, &s1);
    dsaSign(p, q, g, x, m, &r2, &s2);

    unsigned long long rsaSignature;
    unsigned long long e = 7, d = 15, n = 33; 
    rsaSign(e, d, n, m, &rsaSignature);

    printf("DSA Signatures:\n");
    printf("Signature 1: (r: %llu, s: %llu)\n", r1, s1);
    printf("Signature 2: (r: %llu, s: %llu)\n", r2, s2);
    printf("\nRSA Signature:\n");
    printf("Signature: %llu\n", rsaSignature);

    return 0;
}

