#include "../include/jacobsonrank.h"
#include <iostream>

#ifndef bitMask
#ifdef IS32BIT
#define bitMask(i) bitMask32[(i)]
#else
#define bitMask(i) bitMask64[(i)]
#endif
#endif

#define MIN(A, B) ((A) < (B) ? (A) : (B)) 
#define ULL unsigned long long

extern uint32_t bitMask32[];
extern uint64_t bitMask64[];

template <typename T>
unsigned long long binary_search(T *V, T target, unsigned long long beginning, unsigned long long end) {
    if (end == beginning) {
        return end;
    }
    while(1) {
        if (end == beginning) {
            return end - 1;
        }
        unsigned long long middle = (beginning + end) / 2;
        if (V[middle] < target) {
            beginning = middle + 1;
        } else {
            end = middle;
        }
    }
}

JacobsonRank::JacobsonRank(bitVector *B, bool fixSizeToWordSize) {
    const ULL B_length = B->size();
    unsigned chunk1_size;
    unsigned chunk2_size;
    ULL layer1_size;
    ULL layer2_size;
    unsigned chunk2_per_chunk1;

    if (fixSizeToWordSize) {
        chunk1_size = NBITS * NBITS;
        chunk2_size = NBITS;
    } else {
        const long double logN = log2((long double)B_length);
        chunk1_size = ceil(logN) * floor(logN);
        chunk2_size = chunk1_size / ceil(logN);
    }
    layer1_size = (B_length + chunk1_size - 1) / chunk1_size;
    chunk2_per_chunk1 = (chunk1_size + chunk2_size - 1) / chunk2_size;
    layer2_size = chunk2_per_chunk1 * layer1_size;

    this->chunk1_size = chunk1_size;
    this->chunk2_size = chunk2_size;
    this->layer1_size = layer1_size;
    this->layer2_size = layer2_size;
    this->chunk2_per_chunk1 = chunk2_per_chunk1;

    this->layer1 = (ULL*) malloc(layer1_size * sizeof(ULL));
    this->layer2 = (short*) malloc(layer2_size * sizeof(short));

    ULL layer1_counter = 0;
    ULL layer2_counter = 0;
    for (ULL i = 0; i < layer2_size; i++) {
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

JacobsonRank::~JacobsonRank() {
    if (layer1) free(layer1);
    if (layer2) free(layer2);
    if (select_vector) free(select_vector);
}

ULL JacobsonRank::rank1(bitVector *B, ULL i) {
    ULL chunk1 = i / chunk1_size;
    ULL chunk2 = i / chunk2_size;
    unsigned pop_count = std::__popcount(B->accessWord(chunk2, chunk2_size) & ~bitMask(i % chunk2_size));
    return layer1[chunk1] + layer2[chunk2] + pop_count;
}

ULL JacobsonRank::rank0(bitVector *B, ULL i) {
    return i - rank1(B, i);
}

void JacobsonRank::print() {
    std::cout << "Layer1_Size: " << layer1_size << 
        "\n" << "Layer2_Size: " << layer2_size << 
        "\n" << "Chunk1_Size: " << chunk1_size << 
        "\n" << "Chunk2_Size: " << chunk2_size << 
        "\n" << "Chunk2_Per_Chunk1: " << chunk2_per_chunk1 << 
        "\n" << "j: " << select_j << 
        "\n\n";
    for (ULL i = 0; i < layer2_size; i++) {
        if (i % chunk2_per_chunk1 == 0) {
            std::cout << "\n" << layer1[i / chunk2_per_chunk1] << ":\n";
        }
        std::cout << layer2[i] << "   ";
    }
    std::cout << "\n";
}

void JacobsonRank::build_select(bitVector *B) {
    const ULL B_length = B->size();
    ULL select_j = ceil(log2((long double)B_length) * log((long double)B_length));
    ULL *select_vector = (ULL *) malloc(((B_length + select_j - 1) / select_j + 1) * sizeof(ULL));
    ULL counter = 0;
    select_vector[0] = 0;
    for (ULL i = 0; i < B->size(); i++) {
        if ((*B)[i] == 1) {
            counter++;
            if (counter % select_j == 0) {
                select_vector[counter / select_j] = i + 1;
            } 
        }
    } 
    if (counter % select_j == 0) {
        select_vector[counter / select_j] = B->size();
    } 
    this->select_j = select_j;
    this->select_vector = select_vector;
}

ULL JacobsonRank::select1(bitVector *B, ULL i) {
    const ULL lower_bound = select_vector[i / select_j];

    if (i % select_j == 0) {
        return lower_bound; 
    }

    const ULL upper_bound = select_vector[i / select_j + 1];
    const ULL layer1_pos = binary_search(layer1, i, lower_bound / chunk1_size, (upper_bound - 1) / chunk1_size);
    const ULL layer2_pos = binary_search(layer2, (short) (i - layer1[layer1_pos]), layer1_pos * chunk2_per_chunk1, MIN((layer1_pos + 1) * chunk2_per_chunk1 - 1, layer2_size - 1));

    ULL counter = 0;
    const ULL target = i - layer1[layer1_pos] - layer2[layer2_pos];

    // Busca sequencial na palavra, é possível fazer uma busca binária com pop_count mas talvez não seja tão eficiente
    for (ULL j = 0; j < chunk2_size; j++) {
        counter += (*B)[j + layer2_pos * chunk2_size];
        if (counter == target) {
            return layer2_pos * chunk2_size + j + 1;
        } 
    }
    return 0;
}

#undef MIN
