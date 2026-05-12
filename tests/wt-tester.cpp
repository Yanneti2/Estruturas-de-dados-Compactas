#include "../include/bitvector.h"
#include "../include/wt.h"
#include <iostream>
using namespace std;

int main (void){
	// CONSTRUCTION AND ACESS TESTS:

	WaveletTree* wt = new WaveletTree("mississippi",nullptr);
	cout << endl <<"Print Function: " << endl << endl;
	wt->print(); 
	cout << endl << "Acesso em 2: " << wt->access(2) << endl << "Acesso em 4: " << wt->access(4) << endl << "Acesso em 8: " << wt->access(8) << endl << endl;

	// RANK TESTS:

	cout << "Rank(S,6): " << wt->rank_c('s',6) << endl;
	cout << "Rank(I,6): " << wt->rank_c('i',6) << endl << endl;

	// SELECT TESTS:

	cout << "Select(S,3): " << wt->select_c(1,4,'s',3) << endl;	
	cout << "Select(I,10); " << wt->select_c(1,4,'i',10) << endl << endl;

	//wt->~wt();
	return 0;
}
