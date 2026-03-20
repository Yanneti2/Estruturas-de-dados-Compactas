# Types of Entropy

The most basic notion of entropy is that it is the minimum number of bits required by identifiers, called codes C(n). One type of entropy, called **Shannon Entropy**, assumes there is a source with u elements, each with known probabilities P(u). Using codes of len l(u) bits, we can assume the minimum possible average C(u) len with:

- **H**(**U**)**= **−**u**∈**U**∑P**(**u**)**log**2P**(**u**)

Considering l(u) = log2P(u):

- **E**[**ℓ**(**u**)]**=**∑**P**(**u**)**ℓ**(**u**)

The **Empiric Entropy**, on the other hand, shares the same objective as the Shannon, but its a aproximatly algorithm based on observed facts (u dont know the real probabilities). We use P(u) as frequency(u)/n, where n is the total number of cases/elements given by the source:

- **H=**−*∑**P***(**u**)**lo**gP(**u**)

It works as a valid aproximation of the real entropy.

# Codes

"The entropy tells us the minimum average code length we can achieve, and even sug-gests giving each symbolsa code with length log1Pr(s)to reach that optimum. To obtainkth-order entropy, we must use a different set of codes for each different previous con-text. However, in either case the entropy measure does not tell how to build a suitableset of codes."

An encoding is said unambiguos if, there is no relation between the prefixes of the gives codes C(u) of a set of elements u ∈ U.

    Ambiguos: C(u1) = 0, C(u2) = 1, C(u3) = 00.
	Example: 000 => u1u1u1, or u3u1, or u1u3
	Unambiguos: C(u1) = 0, C(u2) = 10, C(u3) = 11.

(to see a unambiguos shannon encoding example, go to "scodes.png")

Given a set of binary codes of lenght l(uk) each, to craft a set of unique and unabiguos codes (prefix freee) we can use the **Kraft-McMillan inequality,** so that is satisfies:

- **∑2(**−**ℓ**(**u**)) ≤ 1

# Huffman Codes

The problem:

Imagine we want to encode a simple message like "hello world", using the traditional ASCII Binary Character Table, we would have something along the lines of:

```
01101000 01100101 01101100 01101100 01101111 (hello)
01110111 01101111 01110010 01101100 01100100 (world)
```

In this representation (im ignoring the ascii code repo) each char uses 8 bits. But the matter is it dosent concern itself with the frequency of that symbol appearence. Take a closer look at the letter 'l', it appears 3 times, or has a weight of 3/10, that means "01101100" is repeated three times. Thats a unnecessary waste of bits!! That's when it gets redundant, causing a considerable drawback in performance.

(to see the continuation of that example, check "HT-example")

In that context, the Huffman algorithm was created. This coding made by David A. Huffman is a lossless data compression algorithm that reduces the total number of bits required to represent text. It does so by assigning binary codes to the frequently used symbols, in order to create an optimal prefix code tree.

Initially, it is created a node for each distinct character, with a frequency value called weight, which correspondes to a singular tree T(i) for {i `∈` [0,n-1]}. The construction of the tree follow a bottom up priority queue (heap) with this array of tree roots as input and builds up the Huffman Tree (H.F.) as output. This  convertion into a binary tree takes O(n log n) time.

(in able to see a visual example of H.F. build, check out "Figure-2.3")

The single H.T. resulting from the construction can be interpreted going left as the bit 0 and right as the bit 1. Then the path from the root to a leaf spells out the code C(n) of that node(n). These paths need to be explicitly "translated" so that the original message can be decrypted.

Useful Media:

* https://www.geeksforgeeks.org/dsa/huffman-coding-greedy-algo-3/
* https://youtu.be/co4_ahEDCho
* https://itsfuad.medium.com/understanding-huffman-coding-an-efficient-compression-algorithm-1f0b6c2df88e
* http://sticksandstones.kstrom.com/appen.html
