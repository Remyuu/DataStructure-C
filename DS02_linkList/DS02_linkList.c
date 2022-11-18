//
//  DS002_LNode.c
//  DataStructure
//
//  Created by Remoo on 2022/9/17.
//
//  Xcode Dev
//

#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int data;
    struct LNode* next;
}lnode;

//基本操作
lnode* CreateLNode(int n);//创建链表
int GetLinkLength(lnode *head);//获取链表长度
int GetValue(lnode *head,int index);//通过索引获取
int FindIndex(lnode *head,int value);//通过值找到索引
int Delete(lnode *head,int index);//删除
int InsertValue(lnode *head,int index,int value);//插入
void PrintLink(lnode *head);//输出

//涉及算法
int Turn(lnode *head);//翻转

int main(void){
    printf("DS02_linkList \n");
    int temp=0;int value=0;
    
    printf("输入_初始化元素（10个）:");
    lnode* test=CreateLNode(10);
    printf("%d",test->data);
    PrintLink(test);
    
    printf("元素数量:%d\n",GetLinkLength(test));
    
    Turn(test);
    PrintLink(test);
    
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

//创建单链表
lnode *CreateLNode(int n){
    lnode* p_head,*p_next,*p_loop;
    int i;
    p_next=p_head=(lnode*)malloc(sizeof(lnode));
    for (i=1; i<=n; i++) {
        p_loop=(lnode*)malloc(sizeof(lnode));
        scanf("%d",&p_loop->data);
        p_next->next=p_loop;
        p_next=p_loop;
    }
    p_next->next=NULL;
    return p_head;
}
//取得链表长度
int GetLinkLength(lnode *head){
    lnode *p;int n;
    n=0;
    p=head->next;
    while(p!=NULL){
        n++;p=p->next;
    }
    return n;
}
//取得元素值
int GetValue(lnode *head,int index){
    lnode *p;int j;
    if(index<1)return 0;
    j=1;p=head->next;
    while(p!=NULL&&j<index){
        p=p->next;j++;
    }
    if(p==NULL)return 0;
    return p->data;
}
//查找元素索引
int FindIndex(lnode *head,int value){
    int i = 1;
    lnode *p_temp = head->next;
    while(p_temp!=NULL&&p_temp->data!=value){
        p_temp=p_temp->next;i++;
    }
    return i;
}
//删除元素
int Delete(lnode *head,int index){
    lnode *p_1,*p_2;int j;
    if(index<1&&index>GetLinkLength(head))
        return 0;
    p_1=head;j=0;
    while(p_1->next!=NULL&&j<index-1){
        p_1=p_1->next;j++;
    }
    p_2=p_1->next;
    p_1->next=p_2->next;
    free(p_2);
    return 1;
}
//插入元素
int InsertValue(lnode *head,int index,int value){
    lnode *p_1,*p_new;int j;
    if(index<1)return 0;
    p_1=head;j=0;
    while(p_1!=NULL&&j<index-1){
        p_1=p_1->next;j++;
    }
    if(p_1==NULL)return 0;
    p_new=(lnode*)malloc(sizeof(lnode));
    p_new->data=value;
    p_new->next=p_1->next;
    p_1->next=p_new;
    return 1;
}
//打印链表
void PrintLink(lnode *head){
    lnode *p;int index;
    p=head->next;index=1;printf("\n");
    while(p!=NULL){
        printf("%3d:%-3d\t",index,p->data);
        p=p->next;index++;
    }
    printf("\n");
}
//逆置元素
int Turn(lnode *head){
    lnode *p,*q;
    p=head->next;
    head->next=NULL;
    while(p!=NULL){//断头，然后头连屁股。重复。
        q=p->next;
        p->next=head->next;
        head->next=p;
        p=q;
    }
    return 1;
}
