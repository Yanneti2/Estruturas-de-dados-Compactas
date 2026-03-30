#include "jacobsonrank.h"
#include "bitvector.h"
// #include "utils.h"
#include <iostream>
#include <chrono>
#include <math.h>
#include <cstdlib>

//std::popcount
//usar de ref len NBIS

int main(void){
    auto start = std::chrono::high_resolution_clock::now();

    //Inicialização do bitvector
    bitVector* B1 = new bitVector(64,2.0);

    TYPE size = 100000;
    int ordem = log10(size);

    for(TYPE i = 0; i < size; i++){
        if(rand() % 2 == 0){
            B1->append1();
        }else{
            B1->append0();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = end - start;
    std::cout << "Construcao bitvector de ordem "  << ordem << " - Tempo de execucao: " << ms_double.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
    rank *R = new rank(B1);
    end = std::chrono::high_resolution_clock::now();
    ms_double = end - start;
    std::cout << "Rank bitvector de ordem "  << ordem << " - Tempo de execucao: " << ms_double.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(TYPE i = 0; i < size; i++){
        R->rank1(B1, (rand() % size));
    }
    end = std::chrono::high_resolution_clock::now();
    ms_double = end - start;
    std::cout << "Query bitvector de ordem "  << ordem << " - Tempo de execucao: " << ms_double.count() << " ms\n";
}