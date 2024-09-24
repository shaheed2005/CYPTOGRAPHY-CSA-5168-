#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8

void xorBlocks(unsigned char *a, unsigned char *b, unsigned char *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void ecbEncrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
    }
}

void cbcEncrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext, int length, unsigned char *iv) {
    unsigned char previousBlock[BLOCK_SIZE] = {0};
    memcpy(previousBlock, iv, BLOCK_SIZE);
    
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        xorBlocks(plaintext + i, previousBlock, block);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        memcpy(previousBlock, ciphertext + i, BLOCK_SIZE);
    }
}

void cfbEncrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext, int length, unsigned char *iv) {
    unsigned char previousBlock[BLOCK_SIZE];
    memcpy(previousBlock, iv, BLOCK_SIZE);
    
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        memcpy(block, previousBlock, BLOCK_SIZE);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        xorBlocks(plaintext + i, block, ciphertext + i);
        memcpy(previousBlock, ciphertext + i, BLOCK_SIZE);
    }
}

void padMessage(unsigned char *input, int *length) {
    int originalLength = *length;
    input[originalLength] = 0x80; 
    for (int i = originalLength + 1; i < BLOCK_SIZE; i++) {
        input[i] = 0x00;
    }
    *length = originalLength + BLOCK_SIZE;
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    unsigned char plaintext[BLOCK_SIZE * 3] = "Hello!"; 
    unsigned char ciphertext[BLOCK_SIZE * 3] = {0};
    unsigned char iv[BLOCK_SIZE] = {0x00};

    int length = strlen((char *)plaintext);
    if (length % BLOCK_SIZE != 0) {
        padMessage(plaintext, &length);
    }

    ecbEncrypt(plaintext, key, ciphertext, length);
    printf("ECB Ciphertext: ");
    for (int i = 0; i < length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    memset(ciphertext, 0, sizeof(ciphertext));
    cbcEncrypt(plaintext, key, ciphertext, length, iv);
    printf("CBC Ciphertext: ");
    for (int i = 0; i < length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    memset(ciphertext, 0, sizeof(ciphertext));
    cfbEncrypt(plaintext, key, ciphertext, length, iv);
    printf("CFB Ciphertext: ");
    for (int i = 0; i < length; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

