#include "jacobsonrank.h"

rank::rank(bitVector *B) {
    const unsigned long long B_length = B->getLength();
    const long double logN = log2(B_length);
    this->logN = logN;

    const unsigned long long len = ceil(B_length / (long double) ceil(logN * logN));
    this->len = len;

    this->relative_ranks = (unsigned long long*) malloc(len * sizeof(unsigned long long));
    unsigned long long len_sub = ceil(ceil(logN * logN) / (long double) ceil(logN));
    this->super_relative_ranks = (short*) malloc(len * len_sub * sizeof(short));

    unsigned long long counter = 0;
    short relative_counter = 0;
    for (unsigned long long i = 0; i < B_length; i++) {
        if (i % (unsigned long long) ceil(logN * logN) == 0) {
            this->relative_ranks[i / (unsigned long long) ceil(logN * logN)] = counter;
            relative_counter = 0;
        }

        if (i % (unsigned long long) ceil(logN) == 0) {
            this->super_relative_ranks[i / (unsigned long long) (len_sub)] = relative_counter;
        }
        int cur_bit = B->access(i);
        counter += cur_bit;
        relative_counter += cur_bit;
    }
}

unsigned long long rank::rank1(bitVector *B, unsigned long long i) {
    unsigned long long len_sub = ceil(ceil(logN * logN) / (long double) ceil(logN));

    unsigned pop_count = 0;
    for (unsigned long long j = 0; j < i % len_sub; j++) {
        pop_count += B->access(i / len_sub * len_sub + j); 
        
    }

    return this->relative_ranks[i / (unsigned long long) ceil(logN * logN)] + this->super_relative_ranks[i / (unsigned long long) len_sub] + pop_count;
}

unsigned long long rank::rank0(bitVector *B, unsigned long long i) {
    return i - rank1(B, i);
}
