/*
  Original by G.P. Telles, 2013-2016.
  Edited in March 2026.
*/

/*
    TODO:
    Uma funcao para appendar um long e/ou uma string a um bitvector. 
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <cassert>
#include "bitvector.h"
#include <iostream>
using namespace std;

#ifndef bitMask
#ifdef IS32BIT
#define bitMask(i) bitMask32[(i)]
#else
#define bitMask(i) bitMask64[(i)]
#endif
#endif

uint32_t bitMask32[] = {
    0xFFFFFFFF,0x7FFFFFFF,0x3FFFFFFF,0x1FFFFFFF,
    0x0FFFFFFF,0x07FFFFFF,0x03FFFFFF,0x01FFFFFF,
    0x00FFFFFF,0x007FFFFF,0x003FFFFF,0x001FFFFF,
    0x000FFFFF,0x0007FFFF,0x0003FFFF,0x0001FFFF,
    0x0000FFFF,0x00007FFF,0x00003FFF,0x00001FFF,
    0x00000FFF,0x000007FF,0x000003FF,0x000001FF,
    0x000000FF,0x0000007F,0x0000003F,0x0000001F,
    0x0000000F,0x00000007,0x00000003,0x00000001,
    0x00000000
};

uint64_t bitMask64[] = {
    0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFFFF,0x3FFFFFFFFFFFFFFF,0x1FFFFFFFFFFFFFFF,
    0x0FFFFFFFFFFFFFFF,0x07FFFFFFFFFFFFFF,0x03FFFFFFFFFFFFFF,0x01FFFFFFFFFFFFFF,
    0x00FFFFFFFFFFFFFF,0x007FFFFFFFFFFFFF,0x003FFFFFFFFFFFFF,0x001FFFFFFFFFFFFF,
    0x000FFFFFFFFFFFFF,0x0007FFFFFFFFFFFF,0x0003FFFFFFFFFFFF,0x0001FFFFFFFFFFFF,
    0x0000FFFFFFFFFFFF,0x00007FFFFFFFFFFF,0x00003FFFFFFFFFFF,0x00001FFFFFFFFFFF,
    0x00000FFFFFFFFFFF,0x000007FFFFFFFFFF,0x000003FFFFFFFFFF,0x000001FFFFFFFFFF,
    0x000000FFFFFFFFFF,0x0000007FFFFFFFFF,0x0000003FFFFFFFFF,0x0000001FFFFFFFFF,
    0x0000000FFFFFFFFF,0x00000007FFFFFFFF,0x00000003FFFFFFFF,0x00000001FFFFFFFF,
    0x00000000FFFFFFFF,0x000000007FFFFFFF,0x000000003FFFFFFF,0x000000001FFFFFFF,
    0x000000000FFFFFFF,0x0000000007FFFFFF,0x0000000003FFFFFF,0x0000000001FFFFFF,
    0x0000000000FFFFFF,0x00000000007FFFFF,0x00000000003FFFFF,0x00000000001FFFFF,
    0x00000000000FFFFF,0x000000000007FFFF,0x000000000003FFFF,0x000000000001FFFF,
    0x000000000000FFFF,0x0000000000007FFF,0x0000000000003FFF,0x0000000000001FFF,
    0x0000000000000FFF,0x00000000000007FF,0x00000000000003FF,0x00000000000001FF,
    0x00000000000000FF,0x000000000000007F,0x000000000000003F,0x000000000000001F,
    0x000000000000000F,0x0000000000000007,0x0000000000000003,0x0000000000000001,
    0x0000000000000000
};

/**
   A new, empty bitsequence.

   \param capacity The initial capacity (number of bitVector).
   \param growth_ratio 
**/

// Initializes a bitvector instance 
bitVector::bitVector(unsigned long cap, float growth_ratio) {

    assert(sizeof(TYPE) * 8 == NBITS);

    _cap = (cap == 0 ? 0 : (cap + (NBITS - 1)) / NBITS);
    _size = 0;
    ratio = growth_ratio;

    A = (unsigned long*) calloc(_cap ,sizeof(unsigned long));
    if (!A)
        throw new bad_alloc();
}

// Frees the memory dinamically alocated to store the bitvector
bitVector::~bitVector() {
    free(A);
}

// TODO: change this funtion to be a method of 'bitVector', does it really need to be a method?

// allocates new space for the bitvector, returns 1 if sucess
int bitVector::grow(unsigned long ncap) {
    if (ncap <= _cap) ncap = _cap++;
    TYPE* AA = (TYPE*) realloc(A, ncap * sizeof(TYPE));
    if (!AA)
        throw new bad_alloc();
    for (unsigned long long i = _cap; i < ncap; i++) 
        AA[i] = 0;
    A = AA;
    _cap = ncap;
    return 1;
}

/**
   \brief Set A[i] to 1.

   If i > |A| - 1 then the behavior is undefined.
**/
void bitVector::set1(unsigned long i) {
    A[i / NBITS] |= (bitMask(i % NBITS) ^ bitMask(i % NBITS + 1));
}

/**
   \brief Set A[i] to 0.

   If i > |A| - 1 then the behavior is undefined.
**/
void bitVector::set0(unsigned long i) {
    A[i / NBITS] &= ~(bitMask(i % NBITS) ^ bitMask(i % NBITS + 1));
}

/**
   \brief Return 0 if A[i] == 0 or 1 if A[i] == 1.

   If i > |A|-1 then the behavior is undefined.
**/
int bitVector::operator[](unsigned long i) const{
    return (A[i / NBITS] & (bitMask(i % NBITS) ^ bitMask(i % NBITS + 1))) ? 1 : 0;
}

bool bitVector::operator==(bitVector B) const {
    size_t thisSize = this->size();
    size_t BSize = B.size();
    if (thisSize != BSize) return false;
    
    for (size_t i = 0; i < thisSize / NBITS; i++) {
        if (this->accessWord(i) != B.accessWord(i)) return false;
    }
    return true;
}
TYPE bitVector::accessWord(unsigned long i) const {
    return A[i];
}

TYPE bitVector::accessWord(unsigned long i, unsigned wordSize) const {
    unsigned long long start = i * wordSize;    
    unsigned long long end = start + wordSize - 1;    
    unsigned long long start_index = start / NBITS;   
    unsigned long long end_index = end / NBITS;   
    start %= NBITS;    
    end %= NBITS;
    if (start_index == end_index) {   
        return (A[start_index] & ~bitMask(end + 1)) << start;
    }
    return (A[start_index] << start) | ((A[end_index] & ~bitMask(end + 1)) >> (NBITS - start));
}

/**
   Add 0 to the end of A and increase |A| by one.
**/
void bitVector::append0() {

    if (_size == NBITS * _cap)
        grow(_cap * ratio);
    _size++;
}

/**
   Add 1 to the end of A and increase |A| by one.
**/
void bitVector::append1() {

    if (_size == NBITS * _cap)
        grow(_cap * ratio);

    set1(_size++);
}

unsigned long bitVector::size() const { return _size; }
unsigned long bitVector::cap() const { return _cap; }

/**
    Coloca uma sequencia predefinida de bits ao final do bitvector.
**/
void bitVector::extend(bitVector* B) {
    if (_cap == 0) _cap = 1;

    while(!((_size + B->size() + NBITS - 1) / NBITS <= _cap))
        grow(_cap * ratio);   

    short bitsSobrando = _size % NBITS;
    short bitsFaltando = NBITS - bitsSobrando;
    short cur = _size / NBITS;

    for (unsigned long long i = 0; i < (B->size() + NBITS - 1) / NBITS; i++) {
         if (bitsSobrando == 0) {
            this->A[cur] = B->A[i];
            cur++;
        } else {
            this->A[cur] |= B->A[i] >> bitsSobrando;
            cur++;
            this->A[cur] |= B->A[i] << bitsFaltando;
        }
    }
    this->_size += B->size();
}

/**
    Copy a part of original bitvector into another bitvector and returns the new one.
**/
bitVector* bitVector::slice(unsigned long i, unsigned long k) const {
    bitVector* Bnew = new bitVector((k + NBITS - 1)  / NBITS, 1.5);
    for (unsigned long j = 0; j < k; j++) {
        if ((*this)[i + j])
            Bnew->append1();
        else
            Bnew->append0();
    }
    return Bnew;
}

/**
    Inserts a bit sequence in the i'th bitvector position.
**/
void bitVector::put(bitVector* B, unsigned long i) {
    bitVector* endOriginal = this->slice(i, this->size() - i);
    this->_size = i;
    this->extend(B);
    this->extend(endOriginal);
    endOriginal->~bitVector();
}

/**
   \brief Print the bit array on the screen.
**/
void bitVector::print() const {
    printf("len: %ld, cap: %ld, ratio: %f\n", _size, _cap, ratio);
    for (unsigned long long i=0; i< _size; i++) {
        printf("%d", (*this)[i]);
    }
    printf("\n\n");
}

#undef bitMask
