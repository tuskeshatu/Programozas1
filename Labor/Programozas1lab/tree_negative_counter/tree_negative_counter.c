#include <stdlib.h>

typedef struct _node {
    double data;
    struct _node* left;
    struct _node* right;
} node;

int negatives(node *root)
{
    if (root == NULL)
        return 0;

    return negatives(root->left) + negatives(root->right) + ((root->data < 0 ? 1 : 0));
}