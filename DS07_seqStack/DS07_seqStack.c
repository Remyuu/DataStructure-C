//
//  main.c
//  DS07_seqStack
//
//  Created by Remoo on 2022/9/28.
//

#include <stdio.h>
#include <stdlib.h>
#define SIZE 20
/*顺序栈：
    栈的顺序储存。
    同时利用一个变量记录当前栈顶的位置（下标或指针），称为栈顶指针。
栈顶是没有存或者可以直接被覆盖的内容！压栈直接压在栈顶处，然后栈顶指针再往上移动。
 */
typedef struct stack{
    int* base;
    int top;
    int stracksize;
}seqStack;

//常规操作
seqStack* CreateStack(void);
int GetLength(seqStack* stack);
int GetTop(seqStack* stack);
void SaveOp(seqStack* stack);
void SaveOp(seqStack* stack);
int IsStackEmpty(seqStack* stack);
void Push(seqStack* stack,int value);
int Pop(seqStack* stack);
void ShowStack(seqStack* stack);
//算法 十进制整数m转换成n进制数。
void Conversion(seqStack* stack,int m,int n);
long Fac(seqStack* stack,int n);

int main(){
    printf("DS07_seqStack \n");
    seqStack* stack;
    stack = CreateStack();
    Conversion(stack,10,2);
}


seqStack* CreateStack(void){
    seqStack *stack;
    stack=(seqStack*)malloc(sizeof(seqStack));
    stack->base=(int*)malloc(SIZE*sizeof(int));
    stack->top=0;
    stack->stracksize=SIZE;
    return stack;
}
//取得栈的长度
int GetLength(seqStack* stack){
    return stack->top;
}
//得到栈顶的元素
int GetTop(seqStack* stack){
    if(stack->top==0)return 0;//top等于0，则为空栈
    return stack->base[stack->top-1];
}
//检查是否栈满 安全检查
void SaveOp(seqStack* stack){
    if (stack->top >= stack->stracksize) {
        stack->stracksize++;
        stack->base=(int*)realloc(stack->base, (stack->stracksize)*sizeof(int));
    }
}
int IsStackEmpty(seqStack* stack){
    if(stack->top==0)return 1;
    else return 0;
}
//压栈
void Push(seqStack* stack,int value){
    SaveOp(stack);
    stack->base[stack->top++]=value;
}
//删除 弹栈
int Pop(seqStack* stack){
    if(IsStackEmpty(stack))return 0;
    stack->top--;
    return 1;
}
void ShowStack(seqStack* stack){
    int i;
    for (i=stack->top-1; i>=0; i--)
        printf("%-4d",stack->base[i]);
    printf("\n");
}

void ClearAll(seqStack* stack){
    for (int i=0; i<=GetLength(stack); i++)
        Pop(stack);
}

void Conversion(seqStack* stack,int m,int n){
    while(m!=0){
        Push(stack,m%n);m=m/n;
    }
    ShowStack(stack);
}

long Fac(seqStack* stack,int n){
    long f=1;int x;
    while(n>0){
        Push(stack,n);
        n--;
    }
    ShowStack(stack);
    while(!IsStackEmpty(stack)){
        x=GetTop(stack);
        Pop(stack);
        f *= x;
    }
    return f;
}
