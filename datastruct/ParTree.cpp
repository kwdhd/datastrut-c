#include "ParTree.h"
#include <stdio.h>

template <class T>
ParTreeNode<T>* ParTree<T>::Find(ParTreeNode<T> *node) const
{   // ���node�Ǹ��ڵ�,�᷵���Լ�...
    if( node == NULL)
        return NULL;
    while(node->getParent())
        node = node->getParent();
    return node;
}

template <class T>
ParTreeNode<T>* ParTree<T>::Find(int i) const
{   // ���node�Ǹ��ڵ�,�᷵���Լ�...
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
        return; // ��ͬһ��������,���úϲ�...
    else
    {   // ��������ٵ����ϲ���������������
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
