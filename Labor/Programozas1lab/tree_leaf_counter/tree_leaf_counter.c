#include <stdlib.h>


typedef struct _node {
    int data;
    struct _node* left;
    struct _node* right;
} node;

int leaf_nodes(node *root)
{
    if (root == NULL)
        return 0;
    
    return leaf_nodes(root->left) + leaf_nodes(root->right) + ((root->left == NULL && root->right == NULL) ? 1 : 0);
    
}