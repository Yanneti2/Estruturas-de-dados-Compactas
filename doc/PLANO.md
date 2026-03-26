# Study Plan

Navarro:

* [X] chapter 2;
* [X] chapter 4;
* [ ] chapter 8;
* [ ] chapter 12;

Jacobson:

* [ ] chapter 5;
* [ ] chapter 8;

RRR:

* [ ] Study RRR theory;

(11/03/2026 meeting):

* [X] Huffman's algorithm (C2);
* [X] Bitvectors (C4);
* [X] Ranking and Select operations in O(1);

  Future:

  - [X] Continue bit array implementation (append_0 and append_1 + "reorganize sorting/organization algorithm??");
  - [ ] Tree compression, study some existent tree implementation and suggest some better representation/algorithm for it;

(25/03/2026 meeting):

    Changes to make (TODO):

* [ ] Change "nivel1" and "nivel2" len arguments to (NBITS)² and NBITS respectifully;
* [ ] Use std::popcount in the rank construction and calcularion;
* [ ] Improve the readibility (clean code) of jacobson.h and .cpp;
* [ ] Change type from ULL to bitvectors in jacobson.*;
* [ ] Include uarray.h as method from bitvector.h;

    Implementation:

* [ ] Implement Jacobson`s Select method;
* [ ] Test Select with binary search X binary search and directory;
* [ ] Compare Select(j) calculation doing only binary search with the whole bitvector;
* [ ] Increment the level1.size() to 512 bits as standart => better binary search;
