#ifndef BSTREE_H
#define BSTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef DataType int;
typedef struct BSTreeNode{
    DataType data;
    struct BSTreeNode left;
    struct BSTreeNode right;
}Bnode,*pBnode;

typedef struct BSTree{
    int size;
    pBnode root;
}Btree,*pBtree;

//
void Init_BSTree();

int BSTree_Insert(DataType data);

int BSTree_Find(DataType data);

int BSTree_Delete(DataType data);
//
void Init_BSTree(pBtree btree)
{
    printf("initializing BSTree..\n");
    btree->size = 0;
    btree->root = NULL;
}

int BSTree_Insert(pBtree btree,DataType data)
{
    return 0;
}

int BSTree_Find(pBtree btree,DataType data)
{
    if(btree->root->data == data)
        return 1;
    if(BSTree_Find(btree->root->left,data))
        return 1;
    if(BSTree_Find(btree->root->right,data))
        return 1;
    return 0;
}

int BSTree_Delete(DataType data)
{
}
#endif