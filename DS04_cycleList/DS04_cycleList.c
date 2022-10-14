//
//  main.c
//  DS04_circleList
//
//  Created by Remoo on 2022/9/27.
//
//  Xcode Dev
//

#include <stdio.h>
#include <stdlib.h>

typedef struct CNode{
    int data;
    struct CNode *next;
}cnode;

//基本算法
cnode *CreateList(int n);
int GetLinkLength(cnode *head);
int GetValue(cnode *head,int index);
int FindIndex(cnode *head,int value);
int Delete(cnode *head,int index);
int InsertValue(cnode *head,int index,int value);
void PrintLink(cnode *head);

int main() {
    printf("DS04_cycleList \n");
    int temp=0;int value=0;
    
    printf("输入_初始化元素（10个）:");
    cnode* test=CreateCNode(10);
    printf("%d",test->data);
    PrintLink(test);
    
    printf("元素数量:%d\n",GetLinkLength(test));

    printf("输入_位序：");
    scanf("%d",&temp);
    value = GetValue(test,temp);
    printf("\n取得值：%d\n",value);

    printf("输入_元素：");
    scanf("%d",&temp);
    value = FindIndex(test,temp);
    printf("\n取得位序：%d\n",value);
    
    printf("输入_待删除位序：");
    scanf("%d",&temp);
    if(Delete(test,temp))printf("\nsucceed");else printf("\nfaild!");
    PrintLink(test);
    
    printf("输入_待插入位序、数值：");
    scanf("%d %d",&temp,&value);
    if(InsertValue(test,temp,value))printf("\nsucceed");else printf("\nfaild!");
    PrintLink(test);
    
}


//创建循环链表
cnode *CreateCNode(int n){
    cnode *head,*p,*s;
    int i;
    p=head=(cnode*)malloc(sizeof(cnode));
    for(i=1;i<=n;i++){
        s=(cnode*)malloc(sizeof(cnode));
        scanf("%d",&s->data);
        p->next=s;
        p=s;
    }
    p->next=head;//尾巴指向头部，即为循环单链表。其余和单链表一致。
    return head;
}
//取得链表长度
int GetLinkLength(cnode *head){
    cnode *p;int n;n=0;
    p=head->next;
    while(p!=head){//只有这一个地方与单链表相异
        n++;p=p->next;
    }
    return n;
}
//取元素操作
int GetValue(cnode *head,int index){
    cnode *p;int j;
    if(index<1)return 0;
    j=1;p=head->next;
    while(p!=head&&j<index){//这里与单链表相异
        p=p->next;j++;
    }
    if(p==head)return 0;//这里与单链表相异
    return p->data;
}
//查找元素索引
int FindIndex(cnode *head,int value){
    int i = 1;
    cnode *p_temp = head->next;
    while(p_temp!=head&&p_temp->data!=value){//这里与单链表相异
        p_temp=p_temp->next;i++;
    }
    return i;
}
//删除元素
int Delete(cnode *head,int index){
    cnode *p_1,*p_2;int j;
    if(index<1&&index>GetLinkLength(head))
        return 0;
    p_1=head;j=0;
    while(p_1->next!=head&&j<index-1){//这里与单链表相异
        p_1=p_1->next;j++;
    }
    p_2=p_1->next;
    p_1->next=p_2->next;
    free(p_2);
    return 1;
}
//插入元素
int InsertValue(cnode *head,int index,int value){
    cnode *p_1,*p_new;int j;
    if(index<1&&index>GetLinkLength(head))return 0;
    p_1=head;j=0;
    while(p_1->next!=head&&j<index-1){//这里与单链表相异
        p_1=p_1->next;j++;//将p_1指到index
    }
    p_new=(cnode*)malloc(sizeof(cnode));
    p_new->data=value;
    p_new->next=p_1->next;
    p_1->next=p_new;
    return 1;
}
//打印链表
void PrintLink(cnode *head){
    cnode *p;int index;
    p=head->next;index=1;printf("\n");
    while(p!=head){//这里与单链表相异
        printf("%3d:%-3d\t",index,p->data);
        p=p->next;index++;
    }
    printf("\n");
}

