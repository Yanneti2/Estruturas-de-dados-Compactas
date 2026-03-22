/*
  A sequence of bitVector.
*/


#ifndef BITVECTOR
#define BITVECTOR


class bitVector {

private:
    unsigned long* A;
    unsigned long cap;  // The number of words of A.
    unsigned long len;  // The lenght of the bit sequence (logical). 
    float ratio;

public:
    int grow(unsigned long ncap);

    // Methods implemented by GPT
    bitVector(unsigned long capacity, float growth_ratio);
    ~bitVector();

    unsigned long length();

    void set1(unsigned long i);
    void set0(unsigned long i);
    int  access(unsigned long i);

    void put(bitVector* SRC, unsigned long k, unsigned long i);

    void append0();
    void append1();

    void append(unsigned long number, unsigned long k);


    void print();
};

#endif
