#include "Graph.h"
#include <queue>
#include <memory.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "ParTree.h"
#include <queue>

using namespace std;

// һЩ��������
bool CmpEdgeWeight(Edge &e1, Edge &e2); // �Ƚϱ��Ȩֵ��С, e1.weight > e2.weight return true;






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
        numEdge+=2; // ����ͼ...
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
        numEdge-=2; // ����ͼ...
        Indegree[to]--;
    }
    matrix[from][to] = 0;
    matrix[to][from] = 0;
    return true;
}

int Graphm::DFS(int vertex)//�����������
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

void Graphm::BFS(int vertex)//�����������
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
bool Graphm::IsConnected()//�ж��Ƿ���ͨ
{
    return false;
}
void Graphm::ConnectedNum()//��ͨ��������Ŀ
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
// ��������ͨͼ...
vector<Edge>& Graphm::Prim(vector<Edge> &arrEdge, int v)
{   // �ӽڵ� v ��ʼ
    // �����еı߷����
    // ����ѡ��ȫ��С,��һ���ڵ���������,һ������
    ClearMarks();
    Mark[v] = VISITED;
    vector<Edge> miniHeap;
    int count = 1;  // �Ѽ�����ļ�����
    for(Edge e = FirstEdge(v); IsEdge(e); e = NextEdge(e))
    {
        miniHeap.push_back(e);
    }
    make_heap(miniHeap.begin(),miniHeap.end(),CmpEdgeWeight);

    while(miniHeap.size() > 0)
    {
        int vto = miniHeap.front().to;
        if(Mark[vto] == UNVISITED)
        {   // ���߼�������
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
        printf("������ͨͼ....\n");
    return arrEdge;
}
// �����㻮��ΪnumVertex���ȼ���
// ��Ȩ�Ĵ�СΪ˳����Edge
// ��һ���ߵ�����������������ͬ�ĵȼ���ʱ,�ϲ������ȼ���
// ֱ��ֻʣһ���ȼ���(�������ͨͼ)
vector<Edge>& Graphm::Kruskal(vector<Edge> &arrEdge, int v)
{   
    // �ȼ��������
    int count = numVertex;
    // 1.��ʼ���ȼ���...
    ParTree<int> ptree = ParTree<int>(numVertex);
    for(int i = 0; i < numVertex; i++)
    {
        ptree.arr[i].setCount(1); ptree.arr[i].setData(i); ptree.arr[i].setParent(NULL);
    }
    // 2. �����е�Edge����
    vector<Edge> miniHeap = vector<Edge>();
    for(int i=0; i<numVertex; i++)
    {
        for(Edge e = FirstEdge(i); IsEdge(e); e = NextEdge(e))
        {
            miniHeap.push_back(e);
        }
    }
    make_heap(miniHeap.begin(),miniHeap.end(),CmpEdgeWeight);
    // 3. ��Ȩ�Ĵ�С˳�����
    Edge e;
    while(miniHeap.size()>0)
    {
        e = miniHeap.front();
        if( ptree.Different(e.from,e.to))   // �������ͬһ���ȼ�����
        {
            ptree.Union(e.from,e.to);   // �ϲ��ȼ���
            count++;
            arrEdge.push_back(e);
        }
        miniHeap.erase(miniHeap.begin());
    }
    // 4.�������ͨͼ count == 1
    if( count != 1)
        printf("Graph ����ͨ...\n");
    return arrEdge;
}
// �����ڵ�������ÿһ����, �����ý�����һ���ܷ����,��㵽�����ڵ�ľ���
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
    // �ҳ����Ϊ0�Ľ�����
    // ������Ľ���ͼ��ɾ��,�޸������ڵ�����
    // �ظ�ֱ�����нӵ����
    ClearMarks();
    int *indegree = new int[numVertex];
    memcpy(indegree,Indegree,sizeof(int)*numVertex);
    int count = 0;
    queue<int> qu;
    for(int i = 0; i < numVertex; i++)
    {
        if(indegree[i] == 0)
            qu.push(i); // �Ƚ��������Ϊ0�����
    }
    while(qu.size()>0)
    {
        int ix = qu.front(); qu.pop();
        // ���ʽ��...
        printf("toposort: %d\n",ix);
        // ��ͼ��ɾ�� ���i
        Mark[ix] = VISITED;
        // �޸������������
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
    for(Edge e = FirstEdge(v); IsEdge(e); e = NextEdge(e)) //�������,��֤ǰ�������...����ʱǰ���ض��ں���֮ǰ����
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
                vt2.push_back(Dist(i,matrix[v1][i],-1)); // ��·��ֱ�ӿɴ�..
            else
                vt2.push_back(Dist(i,INFINITY,INFINITY)); // �޷�����
        else
            vt2.push_back(Dist(i,0,i)); // �Լ�ͨ���Լ����Լ�,����Ϊ0
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
    // ��һ�������ȷ�����·���ĵ�,�ڶ��������δȷ���ĵ�
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

    // ��ʼ��Dist ����
    for(int i = 0; i < numVertex; i++)
        for(int j = 0; j < numVertex; j++)
        {
            if( matrix[i][j] > 0)   // ��·��,ֱ�ӿɴ�
            {
                arr[i][j].pre =  -1;
                arr[i][j].len = matrix[i][j];
                arr[i][j].index = j;
            }
            else
            {
                
                if( i == j)     // �Լ����Լ�
                {
                    arr[i][j].len = 0;
                    arr[i][j].pre = i;
                }
                else            // �޷�����
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
// �Ƚ������ߵ�Ȩֵ
bool CmpEdgeWeight(Edge &e1, Edge &e2)
{
   return e1.weight > e2.weight;
}
