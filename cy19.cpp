
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
#define NUM_KEYS 3

void generate_subkeys(uint64_t key, uint64_t subkeys[NUM_KEYS]);
void des_encrypt(uint64_t *block, uint64_t key);
void xor_blocks(uint64_t *block1, const uint64_t *block2);
void pad_plaintext(uint8_t *plaintext, size_t *len);
void print_hex(uint64_t value);

void des_encrypt(uint64_t *block, uint64_t key) {
   
}

void generate_subkeys(uint64_t key, uint64_t subkeys[NUM_KEYS]) {
    
}

void xor_blocks(uint64_t *block1, const uint64_t *block2) {
    *block1 ^= *block2;
}

void pad_plaintext(uint8_t *plaintext, size_t *len) {
    int pad_value = BLOCK_SIZE - (*len % BLOCK_SIZE);
    for (size_t i = *len; i < *len + pad_value; i++) {
        plaintext[i] = pad_value; 
    }
    *len += pad_value;
}

void encrypt_cbc(uint8_t *plaintext, size_t len, uint64_t iv, uint64_t keys[NUM_KEYS]) {
    uint64_t block;
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        memcpy(&block, &plaintext[i], BLOCK_SIZE);
        xor_blocks(&block, &iv);
        for (int j = 0; j < NUM_KEYS; j++) {
            des_encrypt(&block, keys[j]);
        }
        memcpy(&plaintext[i], &block, BLOCK_SIZE);
        iv = block; 
    }
}

void print_hex(uint64_t value) {
    printf("%016lX\n", value);
}

int main() {
    uint8_t plaintext[64] = "Hello, this is a message for 3DES CBC!"; 
    size_t len = strlen((char *)plaintext);
    pad_plaintext(plaintext, &len);

    uint64_t iv = 0x0123456789ABCDEF; 
    uint64_t key = 0x133457799BBCDFF1; 
    uint64_t keys[NUM_KEYS];

    generate_subkeys(key, keys);
    printf("Subkeys:\n");
    for (int i = 0; i < NUM_KEYS; i++) {
        print_hex(keys[i]);
    }

    encrypt_cbc(plaintext, len, iv, keys);
    printf("Ciphertext:\n");
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        print_hex(*(uint64_t *)&plaintext[i]);
    }

    return 0;
}
