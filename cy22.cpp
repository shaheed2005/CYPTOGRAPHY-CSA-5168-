#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

uint8_t sdes_encrypt(uint8_t plaintext, uint8_t key);
uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t key);

uint8_t xor_blocks(uint8_t block1, uint8_t block2) {
    return block1 ^ block2;
}

void cbc_encrypt(uint8_t *plaintext, size_t len, uint8_t key, uint8_t iv, uint8_t *ciphertext) {
    uint8_t previous_block = iv; 
    for (size_t i = 0; i < len; i++) {
        uint8_t current_block = plaintext[i];
        current_block = xor_blocks(current_block, previous_block); 
        ciphertext[i] = sdes_encrypt(current_block, key); 
        previous_block = ciphertext[i]; 
    }
}

void cbc_decrypt(uint8_t *ciphertext, size_t len, uint8_t key, uint8_t iv, uint8_t *plaintext) {
    uint8_t previous_block = iv; 
    for (size_t i = 0; i < len; i++) {
        uint8_t current_block = ciphertext[i];
        uint8_t decrypted_block = sdes_decrypt(current_block, key); 
        plaintext[i] = xor_blocks(decrypted_block, previous_block); 
        previous_block = ciphertext[i];
    }
}

uint8_t sdes_encrypt(uint8_t plaintext, uint8_t key) {

    return (plaintext + key) % 256; 
}

uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t key) {
    
    return (ciphertext - key + 256) % 256; 
}

int main() {
    
    uint8_t key = 0b0111111101; 
    uint8_t iv = 0b10101010; 
    uint8_t plaintext[] = {0b00000001, 0b00010011}; 
    size_t len = sizeof(plaintext) / sizeof(plaintext[0]);
    uint8_t ciphertext[len];
    uint8_t decrypted[len];

    cbc_encrypt(plaintext, len, key, iv, ciphertext);
    printf("Ciphertext:\n");
    for (size_t i = 0; i < len; i++) {
        printf("%08b\n", ciphertext[i]);
    }

    cbc_decrypt(ciphertext, len, key, iv, decrypted);
    printf("\nDecrypted plaintext:\n");
    for (size_t i = 0; i < len; i++) {
        printf("%08b\n", decrypted[i]);
    }

    return 0;
}
