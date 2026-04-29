#include <iostream>
#include <cstdlib>
#include "..\include\wt.h"
#include <map>
#include <algorithm>

using namespace std;

// lembrar de fazer a implicita dps
// mudar o vector para não utilizar ponteiros

std::map<char, bool> Hashing(string S) {
    std::map<char, bool> chars = {};
    for(uint32_t i = 0; i < S.size(); i++)
        if(chars.find(S[i]) == chars.end()) 
            chars.insert({S[i], true});
    return chars;
}

WaveletTree::WaveletTree(string S, WaveletTree* dad) {
    // cout << S << "\n";
    this->d = dad;
    map<char, bool> alphabet = Hashing(S);
    for (auto i = alphabet.begin(); i != alphabet.end(); i++) {
        alpha += i->first;                         
    }

    if (alpha.size() == 1){
        this->l = NULL;
        this->r = NULL;
        this->d = dad;
        return;
    }

    // uint32_t len = alpha.size() - 1;
    len = alpha.size() - 1;
    sort(alpha.begin(), alpha.end());
    bitVector *vector = new bitVector((unsigned long) ((S.size() + NBITS - 1)/NBITS), 2);
    uint32_t mid = len / 2;
    string LSS, RSS;

    for (uint32_t i = 0; i < S.size(); i++) {
        if (alpha[mid] >= S[i]) {
            vector->append0();
            LSS += S[i];
        }
        else {
            vector->append1();
            RSS += S[i];
        }
    }

    //analisar quando usar jacobson select e naive select

    vector->JacobsonRank_build();
    vector->build_select0();
    vector->build_select1();

    this->freq = vector;
    // freq.print();
    if(LSS.size()) {
        this->l = new WaveletTree(LSS, this);
    }
    if(RSS.size()) {
        this->r = new WaveletTree(RSS, this);
    }
}

void WaveletTree::teste(){

    cout << alpha << endl;
    if(l){
        l->teste();
    }
    if(r){
        r->teste();
    }
}


WaveletTree::~WaveletTree() {
    if (this->l != NULL) {
        this->l->~WaveletTree();
        delete this->l;
    }
    if(this->r != NULL) {
        this->r->~WaveletTree();
        delete this->r;
    }
    delete this->d;
    this->freq->~bitVector();
}

unsigned long long WaveletTree::rank() {
}

char WaveletTree::access(ULL i){

    if(alpha.size() == 1){
        return alpha[0];
    }
    if((*freq)[i] == 0){
        auto j = freq->rank0(i);
        return l->access(j);
    }
    else{
        auto j = freq->rank1(i);
        return r->access(j);
    }
}

ULL WaveletTree::select_c(char c,  ULL j){
    if(1 == alpha.size()){ return j; }
    ULL index = alpha.size()/2;

    if(c <= alpha[index]){
        auto k = l->select_c(c, j);
        return freq->select0(k);
    }
    else{
        auto k = r->select_c(c, j);
        return freq->select1(k);
    }
}
