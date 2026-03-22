# Rank and Select operations:


Rank(m) returns the number of elements in S less than or equal to m and select returns the m'th smallest element in S (in this jacobsons operations). Initialiy its very important to state that these operations are inverses of each order, such that select(rank(m)) = rank(select(m)) = m. We generally must do a linear scan to operate like so, which implies in the O(n) worst cost of these operations.

Consider the original/model bitvector of size n, and directory as a auxiliar small data structure that we will use so that our tools (select and rank operations) can be done in a lower average time. 

RANK: Using a two-level directory we can obtain a total time of O(logn) and aditional space of O(n) => total space of n + O(n). 

    - Level 1 blocks are of size (logn)²;
    - Level 2 blocks are of size logn;

Space needed for this stucture is O(nloglogn/logn) = o(n). Since the extra space for the directory becomes a fraction of the bit vector itself, the structure in study can be configured as an optimal compressed data structure, since it respects and achieve the time and space bounds simultaneosly.

# Bitmasking

    & (Bitwise AND Operator)
    | (Bitwise OR Operator)
    ^ (Bitwise XOR Operator)
    ~ (Bitwise NOT Operator)
    >> (RIght Shift Operator)
    << (Left Shift Operator)

utils: 

    - https://youtu.be/Ew2QnDeTCCE ;
    - 