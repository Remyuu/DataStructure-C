//
//  main.c
//  DS09_circleQueue
//
//  Created by Remoo on 2022/10/7.
//

#include <stdio.h>
#include <stdlib.h>
#define NUM 5

typedef struct circleQueue{
    int* base; //数据地址
    int front; //头指针
    int rear; //尾指针
}cirQueue;

cirQueue* CreateQueue(void);
int GetLength(cirQueue* cq);
int IsEmpty(cirQueue* cq);
int IsFull(cirQueue* cq);
int GetFrontValue(cirQueue* cq);
void In(cirQueue* cq,int value);
void Out(cirQueue* cq);
void ShowQueue(cirQueue* cq);

cirQueue* CreateQueue(void){
    cirQueue* cq =(cirQueue*)malloc(sizeof(cirQueue));
    cq->base=(int*)malloc(NUM*sizeof(int));
    cq->front=cq->rear=0; //头指针，尾指针都赋值为0
    return cq;
}

//获取队列长度
int GetLength(cirQueue* cq){
    //此处有三种情况：
    //1 front==rear
    //2 rear>front
    //3 rear<front rear已经循环了一波了
    int rear = cq->rear;
    int front = cq->front;
    return (rear-front+NUM)%NUM;
}

int IsEmpty(cirQueue* cq){
    if(cq->front==cq->rear)return 1;
    else return 0;
}

int IsFull(cirQueue* cq){
    if((cq->rear+1)%NUM==cq->front)return 1;
    else return 0;
}

int GetFrontValue(cirQueue* cq){
    if(IsEmpty(cq)){
        printf("队列为空。");
        return 0;
    }
    return cq->base[cq->front];
}

//入列
void In(cirQueue* cq,int value){
    if(IsFull(cq)){
        printf("队列满了！");
        return;
    }
    cq->base[cq->rear]=value;
    cq->rear=(cq->rear+1)%NUM;
}

//出列
void Out(cirQueue* cq){
    if(IsEmpty(cq)){
        printf("队列为空。");
        return;
    }
    cq->front=(cq->front+1)%NUM;
}

void ShowQueue(cirQueue* cq){
    int i = cq->front;
    while(i!=cq->rear){
        printf("%4d",cq->base[i]);
        i=(i+1)%NUM;
    }
}

int main(){
    cirQueue* cq=NULL;
    cq = CreateQueue();
    In(cq,1);
    In(cq,2);
    ShowQueue(cq);
    Out(cq);
    ShowQueue(cq);
}
