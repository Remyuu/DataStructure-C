//
//  main.c
//  DS10_LinkQueue
//
//  Created by Remoo on 2022/10/8.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkQueueNode{
    int data;
    struct LinkQueueNode* next;
}lqnode;

typedef struct LinkQueue{
    lqnode* front;
    lqnode* rear;
}lqueue;

lqueue* CreateQueue(void);
int GetLength(lqueue* lq);//求表长
int IsEmpty(lqueue* lq);
int GetFrontValue(lqueue* lq);
void In(lqueue* lq,int value);
void Out(lqueue* lq);
void Show(lqueue* lq);

lqueue* CreateQueue(void){
    lqueue* lq = (lqueue*)malloc(sizeof(lqueue));
    lq->front=lq->rear=(lqnode*)malloc(sizeof(lqnode));
    lq->front->next=NULL;
    return lq;
}
int GetLength(lqueue* lq){
    int i;lqnode* p;
    i=0; p = lq->front->next;
    while(p!=NULL){
        i++;p=p->next;
    }
    return i;
}

int IsEmpty(lqueue* lq){
    if(lq->front==lq->rear)return 1;
    else return 0;
}

int GetFrontValue(lqueue* lq){
    if(IsEmpty(lq))return 0;
    else return lq->front->next->data;
}

void In(lqueue* lq,int value){
    lqnode* p = (lqnode*)malloc(sizeof(lqueue));
    p->data=value;p->next=NULL;
    lq->rear->next=p;
    lq->rear=p;
}

void Out(lqueue* lq){
    lqnode* p;
    if(IsEmpty(lq))return;
    p=lq->front->next;//先存储当前即将被删除的front->next
    lq->front->next=p->next;
    if(lq->rear==p)
        lq->rear=lq->front;
    free(p);
}

void Show(lqueue* lq){
    lqnode* p;
    p=lq->front->next;
    while(p!=NULL){
        printf("%4d",p->data);
        p=p->next;
    }
}
int main(){
    lqueue* lq;
    lq=CreateQueue();
    In(lq,3);In(lq,2);In(lq,1);
    Show(lq);
    Out(lq);
    Show(lq);
    Out(lq);Out(lq);
    Show(lq);
}
