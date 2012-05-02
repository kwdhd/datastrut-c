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
#endif