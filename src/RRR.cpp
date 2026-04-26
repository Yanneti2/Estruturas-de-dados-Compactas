#include "../include/RRR.h"
#include <iostream>

RRR::RRR(bitVector *B, bool fixSizeToWordSize) {
    block_size = ceil(log2(B->size())) / 2 * floor(log2(B->size()));
    total_blocks = (B->size() + block_size - 1) / block_size;
    partial_ranks = (unsigned long long *) malloc(total_blocks * sizeof(unsigned long long));

    K_size = ceil(log2(B->size())) / 2;
    K_per_block = floor(log2(B->size()));
    total_K = (B->size() + K_size - 1) / K_size;
    K = (uint16_t *) malloc(total_K * sizeof(uint16_t));
    offsets = (uint16_t *) malloc(total_K * sizeof(uint16_t));

    vector<TYPE> next(K_size + 1, 0);
    vector<TYPE> pattern_to_class(1 << (K_size), 0);
    for (TYPE i = 0; i < (1 << K_size); i++) {
        unsigned long long popcount = __popcount(i);
        if (popcount <= lookuptable.size()) {
            lookuptable.push_back(vector<TYPE>());
        }

        lookuptable[popcount].push_back(i);
        pattern_to_class[i] = next[__popcount(i)];
        next[__popcount(i)] += 1;
    }
    for (TYPE i : pattern_to_class)
    cout << i << "   ";

    unsigned long long block_counter = 0;
    unsigned long long K_counter = 0;
    for (size_t i = 0; i < total_K; i++) {
        short pop_count = __popcount(B->accessWord(i, K_size));
        K_counter = pop_count;
        if (i % K_per_block == 0) {
            this->partial_ranks[i / K_per_block] = block_counter;
        }
        this->K[i] = K_counter;
        block_counter += pop_count;
        offsets[i] = pattern_to_class[B->accessWord(i, K_size) >> (NBITS - K_size)];
    }
    cout << endl;
    for (uint16_t i = 0; i < total_K; i++)
    cout << offsets[i] << "   ";
    cout << endl;
}

RRR::~RRR() {
    free(offsets);
    free(K);
    free(partial_ranks);
}

unsigned long long RRR::rank1(unsigned long long i) {
    unsigned long long K_pos = i / K_size;
    unsigned long long block = i / block_size;
    unsigned long long first_K = block * K_per_block;
    unsigned long long rank = partial_ranks[block];
    for (unsigned long long i = first_K; i < K_pos; i++) rank += K[i];
    rank += __popcount(lookuptable[K[K_pos]][offsets[K_pos]] >> (K_size - i % K_size));

    return rank;
}

void RRR::print() {
    cout << "BSIZE: " << block_size << "\nTOTAL BLOCKS: " << total_blocks << "\nK SIZE: " << K_size << endl;
    unsigned long long total_blocks;
    unsigned long long *partial_ranks;
    unsigned long long total_K;
    uint16_t K_size;
    uint16_t *K;
    uint16_t K_per_block;
}

unsigned long long RRR::rank0(unsigned long long i) {
    return 0;
}
