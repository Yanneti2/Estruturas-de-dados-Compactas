#include <cstdlib>
#include <iostream>
#include "..\include\bitvector.h"

class WaveletTree {
private:
    WaveletTree *d;
    WaveletTree *l;
    WaveletTree *r;
    bitVector freq;

public:
    WaveletTree(string S, WaveletTree* dad = NULL);
    unsigned long long select();
    unsigned long long rank();
    ~WaveletTree();
};