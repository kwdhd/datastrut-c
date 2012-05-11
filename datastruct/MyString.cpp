//#ifndef MYSTRING
//#define MYSTRING

#include "MyString.h"
#include <stdio.h>
#include <string.h>
#include "MyLib.h"

char* ReverseString(char* str){
    int len = strlen(str);
    ReverseString(str,0,len-1);
    return str;
}
char* ReverseString(char* str,int s,int e){
    if( s>e || s<0 || e<0 || str ==NULL)
        return NULL;
    char *ps=str+s,*pe=str+e;
    while(ps!=pe){
        *ps = *ps^*pe;
        *pe = *ps^*pe;
        *ps = *pe^*ps;
        ps++;
        if(ps!=pe)
            pe--;
    }
    return str;
}
char* ReverseString(char* str,char* s,char* e){
    if(str == NULL || s == NULL || e == NULL|| s > e)
        return NULL;
    char *ps=s,*pe=e;
    while(ps!=pe){
        *ps = *ps^*pe;
        *pe = *ps^*pe;
        *ps = *pe^*ps;
        ps++; pe--;
    }
    return str;
}

int StrLen(char* str){
    int len = 0;
    char* p = str;
    while(*p!='\0'){
        p++; len++;
    }
    return len;
}

char* StrSpy(char* strDest,char* strSrc){
    if(strDest==NULL || strSrc==NULL)
        return NULL;
    char* p = strDest;
    while((*p++=*strSrc)!='\0')
        ;
    return strDest;
}

// 翻转英文单词...
char* ReverseWords(char* str){
    //int len = strlen(str);
    char* p = str,*q = str;
    ReverseString(str);
    while(1){
       if(*p==' '||*p=='\0'){
           ReverseString(str,q,p-1);
           if(*p=='\0')
               break;
           p++; q = p;
       }
       p++;
    }
    return str;
}

int StrCmp(char* s1,char* s2){
    if(s1==NULL || s2==NULL)
        return 0;
    while(*s1!='\0'&&*s2!='\0'&&*s1==*s2){
        s1++; s2++;
    }
    if(*s1=='\0' && *s2=='\0')
        return 0;
    if(*s1!='\0')
        return 1;
    if(*s2!='\0')
        return -1;
}


char* IntToStr(int num){
    return NULL;
}

long StrToLong(char* str){
    long num = 0;
    int len = StrLen(str);
    if( len == 0)
        return 0;
    int neg = 0;
    if(*str == '-'){
        neg = 1;
        str++;
    }
    if(*str == '+')
        str++;
    for(;*str!='\0';str++)
    {
         num = num*10 + CharToInt(*str);
    }
    
    printf("test:%ld,%s\n",num,BitToStr(num));
    if(neg == 1)
    {
        num = ~num+ 1;
        return num;
    }
    else
    {
        return num;
    }
}

int CharToInt(char ch)
{
    if(ch<48 || ch>57)
    {
        perror("Can not convert to int...");
    }
    return (int)ch-48;
}

// 找出最大连续数字串
// abcd12345ed125ss123456789
int MaxContinuNum(char *inputstr,char *outputstr)
{
    if(inputstr == NULL|| outputstr == NULL)
        return -1;
    char *i=inputstr,*j=inputstr;// i指向数字串第一个字符,j指向数字串后第一个字符
    int max=0,count=0;
    char *pmax=inputstr;
    while(*i != '\0'){   // i没到头,i不是数字
        while(*i!= '\0' &&( *i<'0' || *i > '9'))
            i++;
        j = i;
        if(*i!='\0'){
            while(*j>='0'&& *j<='9'){
                j++; count++;
            }
        }else{
            break;
        }
        if( count > max){
            max = count;
            pmax = i;
        }
        if(*j=='\0')
            break;
        i = j+1;
        count = 0;
    }
    for(int i=0;i<max;i++){
        *outputstr = *pmax;
        outputstr++; pmax++;
    }
    *outputstr = '\0';
    return max;
}

//#endif