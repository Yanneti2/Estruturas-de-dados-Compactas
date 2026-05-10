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


    // Checking if our implementation matches the expected hand-crafted excess
    // values array
    for (unsigned long long i = 0; i < size; i++) 
    {
        assert(excesses[i] == excess(&B, i));
    }

    //---------------------------
    //    BWDSearch Operation    |
    //---------------------------

    // i=0: excess(0) = 0. As there is no possible j < i, should return 0.
    assert(backward_search(&B, 0, 1) == 0);

    // i=4: excess(4) = 2, target=1. j=3->3, j=2->2, j=1->1. Expected result=1
    assert(backward_search(&B, 4, -1) == 1);

    // i=9: excess(9) = 3, target=2. j=8->2. Expected result=8
    assert(backward_search(&B, 9, -1) == 8);

    // i=31: excess(31) = 1, target=0. j=30->2. Expected result=30
    assert(backward_search(&B, 31, -1) == 30);

    // i=20: excess=0, target=-1 (impossible) so expected result=0 (sentinel)
    assert(backward_search(&B, 20, -1) == 0);


    // i=16: excess=2, target=20 (impossible as excess(i) <= i) so expected result=0 (sentinel)
    assert(backward_search(&B, 16, 18) == 0);

    return 0;
}
