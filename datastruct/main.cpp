#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Graph.h"
#include <vector>
#include <algorithm>
#include "ParTree.h"
#include "DP.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <bitset>


#include "MyString.h"
#include "MyIO.h"
#include "MyLib.h"
#include "linklist.h"
#include "practice.h"

using namespace std;

void test_Graphm();
void test_DTri();
void test_Knapsack();
void test_MaxSum();
void intepret();
void test_LCS();

//
void Combination(int *arr, int len);
void swap(int *arr,int i,int j);
int Fastest_Way(int *a, int *b, int *s1, int *s2, int len);

// 测试函数声明
void test_LinkList();
void test_MyString();
void test_MyLib();
void test_Bit();
int  test_bit()
{
    printf("test_bit\n");
    return 1;
}
void test_Combination();
void test_Fastest_Way();
//
//
void main()
{
       //test_Combination();
    test_Fastest_Way();
    //test_LinkList();
    //test_MyString();

    //test_Bit();
    //test_MyLib();

    //unsigned int a = -1;
    //int b = 3423;
    //a ^= b^b;
    //printf("%d\n",~a);

    //test_findX();

    //test_IsBackorder();
    //test_IsPreorder();
    //test_foo();
    //test_FOR();
    //test_FindNumber2();
    //test_FindNonRepeat();
    //int* point;

    //printf("%d\n",sizeof(bool));
    //printf("%d\n",sizeof(char));
    //printf("%d\n",sizeof(point));
    //printf("%d\n",sizeof(int));
    //printf("%d\n",sizeof(long)); // long 也是4个字节
    //printf("%d\n",sizeof(long long));
    //printf("%d\n",sizeof(size_t)); // c++ unsigned int
    //printf("%d\n",sizeof(uintptr_t)); // c++ point

    ////bitset<10000000000> *bitarr = new(bitset<10000000000>);
    //bitset<100> *bitarr = new(bitset<100>);
    //(*bitarr) &= 1;
    //*bitarr<<=5;
    //printf("%d\n",sizeof(*bitarr));
    //printf("%ld\n",bitarr->to_ulong());


    //int *b = NULL;
    //b = (int*)malloc(sizeof(int));
    //free(b);
    ////free(b);  // 不能释放两次...会报错...
    //free(NULL); // 可以释放空指针...!
    //0 && test_bit();
    //printf("%c",(1)?'1':'0');
    /*
     int a=0,b=9,c=9,d=9;
     printf("a:%d,b:%d,c:%d\n",a,b,c);
    (b&(1<<0))>>0 && (a=a+(c<<0));
    printf("a:%d,b:%d,c:%d\n",a,b,c);
    c=d;
    (b&(1<<1))>>1 && (a=a+(c<<1));
    printf("a:%d,b:%d,c:%d\n",a,b,c);
    c=d;
    (b&(1<<2))>>2 && (a=a+(c<<2));
    printf("a:%d,b:%d,c:%d\n",a,b,c);
    c=d;
    (b&(1<<3))>>3 && (a=a+(c<<3));
    printf("a:%d,b:%d,c:%d\n",a,b,c);
    c=d;
    (b&(1<<4))>>4 && (a=a+(c<<4));
    printf("a:%d,b:%d,c:%d\n",a,b,c);
    c=d;
    printf("a:%d,b:%d,c:%d\n",a,b,c);
    */

    //int a[3][4]={{1},{},{9}};

    //printf("%d",a[2][3]);
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
    //test_Knapsack();
    //test_MaxSum();
    //intepret();
    //test_LCS();
    test_Matrix_Multiply();
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

void test_MaxSum()
{
    int arr[] = {-2,11,-4,13,-5,-2};
    int len1 = 6;
    for(int i = 0; i < len1; i++)
        printf("%d ",arr[i]);
    printf("\n");

    int res1 = MaxSumArr(arr,len1);
    printf("res: %d\n",res1);


    int temp[][4] = {{0,-2,-7,0},{9,2,-6,2},{-4,1,4,1},{-1,8,0,2}};
    int x = 4, y = 4;
    int **arr2 = (int**)malloc(sizeof(int*)*x);
    for(int i=0; i<x; i++)
    {
        arr2[i] = (int*)malloc(sizeof(int*)*y);
        for(int j=0; j<y; j++)
            arr2[i][j] = temp[i][j];
    }


    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
            printf("%d ",arr2[i][j]);
        printf("\n");
    }
    int res2 = MaxSumMatrix(arr2,x,y);
    printf("res: %d\n",res2);

    int arr3[] = {-2,11,-4,13,-5,-2,0};
    int len3 = 6;

    for(int i = 1; i <=len3; i++)
    {
        printf("res: %d\n",MaxSumM(arr3,len3,i));
    }

}

void intepret()
{
    //char str[] = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj.";
    char str[] = "http://www.pythonchallenge.com/pc/def/map.html";
    int len = strlen(str);
    char *res = (char*)malloc(sizeof(char)*(len+1));
    char pattern[] = "cdefghijklmnopqrstuvwxyzab";
    printf("%s",str);
    for(int i = 0; i < len; i++)
    {
        if( str[i] >='a' && str[i] <='z')
        {
            res[i] = pattern[str[i]-'a'];
           // printf("%c->%c\n",str[i],res[i]);
        }
        else
        {
            res[i] = str[i];
        }
    }
    res[len] = '\0';
    for(int i = 0; i < len; i++)
    {
        printf("%c",res[i]);
    }
    printf("\n");

}

void test_LCS()
{
    char arr1[] = "abcbdab";
    int len1 = strlen(arr1);

    char arr2[] = "bdcaba";
    int len2 = strlen(arr2);

    int res = LCS(arr1,len1,arr2,len2);
    printf("res :%d\n",res);
}
// 测试函数定义
void test_LinkList(){
	int num = 0;
	struct LinkList  ll;
	ll.head = NULL;
	ll.size = 0;
	//InitLinkList(&ll);

    int i = 0;
	while( i < 10){
		srand((unsigned int)time(NULL)*rand());
		num = rand()%100;
		printf("insert %d ",num);
		InsertData(&ll,num);
		i++;
	}

	printf("\n");
	printf("print list:\n");
	PrintLList(ll);
}

void test_MyString(){
    char str[] = "testing reverse words   ";
    int len = StrLen(str);
    char* str2 = (char*)malloc(sizeof(char)*len+1);
    printf("test reversestring: \n%s\n",str);
    ReverseString(str);
    printf("str:%s\n",str);
    ReverseString(str);
    printf("str:%s\n",str);
    printf("reverse words:\n");
    ReverseWords(str);
    printf("str:%s\n",str);

    Print("test StrLen:\n");

    Print("Str To Int\n");
    char str3[] = "-01234343";
    printf("%s,%ld\n",str3,StrToLong(str3));
    //for(int i = 0; i< StrLen(str3);i++)
    //{
    //    printf("%c:%d   \n",str3[i],CharToInt(str3[i]));
    //}


    char str4[]="123456789abcd12345ed125sss1234567890";
    printf("test max num str:%s\n",str4);
    char* str5 = (char*)malloc(sizeof(char)*StrLen(str4));
    int count = MaxContinuNum(str4,str5);
    printf("max num:%d,max str:%s\n",count,str5);
}

void test_MyLib(){
    srand(time(NULL)*rand());
    int i=0,round=5;
    while(i<round){
        int num1 = rand()%1000+1;
        int num2 = rand()%100+1;
        int mod = 0;
        if(num1 < num2)
            continue;
        printf("%d: %d mod %d= ",i+1,num1,num2);
        mod = Mod(num1,num2);
        printf("%d",mod);
        printf(" : %s",(mod==num1%num2 ? "true":"false"));
        Print("\n");
        printf("%d: %d / %d= ",i+1,num1,num2);
        int quotient = Divide(num1,num2);
        printf("%d",quotient);
        printf(" : %s",(quotient==num1/num2 ? "true":"false"));
        Print("\n");
        i++;
    }
    int k = 0;
    printf("count1:%d\n",Count1(k));
    printf("count0:%d\n",Count0(k));
    char* str = BitToStr(k);
    printf("bit to str: %s\n",str);
    free(str);
    k = -1;
    printf("count1:%d\n",Count1(k));
    printf("count0:%d\n",Count0(k));
    str = BitToStr(k);
    printf("bit to str: %s\n",str);
    free(str);

}

void test_Bit(){
    int i = -1;
    int j = 0;
    int k = -1<<31;
    unsigned int l = k;
    //i=i>>2;
    //i--;
    j=~j;
    j++;
    //i = ~k;
    //l=l>>1;
    printf("%d,%x\n",i,i);
    printf("%d,%x\n",j,j);
    printf("%d,%x\n",k,k);
    printf("%u,%x\n",l,l);
}
// 生成所有组合
void Combination(int *arr, int len)
{
    for(int i=1; i<=len; i++)   // 长度
    {
        for(int j=i-1; j<len; j++)    //
        {
            swap(arr,0,j);
            for(int k=0; k<i; k++)
                printf("%d ",arr[k]);
            printf("\n");
            swap(arr,0,j);
        }
    }
}
void swap(int *arr,int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    //arr[i] ^= arr[j];
    //arr[j] ^= arr[i];
    //arr[i] ^= arr[j];
}
void test_Combination()
{
    int arr[] = {1,2,3};
    int len = 3;
    Combination(arr,len);
}
int Max(int a, int b)
{
    return (a>b) ? a : b;
}
int Mini(int a, int b)
{
    return (a>b) ? b : a;
}
void PrintIntArr(int *arr, int len)
{
    for(int i = 0; i < len; i++)
        printf("%d  ",arr[i]);
    printf("\n");
}
// Fastest Way
// s1 从装配线 b到a 的时间, s2 装配线 b到a的时间
int Fastest_Way(int *a, int *b, int *s1, int *s2, int len)
{
    int *ta = (int*)malloc(sizeof(int)*len);    // 保存第i步在a装配线的最小时间
    int *tb = (int*)malloc(sizeof(int)*len);

    PrintIntArr(a,len);
    PrintIntArr(b,len);
    PrintIntArr(s1,len);
    PrintIntArr(s2,len);

    ta[0] = a[0]+s1[0]; tb[0] = b[0]+s2[0];
    for(int i = 1; i<len; i++)
    {
         ta[i] = Mini(ta[i-1],tb[i-1]+s1[i])+a[i];
         tb[i] = Mini(ta[i-1]+s2[i],tb[i-1])+b[i];
    }

    PrintIntArr(ta,len);
    PrintIntArr(tb,len);

    return Mini(ta[len-1]+3,tb[len-1]+2);
}
void test_Fastest_Way()
{
    int a[] = {7,9,3,4,8,4};
    int b[] = {8,5,6,4,5,7};
    int s1[] = {2,2,1,2,2,1};
    int s2[] = {4,2,3,1,3,4};
    int len = 6;
    printf("res = %d \n",Fastest_Way(a,b,s1,s2,len));

}

// Matrix Multiply
int Matrix_Multiply(int *arr, int num)
{

    return -1;
}
