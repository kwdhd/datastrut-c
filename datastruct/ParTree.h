#ifndef KWHDHD_PARTREE
#define KWDHD_PARTREE

// 每对结点只保存指向父节点的指针
// 根节点的指针为空
template <class T>
class ParTreeNode
{
private:
    ParTreeNode *parent;
    T data;
    int count; // 子节点数
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
    ParTreeNode<T>* arr;    // 用数组保存结点
    int size;               // 容量
    int count;              // 结点数

    ParTree(int size)
    {
        this->size = size;
        arr = new ParTreeNode<T>[size];
    }
    ~ParTree()
    {
        delete [] arr;
    }
    // 增大树的容量...
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
    // 找到 i or node 的根节点
    ParTreeNode<T>* Find(ParTreeNode<T>* node) const;
    ParTreeNode<T>* Find(int i) const;
    // 把下标为i,j的结点合并为一棵子树
    void Union(int i, int j);
    // 判定i,j是否在通一颗子树中
    bool Different(int i, int j);
};


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
    ParTreeNode<T> *p1 = Find(&arr[i]);
    ParTreeNode<T> *p2 = Find(&arr[j]);

    return p1 == p2;
}

#endif