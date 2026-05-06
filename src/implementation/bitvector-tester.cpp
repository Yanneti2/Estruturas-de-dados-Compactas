#include "bitvector.h"
#include "endian.h"
#include <iostream>
using namespace std;

int main(void){
    TYPE size = 10000;
    // printar vetor inicilizado
    bitVector* B1 = new bitVector(64,2.0);
    bitVector* B2 = new bitVector(64,2.0);
    printf("\n\n");
    // vetor na forma 10000100001....
    for (TYPE i = 0; i < size; i++){
        if (i%4 == 0){
            B1->append1();
        } else {
            B1->append0();
        }
    }
    B1->print();
    for (TYPE i = 0; i<size; i++){
        if (i%3 ==0) {
            B2->append1();
        } else if (i%8 == 0) {
            B2->append0();
        }
    }
    B2->print();
    B1->extend(B2);
    B1->print();
    return 0;
}