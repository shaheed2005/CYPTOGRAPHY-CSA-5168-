#include <stdio.h>
#include <stdint.h>

uint64_t permute(uint64_t k, const int* table, int size) {
    uint64_t perm = 0;
    for (int i = 0; i < size; i++) {
        perm |= ((k >> (64 - table[i])) & 1) << (size - 1 - i);
    }
    return perm;
}

uint64_t rotate_left(uint64_t k, int shifts) {
    return ((k << shifts) | (k >> (28 - shifts))) & 0xFFFFFFFF;
}

void generate_keys(uint64_t key, uint64_t* subkeys) {
    int pc1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2,
                   59, 51, 43, 35, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37,
                   29, 21, 13, 5, 28, 20, 12, 4, 27, 19, 11, 3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15, 7};
    int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    int pc2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
                   26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
                   51, 45, 33, 48, 44, 49, 39, 56, 34, 24, 29, 1, 35, 10, 18, 36};

    key = permute(key, pc1, 56);
    uint32_t left = key >> 28;
    uint32_t right = key & 0xFFFFFFF;

    for (int i = 0; i < 16; i++) {
        left = rotate_left(left, shifts[i]);
        right = rotate_left(right, shifts[i]);
        subkeys[i] = permute((left << 28) | right, pc2, 48);
    }
}

uint64_t feistel_function(uint64_t half, uint64_t key) {
    int expansion[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11,
                         12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21,
                         20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29,
                         30, 31, 32, 1};
    int s_boxes[8][64] = { /* S-boxes here */ };
    
    half = permute(half, expansion, 48) ^ key;

    uint64_t result = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((half >> (42 - i * 6)) & 0x20) | ((half >> (42 - i * 6 + 5)) & 0x01);
        int col = (half >> (42 - i * 6 + 1)) & 0x0F;
        result |= (uint64_t)s_boxes[i][row * 16 + col] << (28 - i * 4);
    }

    return result;
}

uint64_t des_decrypt(uint64_t ciphertext, uint64_t* subkeys) {
    int initial_perm[64] = { /* Initial permutation table */ };
    int inverse_perm[64] = { /* Inverse permutation table */ };

    ciphertext = permute(ciphertext, initial_perm, 64);
    uint32_t left = ciphertext >> 32;
    uint32_t right = ciphertext & 0xFFFFFFFF;

    for (int i = 15; i >= 0; i--) {
        uint32_t temp = right;
        right = left ^ feistel_function(right, subkeys[i]);
        left = temp;
    }

    uint64_t pre_output = ((uint64_t)left << 32) | right;
    return permute(pre_output, inverse_perm, 64);
}

int main() {
    uint64_t key = 0x0123456789ABCDEF;
    uint64_t ciphertext = 0x133457799BBCDFF1;
    uint64_t subkeys[16];

    generate_keys(key, subkeys);
    uint64_t plaintext = des_decrypt(ciphertext, subkeys);

    printf("Decrypted text: %016llX\n", plaintext);
    return 0;
}

