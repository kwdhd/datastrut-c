#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Graph.h"
#include <vector>
#include <algorithm>
#include "ParTree.h"
#include "DP.h"

using namespace std;

void test_Graphm();
void test_DTri();
void test_Knapsack();
//
void main()
{
    //printf("%d\n",~(unsigned int)0>>1);
    //printf("%d\n",1<<31);

    //int numVertex = 10;
    //int **matrix = (int**)new int*[numVertex];

    //matrix = (int**)new int*[numVertex];
    //for(int i = 0; i < numVertex; i++)
    //    matrix[i] = new int[numVertex];

    //for(int i = 0; i < numVertex; i++)
    //{
    //    memset(matrix[i],0,numVertex*sizeof(int)); // 只能用0或-1
    //}

    //for(int i = 0; i < numVertex; i++)
    //{
    //    for(int j = 0; j < numVertex; j++)
    //    {
    //        printf("[%d][%d]%d  ",i,j,matrix[i][j]);
    //    }
    //    printf("\n");
    //}

    // test Graphm
    //test_Graphm();
    //test_DTri();
    test_Knapsack();
    getchar();
}

bool Cmp_Dist_Index(Dist &d1, Dist &d2)
{
    return d1.index < d2.index;
}

void test_Graphm()
{
    Graphm g = Graphm(4);
    g.Debug();
    int data[8][3] = {{0,1,3},{1,0,3},{0,3,15},{3,0,15},{1,2,4},{2,1,4},{2,3,6},{3,2,6}};

    int data2[8][3] = {{0,1,3},{0,3,15},{2,1,4},{2,3,6}};
    int data3[][3] = {{0,2,1},{0,7,1},{7,8,1},{8,6,1},{1,2,1},{2,3,1},{3,6,1},{3,5,1},{1,4,1},{4,5,1},{1,3,1}};
    int data4[][3] = {{0,1,50},{1,4,50},{0,2,10},{2,0,20},{1,2,15},{2,3,15},{3,1,20},{3,4,35},{4,3,30},{5,3,3}};
    for(int i = 0; i < 8; i++)
    {
       g.SetEdge(data[i][0],data[i][1],data[i][2]);
    }
    g.Debug();
    printf("BFS...\n");
    g.do_traverse("BFS");
    printf("DFS...\n");
    g.ClearMarks();
    g.do_traverse("DFS");


    GraphDM gdm = GraphDM(9);
    for(int i=0; i<12; i++)
       gdm.SetEdge(data3[i][0],data3[i][1],data3[i][2]);
    gdm.Debug();
    printf("Toposort...\n");
    gdm.Topsort();
    printf("Toposort...\n");
    gdm.Topsort_DFS();
    printf("DFS...\n");
    gdm.do_traverse("DFS");
    printf("BFS...\n");
    gdm.do_traverse("BFS");

    GraphDM gdm2 = GraphDM(6);
    for(int i=0; i<10; i++)
       gdm2.SetEdge(data4[i][0],data4[i][1],data4[i][2]);
    gdm2.Debug();
    vector<Dist> v1;
    gdm2.Dijkstra(0,v1);
    printf("result:\n");
    for(vector<Dist>::iterator i = v1.begin(); i != v1.end(); i++)
    {
        printf("index:%d,len:%d,pre:%d  \n",i->index,i->len,i->pre);
    }

    printf("Fellman_Frod...\n");
    v1.clear();
    gdm2.Bellman_Ford(0,v1);
    for(vector<Dist>::iterator i = v1.begin(); i != v1.end(); i++)
    {
        printf("index:%d,len:%d,pre:%d  \n",i->index,i->len,i->pre);
    }


    printf("Floyd...\n");
    Dist **arr;
    gdm2.Floyd(arr);
    printf("\n");
    for(int i = 0; i<6; i++)
    {
        for(int j=0; j<6; j++)
            printf("pre:%d,len:%d ",arr[i][j].pre,arr[i][j].len);
        printf("\n");
    }
    printf("path_Dijkstra...\n");
    vector<vector<Dist>> *vt =  gdm2.Path_Dijkstra();
    for(vector<vector<Dist>>::iterator i = (*vt).begin(); i != (*vt).end(); i++)
    {
        sort(i->begin(),i->end(),Cmp_Dist_Index);
        for(vector<Dist>::iterator ix = i->begin(); ix != i->end(); ix++)
            printf("pre:%d,len:%d ",ix->pre,ix->len);
        printf("\n");
    }

    // 最小生成树
    
    int data5[][3] = {{0,1,10},{0,4,19},{0,5,21},{1,2,5},{1,3,6},{1,5,11},{2,3,6},{3,5,14},{3,4,18},{4,5,33}};
    int len5 = 10;
    Graphm gm3 = Graphm(6);
    for(int i = 0; i < len5; i++)
    {
       gm3.SetEdge(data5[i][0],data5[i][1],data5[i][2]);
    }
    printf("gm3...\n");
    gm3.Debug();

    printf("Prim...\n");
    vector<Edge> edges;
    gm3.Prim(edges);
    for(vector<Edge>::iterator i = edges.begin(); i != edges.end(); i++)
    {
        printf("from:%d,to:%d,weight:%d  \n",i->from,i->to,i->weight);
    }
    
    printf("Kruskal...\n");
    edges.clear();
    gm3.Prim(edges);
    for(vector<Edge>::iterator i = edges.begin(); i != edges.end(); i++)
    {
        printf("from:%d,to:%d,weight:%d  \n",i->from,i->to,i->weight);
    }
}

void test_DTri()
{
    // 构造测试数据
    const int level = 4;
    int len = 10;

    int **arr = (int**)malloc(level*sizeof(int*));
    for(int i=0; i<level; i++)
    {
        arr[i] = (int*)malloc(level*sizeof(int));
    }
    int temp[] =  {1,-1,-1,-1,3,2,-1,-1,4,10,1,-1,4,3,2,20};
    int k = 0;
    for(int i=0; i<level; i++)
    {
        for(int j=0; j<level; j++)
            arr[i][j] = temp[k++];
    }
    DTri dt = DTri(4,arr);
    printf("print DTri...\n");
    dt.PrintDTri();

    int **res = (int**)malloc(level*sizeof(int*));
    int len2 = level*sizeof(int);
    int len1 = level*sizeof(int*);
    for(int i=0; i<level; i++)
    {
        res[i] = (int*)malloc(level*sizeof(int));
        memset(res[i],-1,level*sizeof(int));
        for(int j=0; j<level; j++)
        {
            printf("%d  ",res[i][j]);
        }
        printf("\n");
    }
    //memset(res,-1,sizeof(int)*level);
    //printf("result arr...\n");
    //for(int i=0; i<level; i++)
    //{
    //    printf("%d ",res[i]);
    //}    
    //printf("\n");

    int sum = dt.MaxSum(0,0,res);
    printf("Max Sum: %d \n",sum);
    printf("res arr\n");
    for(int i=0; i<level; i++)
    {
        for(int j=0; j<level; j++)
        {
            if(res[i][j]>0)
            printf("%d  ",res[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // no-recur
    int sum1 = dt.MaxSum_no_recur();
    printf("Max Sum: %d \n",sum1);

}

void test_Knapsack()
{   //
    int num = 5;
    int c = 10;
    int w[] = {6,3,5,4,6};
    int v[] = {2,2,6,5,4};
    //

    Knapsack pack = Knapsack(num,c,v,w);
    pack.PrintKnapsack();
    int res = pack.MaxWeight();
    //
    printf("max weight: %d\n",res);
    
    // less space version
    pack.PrintKnapsack();
    int res1 = pack.MaxWeight_less();
    //
    printf("max weight: %d\n",res1);
}