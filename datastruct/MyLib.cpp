#include "MyLib.h"
#include <stdlib.h>
#include <stdio.h>

int Mod(int num,int mod){
    if(mod==0)
        perror("mod == 0\n");
    while( num >= mod){
        num -= mod;
    }
    return num;
}

int Divide(int dividend,int divisor){
    if(divisor==0)
        perror("mod == 0\n");
    int quotient = 0;
    while(dividend >= divisor){
        dividend -= divisor;
        quotient++;
    }
    return quotient;
}

int Count1(int n){
    int count = 0;
    while(n){
       n &= n - 1;
       count++;
    }
    return count;
}

int Count0(int n){
    int count = Count1(n);
    int bits = sizeof(n)*8;
    return bits-count;
}

// ²¹Âë...
char* BitToStr(int n){
    char* str = (char*)malloc(sizeof(char)*33);
    char* p = str;
    unsigned int i=-1<<31;
    int j=0;
    int bits = 32;
    while(j<bits){
        int k = n&i;
        if(k!=0){
            //Print("1\n");
            *p='1';
        }else{
            *p='0';
            //Print("0\n");
        }
        i=i>>1;
        p++;
        j++;
    }
    *p='\0';
    return str;
}
