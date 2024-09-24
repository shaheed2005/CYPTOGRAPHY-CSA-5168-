#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

uint8_t sdes_encrypt(uint8_t plaintext, uint8_t key);
uint8_t sdes_decrypt(uint8_t ciphertext, uint8_t key);

uint8_t xor_blocks(uint8_t block1, uint8_t block2) {
    return block1 ^ block2;
}

void ctr_encrypt(uint8_t *plaintext, size_t len, uint8_t key, uint8_t *ciphertext) {
    uint8_t counter = 0; 
    for (size_t i = 0; i < len; i++) {
        uint8_t counter_block = counter++; 
        uint8_t encrypted_counter = sdes_encrypt(counter_block, key); 
        ciphertext[i] = xor_blocks(plaintext[i], encrypted_counter); 
    }
}

void ctr_decrypt(uint8_t *ciphertext, size_t len, uint8_t key, uint8_t *plaintext) {
    uint8_t counter = 0; 
    for (size_t i = 0; i < len; i++) {
        uint8_t counter_block = counter++; 
        uint8_t encrypted_counter = sdes_encrypt(counter_block, key); 
        plaintext[i] = xor_blocks(ciphertext[i], encrypted_counter); 
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
    uint8_t plaintext[] = {0b00000001, 0b00000010, 0b00000100}; 
    size_t len = sizeof(plaintext) / sizeof(plaintext[0]);
    uint8_t ciphertext[len];
    uint8_t decrypted[len];

    ctr_encrypt(plaintext, len, key, ciphertext);
    printf("Ciphertext:\n");
    for (size_t i = 0; i < len; i++) {
        printf("%08b\n", ciphertext[i]);
    }
    ctr_decrypt(ciphertext, len, key, decrypted);
    printf("\nDecrypted plaintext:\n");
    for (size_t i = 0; i < len; i++) {
        printf("%08b\n", decrypted[i]);
    }

    return 0;
}
