#include <stdio.h>
#include <stdint.h>

uint64_t permute(uint64_t k, const int* table, int size) {
    uint64_t perm = 0;
    for (int i = 0; i < size; i++) {
        perm |= ((k >> (64 - table[i])) & 1) << (size - 1 - i);
    }
    return perm;
}

uint32_t rotate_left(uint32_t k, int shifts) {
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

uint64_t feistel_function(uint32_t half, uint64_t key) {
    int expansion[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11,
                         12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21,
                         20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29,
                         30, 31, 32, 1};

    int s_boxes[8][64] = {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 12, 4, 11, 8, 5, 15},
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5}
    };

    half = permute(half, expansion, 48) ^ key;

    uint64_t result = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((half >> (42 - i * 6)) & 0x20) | ((half >> (42 - i * 6 + 5)) & 0x01);
        int col = (half >> (42 - i * 6 + 1)) & 0x0F;
        result |= (uint64_t)s_boxes[i][row * 16 + col] << (28 - i * 4);
    }

    return result;
}

uint64_t des_encrypt(uint64_t plaintext, uint64_t* subkeys) {
    int initial_perm[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

    int inverse_perm[64] = {40, 8, 48, 16, 56, 24, 32, 0, 30, 62, 22, 14, 50, 52, 60, 38,
                             2, 36, 12, 28, 46, 54, 18, 34, 44, 10, 4, 20, 26, 58, 42, 48,
                             36, 6, 52, 38, 18, 54, 22, 32, 44, 0, 62, 26, 14, 10, 8, 20,
                             12, 58, 40, 56, 28, 52, 30, 46, 24, 16, 60, 2, 34, 42, 4, 6};

    plaintext = permute(plaintext, initial_perm, 64);
    uint32_t left = plaintext >> 32;
    uint32_t right = plaintext & 0xFFFFFFFF;

    for (int i = 0; i < 16; i++) {
        uint32_t temp = right;
        right = left ^ feistel_function(right, subkeys[i]);
        left = temp;
    }

    uint64_t pre_output = ((uint64_t)left << 32) | right;
    return permute(pre_output, inverse_perm, 64);
}

int main() {
    uint64_t key = 0x0123456789ABCDEF;
    uint64_t plaintext = 0x1234567890ABCDEF;
    uint64_t subkeys[16];

    generate_keys(key, subkeys);
    uint64_t ciphertext = des_encrypt(plaintext, subkeys);

    printf("Encrypted text: %016llX\n", ciphertext);
    return 0;
}

