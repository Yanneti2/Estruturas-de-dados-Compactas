#include <vector>
#include "binary_tree.h"
#include "bitvector.h"
#include "dfs.h"
#include "general_tree.h"
#include <stack>
#include <vector>

#define ULI unsigned long int
/*
 * A partir de uma queue G contendo todos os vertices/nodes de um grafo,
 * bem como de um node inicial S (normalmente root), marcamos cada node como um
 * bool true or false (ja passado ou nao) no decorrer da DFS
*/

/*
void dfs-visit(G,u){
	for each v in G.N(u) // vizinhanca de u
		if v.marked == false
			v.marked = true
			dfs-visit(G,V)
}

void dfs(G) {
	if (!root) return;
	for each vertex u in G.V
		u.marked = false
	for each vertex u in G.V
		if u.marked == false
			u.marked = true
			dfs-visit(G,u)
}
*/

// Same as below but with vector instead of bitvector
void dfs_bt2(vector<int>& V, Tree::Node* node){
	if (!node){
		V.push_back(0);
		return;
	}	
	else {
		V.push_back(1);
		if (!node->left && !node->right){
		       	V.push_back(0);
		       	node->marked = true;
		       	return;
		}
		if (node->left && node->left->marked == false) dfs_bt2(V,node->left);
		node->marked = true;
		if (node->right && node->right->marked == false) dfs_bt2(V,node->right);
		V.push_back(0);
	}
}

// Binary compressed representation for a general binary tree
void dfs_bt(bitVector* B, Tree::Node* node){
	if (!node){
		B->append0();
		return;
	}	
	else {
		B->append1();
		if (!node->left && !node->right){
		       	B->append0();
		       	node->marked = true;
		       	return;
		}
		if (node->left && node->left->marked == false) dfs_bt(B,node->left);
		node->marked = true;
		if (node->right && node->right->marked == false) dfs_bt(B,node->right);
		B->append0();
	}
}
// root->marked == true
// Return a bitvector with the binary sequence of that general tree,
// cap = 2n; n = |treeNodes|

// Binary compressed representation of a general tree
void dfs_gt(bitVector* B, Gtree::gNode* node){
	if (!node){
		B->append0();
		return;	
	}else{
		B->append1();
		if (node->Children.size() == 0){
			B->append0();
			node->marked = true;
			return;	
		}else{
			ULI s = node->Children.size();
			for(ULI i = 0; i < s; i++){
				Gtree::gNode* aux = node->Children[i];
				if (aux && aux->marked == false) dfs_gt(B,aux);	
			}
			node->marked = true;
			B->append0();
		}	
	}	
}
