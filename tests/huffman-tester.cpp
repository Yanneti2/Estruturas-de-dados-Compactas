#include "huffman.h"
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <queue>
#include <cmath>
#include <map>
using namespace std;

int main (void) {
	// WORST CASE ENTROPY TEST:
	
	
	// 111 110 101 011 100 010 001 000, sequence of n = 3 bits with num of encodings of same lenght = 8
	cout << worst_case_entropy(8.0) << endl;	
	// abraabracadabra => a,b,c,d,r with |U| = 15 elements, such that are 5 distinc chars  with diff Pr(u), to encode them all with encodings of same len we need at least:
	cout << worst_case_entropy(5.0) << " bits" << endl << "Ceil: " << ceil(worst_case_entropy(5.0)) << endl << endl;

	// PROBABILITIES TEST:

	// 1,3,3,3,4 => "a", "abc", "bca", "cab", "caba"	
	// esperado: b 0.2, r 0.2, a 0.4, c 0.1, d 0.1, 
	cout << "T1:" <<endl;
	string str = "bracadabra";
	priority_queue<Tree::Node*, vector<Tree::Node*>, Tree::compareNodes> rel = probabilities_frequency(str,true);	
	priority_queue<Tree::Node*, vector<Tree::Node*>, Tree::compareNodes> temp(rel);
	while (!temp.empty()){
		cout << temp.top()->data << " " << temp.top()->frequency << endl;
		temp.pop();
	}
	cout << endl;
	
	cout << "T2:" <<endl;
	string s = "bananaabacate";
	priority_queue<Tree::Node*, vector<Tree::Node*>, Tree::compareNodes> rel1 = probabilities_frequency(s,true);
	priority_queue<Tree::Node*, vector<Tree::Node*>, Tree::compareNodes> temp1(rel1); 
	while (!temp1.empty())
	{
		cout << temp1.top()->data << " " << temp1.top()->frequency << endl;
		temp1.pop();
	}	
	cout << endl;

	cout << "T3:" <<endl;
	string gonzalo = "abracadabra";
	priority_queue<Tree::Node*, vector<Tree::Node*>, Tree::compareNodes> navarro = probabilities_frequency(gonzalo,true);
	priority_queue<Tree::Node*, vector<Tree::Node*>, Tree::compareNodes> temp2(navarro); 
	while (!temp2.empty()){
		cout << temp2.top()->data << " " << temp2.top()->frequency << endl;
		temp2.pop();
	}
	cout << endl;

	// HUFFAN BUILD AND ENCODING TEST:

	Tree::Node* root = build_huffman(rel);
	cout <<  "T1: " <<endl;
	map<char,string> t;
	huffman_coding(root,t,"");
	for(auto const& hhh : t){cout<<hhh.first<<" - "<<hhh.second<<endl; }
	cout<<endl;

	Tree::Node* root1 = build_huffman(rel1);
	cout << "T2:"<<endl;
	map<char,string> t1;
	huffman_coding(root1,t1,"");	
	for(auto const& h : t1){ cout << h.first <<" - " << h.second << endl; }
	cout << endl;

	Tree::Node* root2 = build_huffman(navarro);
	cout << "T3:" << endl;
	map<char,string> t2;
	huffman_coding(root2,t2,"");
	for(auto const& hh : t2) { cout << hh.first << " - " << hh.second << endl; }
	cout << endl;

	// MINIMUM AND AVERAGE CODE LENGTH TEST:
	
	// navarro: probability = navarro(priority_queue)->frequency, code_lenght = t2->second. 
	vector<unsigned long int> vvv1;
	vector<double>vvv2;
	while(!rel.empty()){
		Tree::Node* atual = rel.top();
		rel.pop();
		double freq = atual->frequency;
		unsigned long int size = t[atual->data].size();
		vvv1.push_back(size);
		vvv2.push_back(freq);
	}
	double setSize = vvv1.size();
	cout<<"T1 Average Code Length: "<<average_length_codes(vvv1,vvv2)<<endl<<"T1 Minimum Average Code Length: "<<minimum_average_code_length(vvv2)<<endl<<"T1 Worst Case Entropy: "<<worst_case_entropy(setSize)<<endl<<endl;

	vector<unsigned long int> vv1;
	vector<double>vv2;
	while(!rel1.empty()){
		Tree::Node* atual = rel1.top();
		rel1.pop();
		double freq = atual->frequency;
		unsigned long int size = t1[atual->data].size();
		vv1.push_back(size);
		vv2.push_back(freq);
	}
	double setSizee = vv1.size();
	cout<<"T2 Average Code Length: "<<average_length_codes(vv1,vv2)<<endl<<"T2 Minimum Average Code Length: "<<minimum_average_code_length(vv2)<<endl<<"T2 Worst Case Entropy: "<<worst_case_entropy(setSizee)<<endl<<endl;

	vector<unsigned long int> v1;
	vector<double>v2;
	while(!navarro.empty()){
		Tree::Node* atual = navarro.top();
		navarro.pop();
		double freq = atual->frequency;
		unsigned long int size = t2[atual->data].size();
		v1.push_back(size);
		v2.push_back(freq);
	}
	double setSizeee = v1.size();
	cout<<"T3 Average Code Length: "<<average_length_codes(v1,v2)<<endl<<"T3 Minimum Average Code Length: "<<minimum_average_code_length(v2)<<endl<<"T3 Worst Case Entropy: "<<worst_case_entropy(setSizeee)<<endl<<endl;

	return 0;
}
