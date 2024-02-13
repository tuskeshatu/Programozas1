#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int data;
    struct _node *left;
    struct _node *right;
} node;

void insert(node *root, int insert_val)
{
    if (root == NULL)
    {
        root = malloc(sizeof(node));
        root->data = insert_val;
        root->left = NULL;
        root->right = NULL;
        return;
    }

    node *curelem = root;
    while (1)
    {
        if (insert_val == curelem->data)
            return;

        if (insert_val < curelem->data)
        {
            if (curelem->left == NULL)
                break;
            curelem = curelem->left;
        }
        else
        {
            if (curelem->right == NULL)
                break;
            curelem = curelem->right;
        }
    }

    node *insert = malloc(sizeof(node));

    if (curelem->data > insert_val)
        curelem->left = insert;
    else
        curelem->right = insert;

    insert->data = insert_val;
    insert->left = NULL;
    insert->right = NULL;

    return;
}