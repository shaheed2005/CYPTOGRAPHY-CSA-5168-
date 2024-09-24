#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16

void xorBlocks(unsigned char *a, const unsigned char *b) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        a[i] ^= b[i];
    }
}

void mockEncrypt(unsigned char *input, unsigned char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] + 1; 
    }
}

void cbcMac(unsigned char *key, unsigned char *message, unsigned char *mac) {
    unsigned char block[BLOCK_SIZE] = {0};
    unsigned char encrypted[BLOCK_SIZE];

    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] = message[i]; 
    }

    xorBlocks(block, key);
    mockEncrypt(block, encrypted);
    memcpy(mac, encrypted, BLOCK_SIZE);
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                      0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    unsigned char message[BLOCK_SIZE] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
                                          0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50}; 
    unsigned char mac[BLOCK_SIZE];

    cbcMac(key, message, mac);

    printf("MAC (T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\n");

    unsigned char adversaryMessage[2 * BLOCK_SIZE];
    memcpy(adversaryMessage, message, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        adversaryMessage[BLOCK_SIZE + i] = message[i] ^ mac[i];
    }

    unsigned char adversaryMac[BLOCK_SIZE];
    cbcMac(key, adversaryMessage, adversaryMac);

    printf("Adversary MAC (T'): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", adversaryMac[i]);
    }
    printf("\n");

    return 0;
}

