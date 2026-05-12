#include "bitvector.h"
#include "wt.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <queue>
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
    cout << S << "\n";
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

// da p fazer com .dot do graphviz
void WaveletTree::print() {
	queue<WaveletTree*> q;
	q.push(this);
	while(!q.empty()){
		WaveletTree* cur = q.front();
		q.pop();
		if(cur->freq)cur->freq->print();
		cout<<cur->alpha<<endl<<endl;
		if(cur->l)q.push(cur->l);
		if(cur->r)q.push(cur->r);
	}
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

// seg fault, alpha should be only on root

ULL WaveletTree::select_c(char c,  ULL j){
    ULL a = 0;
	ULL b = len;
    if(a==b) return j;
    ULL aux = floor((a+b)/2);
    if(c <= alpha[aux]){
        j = l->select_c(c,j);
        return freq->naive_select0(j);
    }
    else{
        j = r->select_c(c,j);
        return freq->naive_select1(j);
    }
}
//abcdefimnoprtx
ULL WaveletTree::rank_c(char c, ULL i){
	WaveletTree* root = this;
	ULL a = 0;
	ULL b = len-1;
	while(a!=b){
		if(c <= alpha[floor((a+b)/2)]){
			i = freq->naive_rank0(i);
			root = root->l;
			b = floor((a+b)/2);
		}else{
			i = freq->naive_rank1(i);
			root = root->r;
			a = floor((a+b)/2) + 1;
		}
	}	
	return i;
}
