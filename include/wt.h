#include "../include/bitvector.h"
#include <iostream>
<<<<<<< Updated upstream
#include "..\include\bitvector.h"
#include <map>
#define ULL unsigned long long

//mudar o freq para não utilizar ponteiros
=======
#include <cstdlib>

#define ULL unsigned long long
>>>>>>> Stashed changes

class WaveletTree {
private:
    uint64_t len; //alphabet lenght
    WaveletTree *d;
    WaveletTree *l;
    WaveletTree *r;
<<<<<<< Updated upstream
    bitVector *freq;
    string alpha = ""; // alphabet

public:
    WaveletTree(string S, WaveletTree* dad = NULL);
    ULL rank();
    ~WaveletTree();

    //mudancas feitas
    char access(ULL i);
    void teste();
    ULL select_c(char c, ULL j);
};
=======
    bitVector freq;
    string s;

public:
    WaveletTree(string S, WaveletTree* dad = NULL);
    ~WaveletTree();
    void print();
    ULL rank0(bitVector b, ULL i);
    ULL rank1(bitVector b, ULL i);
    string access(WaveletTree* root, unsigned long long i);
    unsigned long long select0();
    unsigned long long select1();
};
>>>>>>> Stashed changes
