https://www.alexbowe.com/rrr/

The most basic notion of entropy is that it is the minimum number of bits required by identifiers, called codes.

codes??

Using 2n bits for large trees becomes asynmtotically optimal, for smal trees, the O(logn) factor is significant. Whereas the trees in "Genereal-Tree-Encode-2n-bits" become labeled as 000, 001, 010, 011 and 100.

# Huffman Codes

The Huffman's Codes is a lossless data compression algorithm that converts a set of n nodes into a binary tree in time O(n log n).

Initially, it is created a node for each distinct character, with a frequency value called weight, which correspondes to a singular tree T(i) for {i `∈` [0,n-1]}. The construction of the tree follow a bottom up priority queue (heap) with this array of tree roots as input and builds up the Huffman Tree (H.F.) as output.

(in able to see a visual example of H.F. build, check out Figure-2.3.)

The single H.T. resulting from the construction can be interpreted going left as the bit 0 and right as the bit 1. Then the path from the root to a leaf spells out the code C(n) of that node(n). These paths need to be explicitly "translated" so that the original message can be decrypted.

Useful Media:

* https://www.geeksforgeeks.org/dsa/huffman-coding-greedy-algo-3/
* https://youtu.be/co4_ahEDCho
