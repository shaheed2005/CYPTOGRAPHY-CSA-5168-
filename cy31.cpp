#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE_128 16
#define BLOCK_SIZE_64 8
#define ZERO_BLOCK_128 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#define ZERO_BLOCK_64 {0, 0, 0, 0, 0, 0, 0, 0}

void mockEncrypt(const unsigned char *input, unsigned char *output) {
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        output[i] = input[i] + 1;
    }
}

void leftShift(const unsigned char *input, unsigned char *output, int blockSize) {
    int carry = 0;
    for (int i = blockSize - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] >> 7) & 0x01;
    }
    if (carry) {
        if (blockSize == BLOCK_SIZE_128) {
            output[blockSize - 1] ^= 0x87;
        } else {
            output[blockSize - 1] ^= 0x1B;
        }
    }
}

void generateSubkeys(unsigned char *k1, unsigned char *k2, int blockSize) {
    unsigned char zeroBlock[BLOCK_SIZE_128] = ZERO_BLOCK_128;
    unsigned char k_temp[BLOCK_SIZE_128];

    mockEncrypt(zeroBlock, k_temp);
    leftShift(k_temp, k1, blockSize);
    leftShift(k1, k2, blockSize);
}

int main() {
    unsigned char k1[BLOCK_SIZE_128] = {0};
    unsigned char k2[BLOCK_SIZE_128] = {0};

    printf("Subkey constants:\n");
    printf("For 128 bits: 0x87\n");
    printf("For 64 bits: 0x1B\n");

    generateSubkeys(k1, k2, BLOCK_SIZE_128);

    printf("Subkey K1: ");
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        printf("%02x ", k1[i]);
    }
    printf("\n");

    printf("Subkey K2: ");
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        printf("%02x ", k2[i]);
    }
    printf("\n");

    return 0;
}


