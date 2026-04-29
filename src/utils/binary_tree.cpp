#include "../../include/binary_tree.h" 
#include <iostream>
#include <queue>
using namespace std;

// builds a new Tree initializating the root
Tree::Tree(){
	this->root = new Node();
	this->root->left = this->root->right = nullptr;
	this->root->data = '$';
	this->root->frequency = 0.0;
}	

// frees the memory of the existing now old tree
Tree::~Tree(){
	if (!this->root) return;
	queue<Node*> q;
	q.push(root);
	while(!q.empty()){
		int nodes = q.size();
		for (int i = 0; i < nodes; i ++){
			Node* aux = q.front();
			q.pop();
			if (aux->left) q.push(aux->left);
			if (aux->right) q.push(aux->right);
			delete aux;
		}
	}
}
// Returns 0 if not empty and 1 if empty
bool Tree::isEmpty(Node* root){ if (root) return 0; else return 1; } 

// Return the root of the given existen Tree
Tree::Node* Tree::getRoot(){ return this->root; }

// Create and returns a new node
Tree::Node* Tree::create_node(char data, double freq){
	Node* nnode = new Node();
	nnode->left = nnode->right = nullptr;
	nnode->data = data; // standart = $
	nnode->frequency = freq; // standar = 0.0
	return nnode;
}

// Prints the Tree in BFS order
void Tree::print_tree(Node* root){
	if (!root) return;
	queue<Node*> q;
	q.push(root);
	while(q.size()){
		int nodes = q.size();
		for (int i = 0; i < nodes; i++){
			Node* aux = q.front(); 
			q.pop();
			std::cout << "[" << aux->data << "] " << std::endl;
			if (aux->left) q.push(aux->left);
			if (aux->right) q.push(aux->right);
		}
		std::cout << "\n";
	}
}

/* Transforms the existen tree into a queue of nodes in BFS
vector* v explicit_to_implicit(){
	
}
*/
