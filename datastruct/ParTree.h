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
        count = 0;
    }
    ParTreeNode()
    {
        parent = null; count = 0;
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
    void setDate(T &data)
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

#endif