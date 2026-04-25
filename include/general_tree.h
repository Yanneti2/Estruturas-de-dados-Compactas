#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_GENERAL_TREE_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_GENERAL_TREE_H

#include <vector>
using namespace std;

class Gtree{
	public:
		typedef struct gNode{
			bool marked;
			vector<gNode*> Children;
		}gNode;

		Gtree();
		~Gtree();
		gNode* create_node();
		void append_nnode(gNode* root);
		void add_node(gNode* into, gNode* dummy);
		void print_tree(gNode* root);
		gNode* getRoot();
		bool getMarked();
		vector<gNode*> getChildren();
		bool isEmpty(gNode* root);
	private:
		gNode* root;
};

#endif
