//
//  DS03_DNode.c
//  DS03_DNode
//
//  Created by Remoo on 2022/9/26.
//
//  Xcode Dev
//

#include <stdio.h>
#include <stdlib.h>

typedef struct DNode{
    int data;
    struct DNode *next;//下一个节点 后驱节点
    struct DNode *pr;//上一个节点 前驱节点
}dnode;

//基本操作
dnode* CreateDNode(int n);
int Insert(dnode *head,int index,int value);
int Delete(dnode *head,int index);
void PrintLink(dnode *head);//与LNode一样,只是增加了逆向输出的功能
int GetLinkLength(dnode *head);//与LNode一样
int GetValue(dnode *head,int index);//与LNode一样
int FindIndex(dnode *head,int value);//与LNode一样
//算法1
void Move(dnode *head);

int main() {
    printf("DS03_doubleLinkList \n");
    int temp=0;
    dnode* test=CreateDNode(5);


    PrintLink(test);
        
    printf("元素数量:%d\n",GetLinkLength(test));

    PrintLink(test);
    
    printf("输入_待删除位序：");
    scanf("%d",&temp);
    if(Delete(test,temp))printf("\nsucceed");else printf("\nfaild!");
    PrintLink(test);
}


//把所有大于等于0的数放在负数的前面
    /*
     分析：现将p赋值为位序1的地址，q赋值为链表尾部地址。
     p从左向右寻找最近的非负数，q从右向左寻找负数，然后两者交换。循环上述操作。
     */
    
void Move(dnode *head){
    dnode *p,*q;int temp;
    p=head->next;
    for (q=head; q->next!=NULL; q=q->next);//直接将q移动到节点的尾部
    while(p!=q){
        while(p!=q&&p->data>=0)p=p->next;
        while(p!=q&&q->data<0)q=q->pr;
        if(p!=q){
            temp=p->data;
            p->data=q->data;
            q->data=temp;
        }
    }
}


//创建双链表
    /*
     分析：双链表的结构与单链表类似，只是多了一个前驱节点。
     */
dnode* CreateDNode(int n){
    dnode *head,*p,*q;int i;
    p=head=(dnode*)malloc(sizeof(dnode));//先给头节点指针、位序1的指针开辟内存空间
    for(i=1;i<=n;i++){
        q=(dnode*)malloc(sizeof(dnode));
        scanf("%d",&q->data);
        q->pr=p;
        p->next=q;
        p=q;
    }
    p->next=head->pr=NULL;//两端节点置空
    return head;
}
//取得链表长度
    /*
     分析：与单链表一致。
     */
int GetLinkLength(dnode *head){
    dnode *p;int n;
    n=0;
    p=head->next;
    while(p!=NULL){
        n++;p=p->next;
    }
    return n;
}
    /*
     分析：与单链表一致。
     */
int GetValue(dnode *head,int index){
    dnode *p;int j;
    if(index<1)return 0;
    j=1;p=head->next;
    while(p!=NULL&&j<index){
        p=p->next;j++;
    }
    if(p==NULL)return 0;
    return p->data;
}
    /*
     分析：与单链表一致。
     */
int FindIndex(dnode *head,int value){
    int i = 1;
    dnode *p_temp = head->next;
    while(p_temp!=NULL&&p_temp->data!=value){
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
int Delete(dnode *head,int index){//index输入的是位序
    dnode *n;int i;
    if(index<1||index>GetLinkLength(head))return 0;
    n=head;i=0;
    while(n->next!=NULL&&i!=index){
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
int Insert(dnode *head,int index,int value){
    dnode *n,*new;int i;
    if(index<1&&index>GetLinkLength(head))return 0;
    n=head;i=0;
    while(n->next!=NULL&&i!=index){
        n=n->next;i++;
    }//现在n已经指到了index的位置了
    new=(dnode*)malloc(sizeof(dnode));
    new->data=value;
    
    new->next=n;
    new->pr=n->pr;
    n->pr->next=new;//这一行需要小心
    n->pr=new;
    return 1;
}
//打印链表
void PrintLink(dnode *head){
    dnode *p;int index;
    p=head;index=0;printf("\n顺序输出：");
    while(p->next!=NULL){
        p=p->next;index++;
        printf("\n%3d:%-3d\t%p\t%p\t%p",index,p->data,p->pr,p,p->next);
    }
    printf("\n逆序输出：");
    while(p!=head){
        printf("%3d:%-3d\t",index,p->data);
        p=p->pr;index--;
    }
    printf("\n");
}
