#include "ParTree.h"
#include <stdio.h>

template <class T>
ParTreeNode<T>* ParTree<T>::Find(ParTreeNode<T> *node) const
{   // 如果node是根节点,会返回自己...
    if( node == NULL)
        return NULL;
    while(node->getParent())
        node = node->getParent();
    return node;
}

template <class T>
ParTreeNode<T>* ParTree<T>::Find(int i) const
{   // 如果node是根节点,会返回自己...
    if( i<0 || i >= size)
        return NULL;
    ParTreeNode<T> *node = &arr[i];
    while(node->getParent())
        node = node->getParent();
    return node;
}

template <class T>
void ParTree<T>::Union(int i, int j)
{   
    ParTreeNode<T> *p1 = Find(i);
    ParTreeNode<T> *p2 = Find(j);

    int c1 = p1->getCount();
    int c2 = p2->getCount();

    if( p1 == p2)
        return; // 在同一个子树中,不用合并...
    else
    {   // 将结点数少的树合并到结点数多的树中
        (c1 > c2) ? ( p2->setParent(p1),p1->setCount(p1->getCount()+p2->getCount())) : (p1->setParent(p2),p2->setCount(p1->getCount()+p2->getCount()));
    }

    return;
}

template <class T>
bool ParTree<T>::Different(int i, int j)
{
    ParTreeNode<T> p1 = Find(&arr[i]);
    ParTreeNode<T> p2 = Find(&arr[j]);

    return p1 == p2;
}
