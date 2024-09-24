#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LANE_SIZE 64
#define NUM_LANES (1024 / LANE_SIZE)
#define ROUNDS 100

void initializeState(unsigned long long state[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        state[i] = 0;
    }
}

void addMessageBlock(unsigned long long state[NUM_LANES], unsigned long long block[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        state[i] ^= block[i];
    }
}

int allNonZero(unsigned long long state[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        if (state[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void propagateBits(unsigned long long state[NUM_LANES]) {
    for (int i = 0; i < NUM_LANES; i++) {
        if (state[i] != 0) {
            for (int j = 0; j < LANE_SIZE; j++) {
                if (state[i] & (1ULL << j)) {
                    for (int k = 0; k < NUM_LANES; k++) {
                        if (state[k] == 0) {
                            state[k] |= (1ULL << j);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    unsigned long long state[NUM_LANES];
    unsigned long long messageBlock[NUM_LANES] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 
                                                  0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000,
                                                  0x4000, 0x8000};

    initializeState(state);
    addMessageBlock(state, messageBlock);

    int rounds = 0;
    while (!allNonZero(state) && rounds < ROUNDS) {
        propagateBits(state);
        rounds++;
    }

    if (allNonZero(state)) {
        printf("All lanes became nonzero after %d rounds.\n", rounds);
    } else {
        printf("Not all lanes became nonzero within the limit of %d rounds.\n", ROUNDS);
    }

    return 0;
}

