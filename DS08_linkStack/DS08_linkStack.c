//
//  main.c
//  DS08_LStack
//
//  Created by Remoo on 2022/9/30.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}linkStack;

//基本操作
linkStack* CreateStack(void);
int GetTop(linkStack* stack);
int Push(linkStack* stack,int value);
int Pop(linkStack* stack);
int IsEmptyStack(linkStack* stack);
void ShowStack(linkStack* head);
//算法
void TurnLink1(linkStack* s1,linkStack* s2);
void Conversion(linkStack* stack,int m,int n);

int main() {
    printf("DS08_linkStack \n");
    linkStack* stack1;
    stack1 = CreateStack();
    Conversion(stack1,10,2);
    //linkStack *stack1,*stack2;
    //stack1 = CreateStack();
    //stack2 = CreateStack();
    //Push(stack1,11);Push(stack1,12);Push(stack1,13);
    //Push(stack2,21);Push(stack2,22);Push(stack2,23);
    //PrintStack(stack1);
    //PrintStack(stack2);
}

//初始化链栈 头节点的data不存储值
linkStack* CreateStack(void){
    linkStack* stack;//定义linkStack指针类型
    stack=(linkStack*)malloc(sizeof(linkStack));//为linkStack开辟内存空间，其大小是一个节点的大小
    stack->next=NULL;//防止下一个节点为野指针，置NULL
    return stack;//返回stack指针
}
//取得栈顶元素
int GetTop(linkStack* stack){
    return stack->next->data;
}
//取得链栈长度
int GetStackLength(linkStack* head){
    linkStack *p;int n;n=0;
    p=head->next;
    while(p!=NULL){
        n++;p=p->next;
    }
    return n;
}
//压栈
int Push(linkStack* stack,int value){
    linkStack* new_stack;//创建一个临时的节点
    new_stack=(linkStack*)malloc(sizeof(linkStack));//开辟内存空间
    if(!stack)return 0;//如果开辟失败，则Push函数返回0
    new_stack->data=value;//新的节点的data数据域传入value
    new_stack->next=stack->next;
    stack->next=new_stack;//将新节点的next数据域设置为栈顶原next指针，将栈顶的next变成new_stack的地址。
    return 1;
}
//出栈
int Pop(linkStack* stack){
    linkStack* temp_stack;
    if(stack->next==NULL)return 0;//如果栈空，就删除失败
    temp_stack=stack->next;
    stack->next=temp_stack->next;
    free(temp_stack);
    return 1;
}
//判断栈空
int IsEmptyStack(linkStack* stack){
    if(stack->next==NULL)return 1;
    else return 0;
}
//打印链表
void ShowStack(linkStack* head){
    linkStack *stack;int index;
    stack=head->next;index=1;printf("\n");
    while(stack!=NULL){
        printf("%3d:%-3d\t",index,stack->data);
        stack=stack->next;index++;
    }
    printf("\n");
}

//逆置，把s1的元素Pop出，传给s2即可。
void TurnLink1(linkStack* s1,linkStack* s2){
    int x;
    while (s1->next!=NULL) {
        x=GetTop(s1);
        Pop(s1);
        Push(s2,x);
    }
}

void Conversion(linkStack* stack,int m,int n){
    while(m!=0){
        Push(stack,m%n);m=m/n;
    }
    ShowStack(stack);
}
