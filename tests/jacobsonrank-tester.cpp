#include "../include/jacobsonrank.h"
#include "../include/bitvector.h"
#include <iostream>
#include <chrono>
#include <math.h>
#include <cstdlib>

//std::popcount
//usar de ref len NBIS

int main(void){
	for (long long unsigned size = 1000; size < 10000000000; size *= 10) {
		auto B1 = bitVector(64,2.0);
		int ordem = log10(size);

		for(TYPE i = 0; i < size; i++){
		    if(rand() % 2 == 0){
			B1.append1();
		    }else{
			B1.append0();
		    }
		}
		auto R1 = JacobsonRank(&B1);
		auto start = std::chrono::high_resolution_clock::now();
		R1.build_select1(&B1);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = end - start;
		std::cout << "Tempo de construção da estrutura de select1 de ordem "  << ordem << ": "<< ms_double.count() << " ms\n";

		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 4 * size / 10; i++)
		{
		    unsigned long long foo = 1 + (foo > 1 ? rand() % (4 * size / 10) : 0);
		    R1.select1(&B1, foo);
		}
		end = std::chrono::high_resolution_clock::now();
		ms_double = end - start;
		std::cout << "Tempo de " << 4 * size / 10 << " operações select1: " << ms_double.count() << " ms\n\n";
	}
	std::cout << "\n" << "\n" << "\n";
	for (long long unsigned size = 1000; size < 10000000000; size *= 10) {
		auto B2 = bitVector(64,2.0);
		int ordem = log10(size);

		for(TYPE i = 0; i < size; i++){
		    if(rand() % 2 == 0){
			B2.append1();
		    }else{
			B2.append0();
		    }
		}
		auto R2 = JacobsonRank(&B2);
		auto start = std::chrono::high_resolution_clock::now();
		R2.build_select0(&B2);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = end - start;
		std::cout << "Tempo de construção da estrutura de select0 de ordem "  << ordem << ": "<< ms_double.count() << " ms\n";
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 4 * size / 10; i++)
		{
		    unsigned long long foo = rand() % (4 * size / 10);
		    R2.select0(&B2, foo);
		}
		end = std::chrono::high_resolution_clock::now();
		ms_double = end - start;
		std::cout << "Tempo de " << 4 * size / 10 << " operações select0: " << ms_double.count() << " ms\n\n";
    	}
	std::cout << "\n" << "\n" << "\n";
	for (long long unsigned size = 1000; size < 10000000000; size *= 10) {
		auto B3 = bitVector(64,2.0);
		int ordem = log10(size);

		for(TYPE i = 0; i < size; i++){
		    if(rand() % 2 == 0){
			B3.append1();
		    }else{
			B3.append0();
		    }
		}
		auto R3 = JacobsonRank(&B3);
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 4 * size /10; i++) {
			unsigned long long foo = rand() % (4*size/10);
			R3.rank1(&B3,foo);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = end - start;
		std::cout << "Tempo de " << 4 * size / 10 << " operações rank1: " << ms_double.count() << " ms\n\n";
	}
	std::cout << "\n" << "\n" << "\n";
	for (long long unsigned size = 1000; size < 10000000000; size *= 10) {
		auto B4 = bitVector(64,2.0);
		int ordem = log10(size);

		for(TYPE i = 0; i < size; i++){
		    if(rand() % 2 == 0){
			B4.append1();
		    }else{
			B4.append0();
		    }
		}
		auto R4 = JacobsonRank(&B4);
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 4 * size /10; i++) {
			unsigned long long foo = rand() % (4*size/10);
			R4.rank0(&B4,foo);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = end - start;
		std::cout << "Tempo de " << 4 * size / 10 << " operações rank0: " << ms_double.count() << " ms\n\n";
	}    
}
