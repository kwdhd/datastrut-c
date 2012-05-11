#ifndef MYSTRING_H
#define MYSTRING_H


#include <stdio.h>
#include <stdlib.h>


char* ReverseString(char* str);

char* ReverseString(char* str,int s,int e);

char* ReverseString(char* str,char* s,char* e);

int StrLen(char* str);

char* StrSpy(char* dst,char* sst);

char* ReverseWords(char* str);

int StrCmp(char* s1,char* s2);

void Print(char* str);

char* IntToStr(int num);

long StrToLong(char* str);

int CharToInt(char ch);

int MaxContinuNum(char *inputstr,char *outputstr);

#endif