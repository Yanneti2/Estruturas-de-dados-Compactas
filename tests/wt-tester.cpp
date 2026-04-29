#include "../include/bitvector.h"
#include "../include/wt.h"
#include <iostream>
using namespace std;

int main (void){
	WaveletTree* wt = new WaveletTree("mississippi",nullptr);
	//wt->print();
	cout << access(wt,2) << access(wt,4) << access(wt,8) << endl;
	return 0;
}
