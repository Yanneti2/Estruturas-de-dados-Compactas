#include "endian.h"
#include "bitvector.h"
#include <cmath>

#ifndef JACOBSONRANK
#define JACOBSONRANK

class rank {
private:

public:
    unsigned long long len;
    long double logN;
    unsigned long long *relative_ranks;
    short *super_relative_ranks;
    rank(bitVector *B);
    ~rank();
    unsigned long long rank0(bitVector *B, unsigned long long i);
    unsigned long long rank1(bitVector *B, unsigned long long i);
};

#endif
