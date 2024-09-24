#include <stdio.h>
#include <ctype.h>
#include <string.h>

void caesarCipher(char *text, int shift, int encrypt) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isupper(ch)) {
            text[i] = ((ch - 'A' + (encrypt ? shift : -shift)) % 26 + 26) % 26 + 'A';
        } else if (islower(ch)) {
            text[i] = ((ch - 'a' + (encrypt ? shift : -shift)) % 26 + 26) % 26 + 'a';
        }
    }
}

int main() {
    char text[100];
    int shift;
    int choice;

    printf("Enter the shift value (1-25): ");
    scanf("%d", &shift);
    if (shift < 1 || shift > 25) {
        printf("Invalid shift value.\n");
        return 1;
    }

    printf("Enter 1 for encryption or 2 for decryption: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        return 1;
    }

    printf("Enter the text: ");
    getchar();
    fgets(text, sizeof(text), stdin);
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    caesarCipher(text, shift, choice == 1);

    printf("Result: %s\n", text);

    return 0;
}

