/*
  G.P. Telles, 2013-2016.
*/


#include <stdio.h>
#include <stdlib.h>

#include <stdexcept>
#include <cassert>

#include "bitvector.h"
using namespace std;

// TODO: change word size to 32 bitVector with uint32_t
// TODO: check system word size and use word size accordingly
/**
   A new, empty bitsequence.

   \param capacity The initial capacity (number of bitVector).
   \param growth_ratio 
**/


bitVector::bitVector(unsigned long capacity, float growth_ratio) {

    assert(sizeof(unsigned long) == 8);

    cap = (capacity == 0 ? 0 : (capacity+63)/64);
    len = 0;
    ratio = growth_ratio;

    A = (unsigned long*) calloc(cap,sizeof(unsigned long));
    if (!A)
        throw new bad_alloc();
}

bitVector::~bitVector() {
    free(A);
}

// TODO: change this funtion to be a method of 'bitVector'
int bitVector::grow(unsigned long ncap) {

    ncap = (ncap + 63) / 64;

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
//TODO: change 'test' to 'access'
int bitVector::access(unsigned long i) {

    return (A[i / 64] & (0x8000000000000000 >> (i%64))) ? 1 : 0;
}

/**
   Add 0 to the end of A and increase |A| by one.
**/
void bitVector::append0() {

    if (len == 64 * cap)
        grow(cap * ratio);

    set0(len++);
}

/**
   Add 1 to the end of A and increase |A| by one.
**/
void bitVector::append1() {

    if (len == 64*cap)
        grow(cap * ratio);

    set1(len++);
}



/*
void bitVector::append1(unsigned long k) {

  mesma estrutura do put.

}
*/



/**
   \brief Print the bit array on the screen.
**/
void bitVector::print() {

    printf("len: %ld, cap: %ld, ratio: %f\n",len,cap,ratio);

    // ruler:
    printf(" ");
    for (int i=0; i<64*cap; i++) {
        if (i>0 && i%10 == 0)
            printf("%10d",i/10);
        //else
        //  printf(" ");

        //if (i%8 == 7)
        //  printf(" ");
    }
    printf("\n");

    for (int i=0; i<64*cap; i++) {
        printf("%d",i%10);

        //if (i%8 == 7)
        //  printf(" ");
    }
    printf("\n");

    // A:
    for (int i=0; i<64*cap; i++) {
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
    unsigned long right = i % 64;  
    unsigned long left = 64 - right;

    unsigned long lmask = left == 64 ? 0UL : 0xFFFFFFFFFFFFFFFF << left;
    unsigned long rmask = ~lmask;

    // The next word of this->A that will be written:
    unsigned long word = i / 64;

    // The number of words of SRC->A that were read:
    unsigned long w = 0;

    while (k >= 64) {
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
        k -= 64;
    }    

    if (k > left) {
        this->A[word] &= lmask;
        this->A[word] |= SRC->A[w] >> right;
        k -= left;
        i = 0;
        word++;
    }
    else
    left = 0;

    if (k) {
        this->A[word] &= ~((0xFFFFFFFFFFFFFFFF << (64-k)) >> i);
        this->A[word] |= ((SRC->A[w] << left) >> (64-k)) << (64-k-i);
    }
}

/**
   Append the k most significant bitVector of number to the bit sequence.

   Increase the length of the bit sequence by k.
**/
void bitVector::append(unsigned long number, unsigned long k) {

    bitVector S(64,1.0);
    S.A[0] = number;

    put(&S, k, S.len);
}
