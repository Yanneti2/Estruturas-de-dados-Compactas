#include <iostream>
#include "bitvector.h"
#include "dfs.h"
#include "binary_tree.h"
#include "general_tree.h"
#include <vector>

// Fazer os assert para as funcoes (make)
// Test difference in speed using <vector> and bitVector();
int main (void){
	// size = 2N, N = |treeNodes|
	Tree* t1 = new Tree();
	Tree::Node* r1 = t1->getRoot();
	Tree::Node* aux = r1;
	for (int i = 0; i < 10; i++){
		aux->left = t1->create_node();
		aux = aux->left;
			
	}
	bitVector* B1 = new bitVector(64,2.0); //size = 22
	dfs_bt(B1,r1);
	B1->print();
	//vector<int> v;
	//dfs_bt2(v, r1);
	//std::cout << v.size() << "\n";
	//for (unsigned long int i = 0; i < v.size(); i++) { std::cout << v[i]; }
	//std::cout << "\n";

	Tree* t2 = new Tree();
	Tree::Node* r2 = t2->getRoot();
	r2->left = t2->create_node();
	r2->right = t2->create_node();
	Tree::Node* au = r2->left;
	au->left = t2->create_node();
	bitVector* B2 = new bitVector(64,2.0); //size = 8
	dfs_bt(B2,r2);
	B2->print();
	//vector<int> h;
	//dfs_bt2(h, r2);
	//std::cout << h.size() << "\n";
	//for (unsigned long int i = 0; i < h.size(); i++) { std::cout << h[i]; }
	//std::cout << "\n";	

	Tree* t3 = new Tree();
	Tree::Node* r3 = t3->getRoot();
	r3->left = t3->create_node();
	Tree::Node* a = r3->left;
	a->left = t3->create_node();
	a->right = t3->create_node();
	bitVector* B3 = new bitVector(64, 2.0); //size = 8
	dfs_bt(B3,r3);
	B3->print();
	//vector<int> t; dfs_bt2(t, r3);
	//std::cout << t.size() << "\n";
	//for (unsigned long int i = 0; i < t.size(); i++) { std::cout << t[i]; }
	//std::cout << "\n";

	//vector<int> j;
	//j.push_back(0);
	//j.push_back(1);
	//std::cout << j.size() << "\n";
	//for (unsigned long int i = 0; i < j.size(); i++){
	//	std::cout << i;
	//}
	//std::cout << "\n";
	
	Gtree* g1 = new Gtree();
	Gtree::gNode* rg1 = g1->getRoot();
	for (int i = 0; i < 3; i++){ g1->append_nnode(rg1); }
	bitVector* B4 = new bitVector(64,2.0);	
	dfs_gt(B4,rg1);
	B4->print();

	Gtree* g2 = new Gtree();
	Gtree::gNode* rg2 = g2->getRoot();
	Gtree::gNode* dummy = g2->create_node();
	g2->append_nnode(rg2);
	g2->add_node(rg2,dummy);
	for (int i = 0; i < 3; i++)g2->append_nnode(dummy);
	g2->append_nnode(rg2);
	bitVector* B5 = new bitVector(64,2.0);
	dfs_gt(B5,rg2);
	B5->print();

	Gtree* g3 = new Gtree();
	Gtree::gNode* rg3 = g3->getRoot();
	for (int i = 0; i < 4; i++){ g3->append_nnode(rg3); }
	bitVector* B6 = new bitVector(64,2.0);	
	dfs_gt(B6,rg3);
	B6->print();

	return 0;
}
