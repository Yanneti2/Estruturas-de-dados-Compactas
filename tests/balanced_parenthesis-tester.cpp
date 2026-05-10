#include "bp.h"
#include "bitvector.h"
#include <cassert>

int main(int argc, char *argv[])
{
    // Creating the BP bitvector
    unsigned long long size = 32;
    bitVector B = bitVector(); 


    char pattern[] = "((())()(())(()())())()((())())()";

    // using sizeof(pattern) -1 to ignore the \0 at end of pattern
    for (int i = 0; i < sizeof(pattern) - 1; i++)
    {
        if (pattern[i] == '(')
        {
            B.append1();
            continue;
        }
        B.append0();
    }

    
   //---------------------------
   //     Excess Operation     |
   //---------------------------

    // Hand-crafted excesses:
    //
    // 01232121
    // ((())()(
    // 
    // 23212323
    // ())(()()
    // 
    // 21210101
    // )())()((
    // 
    // 23212101
    // ())())()

    unsigned long long excesses[] = { 
        0, 1, 2, 3, 2, 1, 2, 1,
        2, 3, 2, 1, 2, 3, 2, 3,
        2, 1, 2, 1, 0, 1, 0, 1,
        2, 3, 2, 1, 2, 1, 0, 1
    };

    for (unsigned long long i = 0; i < size; i++) 
    {
        assert(excesses[i] == excess(&B, i));
    }


    return 0;
}
