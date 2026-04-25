#include "binary_tree.h"
#include "general_tree.h"
#include <vector>

#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_DFS
#define ESTRUTURAS_DE_DADOS_COMPACTAS_DFS

/*
 * Faz sentido isso aq ter um header e nao ser so transferido como private
 * para dentro da classe que ele diz respeito (binary tree or general tree)?
 *
*/

void dfs_bt2(vector<int>& V, Tree::Node* node);
void dfs_bt(bitVector* B, Tree::Node* root);
void dfs_gt(bitVector* B, Gtree::gNode* root);

#endif
