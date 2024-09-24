#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long modInverse(unsigned long long a, unsigned long long m) {
    a = a % m;
    for (unsigned long long x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return 0;
}

unsigned long long generatePrime() {
    return 61; 
}

void generateKeyPair(unsigned long long *n, unsigned long long *e, unsigned long long *d) {
    unsigned long long p = generatePrime();
    unsigned long long q = generatePrime();
    
    *n = p * q;
    unsigned long long phi = (p - 1) * (q - 1);
    
    *e = 65537; 
    *d = modInverse(*e, phi);
}

int main() {
    unsigned long long n, e, d;

    srand(time(0));
    generateKeyPair(&n, &e, &d);

    printf("New Public Key (n, e): (%llu, %llu)\n", n, e);
    printf("New Private Key (d): %llu\n", d);

    return 0;
}

