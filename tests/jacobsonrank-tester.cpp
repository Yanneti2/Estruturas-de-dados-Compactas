#include "jacobsonrank.h"
#include "bitvector.h"
#include <iostream>
#include <chrono>
#include <math.h>
#include <cstdlib>

//std::popcount
//usar de ref len NBIS

int main(void){

    //Inicialização do bitvector
    for (long long unsigned size = 1000; size < 10000000000; size *= 10) {
        bitVector* B1 = new bitVector(64,2.0);
        int ordem = log10(size);

        for(TYPE i = 0; i < size; i++){
            if(rand() % 2 == 0){
                B1->append1();
            }else{
                B1->append0();
            }
        }

        JacobsonRank *R = new JacobsonRank(B1, false);

        auto start = std::chrono::high_resolution_clock::now();
        R->build_select(B1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = end - start;
        std::cout << "Tempo de construção da estrutura de select de ordem "  << ordem << ": "<< ms_double.count() << " ms\n";

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 4 * size / 10; i++)
        {
            unsigned long long foo = rand() % (4 * size / 10);
            R->select1(B1, foo);
        }
        end = std::chrono::high_resolution_clock::now();
        ms_double = end - start;
        std::cout << "Tempo de " << 4 * size / 10 << " operações select: " << ms_double.count() << " ms\n\n";

        delete R;
        delete B1;
    }
}
