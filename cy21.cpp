#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
#define NUM_BLOCKS 8

void block_encrypt(uint64_t *block, uint64_t key) {
    *block ^= key; 
}

void encrypt_ecb(uint8_t *plaintext, size_t len, uint64_t key, uint64_t *ciphertext) {
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        uint64_t block;
        memcpy(&block, &plaintext[i], BLOCK_SIZE);
        block_encrypt(&block, key);
        ciphertext[i / BLOCK_SIZE] = block;
    }
}

void encrypt_cbc(uint8_t *plaintext, size_t len, uint64_t key, uint64_t *ciphertext, uint64_t iv) {
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        uint64_t block;
        memcpy(&block, &plaintext[i], BLOCK_SIZE);
        block ^= iv; 
        block_encrypt(&block, key);
        ciphertext[i / BLOCK_SIZE] = block;
        iv = block; 
    }
}

void encrypt_cfb(uint8_t *plaintext, size_t len, uint64_t key, uint64_t *ciphertext, uint64_t iv) {
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        uint64_t block;
        block_encrypt(&iv, key); 
        memcpy(&block, &plaintext[i], BLOCK_SIZE);
        block ^= iv; 
        ciphertext[i / BLOCK_SIZE] = block;
        iv = ciphertext[i / BLOCK_SIZE]; 
    }
}

void print_hex(uint64_t value) {
    printf("%016lX\n", value);
}

int main() {
    uint8_t plaintext[BLOCK_SIZE * NUM_BLOCKS] = "Hello, World!"; 
    size_t len = strlen((char *)plaintext);
    
    if (len % BLOCK_SIZE != 0) {
        fprintf(stderr, "Plaintext length must be a multiple of block size.\n");
        return 1;
    }

    uint64_t key = 0x133457799BBCDFF1; 
    uint64_t iv = 0x0123456789ABCDEF; 
    uint64_t ciphertext[NUM_BLOCKS];

    printf("ECB Ciphertext:\n");
    encrypt_ecb(plaintext, len, key, ciphertext);
    for (size_t i = 0; i < NUM_BLOCKS; i++) {
        print_hex(ciphertext[i]);
    }

    printf("\nCBC Ciphertext:\n");
    memset(ciphertext, 0, sizeof(ciphertext)); 
    encrypt_cbc(plaintext, len, key, ciphertext, iv);
    for (size_t i = 0; i < NUM_BLOCKS; i++) {
        print_hex(ciphertext[i]);
    }

    printf("\nCFB Ciphertext:\n");
    memset(ciphertext, 0, sizeof(ciphertext)); 
    encrypt_cfb(plaintext, len, key, ciphertext, iv);
    for (size_t i = 0; i < NUM_BLOCKS; i++) {
        print_hex(ciphertext[i]);
    }

    return 0;
}
