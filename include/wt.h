#include "../include/bitvector.h"
#include <iostream>
#include <map>
#define ULL unsigned long long

//mudar o freq para não utilizar ponteiros

class WaveletTree {
private:
    uint64_t len; // b
    WaveletTree *d;
    WaveletTree *l;
    WaveletTree *r;
    bitVector *freq;
    string alpha = ""; // alphabet

public:
    WaveletTree(string S, WaveletTree* dad = NULL);
    ULL rank();
    ~WaveletTree();

    //mudancas feitas
    char access(ULL i);
    void teste();
    ULL select_c(ULL a, ULL b, char c,  ULL j);
    ULL rank_c(char c, ULL i);
    void print();
};
