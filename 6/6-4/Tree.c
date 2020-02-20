//
// Created by xjs on 2020/2/7.
//

#include "Tree.h"
#include <stdlib.h>
#include <string.h>

struct Tree creatTree()
{
    struct Tree root = {NULL};
    return root;
}

struct Tnode *pushTree(struct Tree *root, void *element, int (*cmp)(void *, void *), void *(*callback_element)(void *, void *))
{
    return root->root = insertTnode(root->root, element, cmp, callback_element);
}

static struct Tnode *insertTnode(struct Tnode *node, void *element, int (*cmp)(void *, void *), void *(*callback_element)(void *, void *))
{
    int flag;
    if(node == NULL)
    {
        node = Talloc();
        node->element = callback_element(element, node->element);
    }
    else if((flag = cmp(element, node->element)) < 0)
        node->left = insertTnode(node->left, element, cmp, callback_element);
    else if(flag > 0)
        node->right = insertTnode(node->right, element, cmp, callback_element);
    else
        node->element = callback_element(element, node->element);
    return node;
}

void printTree(struct Tree *root, void (*callback_print)(void *))
{
    recursionTree(root->root, callback_print);
}

void deleteTree(struct Tree *root, void (*callback_free)(void *))
{
    freeNode(root->root, callback_free);
    root->root = NULL;
}

static void freeNode(struct Tnode *node, void (*callback_free)(void *))
{
    if(node == NULL)
        return;
    freeNode(node->left, callback_free);
    freeNode(node->right, callback_free);
    callback_free(node->element);
    free(node);
}

void recursionTree(struct Tnode *node, void (*callback)(void *))
{
    if(node == NULL)
        return;
    recursionTree(node->left, callback);
    callback(node->element);
    recursionTree(node->right, callback);
}

static struct Tnode *Talloc()
{
    struct Tnode *node = (struct Tnode*)malloc(sizeof(struct Tnode));
    memset(node, 0, sizeof(struct Tnode));
    return node;
}