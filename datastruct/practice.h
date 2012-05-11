#ifndef PRACTICE_H
#define PRACTICE_H

#define POW(a,b,c,d,i) (b&(1<<i))>>i && (a=a+(c<<i)); c=d;

//#define POW(a,b,n,i) int c=n; (b&(1<<i))>>i && (a=a+(c<<i));

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

// 声明
int FindNonRepeat(char* arr,int size);

int FOR(int s,int e,int f(int));

int pow(int n);

int findX(int arr[],int size);

void test_findX();

int findX2(int arr[],int size);

int* MakeArr(int size);

int IsInorder(int arr[],int left,int right);
void test_IsInorder(void);

int IsPreorder(int arr[],int left,int right);
void test_IsPreorder(void);

int IsBackorder(int arr[],int left,int right);
void test_IsBackorder(void);

int foo(int n);

void FindNumber(int a[],int n, int dest);
// 定义
int findX(int arr[],int size)
{
    int res = 0;
    for(int i=0;i<size;++i)
    {
        res ^= arr[i]^(i+1);
    }
    res ^= size;
    return res;
}
void test_findX()
{
    int size = 501;
    int* arr = MakeArr(size);
    int x1 = findX(arr,size+1);
    for(int i = 0;i<size+1;i++)
        printf("%d ",arr[i]);
    Print("\n");
    printf("重复数为:%d,%d",x1,arr[size]);
    Print("\n");
    printf("重复数为:%d,%d",findX2(arr,size+1),arr[size]);
}
int findX2(int arr[],int size)
{
    int sum = 0;
    for(int i=0;i<size-1;i++)
        sum +=i+1;
    for(int i=0;i<size;i++)
        sum -= arr[i];
    return -sum;
}
int* MakeArr(int size)
{
    int *arr = (int*)malloc(sizeof(int)*(size+1));
    if( NULL == arr)
        return NULL;
    for(int i=0;i<size;i++)
    {
        arr[i]=i+1;
    }
    srand(unsigned int(time(NULL)));
    arr[size] = rand()%size;
    printf("arr[size]:%d\n",arr[size]);
    int i = rand()%size;
    arr[i] ^= arr[size];
    arr[size] ^= arr[i];
    arr[i] ^= arr[size];
    printf("arr[size]:%d\n",arr[size]);
    return arr;
}
// 5,6,7,8,9,10,11
int IsInorder(int arr[],int left,int right)
{
    for(int i=left; i<right; i++){
        if(arr[i]>=arr[i+1])
            return 0;
    }
    return 1;
}
// 8,6,5,7,10,9,11
// 8,6,5,7
// 8,10,9,11
int IsPreorder(int arr[],int left,int right)
{
    if(left>=right)
        return 1;
    int j = left+1,k=0;
    int root = arr[left];

    // 右树 比 root 小
    while(j<=right && arr[j] < root){
        j++;
    }
    if(0 == IsPreorder(arr,left+1,j-1))
        return 0;

    // 左树 比 root 大
    k = j;
    while(j<=right && arr[j] > root){
        j++;
    }
    if(j<=right)
        return 0;
    if(0 == IsPreorder(arr,k,right))
        return 0;

    return 1;
}
void test_IsPreorder(void)
{
    //int arr[] = {8,6,5,7,10,9,11}; int size = 7; // 左右子树 都有
    //int arr[] = {5,8,4,7}; int size = 4; // 错误
    //int arr[] = {8,6,5,7};  int size = 4;// 只有左树
    int arr[] = {8,10,9,11}; int size = 4; // 只有右树
    
    for(int i = 0; i<size; i++)
        printf("%d ",arr[i]);
    Print("\n");
    printf("%s\n",(IsPreorder(arr,0,size-1))?"true":"false");
}
// 5,7,6,9,11,10,8
int IsBackorder(int arr[],int left,int right)
{
    if(left>=right)
        return 1;
    int j = right-1,k=0;
    int root = arr[right];
    // 右树 比 root 大
    while(j>=left && arr[j] > root){
        j--;
    }
    if(0 == IsBackorder(arr,j+1,right-1))
        return 0;
    // 左树 比 root 小
    k = j;
    while(j>=left && arr[j] < root){
        j--;
    }
    if(j>=left)
        return 0;
    if(0 == IsBackorder(arr,left,k))
        return 0;

    return 1;
}

int helper(int a[],int s,int e)
{
    if(e==s) return 1;
    int i=e-1;
    while(a[e]>a[i] && i>=s) i--;
    if(!helper(a,i+1,e-1))
        return 0;
    while(a[e]<a[i]&&i>=s) i--;
    return helper(a,s,i);
}
int IsBackorder2(int arr[],int size)
{
    return helper(arr,0,size-1);
}

void test_IsBackorder()
{
    int arr[] = {5,7,6,9,11,10,8}; int size=7;// 左右子树 都有
    //int arr[] = {7,4,6,5}; int size = 4;// 错误
    //int arr[] = {5,7,6,8};  // 只有左树
    //int arr[] = {9,11,10,8}; // 只有右树
    
    for(int i = 0; i<size; i++)
        printf("%d ",arr[i]);
    Print("\n");
    int res =IsBackorder(arr,0,size-1);
    printf("%s\n",(res)?"true":"false");
}

int foo(int n)
{
    n <0 && (n=0);
    int a=0,b=n,c=n,d=n;

    for(int i=0;i<32;i++)
    {
        POW(a,b,c,d,i);
        //printf("a=%d,b=%d,c=%d,d=%d,i=%d\n",a,b,c,d,i);
    }
    int res = (a+n)>>1;

   return res;
}
int test()
{
    printf("test");
    return 1;
}
void test_foo()
{
    int n = -2;
    printf("sum(%d) = %d\n",n,foo(n));
    int i=0;
    //FOR(i,10,test);
}
int test_print(int i)
{
    printf("%d ",i);
    return 1;
}
void test_FOR()
{
    FOR(0,10,test_print);
}
int FOR(int s,int e,int f(int))
{
    s<e && f(s) && (FOR(s+1,e,f));
    return 1;
}

void FindNumber2(int a[],int n, int dest,int* res)
{
    if(NULL==a || n==0)
        return;
    int i =0,j=n-1;
    int k =0;
    memset(res,-1,n*sizeof(int));
    while(a[j]>=dest)
        j--;
    while(1)
    {
        if(i<j)
        {
            if(a[i]+a[j]<dest)
            {
                i++;
            }
            else if(a[i]+a[j]==dest)
            {   //find
                res[k++] = a[i];
                res[k++] = a[j];
                i++; j--;
            }
            else
            {
                j--;
            }
        }
        else
            break;
    }
}
void test_FindNumber2()
{
    //int arr[] = {1,2,3,4,5,6,7,8,9,10}; const int size=10;
    int arr[] = {1,2,4,7,11,15}; const int size=6;
    int res[size] = {0};
    FindNumber2(arr,size,15,res);
    for(int i = 0;i<size;i++)
    {
        if(res[i]==-1)
            break;
        printf("%d ",res[i]);
    }
}

int FindNonRepeat(char* arr)
{
    // 使用char类型保存个数,如果重复的次数太多可能会溢出
    char a[255] = {0};
    char *p = arr;
    while(*p!='\0')
        a[*p++]++;
    p = arr;
    while(*p!='\0')
        if(a[*p]==1)
        {
            printf("%c\n",*p);
            return 1;
        }
        else
            p++;
    printf("find nothing...\n");
    return 0;
}
void test_FindNonRepeat()
{
    char arr[] = "aacbcdedeeeff";
    FindNonRepeat(arr);
}
#endif