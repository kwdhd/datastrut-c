#ifndef KWDHD_GRAPH_H
#define KWDHD_GRAPH_H

#include <stdio.h>
#include <stdio.h>
#include <memory.h>
#include <vector>

#define UNVISITED (1<<31)
#define INFINITY (~(unsigned int)0>>3)
#define VISITED 1

using namespace std;

// Edge Class
class Edge
{
public:
    int from;
    int to;
    int weight;
    Edge(int from = -1, int to = -1, int weight = 0)
    {
        from = from; to = to; weight = weight;
    }
    int Weight()
    {
        return weight;
    }
    int FromVertex()
    {
        return from;
    }
    int ToVertex()
    {
        return to;
    }
    void SetEdge(int from, int to, int weight=0)
    {
        from = from; to = to; weight = weight;
    }
};

// Graph Base Class
class Graph
{
public:
    int numVertex;
    int numEdge;
    int *Mark;  // 访问记录器
    int *Indegree; // 入度

    Graph(int numvertex)
    {
        numVertex = numvertex;
        numEdge = 0;
        Indegree = new int[numvertex];

        Mark = new int[numvertex];
        for(int i = 0; i< numvertex; i++)
        {
            Mark[i] = UNVISITED;
            Indegree[i] = 0;
        }
    }

    ~Graph()
    {
        delete [] Mark;
        delete [] Indegree;
    }

    //virtual Edge FirstEdge(int oneVertex) = 0;  // 相关联的第一条边
    //virtual Edge NextEdge(Edge preEdge) = 0;     // 与preEdge相交的下一条边

    int VerticesNum()
    {
        return numVertex;
    }
    int EdgesNum()
    {
        return numEdge;
    }
    bool IsEdge(Edge oneEdge)
    {
        if(oneEdge.weight>0 && oneEdge.weight < INFINITY && oneEdge.to >= 0)
            return true;
        else
            return false;
    }
    
   // virtual bool SetEdge(int form, int to, int weight=0) = 0;
   // virtual bool DelEdge(int from, int to) = 0;

    int FromVertex(Edge oneEdge)
    {
        return oneEdge.FromVertex();
    }
    int ToVertex(Edge oneEdge)
    {
        return oneEdge.ToVertex();
    }
    int Weight(Edge oneEdge)
    {
        return oneEdge.Weight();
    }
    void ClearMarks()
    {
        for(int i = 0; i < numVertex; i++)
        {
            Mark[i] = UNVISITED;
        }
    }
    //virtual void prim(int vertex) = 0;//生成最小树
    //virtual int DFS(int vertex) = 0;//深度优先搜索
    //virtual void DFS(int node,int v[],int& n) = 0;
    //virtual void BFS(int vertex) = 0;//广度优先搜索
    //virtual bool IsConnected() = 0;//判断是否连通
    //virtual void ConnectedNum() = 0;//连通分量的数目
};

// 用邻接矩阵存储的无向图
// 矩阵的值小于0表示没有这条边,大于0表示权值
class Graphm : public Graph
{
public:
    int ** matrix;

    Graphm(int numVertex) : Graph(numVertex)
    {
        matrix = (int**)new int*[numVertex];
        for(int i = 0; i < numVertex; i++)
            matrix[i] = new int[numVertex];
        for(int i = 0; i < numVertex; i++)
            memset(matrix[i],0,numVertex*sizeof(int));
    }
    ~Graphm()
    {
        for(int i = 0; i < numVertex; i++)
            delete [] matrix[i];
        delete [] matrix;
    }

    Edge FirstEdge(int oneVertex);  // 返回以oneVertex为起点的第一条边
    Edge NextEdge(Edge preEdge);    // 返回与preEdge相交的下一条边
    bool SetEdge(int from, int to, int weight);  // 插入一条边
    bool DelEdge(int from, int to);

    bool InsertVertex(int oneVertex); // 插入一个节点,把对角线上相应元素置为1
    bool DelVertex(int oneVertex);

    void prim(int vertex);//生成最小树
    int DFS(int vertex);//深度优先搜索
    void DFS(int node,int v[],int& n);
    void BFS(int vertex);//广度优先搜索
    bool IsConnected();//判断是否连通
    void ConnectedNum();//连通分量的数目
    int do_traverse(char* type = "DFS");
    void Print_Matrix();
    void Debug()
    {
        printf("numVertex: %d,numEdges: %d \n",numVertex,numEdge);
        printf("Mark...\n");
        for(int i = 0; i < numVertex; i++)
            printf("%d  ",Mark[i]);
        printf("\n");
        printf("Indegree...\n");
        for(int i = 0; i< numVertex; i++)
            printf("%d  ",Indegree[i]);
        printf("\n");
        printf("matrix...\n");
        Print_Matrix();
    }
};

class Dist
{
public:
    int index;
    int len;
    int pre;
    Dist()
    {
        index = 0; len = 0; pre =0;
    }
    Dist(int ix, int len, int pre)
    {
        index = ix; this->len = len; this->pre = pre;
       // printf("%d, %d...\n",ix,index);
    }
    ~Dist(){}
    Dist(const Dist&  d1)
    {
        index = d1.index;
        len = d1.len;
        pre = d1.pre;
    }
    bool operator<(const Dist &arg)
    {
        return (this->len < arg.len);
    }
    bool operator==(const Dist &arg)
    {
        return (this->len == arg.len);
    }
    bool operator>(const Dist &arg)
    {
        return (this->len > arg.len);
    }
    bool operator>=(const Dist &arg)
    {
        return (this->len >= arg.len);
    }
    bool operator<=(const Dist &arg)
    {
        return (this->len <= arg.len);
    }

};   

// 用邻接矩阵存储的有向图
// 矩阵的值小于0表示没有这条边,大于0表示权值
// Directed Matrix Graph
class GraphDM : public Graphm
{

public:
    GraphDM(int numVertex) : Graphm(numVertex)
    {

    }
    ~GraphDM()
    {
    }
    bool SetEdge(int from, int to, int weight);  // 插入一条边
    bool DelEdge(int from, int to);

    void Topsort(); //拓扑排序
    void Topsort_DFS(); //使用深度遍历的拓扑排序
    void Do_toposort(int v, int *result, int &tag);

    void Dijkstra(int v1,vector<Dist> &vt1);
    int** Floyd();
    Dist** Floyd(Dist **&arr);
    vector<vector<Dist>> * Path_Dijkstra();
    vector<Edge>& Prim(vector<Edge> &arrEdge,int v = 0);


    void Debug()
    {
        printf("numVertex: %d,numEdges: %d \n",numVertex,numEdge);
        printf("Mark...\n");
        for(int i = 0; i < numVertex; i++)
            printf("%d  ",Mark[i]);
        printf("\n");
        printf("Indegree...\n");
        for(int i = 0; i< numVertex; i++)
            printf("%d  ",Indegree[i]);
        printf("\n");
        printf("matrix...\n");
        Print_Matrix();
    }
};


bool Cmp_Dist(Dist &d1, Dist &d2);

#endif