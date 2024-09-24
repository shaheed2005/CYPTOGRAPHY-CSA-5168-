#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    unsigned long long total_possible_keys = factorial(26); // 26!
    unsigned long long unique_keys = total_possible_keys / 2; // 26!/2! for I/J

    printf("Total possible keys: ~2^%llu\n", (unsigned long long)(log2(total_possible_keys)));
    printf("Effectively unique keys: ~%llu\n", unique_keys);

    return 0;
}

