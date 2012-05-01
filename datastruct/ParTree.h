#ifndef KWHDHD_PARTREE
#define KWDHD_PARTREE

// ÿ�Խ��ֻ����ָ�򸸽ڵ��ָ��
// ���ڵ��ָ��Ϊ��
template <class T>
class ParTreeNode
{
private:
    ParTreeNode *parent;
    T data;
    int count; // �ӽڵ���
public:
    ParTreeNode(ParTreeNode *parent, T data)
    {
        this->parent = parent;
        this->data = data;
        count = 1;
    }
    ParTreeNode()
    {
        parent = NULL; count = 0;
    }
    ParTreeNode(const ParTreeNode &ptnode)
    {
        parent = ptnode->parent;
        data = ptnode->data;
        count = ptnode->count;
    }

    T& getData()
    {
        return data;
    }
    void setData(T &data)
    {
        this->data  = data;
    }
    ParTreeNode<T>* getParent()
    {
        return parent;
    }
    void setParent(ParTreeNode<T>* parent)
    {
        this->parent = parent;
    }
    int getCount()
    {
        return count;
    }
    void setCount(int count)
    {
        this->count = count;
    }
};
// 
template <class T>
class ParTree
{
public:
    ParTreeNode<T>* arr;    // �����鱣����
    int size;               // ����
    int count;              // �����

    ParTree(int size)
    {
        this->size = size;
        arr = new ParTreeNode<T>[size];
    }
    ~ParTree()
    {
        delete [] arr;
    }
    // ������������...
    void ReSize(int newSize)
    {
        if( newSize <= size)
            return;
        ParTreeNode<T>* newArr = ParTreeNode<T>[newSize];
        for(int i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }
        delete [] arr;
        arr = newArr;
        size = newSize;
    }
    // �ҵ� i or node �ĸ��ڵ�
    ParTreeNode<T>* Find(ParTreeNode<T>* node) const;
    ParTreeNode<T>* Find(int i) const;
    // ���±�Ϊi,j�Ľ��ϲ�Ϊһ������
    void Union(int i, int j);
    // �ж�i,j�Ƿ���ͨһ��������
    bool Different(int i, int j);
};


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
    ParTreeNode<T> *p1 = Find(&arr[i]);
    ParTreeNode<T> *p2 = Find(&arr[j]);

    return p1 == p2;
}

#endif