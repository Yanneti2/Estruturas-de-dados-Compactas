#include "jacobsonrank.h"
#include <iostream>

#ifndef mask
#ifdef IS32BIT
#define mask(i) mask32[(i)]
#else
#define mask(i) mask64[(i)]
#endif
#endif

extern uint32_t mask32[];

extern uint64_t mask64[];

rank::rank(bitVector *B, bool fixSizeToWordSize) {
    unsigned long long B_length = B->getLength();
    unsigned chunk1_size;
    unsigned chunk2_size;
    unsigned long long layer1_size;
    unsigned long long layer2_size;
    unsigned chunk2_per_chunk1;

    if (fixSizeToWordSize) {
        chunk1_size = NBITS * NBITS;
        chunk2_size = NBITS;
    } else {
        const long double logN = log2(B_length);
        chunk1_size = ceil(logN) * floor(logN);
        chunk2_size = chunk1_size / ceil(logN);
    }
    layer1_size = (B_length + chunk1_size - 1) / chunk1_size;
    chunk2_per_chunk1 = (chunk1_size + chunk2_size - 1) / chunk2_size;
    layer2_size = chunk2_per_chunk1 * (layer1_size - 1) + (B_length % chunk1_size + chunk2_size - 1) / chunk2_size + 1;

    this->chunk1_size = chunk1_size;
    this->chunk2_size = chunk2_size;
    this->layer1_size = layer1_size;
    this->layer2_size = layer2_size;
    this->chunk2_per_chunk1 = chunk2_per_chunk1;

    this->layer1 = (unsigned long long*) malloc(layer1_size * sizeof(unsigned long long));
    this->layer2 = (short*) malloc(layer2_size * sizeof(short));

    unsigned long long layer1_counter = 0;
    unsigned long long layer2_counter = 0;
    for (unsigned long long i = 0; i < layer2_size; i++) {
        if (i % chunk2_per_chunk1 == 0) {
            this->layer1[i / chunk2_per_chunk1] = layer1_counter;
            layer2_counter = 0;
        }
        this->layer2[i] = layer2_counter;
        short pop_count = std::__popcount(B->accessWord(i, chunk2_size));
        layer1_counter += pop_count;
        layer2_counter += pop_count;
    }
}

unsigned long long rank::rank1(bitVector *B, unsigned long long i) {
    unsigned long long chunk1 = i / chunk1_size;
    unsigned long long chunk2 = i / chunk2_size;
    unsigned pop_count = std::__popcount(B->accessWord(chunk2, chunk2_size) & ~mask(i % chunk2_size));
    return this->layer1[chunk1] + this->layer2[chunk2] + pop_count;
}

unsigned long long rank::rank0(bitVector *B, unsigned long long i) {
    return i - rank1(B, i);
}

void rank::print() {
    std::cout << "Layer1_Size: " << layer1_size << 
        "\n" << "Layer2_Size: " << layer2_size << 
        "\n" << "Chunk1_Size: " << chunk1_size << 
        "\n" << "Chunk2_Size: " << chunk2_size << 
        "\n" << "Chunk2_Per_Chunk1: " << chunk2_per_chunk1 << 
        "\n\n";
    for (unsigned long long i = 0; i < layer2_size; i++) {
        if (i % chunk2_per_chunk1 == 0) {
            std::cout << "\n" << this->layer1[i / chunk2_per_chunk1] << ":\n";
        }
        std::cout << this->layer2[i] << "   ";
    }
    std::cout << "\n";
}
