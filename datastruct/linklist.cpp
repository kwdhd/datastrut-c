
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"


void PrintInt(int data){
    printf("%d ",data);
}

void InsertData(struct LinkList* ll,int data){

    struct LinkListNode* p = NULL;
    struct LinkListNode* node = (struct LinkListNode*)malloc(sizeof(struct LinkListNode));

    if( node == NULL){
        printf("error: cannot create new LinkListNode...\n");
        return;
    }
    node->next = NULL;
    node->data = data;

    if( ll->head == NULL){
        ll->head = node;
        ll->size++;
        return;
    };
    //struct LinkListNode* p = NULL;
    p = ll->head;
    while(p->next)
        p = p->next;
    p->next = node;
    ll->size++;
}

int DeleteData(struct LinkList* ll,int data){
    struct LinkListNode* p = ll->head;
    if( p->data == data){
        free(ll->head);
        ll->head = NULL;
        ll->size--;
        return 1;
    }
    while( p->next  && p->next->data != data)
        p = p->next;
    if( p->next && p->next->data == data ){
        struct LinkListNode* q = p->next;
        p->next = p->next->next;
        free(q);
        ll->size--;
        return 1;
    }
    return 0;
}

struct LinkListNode* FindData(struct LinkList ll,int data){
    struct LinkListNode* p = ll.head;
    while( p && p->data != data)
        p = p->next;
    if( p )
        return p;
    return NULL;
}

void PrintLList(struct LinkList ll){
    struct LinkListNode* p = ll.head;
    while( p ){
        printf("%d  ",p->data);
        p = p->next;
    }
}

void InitLinkList(struct LinkList* lp){
    lp->size = 0;
    lp->head = NULL;
}

// �����������Ƿ��ཻ,���ؽ���
pLNode IsJoined(LList* l1,LList* l2){
    pLNode p1 = l1->head, p2 = l2->head;
    int c1 = 0, c2 = 0;
    if( p1 == NULL || p2 == NULL)
        return NULL;
    while(p1->next){
        p1 = p1->next;
        c1++;
    }
    while(p2->next){
        p2 = p2->next;
        c2++;
    }
    // ���һ�����һ����ͬ
    if( p1 == p2){
        pLNode q =NULL;
        int c = (c1>c2)?(q=p1,p1=p2,c1-c2):(q=p2,c2-1);
        p1 = l1->head; p2 = l2->head;
        for(int i =0;i<c1;i++)
            q=q->next;
        while(p1!=q){
            p1 = p1->next;
            q = q->next;
        }
        return p1;
    }
    return NULL;
}
// ���������Ƿ��ཻ,���ؽ���
pLNode IsJoinedWithCircle(LList*l1, LList* l2){
    pLNode j1,j2,p1,p2;
    p1 = l1->head; p2 = l2->head;
    j1 = HasCircle(l1); j2 = HasCircle(l2);
    if( 0 == (int)j1 + (int)j2)
        return IsJoined(l1,l2);
    if( 1 == (int)j1 + (int)j2)
        return NULL;
    if( 2 == (int)j1 + (int)j2){
        // 3�����,1. ���뽻��2. �ڻ����ཻ��3. �ڻ����ཻ
        if( j1 == j2 ){
            int c1=0,c2=0,c=0;
            pLNode q = NULL;
            while(p1!=j1){
                p1=p1->next;
                c1++;
            }
            while(p2!=j2){
                p2=p2->next;
                c2++;
            }
            c = (c1>c2)?(q=p1,p1=p2,c1-c2):(q=p2,c2-1);
            while(p1!=q){
                p1=p1->next; q=q->next;
            }
            return p1;
        }
        else{
            pLNode q = p1; p1=p1->next;
            while(q!=p1){
                if(p1 = p2)
                    return p2;
                p1=p1->next;
            }
            // ѭ��һ�ܶ�û���ཻ
            return NULL;
        }
    }
}
// �жϵ������Ƿ��л�
pLNode HasCircle(LList* ll){
    if( ll == NULL)
        return NULL;
    pLNode p = ll->head;
    pLNode q = ll->head;
    while(q&& q->next){
        // q �ߵı� p ��
        p = p->next;
        q = q->next->next;
        if( p == q){
            p = ll->head;
            while(p != q){
                p = p->next;
                q = q->next;
            }
            // ���ؽ���
            return p;
        }
    }
    // ���������������� NULL
    // if q->next || q->next->next == NULL, �л�
    return NULL;
}
// ��ת����...
void ReverseLinkList(pLList ll){
    // û�нڵ��ֻ��һ���ڵ�
    if(ll->head==NULL||ll->head->next==NULL)
        return;
    pLNode pre=ll->head,p=ll->head->next,next=ll->head->next;
    pre->next = NULL;
    while(next){
        p->next = pre;
        pre = p;
        p = next;
        next = next->next;
    }
    ll->head = p;
}