/*
  Original by G.P. Telles, 2013-2016.
  Edited in March 2026.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <cassert>
#include "bitvector.h"
using namespace std;

// uint32_t mask[] = {
//   0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFFFF,0x3FFFFFFFFFFFFFFF,0x1FFFFFFFFFFFFFFF,
//   0x0FFFFFFFFFFFFFFF,0x07FFFFFFFFFFFFFF,0x03FFFFFFFFFFFFFF,0x01FFFFFFFFFFFFFF,
//   0x00FFFFFFFFFFFFFF,0x007FFFFFFFFFFFFF,0x003FFFFFFFFFFFFF,0x001FFFFFFFFFFFFF,
//   0x000FFFFFFFFFFFFF,0x0007FFFFFFFFFFFF,0x0003FFFFFFFFFFFF,0x0001FFFFFFFFFFFF,
//   0x0000FFFFFFFFFFFF,0x00007FFFFFFFFFFF,0x00003FFFFFFFFFFF,0x00001FFFFFFFFFFF,
//   0x00000FFFFFFFFFFF,0x000007FFFFFFFFFF,0x000003FFFFFFFFFF,0x000001FFFFFFFFFF,
//   0x000000FFFFFFFFFF,0x0000007FFFFFFFFF,0x0000003FFFFFFFFF,0x0000001FFFFFFFFF,
//   0x0000000FFFFFFFFF,0x00000007FFFFFFFF,0x00000003FFFFFFFF,0x00000001FFFFFFFF,
//   0x00000000FFFFFFFF
// }

uint64_t mask[] = {
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

#define mask(i) mask[(i)]

/**
   A new, empty bitsequence.

   \param capacity The initial capacity (number of bitVector).
   \param growth_ratio 
**/

// Initializes a bitvector instance 
bitVector::bitVector(unsigned long capacity, float growth_ratio) {

    assert(sizeof(unsigned long) == 8);

    cap = (capacity == 0 ? 0 : (capacity+(NBITS-1))/NBITS);
    len = 0;
    ratio = growth_ratio;

    A = (unsigned long*) calloc(cap,sizeof(unsigned long));
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

    ncap = (ncap + (NBITS-1)) / NBITS;

    unsigned long* AA = (unsigned long*) realloc(A, ncap * sizeof(unsigned long));
    if (!AA)
        throw new bad_alloc();

    for (unsigned long i = cap; i < ncap; i++) 
        AA[i] = 0;

    A = AA;
    cap = ncap;

    return 1;
}

/**
   \brief Set A[i] to 1.

   If i > |A| - 1 then the behavior is undefined.
**/
void bitVector::set1(unsigned long i) {

    A[i / 64] |= 0x8000000000000000 >> (i % 64);
}

/**
   \brief Set A[i] to 0.

   If i > |A| - 1 then the behavior is undefined.
**/
void bitVector::set0(unsigned long i) {

    A[i / 64] &= ~(0x8000000000000000 >> (i % 64));
}

/**
   \brief Return 0 if A[i] == 0 or 1 if A[i] == 1.

   If i > |A|-1 then the behavior is undefined.
**/
int bitVector::access(unsigned long i) {

    return (A[i / 64] & (0x8000000000000000 >> (i%64))) ? 1 : 0;
}

/**
   Add 0 to the end of A and increase |A| by one.
**/
void bitVector::append0() {

    if (len == NBITS * cap)
        grow(cap * ratio);

    set0(len++);
}

/**
   Add 1 to the end of A and increase |A| by one.
**/
void bitVector::append1() {

    if (len == NBITS*cap)
        grow(cap * ratio);

    set1(len++);
}

// fazer uma funcao para colocar uma sequencia predefinida de bits ao final de um bitvector
/*
int bitVector::append_seq() {
    appendar uma sequencia de bits ao final deve ser aumentar esse numero
    de bits com callor (setar tudo 0) e fazer um and com a sequencia de 
    bits que deseja alocar naquele lugar 
}
*/

/**
   \brief Print the bit array on the screen.
**/
void bitVector::print() {

    printf("len: %ld, cap: %ld, ratio: %f\n",len,cap,ratio);

    // ruler:
    printf(" ");
    for (int i=0; i<NBITS*cap; i++) {
        if (i>0 && i%10 == 0)
            printf("%10d",i/10);
        //else
        //  printf(" ");

        //if (i%8 == 7)
        //  printf(" ");
    }
    printf("\n");

    for (int i=0; i<NBITS*cap; i++) {
        printf("%d",i%10);

        //if (i%8 == 7)
        //  printf(" ");
    }
    printf("\n");

    // A:
    for (int i=0; i<NBITS*cap; i++) {
        printf("%d",bitVector::access(i));

        //if (i%8 == 7) {
        //  printf(" ");
        //}
    }
    printf("\n\n");

    // B->A in hex:
    //u8* c = (u8*) B->A;
    //
    //for (i=0; i<(B->cap-1)/8+1; i++) {
    //  printf("0x%02x    ",(unsigned char)*c);
    //  printf(" ");
    //  c++;
    //}
    //printf("\n");
}

/**
  \brief this[i .. i+k-1] = SRC[0,k-1] 

  Copy the leading k bitVector of SRC onto bitVector i,i+1,...,i+k-1 of this bit sequence.

  Increase the length of the bit sequence as needed. 

  Takes time proportinal to k/64.
**/
void bitVector::put(bitVector* SRC, unsigned long k, unsigned long i) {

    while (len < i + k - 1)
        grow(cap * ratio);
    // The number of bitVector of a 64-bit word of SRC->A that will be copied at
    // the right of a word of this->A and at the left of the next word of A:
    unsigned long right = i % NBITS;  
    unsigned long left = NBITS - right;

    unsigned long lmask = left == NBITS ? 0UL : 0xFFFFFFFFFFFFFFFF << left;
    unsigned long rmask = ~lmask;

    // The next word of this->A that will be written:
    unsigned long word = i / NBITS;

    // The number of words of SRC->A that were read:
    unsigned long w = 0;

    while (k >= NBITS) {
        if (right == 0) {
            this->A[word] = SRC->A[w];
            word++;
        }
        else {
            this->A[word] &= lmask;
            this->A[word] |= SRC->A[w] >> right;
            word++;
            this->A[word] &= rmask;
            this->A[word] |= SRC->A[w] << left;
        }

        w++;
        k -= NBITS;
    }    

    if (k > left) {
        this->A[word] &= lmask;
        this->A[word] |= SRC->A[w] >> right;
        k -= left;
        i = 0;
        word++;
    } else {
        left = 0;
    }
    if (k) {
        this->A[word] &= ~((0xFFFFFFFFFFFFFFFF << (NBITS-k)) >> i);
        this->A[word] |= ((SRC->A[w] << left) >> (NBITS-k)) << (NBITS-k-i);
    }
}

/**
   Append the k most significant bitVector of number to the bit sequence.

   Increase the length of the bit sequence by k.
**/
void bitVector::append(unsigned long number, unsigned long k) {

    bitVector S(NBITS,1.0);
    S.A[0] = number;

    put(&S, k, S.len);
}
