#include <cstdint>

#ifndef BITVECTOR
#define BITVECTOR

// TODO: check system word size and use word size accordingly
#if INTPTR_MAX == INT64_MAX
#define IS64BIT
#define NBITS 64
#define TYPE uint64_t
#elif INTPTR_MAX == INT32_MAX
#define IS32BIT
#define NBITS 32
#define TYPE uint32_t
#else
#error "Not a known processor"
#endif

using namespace std;

class bitVector {
    // TODO: *a should be unsigned long???
private:
    TYPE *A;   // The bitvector itself
    size_t _cap;  // The number of words of A.
    size_t _size;  // The lenght of the bit sequence (logical). 
    float ratio;        // The growing factor;

public:
    // Methods implemented post GPT (originals by stringers)
    int grow(unsigned long ncap);
    size_t size() const;
    size_t cap() const;

    // Methods implemented by GPT (originals and modded)
    bitVector(unsigned long capacity, float growth_ratio);
    ~bitVector();

    void append0();
    void append1();
    void set0(unsigned long i);
    void set1(unsigned long i);
    void extend(bitVector *B);
    void put(bitVector *B, unsigned long i);

    bool operator==(bitVector B) const;
    int  operator[](unsigned long i) const;
    TYPE accessWord(unsigned long i) const;
    TYPE accessWord(unsigned long i, unsigned wordSize) const;
    bitVector *slice(unsigned long i, unsigned long k) const;

    void put(bitVector *SRC, unsigned long k, unsigned long i);


    void append(unsigned long number, unsigned long k);

    void print() const;
};

#endif
