# 1.线性表
```
typedef struct sqlist
{
    int *data;
    int length;
    int listsize;
}sqnode;//表头
```
# 2.链表
```
typedef struct LNode{
    int data;
    struct LNode* next;
}lnode;
```
# 3.双链表
```
typedef struct DNode{
    int data;
    struct DNode *next;//下一个节点 后驱节点
    struct DNode *pr;//上一个节点 前驱节点
}dnode;
```
# 4.循环链表
```
typedef struct CNode{
    int data;
    struct CNode *next;
}cnode;
```
# 5.循环双链表
```
typedef struct CDNode{
    int data;
    struct CDNode *next;//下一个节点 后驱节点
    struct CDNode *pr;//上一个节点 前驱节点
}cdnode;
```
# 6.静态链表
```
typedef struct slink{
    int data;
    int cur;
}StaticLink[SIZE];
```
# 7.顺序栈
```
typedef struct stack{
    int* base;
    int top;
    int stracksize;
}seqStack;
```
# 8.链栈
```
typedef struct node{
    int data;
    struct node* next;
}linkStack;
```
# 9.顺序队列
```
typedef struct circleQueue{
    int* base; //数据地址
    int front; //头指针
    int rear; //尾指针
}cirQueue;
```
# 10.链队列
```
typedef struct LinkQueueNode{
    int data;
    struct LinkQueueNode* next;
}lqnode;

typedef struct LinkQueue{
    lqnode* front;
    lqnode* rear;
}lqueue;
```

# 11.顺序串
```
typedef struct{
    char* ch;//串的起始地址
    int length;//串的长度，不代表seqStr串所占内存空间
    int stringSize;//当前串所分配的内存空间(未乘sizeof(char))
}seqStr;
```
