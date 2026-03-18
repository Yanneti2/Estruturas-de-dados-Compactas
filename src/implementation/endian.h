/**
   \file endian.h
   \brief Endianness conversions.

   Guilherme P. Telles, Jun 2014.
**/

#ifndef ENDIANH
#define ENDIANH

#include <stdint.h>

//extern inline
int is_bigendian();

int32_t reverse32(int32_t x);
int64_t reverse64(int64_t x);
float reversefloat(float x);
double reversedouble(double x);

#endif
