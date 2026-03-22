// Guilherme P. Telles

#include <stdint.h>

int is_bigendian() {

    int i = 1;

    if (((char*) &i)[0] == 1)
        return 0;
    else
        return 1;
}



int32_t reverse32(int32_t x) {

    int8_t* px = (int8_t*) &x;
    int32_t y;
    int8_t* py = (int8_t*) &y;

    py[0] = px[3];
    py[1] = px[2];
    py[2] = px[1];
    py[3] = px[0];

    return y;
}



int64_t reverse64(int64_t x) {

    int8_t* px = (int8_t*) &x;
    int64_t y;
    int8_t* py = (int8_t*) &y;

    py[0] = px[7];
    py[1] = px[6];
    py[2] = px[5];
    py[3] = px[4];
    py[4] = px[3];
    py[5] = px[2];
    py[6] = px[1];
    py[7] = px[0];

    return y;
}



double reversedouble(double x) {

    char* px = (char*) &x;
    double y;
    char* py = (char*) &y;

    if (sizeof(double) == 8) {
        py[0] = px[7];
        py[1] = px[6];
        py[2] = px[5];
        py[3] = px[4];
        py[4] = px[3];
        py[5] = px[2];
        py[6] = px[1];
        py[7] = px[0];
    }
    else {
        py[0] = px[3];
        py[1] = px[2];
        py[2] = px[1];
        py[3] = px[0];
    }

    return y;
}



float reversefloat(float x) {

    char* px = (char*) &x;
    float y;
    char* py = (char*) &y;

    py[0] = px[3];
    py[1] = px[2];
    py[2] = px[1];
    py[3] = px[0];

    return y;
}
