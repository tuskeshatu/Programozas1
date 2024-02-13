#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct r
{
    struct r *left, *right;
    char name[20 + 1]; // neve
    double w;          // vizhozama
} *river_tree;

void fill(river_tree root)
{
    if (root->left == NULL && root->right == NULL)
        return;

    fill(root->left);
    fill(root->right);

    if (root->left->w < root->right->w)
    {
        strcpy(root->name, root->right->name);
        root->w = root->left->w + root->right->w;
    }
    else
    {
        strcpy(root->name, root->left->name);
        root->w = root->left->w + root->right->w;
    }
}

int main(int argc, char const *argv[])
{
    river_tree root = malloc(sizeof(river_tree));
    root->left = malloc(sizeof(river_tree));
    root->right = malloc(sizeof(river_tree));

    root->left->left = NULL;
    root->left->right = NULL;

    root->right->left = NULL;
    root->right->right = NULL;

    strcpy(root->left->name, "Duna");
    root->left->w = 1.1;

    strcpy(root->right->name, "Drava");
    root->right->w = 0.3;

    fill(root);

    return 0;
}
