#include "endian.h"
#include "bitvector.h"
#include <cmath>

#ifndef JACOBSONRANK
#define JACOBSONRANK

class rank {
private:
    unsigned long long layer1_size;
    unsigned long long layer2_size;
    unsigned chunk1_size;
    unsigned chunk2_size;
    unsigned chunk2_per_chunk1;
    unsigned long long *layer1;
    short *layer2;

public:
    rank(bitVector *B, bool fixSizeToWordSize = false);
    ~rank();
    unsigned long long rank0(bitVector *B, unsigned long long i);
    unsigned long long rank1(bitVector *B, unsigned long long i);
    void print();
};

#endif
