#include <iostream>
#include <cstdlib>
#include "wt.h"
#include <map>
#include "../include/bitvector.h"
#include <algorithm>

using namespace std;

// lembrar de fazer a implicita dps

map<char, bool> Hashing(string S) {
    map<char, bool> chars = {};
    for(uint32_t i = 0; i < S.size(); i++)
        if(chars.find(S[i]) == chars.end()) 
            chars.insert({S[i], true});
    return chars;
}

WaveletTree::WaveletTree(string S, WaveletTree* dad) {
    cout << S << "\n";
    this->d = dad;
    map<char, bool> chars = Hashing(S);
    string alpha;
    for (auto i = chars.begin(); i != chars.end(); i++) {
        alpha += i->first;                         
    }

    if (alpha.size() == 1){
        this->l = NULL;
        this->r = NULL;
        this->d = dad;
        return;
    }

    uint32_t len = alpha.size() - 1;
    sort(alpha.begin(), alpha.end());
    bitVector vector = bitVector((unsigned long) ((S.size() + NBITS - 1)/NBITS), 2);
    uint32_t mid = len / 2;
    string LSS, RSS;

    for (uint32_t i = 0; i < S.size(); i++) {
        if (alpha[mid] >= S[i]) {
            vector.append0();
            LSS += S[i];
        }
        else {
            vector.append1();
            RSS += S[i];
        }
    }
    this->freq = vector;
    if(LSS.size()) {
        this->l = new WaveletTree(LSS, this);
    }
    if(RSS.size()) {
        this->r = new WaveletTree(RSS, this);
    }
}


WaveletTree::~WaveletTree() {
    delete this->d;
    delete this->r;
    delete this->l;
    this->freq.~bitVector();
}

unsigned long long WaveletTree::rank() {
}

unsigned long long WaveletTree::select() {
}

