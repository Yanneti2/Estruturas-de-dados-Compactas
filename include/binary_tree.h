#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_BINARY_TREE_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_BINARY_TREE_H

class Tree{
	public:
		typedef struct Node {
			struct Node* left;
			struct Node* right;
			bool marked;
		}node;

		Tree();
		~Tree();
		Node* create_node();
		void print_tree(Node* root);
		Node* getRoot();
		bool getMarked();
		bool isEmpty(Node* root);

	private:
		Node* root;
};

#endif
