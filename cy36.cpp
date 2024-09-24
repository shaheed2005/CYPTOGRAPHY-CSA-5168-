#include <stdio.h>
#include <string.h>

char encrypt(int a, int b, char p) {
    if (p >= 'A' && p <= 'Z') {
        return 'A' + (a * (p - 'A') + b) % 26;
    } else if (p >= 'a' && p <= 'z') {
        return 'a' + (a * (p - 'a') + b) % 26;
    }
    return p;
}

int main() {
    char plaintext[100];
    int a, b;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    printf("Enter values for a and b: ");
    scanf("%d %d", &a, &b);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        plaintext[i] = encrypt(a, b, plaintext[i]);
    }

    printf("Encrypted text: %s", plaintext);
    
    return 0;
}

