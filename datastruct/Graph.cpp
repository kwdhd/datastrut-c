#include "Graph.h"
#include <queue>
#include <memory.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "ParTree.h"
#include <queue>

using namespace std;

// 一些辅助方法
bool CmpEdgeWeight(Edge &e1, Edge &e2); // 比较变得权值大小, e1.weight > e2.weight return true;






// Matrix Graph
Edge Graphm::FirstEdge(int oneVertex)
{
    Edge myEdge;
    myEdge.from = oneVertex;
    myEdge.to = -1;

    for(int i = 0; i < numVertex; i ++)
    {
        if(matrix[oneVertex][i] != 0)
        {
            myEdge.to = i;
            myEdge.weight = matrix[oneVertex][i];
            break;
        }
    }
    return myEdge;
}
Edge Graphm::NextEdge(Edge preEdge)
{
    Edge myEdge;
    myEdge.from = preEdge.from;

    myEdge.to = -1;
    for(int i = preEdge.to+1; i < numVertex; i++)
    {
        if(matrix[preEdge.from][i]!=0)
        {
            myEdge.to = i;
            myEdge.weight = matrix[preEdge.from][i];
            break;
        }
    }
    return myEdge;
}

bool Graphm::SetEdge(int from, int to, int weight)
{
    if( from<0 || from > numVertex-1 || to < 0 || to >numVertex-1)
        return false;
    if(matrix[from][to] <= 0)
    {
        numEdge+=2; // 无向图...
        Indegree[to]++;
    }
    matrix[from][to] = weight;
    matrix[to][from] = weight;
    return true;
}
bool Graphm::DelEdge(int from, int to)
{
    if( from<0 || from > numVertex-1 || to < 0 || to >numVertex-1)
        return false;
    if(matrix[from][to]>0)
    {
        numEdge-=2; // 无向图...
        Indegree[to]--;
    }
    matrix[from][to] = 0;
    matrix[to][from] = 0;
    return true;
}

int Graphm::DFS(int vertex)//深度优先搜索
{
    printf("DFS traverse vertex: %d\n",vertex);
    Mark[vertex] = VISITED;

    for(Edge e = FirstEdge(vertex); IsEdge(e); e=NextEdge(e))
        if( Mark[e.to] == UNVISITED)
            DFS(e.to);
    return 1;
}

int Graphm::do_traverse(char* type)
{
    if(type == NULL || *type == '\0')
        return false;
    ClearMarks();

    for(int i=0; i<numVertex; i++)
        if(Mark[i] == UNVISITED)
        {
            if( *type == 'D' || *type == 'd')
                DFS(i);
            else if( *type == 'B' || *type == 'b')
                BFS(i);
        }
    return true;
}

void Graphm::BFS(int vertex)//广度优先搜索
{
    queue<int> qu;
    qu.push(vertex);
    int ix;

    while(qu.size())
    {
        ix = qu.front(); qu.pop();
        if( Mark[ix] == UNVISITED)
        {
            printf("BFS traverse vertex: %d\n",ix);
            Mark[ix] = VISITED;

            for(int i = 0; i < numVertex; i++)
            {
                if(matrix[ix][i] > 0 && Mark[i] == UNVISITED)
                {   
                    printf("BFS traverse vertex: %d\n",i);
                    qu.push(i); Mark[i] = VISITED;
                }
            }
        }
    }
}
bool Graphm::IsConnected()//判断是否连通
{
    return false;
}
void Graphm::ConnectedNum()//连通分量的数目
{
}
bool Graphm::InsertVertex(int oneVertex)
{
    if( oneVertex>=0 && oneVertex <= numVertex)
        matrix[oneVertex][oneVertex] = 1;
    else
        return false;
    return true;
}
bool Graphm::DelVertex(int oneVertex)
{
    if( oneVertex>=0 && oneVertex <= numVertex)
        matrix[oneVertex][oneVertex] = 0;
    else
        return false;
    return true;
}
void Graphm::Print_Matrix()
{
    for(int i=0; i<numVertex; i++)
    {
        for(int j=0; j<numVertex; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
         
}
// 必须是连通图...
vector<Edge>& Graphm::Prim(vector<Edge> &arrEdge, int v)
{   // 从节点 v 开始
    // 将所有的边放入对
    // 从中选出全最小,且一个节点以在树中,一个不在
    ClearMarks();
    Mark[v] = VISITED;
    vector<Edge> miniHeap;
    int count = 1;  // 已加入结点的计数器
    for(Edge e = FirstEdge(v); IsEdge(e); e = NextEdge(e))
    {
        miniHeap.push_back(e);
    }
    make_heap(miniHeap.begin(),miniHeap.end(),CmpEdgeWeight);

    while(miniHeap.size() > 0)
    {
        int vto = miniHeap.front().to;
        if(Mark[vto] == UNVISITED)
        {   // 将边加入树中
            Mark[vto] = VISITED;
            arrEdge.push_back(miniHeap.front());
            count++;
            // 
            for(Edge e = FirstEdge(vto); IsEdge(e); e = NextEdge(e))
            {
                if(Mark[e.to] == UNVISITED)
                    miniHeap.push_back(e);
            }
        }
        miniHeap.erase(miniHeap.begin());
        make_heap(miniHeap.begin(),miniHeap.end(),CmpEdgeWeight);
    }
    if( count < numVertex)
        printf("不是连通图....\n");
    return arrEdge;
}
// 将定点划分为numVertex个等价类
// 以权的大小为顺序处理Edge
// 当一条边的两个结点分属两个不同的等价类时,合并两个等价类
// 直到只剩一个等价类(如果是连通图)
vector<Edge>& Graphm::Kruskal(vector<Edge> &arrEdge, int v)
{   
    // 等价类的数量
    int count = numVertex;
    // 1.初始化等价类...
    ParTree<int> ptree = ParTree<int>(numVertex);
    for(int i = 0; i < numVertex; i++)
    {
        ptree.arr[i].setCount(1); ptree.arr[i].setData(i); ptree.arr[i].setParent(NULL);
    }
    // 2. 对所有的Edge建堆
    vector<Edge> miniHeap = vector<Edge>();
    for(int i=0; i<numVertex; i++)
    {
        for(Edge e = FirstEdge(i); IsEdge(e); e = NextEdge(e))
        {
            miniHeap.push_back(e);
        }
    }
    make_heap(miniHeap.begin(),miniHeap.end(),CmpEdgeWeight);
    // 3. 以权的大小顺序处理边
    Edge e;
    while(miniHeap.size()>0)
    {
        e = miniHeap.front();
        if( ptree.Different(e.from,e.to))   // 如果不在同一个等价类中
        {
            ptree.Union(e.from,e.to);   // 合并等价类
            count++;
            arrEdge.push_back(e);
        }
        miniHeap.erase(miniHeap.begin());
    }
    // 4.如果是连通图 count == 1
    if( count != 1)
        printf("Graph 不连通...\n");
    return arrEdge;
}
// 检查与节点相连的每一条边, 看利用结点的另一端能否更新,结点到其他节点的距离
void Graphm::Bellman_Ford(int v, vector<Dist>& res)
{
    for(int i = 0; i < numVertex; i++)
    {
        res.push_back(Dist(i,INFINITY,-1));
    }

    queue<Edge> qu;
    for(Edge e = FirstEdge(v); IsEdge(e); e = NextEdge(e))
    {
        qu.push(e);
       // res.push_back(Dist(e.to,e.weight,-1));
        res[e.to].index = e.to; res[e.to].len = e.weight; res[e.to].pre = -1;
    }
    res[v].index = v; res[v].len = 0; res[v].pre = -1;

    Edge eu = Edge();
    while(qu.size()>0)
    {
        eu = qu.front(); qu.pop();

        for(Edge e = FirstEdge(eu.to); IsEdge(e); e = NextEdge(e))
        {
            if( res[e.to].len > e.weight + res[e.from].len)
            {
                res[e.to].len = e.weight + res[e.from].len;
                res[e.to].pre = e.from;
                qu.push(e);
            }
        }
    }
    
}




















// Directed Matrix Graph
void GraphDM::Topsort()
{
    // 找出入度为0的结点输出
    // 将输出的结点从图中删除,修改其他节点的入度
    // 重复直到所有接点输出
    ClearMarks();
    int *indegree = new int[numVertex];
    memcpy(indegree,Indegree,sizeof(int)*numVertex);
    int count = 0;
    queue<int> qu;
    for(int i = 0; i < numVertex; i++)
    {
        if(indegree[i] == 0)
            qu.push(i); // 先将所有入度为0的入队
    }
    while(qu.size()>0)
    {
        int ix = qu.front(); qu.pop();
        // 访问结点...
        printf("toposort: %d\n",ix);
        // 从图中删除 结点i
        Mark[ix] = VISITED;
        // 修改相连结点的入度
        for(Edge e = FirstEdge(ix); IsEdge(e); e = NextEdge(e))
        {
            indegree[e.to]--;
            if(indegree[e.to] == 0)
                qu.push(e.to);
        }
        count++;
    }
    if(count<numVertex-1)
        printf("Graph has loop!\n");
}
void GraphDM::Topsort_DFS()
{
    ClearMarks();
    int *result = new int[numVertex];
    int tag = 0;
    for(int i = 0; i < numVertex; i++)
        if(Mark[i] == UNVISITED)
            Do_toposort(i,result,tag);
    for(int i=numVertex-1; i>=0; i--)
        printf("%d  ",result[i]);
    printf("\n");
}
void GraphDM::Do_toposort(int v, int *result, int &tag)
{
    Mark[v] = VISITED;
    for(Edge e = FirstEdge(v); IsEdge(e); e = NextEdge(e)) //深度优先,保证前结点后访问...逆序时前结点必定在后结点之前访问
    {
        if( Mark[ToVertex(e)] == UNVISITED)
            Do_toposort(ToVertex(e),result,tag);
    }
    result[tag++] = v;
}
bool GraphDM::SetEdge(int from, int to, int weight)
{
    if( from < 0 || from>numVertex-1 || to<0 || to>numVertex-1)
    {
        printf("invalid form and to...\n");
        return false;
    }
    if( matrix[from][to] <= 0)
    {
        Indegree[to]++;
        numEdge++;
        
    }
    matrix[from][to] = weight;
    return true;
}
bool GraphDM::DelEdge(int from, int to)
{
    if( from < 0 || from>numVertex-1 || to<0 || to>numVertex-1)
    {
        printf("invalid form and to...\n");
        return false;
    }
    if( matrix[from][to] > 0)
    {
        Indegree[to]--;
        numEdge--;
    }
    matrix[from][to] = 0;
    
    return true;
}
bool Cmp_Dist(Dist &d1, Dist &d2)
{
    return d1.len > d2.len;
}
void GraphDM::Dijkstra(int v1,vector<Dist> &vt1)
{
    vector<Dist> vt2;
    Dist d1;
    vt1.push_back(Dist(v1,0,v1));

    for(int i = 0; i < numVertex; i++)
    {
        if(v1 != i)
            if( matrix[v1][i] > 0)
                vt2.push_back(Dist(i,matrix[v1][i],-1)); // 有路径直接可达..
            else
                vt2.push_back(Dist(i,INFINITY,INFINITY)); // 无法到达
        else
            vt2.push_back(Dist(i,0,i)); // 自己通过自己到自己,长度为0
    }
    make_heap(vt2.begin(),vt2.end(),Cmp_Dist);
    //printf("print heap:\n");
    //for(vector<Dist>::iterator i = vt2.begin(); i != vt2.end(); i++)
    //    printf("index:%d,len:%d,pre:%d  \n",i->index,i->len,i->pre);

    while(vt2.size()!=0)
    {
        int size = vt2.size();
        d1 = vt2.front(); 
        vt2.erase(vt2.begin());
        //printf("%d-%d=%d\n",size,vt2.size(),size-vt2.size());
        vt1.push_back(d1);
        int len = d1.len;
        for(Edge e = FirstEdge(d1.index); IsEdge(e); e=NextEdge(e))
        {
            for(vector<Dist>::iterator i = vt2.begin(); i != vt2.end(); i++)
            {
                if(i->index == e.to && (i->len> len+e.weight))
                {
                    i->len = len + e.weight; i->pre = e.from;
                }
            }
        }
        make_heap(vt2.begin(),vt2.end(),Cmp_Dist);
    }
    // 第一组包含已确定最短路径的点,第二组包含还未确定的点
}
int mini(int a, int b)
{
    return a>b? a : b;
}
Dist** GraphDM::Floyd(Dist **&arr)
{
    arr = new Dist*[numVertex];
    for(int i=0; i<numVertex; i++)
        arr[i] = new Dist[numVertex];

    // 初始化Dist 数组
    for(int i = 0; i < numVertex; i++)
        for(int j = 0; j < numVertex; j++)
        {
            if( matrix[i][j] > 0)   // 有路径,直接可达
            {
                arr[i][j].pre =  -1;
                arr[i][j].len = matrix[i][j];
                arr[i][j].index = j;
            }
            else
            {
                
                if( i == j)     // 自己到自己
                {
                    arr[i][j].len = 0;
                    arr[i][j].pre = i;
                }
                else            // 无法到达
                {
                    arr[i][j].len = INFINITY;
                    arr[i][j].pre = INFINITY;
                }
                arr[i][j].index = j;
            }
        }
    for(int k=0; k<numVertex; k++)
        for(int i=0; i<numVertex; i++)
            for(int j=0; j<numVertex; j++)
            {
                if(arr[i][j].len > arr[i][k].len + arr[k][j].len)
                {
                    arr[i][j].len = arr[i][k].len + arr[k][j].len;
                    arr[i][j].pre = k;
                }
            }
    return arr;
}
vector<vector<Dist>> * GraphDM::Path_Dijkstra()
{
    vector<vector<Dist>> *vt =  new vector<vector<Dist>>(10);

    for(int i = 0; i < numVertex; i++)
        GraphDM::Dijkstra(i,(*vt)[i]);

    return vt;
}
// 比较两条边的权值
bool CmpEdgeWeight(Edge &e1, Edge &e2)
{
   return e1.weight > e2.weight;
}
