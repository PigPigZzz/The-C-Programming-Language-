//
// Created by xjs on 2020/2/7.
//

#include "Tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Tree creatTree()
{
    struct Tree root = {NULL};
    return root;
}

struct Tnode *pushTree(struct Tree *root, char *str, int n)
{
    return root->root = insertTnode(root->root, str, n);
}

static struct Tnode *insertTnode(struct Tnode *node, char *str, int n)
{
    int flag;
    if(node == NULL)
    {
        node = Talloc();
        node->str = strndup(str, n);
        node->strlist[node->list_size++] = strdup(str);
        return node;
    }
    else if((flag = strncmp(str, node->str, n)) < 0)
        node->left = insertTnode(node->left, str, n);
    else if(flag > 0)
        node->right = insertTnode(node->right, str, n);
    else
        node->strlist[node->list_size++] = strdup(str);
    return node;
}

void printTree(struct Tree *root)
{
    recursionTree(root->root, printNode);
}

void deleteTree(struct Tree *root)
{
    freeNode(root->root);
    root->root = NULL;
}

static void freeNode(struct Tnode *node)
{
    if(node == NULL)
        return;
    freeNode(node->left);
    freeNode(node->right);
    for(int i = 0; i < node->list_size; i++)
        free(node->strlist[i]);
    free(node->str);
    free(node);
}

static void printNode(struct Tnode *node)
{
    printf("group: %s\n", node->str);
    for(int i = 0; i < node->list_size; i++)
        printf("%s\n", node->strlist[i]);
    putchar('\n');
}

void recursionTree(struct Tnode *node, void (*callback)(struct Tnode *))
{
    if(node == NULL)
        return;
    recursionTree(node->left, callback);
    callback(node);
    recursionTree(node->right, callback);
}

static struct Tnode *Talloc()
{
    struct Tnode *node = (struct Tnode*)malloc(sizeof(struct Tnode));
    memset(node, 0, sizeof(struct Tnode));
    return node;
}