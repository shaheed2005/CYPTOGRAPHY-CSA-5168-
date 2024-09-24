#include <stdio.h>

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    unsigned long long n, block;

    printf("Enter n (the modulus): ");
    scanf("%llu", &n);
    
    printf("Enter the plaintext block: ");
    scanf("%llu", &block);

    unsigned long long result = gcd(n, block);

    if (result > 1 && result < n) {
        printf("Common factor found: %llu\n", result);
    } else {
        printf("No non-trivial common factor found.\n");
    }

    return 0;
}

