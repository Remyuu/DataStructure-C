//
//  main.c
//  DS05_CDNode
//
//  Created by Remoo on 2022/9/27.
//
//  Xcode Dev
//

#include <stdio.h>
#include <stdlib.h>

typedef struct CDNode{
    int data;
    struct CDNode *next;//下一个节点 后驱节点
    struct CDNode *pr;//上一个节点 前驱节点
}cdnode;

//基本操作
cdnode* CreateDNode(int n);
int Insert(cdnode *head,int index,int value);
int Delete(cdnode *head,int index);
void PrintLink(cdnode *head);//与LNode一样,只是增加了逆向输出的功能
int GetLinkLength(cdnode *head);//与LNode一样
int GetValue(cdnode *head,int index);//与LNode一样
int FindIndex(cdnode *head,int value);//与LNode一样
//算法1
void Move(cdnode *head);

int main() {
    printf("DS05_cycleDoubleList \n");
    int temp=0;
    cdnode* test=CreateDNode(5);
    PrintLink(test);

    printf("元素数量:%d\n",GetLinkLength(test));

    Insert(test,2,100);
    PrintLink(test);
    
    printf("输入_待删除位序：");
    scanf("%d",&temp);
    if(Delete(test,temp))printf("\nsucceed");else printf("\nfaild!");
    PrintLink(test);
}



//创建双链表
    /*
     分析：双链表的结构与单链表类似，只是多了一个前驱节点。
     */
cdnode* CreateDNode(int n){
    cdnode *head,*p,*q;int i;
    p=head=(cdnode*)malloc(sizeof(cdnode));//先给头节点指针、位序1的指针开辟内存空间
    for(i=1;i<=n;i++){
        q=(cdnode*)malloc(sizeof(cdnode));
        scanf("%d",&q->data);
        q->pr=p;
        p->next=q;
        p=q;
    }
    p->next=head;head->pr=p;//两端节点连首尾
    return head;
}
//取得链表长度
    /*
     分析：与单链表一致。
     */
int GetLinkLength(cdnode *head){
    cdnode *p;int n;
    n=0;
    p=head->next;
    while(p!=head){
        n++;p=p->next;
    }
    return n;
}
    /*
     分析：与单链表一致。
     */
int GetValue(cdnode *head,int index){
    cdnode *p;int j;
    if(index<1)return 0;
    j=1;p=head->next;
    while(p!=head&&j<index){
        p=p->next;j++;
    }
    if(p==head)return 0;
    return p->data;
}
    /*
     分析：与单链表一致。
     */
int FindIndex(cdnode *head,int value){
    int i = 1;
    cdnode *p_temp = head->next;
    while(p_temp!=head&&p_temp->data!=value){
        p_temp=p_temp->next;i++;
    }
    return i;
}
//删除链表
    /*
     分析：先确定删除位置i的合理性，包括输入值要大于等于1且小于链表长度。
     其次将指针定位到需要删除的节点位序上。然后取出前驱节点和后驱节点。
     将上一个节点的next地址赋值给下一个节点的pr，奖下一个节点的pr赋值给上一个节点的next。
     最后free需要删除的节点即可。
     */
int Delete(cdnode *head,int index){//index输入的是位序
    cdnode *n;int i;
    if(index<1&&index>GetLinkLength(head))return 0;
    n=head;i=0;
    while(n->next!=head&&i!=index){
        n=n->next;i++;
    }//现在n已经指到了index的位置了
    n->pr->next=n->next;
    n->next->pr=n->pr;
    free(n);
    return 1;
}
//插入元素
    /*
     首先判断输入i合理性，包括输入值要大于等于1且小于链表长度。
     其次将指针n指向位序i。
     创建malloc一个new节点，data赋值对应内容value。
     new节点的后驱节点是原位序为i的地址，new的前驱节点是原位序为i的前驱节点。
     然后将原位序为i的前驱节点的后驱节点改为new的地址，将原位序为i的前驱节点改为new的地址。
     */
int Insert(cdnode *head,int index,int value){
    cdnode *n,*new;int i;
    if(index<1&&index>GetLinkLength(head))return 0;
    n=head;i=0;
    while(n->next!=head&&i!=index){
        n=n->next;i++;
    }//现在n已经指到了index的位置了
    new=(cdnode*)malloc(sizeof(cdnode));
    new->data=value;
    
    new->next=n;
    new->pr=n->pr;
    n->pr->next=new;//这一行需要小心
    n->pr=new;
    return 1;
}
//打印链表
void PrintLink(cdnode *head){
    cdnode *p;int index;
    p=head->next;index=1;printf("\n顺序输出：");
    while(p!=head){
        printf("%3d:%-3d\t",index,p->data);
        p=p->next;index++;
    }
    p=head->pr;
    printf("\n逆序输出：");
    while(p!=head){
        printf("%3d:%-3d\t",index,p->data);
        p=p->pr;index--;
    }
    printf("\n");
}
