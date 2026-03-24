#ifndef BITVECTOR
#define BITVECTOR

// TODO: check system word size and use word size accordingly
#if ((ULONG_MAX) == (UINT_MAX))
#define IS32BIT
#else
# define IS64BIT
#endif

#ifdef IS32BIT
#define NBITS 32
#define TYPE uint32_t
#else
#define NBITS 64
#define TYPE uint64_t
#endif

class bitVector {
  // TODO: *a should be unsigned long???
  private:
      unsigned long* A;   // The bitvector itself
      unsigned long cap;  // The number of words of A.
      unsigned long len;  // The lenght of the bit sequence (logical). 
      float ratio;        // The growing factor;

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
