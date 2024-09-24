#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int extended_euclidean(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extended_euclidean(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int mod_inverse(int e, int phi) {
    int x, y;
    int g = extended_euclidean(e, phi, &x, &y);
    if (g != 1) {
        return -1;
    }
    return (x % phi + phi) % phi;
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q;

    for (p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    if (p * q != n) {
        printf("Failed to factor n.\n");
        return 1;
    }

    int phi = (p - 1) * (q - 1);
    int d = mod_inverse(e, phi);

    if (d == -1) {
        printf("Modular inverse does not exist.\n");
    } else {
        printf("Private key d: %d\n", d);
    }

    return 0;
}

