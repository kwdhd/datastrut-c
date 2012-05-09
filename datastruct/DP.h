#ifndef KWDHD_DP
#define KWDHD_DP

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <vector>
#include "KwdhdLib.h"
using namespace std;

// Helper Function

// Digital Triangle...
class DTri
{
public:
    int **arr;
    int level;
    DTri(int level)
    {
        this->level = level;
        arr = (int**)malloc(level*sizeof(int*));
        for(int i=0; i<level; i++)
        {
            arr[i] = (int*)malloc(level*sizeof(int));
        }
    }
    DTri(int level,int **arr)
    {
        this->level = level;
        this->arr = arr;
    }

    // 
    bool IsValid(int i, int j)
    {
        if( i< 0 || i >= level || j<0 || j>i)
            return false;
        return true;
    }
    // LeftChild
    int *Left(int i, int j)
    {
        if( IsValid(i,j))
            return &arr[i+1][j];
        else
            return NULL;
    }
    // RightChild
    int *Right(int i, int j)
    {
        if( IsValid(i,j))
            return &arr[i+1][j+1];
        else
            return NULL;
    }
    void PrintDTri()
    {
        for(int i=0; i<level; i++)
        {
            for(int j=0; j<level; j++)
            {
                if(arr[i][j] > 0)
                    printf("%d ",arr[i][j]);
            }
            printf("\n");
        }
    }
    static int max(int i, int j)
    {
        return  (i > j) ? i : j;
    }
    // find the max sum path
    int MaxSum(int i, int j, int **res)
    {
        if( !IsValid(i,j))
            return -1;
        if( i == level-1)
        {
            res[i][j] = arr[i][j];
            return arr[i][j];
        }
        else
        {
            res[i][j] = arr[i][j] +max(MaxSum(i+1,j,res),MaxSum(i+1,j+1,res));
           /* if( i == 0)
            {
                printf("res...\n");
                for( int k  = 0; k < level; k++)
                    printf("%d ",res[i][k]);
                printf("\n");
            }*/
            return res[i][j];
        }
    }
    // find the max sum path no-recur version
    int MaxSum_no_recur()
    {
        int *res = (int*)malloc(sizeof(int)*level);
        for(int k = 0; k < level; k++)
            res[k] = arr[level-1][k];
        printf("res arr\n");
        for(int i=0; i<level; i++)
        {
            printf("%d  ",res[i]);
        }
        printf("\n");
        for(int m = level-2; m>=0; m--)//从倒数第二行开始
        {
            for(int n = 0; n<=m; n++)
            {
                res[n] = arr[m][n] + ( res[n] > res[n+1] ? res[n] : res[n+1]);
            }  
            printf("res arr\n");
            for(int i=0; i<level; i++)
            {
                printf("%d  ",res[i]);
            }
            printf("\n");
        }

        return res[0];
    }
};

// Knapsack
class Knapsack
{
public:
    int num;    // 物品数量
    int c;      // 背包容量
    int *v;     // 物品体积数组
    int *w;     // 物品重量数组

    Knapsack(int num, int c, int *v, int *w)
    {
        this->num = num;
        this->c = c;
        this->v = v;
        this->w = w;
    }
    void PrintKnapsack()
    {
        printf("Print Knapsack:\n");
        printf("num: %d, c: %d \n",num,c);
        printf("v: ");
        for(int i = 0; i < num; i++)
            printf("%d:%d ",i,v[i]);
        printf("\n");
        printf("w: ");
        for(int i = 0; i < num; i++)
            printf("%d:%d ",i,w[i]);
        printf("\n");
    }
    int MaxWeight()
    {
        // 
        int **res = (int**)malloc(sizeof(int*)*num);
        for(int i=0; i<num; i++)
        {
            res[i] = (int*)malloc(sizeof(int)*(c+1));   // 容量
            memset(res[i],0,sizeof(int)*(c+1));
        }
        printf("print res arr...\n");
        PrintIntArr(res,num,c+1);
     
        //
        for(int i = num-1; i >=0; i--)
        {
            for(int j= 1; j<=c; j++)
            {
                if( i == num-1) // 从最后一个物品往前推
                {   
                    if(v[i] <= j)
                        res[i][j] = w[i];
                }
                else if( v[i] <= j)   // 能装进去
                {
                    res[i][j] = max(res[i+1][j], res[i+1][j-v[i]]+w[i]);
                }
                else
                {
                    res[i][j] = res[i+1][j];
                }
            }
        }
        printf("print res arr...\n");
        PrintIntArr(res,num,c+1);
        return res[0][c];
    }
    // Less Space consume
    int MaxWeight_less()
    {
        int *res = (int*)malloc(sizeof(int)*(c+1));
  
      memset(res,0,sizeof(int)*(c+1));
        for(int k = 1; k < c+1; k++)
            printf("%d ",res[k]);
        printf("\n");

        for(int i = num-1; i >=0; i--)
        {
            for(int j=c; j>=1; j--) // j必须从大到小,不然会覆盖掉要用的res[j]
            {
                if( i == num-1) // 从最后一个物品往前推
                {   
                    if(v[i] <= j)
                        res[j] = w[i];
                }
                else if( v[i] <= j)   // 能装进去
                {
                    res[j] = max(res[j], res[j-v[i]]+w[i]);
                }
                //for(int k = 1; k < c+1; k++)
                //    printf("%d ",res[k]);
                //printf("\n");
            }
        }

        for(int k = 1; k < c+1; k++)
            printf("%d ",res[k]);
        printf("\n");
        return res[c];
    }
};

// Largest sub-segment
int MaxSumArr(int *arr, int len)
{
    int sum = 0;
    int max = 0;
    for(int i = 0; i<len; i++)
    {
        if((sum+arr[i])>0)
        {
            sum += arr[i];
            if( sum > max)
                max = sum;
        }
        else
            sum = 0;
    }
    return max;
}
int MaxSumMatrix(int **arr, int x, int y)
{
    int sum = 0;
    int *b = new int[y];
    for(int i=0; i<x; i++) // 行
    {
        for(int k=0; k<y; k++)
            b[k] = 0;
        for(int j=i; j<x; j++)
        {
            for(int k=0; k<y; k++)
                b[k]+=arr[j][k];
            int max = MaxSumArr(b,y);
            if(max > sum)
                sum = max;
        }
    }
    return sum;
}
// 最大子M段和
int MaxSumM(int *arr, int n, int m)    // 
{
    int sum = 0;

    if(n<m || m<1)  return 0;
    int **b = new int*[m+1];  // m row
    for(int i=0; i<m; i++)
        b[i] = new int[n+1];  // n col
    for(int i=0; i<=m; i++)
        b[i][0] = 0;
    for(int j=1; j<=m; j++)
        b[0][j] = 0;
    for(int i=1; i<=m; i++)
    {
        for(int j=i; j<=n-m+i; j++)
        {
            if(j>i)
            {
                b[i][j] = b[i][j-1] + arr[j];
                for(int k=i-1; k<j; k++)
                    if(b[i][j]<b[i-1][k]+arr[j])
                        b[i][j]=b[i-1][j]+arr[j];
            }
            else
                b[i][j] = b[i-1][j-1]+arr[j];
        }
    }

    for(int j = m; j <=n; j++)
        if(sum<b[m][j]) sum = b[m][j];

    return sum;
}
int LCS(char *X, int m, char *Y, int n)
{
    if( m == 0 || n == 0)
        return 0;
    
    if( X[m] == Y[n] )
        return LCS(X, m-1, Y, n-1) + 1;
    else
    {
        return max(LCS(X,m-1,Y,n),LCS(X,m,Y,n-1));
    }
 //   return -1;
}

int Matrix_Multiply(int *d,int len)
{
    int **res = (int**)malloc(sizeof(int*)*len);
    for(int i=0; i<len; i++)
    {
        res[i] = (int*)malloc(sizeof(int)*len);
        memset(res[i],0,len*sizeof(int));
      /*  for(int j = 0; j < len; j++)
            printf("%d  ",res[i][j]);
        printf("\n");*/
    }
    int **s = (int**)malloc(sizeof(int*)*len);
    for(int i=0; i<len; i++)
    {
        s[i] = (int*)malloc(sizeof(int)*len);
        memset(s[i],-1,len*sizeof(int));
    }

    for(int j = 1; j< len; j++)
    {
        for(int i = 0; i < len; i++)// i..i+j
        {
            if(i + j < len)
            {
                int temp = 0;
                for(int k = i; k < i+j; k++)
                {   // 从k处断裂
                    temp = res[i][k]+res[k+1][j+i] + d[i]*d[k+1]*d[j+i+1];
                   // printf(" temp: %d\n",temp);
                    if( temp < res[i][j+i] || res[i][j+i] == 0)
                    {
                        res[i][j+i] = temp;
                        s[i][j+i] = k;
                    }
                }
            }
        }
    }
    printf("res: \n");
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }
    printf("s: \n");
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            printf("%d ",s[i][j]);
        }
        printf("\n");
    }
    //printf("%d\n",res[0][len-1]);
    return res[0][len-1];
}

int LookUp(int *m,int i, int j, int **res, int **s)
{
    if(res[i][j] != 0)
        return res[i][j];
    if(i >= j)
        return 0;
    for(int k = i; k < j; k++)
    {
        int t1 = LookUp(m,i,k,res,s);
        int t2 = LookUp(m,k+1,j,res,s);
        int t3 = m[i]*m[k+1]*m[j+1];
        int t =  t1 + t2 + t3;
       // printf("temp: %d,t1: %d, t2: %d, t3: %d, i: %d, j: %d, k: %d, res[%d][%d]: %d, s[%d][%d]: %d\n",t,t1,t2,t3,i,j,k,i,j,res[i][j],i,j,s[i][j]);
        if( t < res[i][j] || res[i][j] == 0)
        {
            res[i][j] = t;
            s[i][j] = k;
        }
    }
    return res[i][j];
}
int Memorized_MatrixMultiply(int *m, int len)
{
    int **res = (int**)malloc(sizeof(int*)*len);
    for(int i=0; i<len; i++)
    {
        res[i] = (int*)malloc(sizeof(int)*len);
        memset(res[i],0,len*sizeof(int));
    }

    int **s = (int**)malloc(sizeof(int*)*len);
    for(int i=0; i<len; i++)
    {
        s[i] = (int*)malloc(sizeof(int)*len);
        memset(s[i],-1,len*sizeof(int));
    }
    int r = LookUp(m,0,len-1,res,s);
    printf("res: \n");
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }
    printf("s: \n");
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            printf("%d ",s[i][j]);
        }
        printf("\n");
    }

    return r;
}
void test_Matrix_Multiply()
{
    int arr[] = {30,35,15,5,10,20,25};
    int len = 6;
    for(int i = 0; i <= len; i++)
        printf("%d ",arr[i]);
    printf("\n");

    int res = Matrix_Multiply(arr,len);
    printf("res: %d\n",res);

    int res2 = Memorized_MatrixMultiply(arr, len);
    printf("res: %d\n",res2);
}

#endif