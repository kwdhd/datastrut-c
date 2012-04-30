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

#endif