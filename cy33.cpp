#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 8
#define ROUNDS 16

uint8_t initialPermutation[64] = { /* IP table */ };
uint8_t finalPermutation[64] = { /* IP-1 table */ };
uint8_t expansion[48] = { /* Expansion table */ };
uint8_t sBoxes[8][64] = { /* S-Boxes */ };
uint8_t permutation[32] = { /* Permutation table */ };
uint8_t keySchedule[16][6]; // 16 subkeys

void generateKeys(uint8_t *key) {
    
}

void desFunction(uint8_t *halfBlock, uint8_t *subkey) {
    
}

void desEncrypt(uint8_t *input, uint8_t *output, uint8_t *key) {
    uint8_t block[BLOCK_SIZE];
    uint8_t left[4], right[4];
    generateKeys(key);
    
    for (int i = 0; i < 64; i++) {
        block[i / 8] |= (input[i / 8] >> (7 - (i % 8)) & 0x01) << (7 - initialPermutation[i]);
    }
    for (int round = 0; round < ROUNDS; round++) {
        
    }
    
}

void desDecrypt(uint8_t *input, uint8_t *output, uint8_t *key) {
    uint8_t block[BLOCK_SIZE];
    uint8_t left[4], right[4];
    generateKeys(key);
    
    for (int i = 0; i < 64; i++) {
        block[i / 8] |= (input[i / 8] >> (7 - (i % 8)) & 0x01) << (7 - initialPermutation[i]);
    }
    for (int round = ROUNDS - 1; round >= 0; round--) {
       
        
    }
    
}

int main() {
    uint8_t key[KEY_SIZE] = { /* 8 bytes key */ };
    uint8_t plaintext[BLOCK_SIZE] = { /* 8 bytes plaintext */ };
    uint8_t ciphertext[BLOCK_SIZE];
    uint8_t decrypted[BLOCK_SIZE];

    desEncrypt(plaintext, ciphertext, key);
    desDecrypt(ciphertext, decrypted, key);

    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\nDecrypted: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", decrypted[i]);
    }
    printf("\n");

    return 0;
}

