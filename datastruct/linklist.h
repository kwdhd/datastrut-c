#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdio.h>
#include <stdlib.h>


typedef  void (*Visit)(int data);

typedef struct LinkListNode{
	int data;
	struct LinkListNode* next;
}LNode,*pLNode;

typedef struct LinkList{
	struct LinkListNode* head;
	int size;
}LList,*pLList;

void InitLinkList(struct LinkList* pl);

void PrintInt(int data);

void InsertData(struct LinkList* ll,int data);

int DeleteData(struct LinkList* ll,int data);

struct LinkListNode* FindData(struct LinkList ll,int data);

void PrintLList(struct LinkList ll);

pLNode IsJoined(LList* l1,LList* l2);

pLNode IsJoinedWithCircle(LList*l1, LList* l2);

pLNode HasCircle(LList* ll);

#endif