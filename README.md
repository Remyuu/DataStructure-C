目前进度到：**线索化链式二叉树**。
所有代码均通过测试。
更新时间戳。
也可以在GitHub中克隆代码：[https://github.com/Remyuu/DataStructureSourceCode][1]
> 代码开发测试环境    Xcode Version 13.4.1 (13F100)


<!--more-->


# 1.顺序表
## 结构-2022/9/6.

```C
typedef struct sqlist
{
    int *data;
    int length;
    int listsize;
}sqnode;//表头
```

## 顺序表代码
```C
//
//  DS01_sqlist.c
//  MacC_Learn01
//
//  Created by Remoo on 2022/9/6.
//
//  Xcode Dev
//

#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 10
typedef struct
{
    int *data;
    int length;
    int listsize;
}sqlist;//表头
void initlist(sqlist *L);
int getlen(sqlist *L);
int getelem(sqlist *L,int i, int *e);
void list(sqlist *L);
int insert(sqlist *L,int i,int x);
int SeqListErase(sqlist* sl, int pos);
int main(void)
{
    sqlist sq_list;
    int x;
    int *elem=(int *)malloc(sizeof(int));
    
    initlist(&sq_list);
    //此时sq_list的data已经存储了malloc出来的内存首地址
    printf("input datas(-1:end):");
    scanf("%d",&x);
    int i=1;
    while(x!=-1)
    {
        insert(&sq_list,i,x);
        i++;
        scanf("%d",&x);
    }
    printf("目前顺序表元素如下:\n");
    list(&sq_list);
    
    int index,x0;
    printf("在第几位序插入什么元素：\n");
    scanf("%d %d",&index,&x0);
    if(insert(&sq_list,index,x0))
        list(&sq_list);
    else
        printf("插入失败!");
    
    
    printf("取第几个元素：\n");
    int n;
    scanf("%d",&n);
    if(getelem(&sq_list,n,elem))
        printf("取出的元素是：%d\n",*elem);
    else
        printf("取出失败!");
    printf("删除第几个元素：\n");
    int d;
    scanf("%d",&d);
    if(SeqListErase(&sq_list,d))
        list(&sq_list);
    else
        printf("删除失败！");
    free(sq_list.data);
    free(elem);
    return 0;
}

/* 1.初始化操作(创建一个空的顺序表L) */
void initlist(sqlist *L)
{
    L->data=(int *)malloc(sizeof(int)*INITSIZE);/* 申请存储空间*/
    L->length=0;              /* 初始长度为0 */
    L->listsize=INITSIZE;     /* 容量为初始量 */
}

/* 2. 求表长操作 */
int getlen(sqlist *L)
{return(L->length);}

/* 3. 取元素操作 */
int getelem(sqlist *L,int i, int *e)
{
    if(i< 1||i>L->length) return 0;
    *e = L->data[i-1];
    return 1;
}

/* 4.输出操作(输出顺序表L的各数据元素值) */
void list(sqlist *L)
{
    int i;
    for(i=0;i< L->length;i++)
    printf("%5d ",L->data[i]);
    printf("\n");
}
/* 5. 插入操作(在顺序表L中的第i个位序上插入一个值为x的数据元素) */
int insert(sqlist *L,int i,int x)
{
    int j;
    if(i< 1||i>L->length+1) return 0;  // 参数i不合理,返回0
    if(L->length==L->listsize)        // 存储空间不够，增加一个存储空间
    {
        L->data=(int *)realloc(L->data,(L->listsize+1)*sizeof(int));
        L->listsize++;                // 增加一个存储空间长度
    }
    for(j=L->length-1;j>=i-1;j--)
        L->data[j+1]=L->data[j];      // 将序号为i及之后的数据元素后移一位
    L->data[i-1]=x;                   // 在序号i处放入x
    L->length++;                      // 顺序表长度增1
    return 1;                         // 插入成功,返回1
}

int SeqListErase(sqlist* sl, int pos){
    if(pos > sl->length)return 0;
    for (int i = pos; i < sl->length; i++){
        sl->data[i - 1] = sl->data[i];
    }
    sl->length--;
    return 1;
}
```


# 2.链表
## 结构-2022/9/17.

```C
typedef struct LNode{
    int data;
    struct LNode* next;
}lnode;
```

## 链表代码
```C
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
lnode* CreateLNode(int n);
int GetLinkLength(lnode *head);
int GetValue(lnode *head,int index);
int FindIndex(lnode *head,int value);
int Delete(lnode *head,int index);
int InsertValue(lnode *head,int index,int value);
void PrintLink(lnode *head);

//涉及算法
int Turn(lnode *head);

int main(void){
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
    if(index< 1)return 0;
    j=1;p=head->next;
    while(p!=NULL&&j< index){
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
    if(index< 1&&index>GetLinkLength(head))
        return 0;
    p_1=head;j=0;
    while(p_1->next!=NULL&&j< index-1){
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
    if(index< 1)return 0;
    p_1=head;j=0;
    while(p_1!=NULL&&j< index-1){
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
```




# 3.双链表
## 结构-2022/9/26.
```C
typedef struct DNode{
    int data;
    struct DNode *next;//下一个节点 后驱节点
    struct DNode *pr;//上一个节点 前驱节点
}dnode;
```

## 双链表代码
```C
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
        while(p!=q&&q->data< 0)q=q->pr;
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
    if(index< 1)return 0;
    j=1;p=head->next;
    while(p!=NULL&&j< index){
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
    if(index< 1||index>GetLinkLength(head))return 0;
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
    if(index< 1&&index>GetLinkLength(head))return 0;
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
```


# 4.循环单向链表
## 结构-2022/9/27.

```C
typedef struct CNode{
    int data;
    struct CNode *next;
}cnode;
```

## 循环单向链表代码
```C
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
    if(index< 1)return 0;
    j=1;p=head->next;
    while(p!=head&&j< index){//这里与单链表相异
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
    if(index< 1&&index>GetLinkLength(head))
        return 0;
    p_1=head;j=0;
    while(p_1->next!=head&&j< index-1){//这里与单链表相异
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
    if(index< 1&&index>GetLinkLength(head))return 0;
    p_1=head;j=0;
    while(p_1->next!=head&&j< index-1){//这里与单链表相异
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

int main() {
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
```



# 5.循环双链表
## 结构-2022/9/27.

```C
typedef struct CDNode{
    int data;
    struct CDNode *next;//下一个节点 后驱节点
    struct CDNode *pr;//上一个节点 前驱节点
}cdnode;
```

## 循环双头链表代码
```C
//
//  main.c
//  DS05_CDNode
//
//  Created by Remoo on 2022/9/27.
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
    if(index< 1)return 0;
    j=1;p=head->next;
    while(p!=head&&j< index){
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
    if(index< 1&&index>GetLinkLength(head))return 0;
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
    if(index< 1&&index>GetLinkLength(head))return 0;
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
```



# 6.静态链表
## 结构-2022/9/28.

```C
typedef struct slink{
    int data;
    int cur;
}StaticLink[SIZE];
```

## 静态链表代码
```C
//
//  main.c
//  DS06_SNode
//
//  Created by Remoo on 2022/9/28.
//
//  Xcode Dev
//

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

//连续的一块内存空间

typedef struct {
    int data;
    int cur;
}StaticLink[SIZE];

void CreateList(StaticLink space){
    int i;
    for (i=0; i< SIZE-1; i++) {
        space[SIZE].cur=i+1;
        space[SIZE-1].cur=0;
    }
}

int GetNode(StaticLink space){
    int i;
    i=space[0].cur;
    if(i==0)return 0;
    space[0].cur=space[i].cur;
    return i;
}

void FreeNode(StaticLink space,int i){
    space[i].cur=space[0].cur;space[0].cur=i;
}

void CreateLink(StaticLink space,int n){
    int head,k,s,i;
    k=head=GetNode(space);
    for(i=1;i<=n;i++){
        s=GetNode(space);
        scanf("%d",&space[s].data);
        space[k].cur=s;
        k=s;
    }
    space[k].cur=0;
}

int GetLength(StaticLink space,int head){
    int i,k;
    k=space[head].cur;i=0;
    while(k!=0){
        i++;k=space[k].cur;
    }
    return i;
}

int GetValue(StaticLink space,int head,int i){
    int j,k;
    if(i < 1)return 0;
    j=0;k=head;
    while(k!=0&&j < i){
        j++;k=space[k].cur;
    }
    if(k==0)return 0;
    return space[k].data;
}

int Insert(StaticLink space,int head,int i,int value){
    int j,k,m;
    if(i < 1)return 0;
    k=head;j=0;
    while(k!=0&&j< i-1){
        j++;k=space[k].cur;
    }
    if(k==0)return 0;
    m=GetNode(space);
    if(m!=0){
        space[m].data=value;
        space[m].cur=space[k].cur;
        space[k].cur=m;
        return 1;
    }
    else return 0;
}
int Delete(StaticLink space,int head,int i){
    int j,k,m;
    if(i< 0)return 0;
    k=head;j=0;
    while(k!=0&&j< i-1){
        j++;k=space[k].cur;
    }
    if(k==0)return 0;
    m=space[k].cur;
    space[k].cur=space[m].cur;
    FreeNode(space, m);
    return 1;
}

void Show(StaticLink space,int head){
    int i;
    i=space[head].cur;
    while(i!=0){
        printf("%4d",space[i].data);
        i=space[i].cur;
    }
    printf("\n");
}
int main() {

}
```


# 7.顺序栈
## 结构-2022/9/28.

```C
typedef struct stack{
    int* base;
    int top;
    int stracksize;
}seqStack;
```

## 顺序栈代码
```C
//
//  main.c
//  DS07_seqStack
//
//  Created by Remoo on 2022/9/28.
//

#include <stdio.h>
#include <stdlib.h>
#define SIZE 20
/*
顺序栈：
    栈的顺序储存。
    同时利用一个变量记录当前栈顶的位置（下标或指针），称为栈顶指针。
栈顶是没有存或者可以直接被覆盖的内容！压栈直接压在栈顶处，然后栈顶指针再往上移动。
*/
typedef struct{
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

int main(){
    seqStack* stack;
    stack = CreateStack();
    printf("%ld\n",Fac(stack,10));
    Push(stack, 999);
    ShowStack(stack);
}
```


# 8.链栈
## 结构-2022/9/30.

```C
typedef struct node{
    int data;
    struct node* next;
}linkStack;
```

## 链栈代码
```C
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
void PrintStack(linkStack* head);
//算法
void TurnLink1(linkStack* s1,linkStack* s2);

int main() {
    printf("DS08_linkStack \n");
    linkStack *stack1,*stack2;
    stack1 = CreateStack();
    stack2 = CreateStack();
    Push(stack1,11);Push(stack1,12);Push(stack1,13);
    Push(stack2,21);Push(stack2,22);Push(stack2,23);
    PrintStack(stack1);
    PrintStack(stack2);
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
void PrintStack(linkStack* head){
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
```


# 9.循环队列
## 结构-2022/10/7.

```C
typedef struct circleQueue{
    int* base; //数据地址
    int front; //头指针
    int rear; //尾指针
}cirQueue;
```

## 循环队列代码
```C
//
//  main.c
//  DS09_circleQueue
//
//  Created by Remoo on 2022/10/7.
//

#include <stdlib.h>
#include <stdio.h>
#define NUM 3

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
    In(cq,1);In(cq,2);
    ShowQueue(cq);
    Out(cq);
    ShowQueue(cq);
}
```


# 10.链队列
## 结构-2022/10/8.

```C
typedef struct LinkQueueNode{
    int data;
    struct LinkQueueNode* next;
}lqnode;

typedef struct LinkQueue{
    lqnode* front;
    lqnode* rear;
}lqueue;
```

## 链队列代码
```C
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
```



# 11.顺序串
## 结构-2022/10/12.

```C
typedef struct{
    char* ch;//串的起始地址
    int length;//串的长度，不代表seqStr串所占内存空间
    int stringSize;//当前串所分配的内存空间(未乘sizeof(char))
}seqStr;
```

## 顺序串代码
```C
//
//  main.c
//  DS11_seqString
//
//  Created by Remoo on 2022/10/12.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char* ch;//串的起始地址
    int length;//串的长度，不代表seqStr串所占内存空间
    int stringSize;//当前串所分配的内存空间(未乘sizeof(char))
}seqStr;

seqStr* CreateString(int StringSize);
void ApplyString(seqStr* seqstr,char* str);
int GetLength(seqStr* seqstr);
void Copy(seqStr* ss1,seqStr* ss2);
void Append(seqStr* ss1,seqStr* ss2);
int IsEqual(seqStr* ss1,seqStr* ss2);
void Change(seqStr* ss,int index,char c);
void Insert(seqStr* ss1,int index,seqStr* ss2);
void Delete(seqStr* ss,int start,int end);
void Show(seqStr* ss);

seqStr* CreateString(int StringSize){
    seqStr* s = (seqStr*)malloc(sizeof(seqStr));
    s->ch=(char*)malloc(sizeof(char)*StringSize);
    s->length=0;
    s->stringSize=StringSize;
    return s;
}

//char[]转seqStr
void ApplyString(seqStr* seqstr,char* str){
    int i=0;
    while(str[i]!='\0')i++;//计算str的长度
    if(seqstr->stringSize < i){//如果串不够长，就重新分配内存空间
        seqstr->ch=(char*)realloc(seqstr->ch, (i*sizeof(char)));
        seqstr->stringSize=i;
    }
    seqstr->length=i;
    for (i=0; i < seqstr->length; i++) {//一个一个赋值
        seqstr->ch[i]=str[i];
    }
}

//求串的长度
int GetLength(seqStr* seqstr){
    return seqstr->length;
}

//将ss1的串复制给ss2
void Copy(seqStr* ss1,seqStr* ss2){
    int i;
    if(ss2->stringSize < GetLength(ss1)){
        ss2->ch=(char*)realloc(ss2->ch, GetLength(ss1)*sizeof(char));
        ss2->stringSize=GetLength(ss1);
    }
    ss2->length=GetLength(ss1);
    for (i=0; i < ss2->length; i++) {
        ss2->ch[i]=ss1->ch[i];
    }
}

//两个seqStr拼接，只改变前者的值
void Append(seqStr* ss1,seqStr* ss2){
    int i;
    if(ss1->stringSize < ss2->length){
        ss1->ch=(char*)realloc(ss1->ch, ss2->length*sizeof(char));
        ss1->stringSize=ss2->length;
    }
    for (i = 0; i < ss2->length; i++) {
        ss1->ch[i+ss1->length]=ss2->ch[i];
    }
    ss1->length=ss1->length + ss2->length;
}

//判断两个seqStr对象值是否相等
int IsEqual(seqStr* ss1,seqStr* ss2){
    int i;
    if(GetLength(ss1)!=GetLength(ss2))
        return 0;
    for (i=0; i < GetLength(ss1); i++) {
        if(ss1->ch[i]!=ss2->ch[i])
            return 0;
    }
    return 1;
}

//获得字串
seqStr* GetSubString(seqStr* seqstr,int start,int end){
    int delta;
    //合理性判断
        //i  0 - n 闭
        //j  i - n 闭
    if(start < 0||start>seqstr->length||start>end||end>seqstr->length){//若输入不合法，则原封不动返回。
        //return (seqStr*)malloc(0);
        return seqstr;
    }
    seqStr* string;
    string = CreateString(end-start);
    
    string->length=end-start;
    for (delta=start; start < end; start++) {
        string->ch[start-delta]=seqstr->ch[start];
        //printf("(%d,%c)\t",i-start,string->ch[i-start]);
    }
    return string;
}

void Change(seqStr* ss,int index,char c){
    //合法性修正
    index = index < 0?0:index;
    index = index>GetLength(ss)?GetLength(ss):index;
    ss->ch[index]=c;
}

void Insert(seqStr* ss1,int index,seqStr* ss2){
    int i;
    //合法性修正
    index = index < 0?0:index;
    index = index>GetLength(ss1)?GetLength(ss1):index;
    if(ss1->stringSize<(GetLength(ss1)+GetLength(ss2)))//扩容
        ss1->ch = (char*)realloc(ss1->ch, sizeof(char)*(GetLength(ss1)+GetLength(ss2)));
    ss1->length=GetLength(ss1)+GetLength(ss2);
    ss1->stringSize=ss1->length;
    //将ss1中的后半部分后移
    for(i=0;i < GetLength(ss1)-index-1;i++){
        ss1->ch[i+GetLength(ss2)+index]=ss1->ch[i+index];
    }
    //插入、覆盖
    for (i=0; i < GetLength(ss2); i++) {
        ss1->ch[i+index]=ss2->ch[i];
    }
    //改变长度
    ss1->stringSize=ss1->length;
}

void Delete(seqStr* ss,int start,int end){
    int index;
    if(start < 0||start>ss->length||start>end||end>ss->length)
        return;
    for (index=0; index!=GetLength(ss)-end; index++){
        //printf("(%d,%c)->",start+index,ss->ch[start+index]);
        //Show(ss);
        ss->ch[start+index]=ss->ch[end+index];
        //printf("(%d,%c)\t",start+index,ss->ch[start+index]);
        //Show(ss);
    }
    ss->length=GetLength(ss)-(end-start);
}

void Show(seqStr* ss){
    int i;
    for (i=0; i < GetLength(ss); i++) {
        printf("%c",ss->ch[i]);
    }
    printf("\n");
}

int main(){
    seqStr* ss1 = CreateString(10);
    ApplyString(ss1,"abcdefg");
    ss1 = GetSubString(ss1, 0,7);
    printf("\nLength:%d\n",GetLength(ss1));
    Show(ss1);
    Delete(ss1, 1, 3);
    Show(ss1);
    seqStr* ss2 = CreateString(10);
    Copy(ss1, ss2);
    Show(ss1);
    Show(ss2);
    Insert(ss1, 2, ss2);
    Show(ss1);
}
```



# 12.链串
## 结构-2022/10/14.

```C
typedef struct StringNode{//该文件是带头节点结构
    char ch;
    struct StringNode* next;
}linkStr;
```

## 链串代码
```C
//
//  main.c
//  DS12_linkString
//
//  Created by Remoo on 2022/10/14.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct StringNode{//该文件是带头节点结构
    char ch;
    struct StringNode* next;
}linkStr;

linkStr* CreateString(void);
void ApplyString(linkStr* ls,char* string);
void Copy(linkStr* ls1,linkStr* ls2);
int GetLength(linkStr* ls);
int IsEqual(linkStr* ls1,linkStr* ls2);
void Show(linkStr* ls);
linkStr* GetSum(linkStr* ls1,linkStr* ls2);
linkStr* GetSubString(linkStr* ls,int start,int end);
void Free(linkStr* ls,int start,int end);
void Insert(linkStr* ls1,int index,linkStr* ls2);

//创建链串头节点
linkStr* CreateString(void){
    linkStr* ls;
    ls = (linkStr*)malloc(sizeof(linkStr));
    ls->next=NULL;//防止野指针
    return ls;
}

//将char数组复制给链串
    //思路：先用原有的空间，没有的再申请空间。若有多余，释放后面的空间。
void ApplyString(linkStr* ls,char* string){
    int i;
    linkStr *q,*r;
    linkStr* nextP;
    r=ls;q=ls->next;//r是头节点地址，q是头节点的后驱节点。
    for (i=0; string[i]!='\0'; i++) {//如果char数组索引i不为末尾，则执行
        //现在拿到一个char数组位序i的元素。
            //r是需要写入元素地址的前驱节点
            //q是需要写入元素的地址
        if(q!=NULL){//如果需要写入数据的地址（后驱节点）不为空
            q->ch=string[i];//直接写入数据
            r=q;//r记录为q，则下一次经过此处循环时，r仍为需要写入数据的前驱节点
            q=q->next;//q移动到下一个地址
            //也就是说：若q的next是NULL，则会循环下面的代码块
        }else{//若后驱节点为空，直接开辟新节点，再写入。然后将
            nextP = (linkStr*)malloc(sizeof(linkStr));
            nextP->ch=string[i];
            r->next=nextP;//将新创建的节点链上去
            r=nextP;
        }
    }
    //当char数组的所有元素都录入链串，则将末尾的节点的后驱节点赋值NULL
    r->next=NULL;
    while(q!=NULL){//释放多余的节点
        r=q->next;free(q);q=r;
    }
}

void Copy(linkStr* ls1,linkStr* ls2){
    linkStr* ls1_p,*temp,*ls2_p;
    ls1_p=ls1;ls2_p=ls2;
    while(ls2_p->next!=NULL){//当被复制的表还有元素，则执行转移
        if(ls1_p->next==NULL)
            ls1_p->next=CreateString();
        ls1_p->next->ch=ls2_p->next->ch;
        ls1_p=ls1_p->next;
        ls2_p=ls2_p->next;
    }
    while(ls1_p->next!=NULL){
        temp=ls1_p->next->next;
        free(ls1_p->next);
        ls1_p->next=temp;
    }
}

int GetLength(linkStr* ls){
    int count=0;
    while(ls->next!=NULL){
        count++;
        ls=ls->next;
    }
    return count;
}

int IsEqual(linkStr* ls1,linkStr* ls2){
    while(ls1->next!=NULL&&ls2->next!=NULL){
        if(ls1->next->ch!=ls2->next->ch){
            return 0;//串的内容不相等
        }
        ls1=ls1->next;
        ls2=ls2->next;
    }
    if(ls1->next==NULL&&ls2->next==NULL)
        return 1;//串相等
    else
        return 0;//串长不等，但是前面部分都相等
}


linkStr* GetSum(linkStr* ls1,linkStr* ls2){
    linkStr* head,*ls3;
    ls3 = CreateString();
    head=ls3;
    while(ls1->next!=NULL){
        ls3->next=CreateString();
        ls3->next->ch=ls1->next->ch;
        ls1=ls1->next;
        ls3=ls3->next;
    }
    while(ls2->next!=NULL){
        ls3->next=CreateString();
        ls3->next->ch=ls2->next->ch;
        ls2=ls2->next;
        ls3=ls3->next;
    }
    return head;
}

//取字串
linkStr* GetSubString(linkStr* ls,int start,int end){
    int index;
    linkStr* head,*sls;
    sls = CreateString();
    head = sls;
    //合理性判断，非法则返回空串
    if(start<0||start>GetLength(ls)||end<start||end>GetLength(ls))
        return head;
    //指针指到start
    for (index=0; index<start; index++) {
        ls=ls->next;
    }
    for (index=0; index<end-start; index++){
        sls->next=CreateString();
        sls->next->ch=ls->next->ch;
        sls=sls->next;
        ls=ls->next;
    }
    sls->next=NULL;
    return head;
}

//删除字串 "abc"
void Free(linkStr* ls,int start,int end){
    int index;
    linkStr* temp;
    //合理性判断，非法则返回
    if(start<0||start>GetLength(ls)||end<start||end>GetLength(ls))
        return;
    for (index=0; index<start; index++)
        ls=ls->next;
    for (index=0; index<end-start; index++) {
        temp=ls->next->next;
        free(ls->next);
        ls->next=temp;
    }
}


//ls2插入ls1的第index索引处  "abcd" "123"
void Insert(linkStr* ls1,int index,linkStr* ls2){
    int i;
    linkStr* ls1_2_head;//ls1的后半部分节点
    ls1_2_head = CreateString();
    //合理性纠正
    index = index < 0?0:index;
    index = index>GetLength(ls1)?GetLength(ls1):index;
    for (i=0; i<index; i++)
        ls1=ls1->next;
    ls1_2_head->next = ls1->next;
    Free(ls1, index, GetLength(ls1));
    while(ls2->next!=NULL){
        ls1->next=CreateString();
        ls1->next->ch=ls2->next->ch;
        ls1=ls1->next;
        ls2=ls2->next;
    }
    while(ls1_2_head->next!=NULL){
        ls1->next=CreateString();
        ls1->next->ch=ls1_2_head->next->ch;
        ls1=ls1->next;
        ls1_2_head=ls1_2_head->next;
    }
    ls1->next=NULL;
}

void Show(linkStr* ls){
    linkStr* p;
    p=ls->next;
    while(p!=NULL){
        printf("%c",p->ch);
        p=p->next;
    }
    printf("\n");
}

int main(){
    linkStr* ls1;linkStr* ls2;linkStr* ls3;
    ls1 = CreateString();
    ls2 = CreateString();
    ApplyString(ls1, "Hello World");
    ApplyString(ls2, "My Name Is Remoo");
    Show(ls1);Show(ls2);
    printf("Length:%d\n",GetLength(ls1));
    printf("是否相等:%d\n",IsEqual(ls1, ls2));
    
    Copy(ls1, ls2);
    Show(ls1);Show(ls2);
    printf("Length:%d\n",GetLength(ls1));
    printf("是否相等:%d\n",IsEqual(ls1, ls2));
    
    ls3 = GetSum(ls1, ls2);
    Show(ls3);
    
    Free(ls1,0,GetLength(ls1));
    ls1 = GetSubString(ls3, 11, 16);
    Show(ls1);
    Free(ls1,3,4);
    Show(ls1);
    Insert(ls1, 3, ls2);
    Show(ls1);
}
```




# 13.BF、KMP算法

## 算法声明-2022/10/18.

```C
/*Based on seqStr*/
int BF_Search(seqStr* text,seqStr* pattern);
int KMP_Search(seqStr* text,seqStr* pattern);
```

## BF、KMP算法代码

```C
//
//  main.c
//  DS13_StringsPatternMatching
//
//  Created by Remoo on 2022/10/18.
//

//Include Brute_Force & KMP use LinkString
//KMP
//公共前后缀的长度要小于字串的长度

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char* ch;
    int length;
    int stringSize;
}seqStr;

seqStr* CreateString(int StringSize);
void ApplyString(seqStr* seqstr,char* str);
int GetLength(seqStr* seqstr);
void Show(seqStr* ss);

int BF_Search(seqStr* text,seqStr* pattern);
int KMP_Search(seqStr* text,seqStr* pattern);


seqStr* CreateString(int StringSize){
    seqStr* s = (seqStr*)malloc(sizeof(seqStr));
    s->ch=(char*)malloc(sizeof(char)*StringSize);
    s->length=0;s->stringSize=StringSize;
    return s;
}
void ApplyString(seqStr* seqstr,char* str){
    int i=0;
    while(str[i]!='\0')i++;//计算str的长度
    if(seqstr->stringSize < i){//如果串不够长，就重新分配内存空间
        seqstr->ch=(char*)realloc(seqstr->ch, (i*sizeof(char)));
        seqstr->stringSize=i;
    }
    seqstr->length=i;
    for (i=0; i < seqstr->length; i++) {//一个一个赋值
        seqstr->ch[i]=str[i];
    }
}
int GetLength(seqStr* seqstr){
    return seqstr->length;
}
void Show(seqStr* ss){
    int i;
    for (i=0; i < GetLength(ss); i++)
        printf("%c",ss->ch[i]);
    printf("\n");
};


int BF_Search(seqStr* text,seqStr* pattern){
    int i,j;
    i=0;j=0;
    while(i<GetLength(text)&&j<GetLength(pattern))//驱动指针前进
        if(text->ch[i]==pattern->ch[j]){
            i++;j++;//继续匹配下一个字符
        }else{
            i=i-j+1;j=0;//text+1
        }
    if (j==GetLength(pattern)) {
        return i-GetLength(pattern)+1;//返回位序
    }else{
        return 0;
    }
}

void GetNext(seqStr* pattern,int next[]){
    int j,k;
    j=0;k=-1;next[0]=-1;
    while(j<GetLength(pattern)){
        if(k==-1||pattern->ch[j]==pattern->ch[k]){
            j++;k++;next[j]=k;
        }else
            k=next[k];//当k不在-1且有不匹配的字，则将k打回原点
    }
}

int KMP_Search(seqStr* text,seqStr* pattern){
    int next[GetLength(pattern)],i,j;
    GetNext(pattern,next);
    i=0;j=0;
    while(i<GetLength(text)&&j<GetLength(pattern))
        if(j==-1||text->ch[i]==pattern->ch[j]){
            i++;j++;
        }else{
            j=next[j];
        }
    if(j>=GetLength(pattern))
        return i-GetLength(pattern)+1;
    return 0;
}

int main(){
    int index1,index2;
    seqStr* text,*pattern;
    text = CreateString(10);pattern = CreateString(10);
    ApplyString(text, "1111113");
    ApplyString(pattern, "13");
    Show(text);Show(pattern);
    
    index1 = BF_Search(text, pattern);
    index2 = KMP_Search(text,pattern);
    
    printf("BF result:%d\nKMP result:%d\n",index1,index2);
}
```






# 14.三元组顺序表
## 结构-2022/10/19.

```C
typedef struct{
    int i;int j;
    int value;
}TupleNode;//三元组单个节点

typedef struct{
    int rownum;
    int colnum;
    int valuenum;//非0元素个数
    TupleNode data[SIZE];
}Matrix;
```

## 三元组顺序表代码

```C
//
//  main.c
//  DS14_ sparseMatrix
//
//  Created by Remoo on 2022/10/19.
//

/*
 计算机存储矩阵虽然可以用二维数组，
 但是对于特殊的矩阵如稀疏矩阵，
 我们用顺序表以特殊的排列方式存储，
 达到压缩存储空间的目的。
 ====
 我们介绍两种方式压缩存储稀疏矩阵
 1、三元组顺序表法
 2、十字链表法
 */

#include <stdio.h>
#include <stdlib.h>

#define Row 4 /*行*/
#define Col 5 /*列*/
#define SIZE 100 /*定义顺序表最大长度*/

typedef struct{
    int i;int j;
    int value;
}TupleNode;//三元组单个节点

typedef struct{
    int rownum;
    int colnum;
    int valuenum;//非0元素个数
    TupleNode data[SIZE];
}Matrix;

Matrix* CreateSparseTable(int A[Row][Col]);
int GetValue(Matrix* M,int i,int j);
void Insert(Matrix* M,int i,int j,int value);
void Show(Matrix* M);

Matrix* CreateSparseTable(int A[Row][Col]){
    int i,j;
    Matrix* M = (Matrix*)malloc(sizeof(Matrix));
    M->rownum=Row;M->colnum=Col;
    M->valuenum=0;
    for (i=0; i<Row; i++)
        for (j=0; j<Col; j++)
            if(A[i][j]!=0){
                M->data[M->valuenum].i=i;
                M->data[M->valuenum].j=j;
                M->data[M->valuenum].value=A[i][j];
                M->valuenum++;
            }
    return M;
}

int GetValue(Matrix* M,int i,int j){
    
    int q,value;
    value = 0;
    for (q=0; q<M->valuenum; q++)
        if(M->data[q].i==i&&M->data[q].j==j)
            value = M->data[q].value;
    
    return value;
}

void Insert(Matrix* M,int i,int j,int value){
    int q;

    for (q=0; q<M->valuenum; q++)
        if(M->data[q].i==i&&M->data[q].j==j){
            M->data[q].value = value;
            return;
        }
    M->data[q+1].value=value;
    M->data[q+1].i=i;
    M->data[q+1].j=j;
    M->valuenum++;
}

void Show(Matrix* M){
    int i,j,q,value;
    for (i=0; i<M->rownum; i++){
        for (j=0; j<M->colnum; j++) {
            value = 0;
            for (q=0; q<M->valuenum; q++)
                if(M->data[q].i==i&&M->data[q].j==j)
                    value = M->data[q].value;
            printf("%4d ",value);
        }
        printf("\n");
    }
    
}


int main(){
    int testMatrix[4][5]={
        {0,0,0,0,1},
        {4,0,0,0,0},
        {0,0,1,0,0},
        {0,1,0,0,0}};
    Matrix* M;
    M = CreateSparseTable(testMatrix);
    Show(M);
    printf("%d \n",GetValue(M, 1, 0));
    
}


```



# 15.十字链表
## 结构-2022/10/19
```C
代码仍在编写中。
```

## 十字链表代码
```C
代码仍在编写中。
```


# 16.顺序存储二叉树
## 结构-2022/10/22
```C
typedef struct seqBinTree{
    int* data;
    int length;//数的节点数量
    int treeSize;//占用的空间
}sbt;
```

## 顺序存储二叉树代码
```C
//
//  main.c
//  DS16_seqBinaryTree
//
//  Created by Remoo on 2022/10/22.
//

#include <stdio.h>
#include <stdlib.h>

//适合存储完全二叉树，否则用链式存储的二叉树。
/*
 二叉树的性质：
 1- 在二叉树的第i层上至多有2i−1个结点（i≥1）
 2- 深度为k的二叉树至多有2k−1个结点（k≥1）
 3- 对任何一棵二叉树T，如果其终端结点数为n0，度为2的结点数为n2，则n0=n2+1
 4- 满二叉树的特点是：每一层上的结点数都是最大结点数，即每一层i的结点数都具有最大值2^(i−1)
 5- 具有n个结点的完全二叉树的深度为￼int(log_2(n))+1
 */

/*
 (从1开始)
 左孩子:2i 右孩子:2i+1
 父节点:i/2 所在层数:int(log_2(n))+1=int(log_2(n+1))
 */

typedef struct seqBinTree{
    int* data;
    int length;//数的节点数量
    int treeSize;//占用的空间
}sbt;

sbt* CreateSeqBiTree(int size);
void setBiTree(sbt* seqbt);//手动置树数值
void setBiTreeAuto(sbt* seqbt);//自动置树数值
int getLeftChild(sbt* seqbt,int index);
int getRightChild(sbt* seqbt,int index);
int getParent(sbt* seqbt,int index);

sbt* CreateSeqBiTree(int size){
    sbt* seqbt = (sbt*)malloc(sizeof(sbt));
    seqbt->data= (int*)malloc((size+1)*sizeof(int));
    seqbt->length=0;
    seqbt->treeSize=size+1;
    return seqbt;
}
void setBiTree(sbt* seqbt){
    int i;
    printf("Set Seq Bin Tree:");
    for (i=1; i<seqbt->treeSize; i++){
        printf("\n%d:",i);
        scanf("%d",&seqbt->data[i]);
    }
    seqbt->length=seqbt->treeSize-1;
}
void setBiTreeAuto(sbt* seqbt){
    int i;
    for (i=1; i<seqbt->treeSize; i++)
        seqbt->data[i]=i;
    seqbt->length=seqbt->treeSize-1;
}

int getLeftChild(sbt* seqbt,int index){
    if(index*2>seqbt->length) return 0;
    return seqbt->data[index*2];
}

int getRightChild(sbt* seqbt,int index){
    if(index*2+1>seqbt->length) return 0;
    return seqbt->data[index*2+1];
}

int getParent(sbt* seqbt,int index){
    if(index>seqbt->length) return 0;
    return seqbt->data[index/2];
}

int main(){
    sbt* bt= CreateSeqBiTree(10);
    //setBiTree(bt);
    setBiTreeAuto(bt);
    printf("\n左孩子：%d\n右孩子：%d\n父亲：%d\n",
           getLeftChild(bt, 2),
           getRightChild(bt, 2),
           getParent(bt, 2));
}
```


# 17.链式二叉树
## 结构-2022/10/29
```C
typedef struct linkBinTreeNode{
    int data;
    struct linkBinTreeNode *lc,*rc;
}lbn;
```

## 链式二叉树代码
```C
//
//  main.c
//  DS17_linkedBinaryTree
//
//  Created by Remoo on 2022/10/29.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct linkBinTreeNode{
    int data;
    struct linkBinTreeNode *lc,*rc;
}lbn;

//****链队列数据结构：****
typedef struct LinkQueueNode{
    lbn* data;
    struct LinkQueueNode* next;
}lqnode;
typedef struct LinkQueue{
    lqnode* front;
    lqnode* rear;
}lqueue;
lqueue* CreateQueue(void);
int IsEmpty(lqueue* lq);
lbn* GetFrontValue(lqueue* lq);
void In(lqueue* lq,lbn* value);
void Out(lqueue* lq);
lqueue* CreateQueue(void){
    lqueue* lq = (lqueue*)malloc(sizeof(lqueue));
    lq->front=lq->rear=(lqnode*)malloc(sizeof(lqnode));
    lq->front->next=NULL;
    return lq;
}
int IsEmpty(lqueue* lq){
    if(lq->front==lq->rear)return 1;
    else return 0;
}
lbn* GetFrontValue(lqueue* lq){
    if(IsEmpty(lq))return 0;
    else return lq->front->next->data;
}
void In(lqueue* lq,lbn* value){
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
//****链队列构造完毕****

lbn* CreateLinkBiTreeRoot(int data);
lbn* CreateLeftChild(lbn* parent,int data);
lbn* CreateRightChild(lbn* parent,int data);
int getLeftChild(lbn* lb);
int getRightChild(lbn* lb);
int getParent(lbn* lb);

void LNR(lbn* lb);//中序遍历 左中右
void NLR(lbn* lb);//先序遍历 中左右
void LRN(lbn* lb);//后序遍历 左右中

void LevelOrder(lbn* lb);//层序遍历

void CreateTreeByLNRAndNLR(void);//根据 前序+中序 -> 二叉树


void getPredecessor(lbn* root,lbn* target);

lbn* CreateLinkBiTreeRoot(int data){
    lbn* root = (lbn*)malloc(sizeof(lbn));
    root->data=data;
    root->lc=NULL;
    root->rc=NULL;
    return root;
}
lbn* CreateLeftChild(lbn* parent,int data){
    lbn* child = (lbn*)malloc(sizeof(lbn));
    parent->lc=child;
    child->data=data;
    child->lc=NULL;
    child->rc=NULL;
    return child;
}
lbn* CreateRightChild(lbn* parent,int data){
    lbn* child = (lbn*)malloc(sizeof(lbn));
    parent->rc=child;
    child->data=data;
    child->lc=NULL;
    child->rc=NULL;
    return child;
}

int getLeftChild(lbn* lb){
    if(lb->lc!=NULL)
        return lb->lc->data;
    return -99999;
}
int getRightChild(lbn* lb){
    if(lb->rc!=NULL)
        return lb->rc->data;
    return -99999;
}

void LNR(lbn* lb){
    if(lb==NULL)
        return;
    LNR(lb->lc);
    printf("%d ",lb->data);
    LNR(lb->rc);
}

void NLR(lbn* lb){
    if(lb==NULL)
        return;
    printf("%d ",lb->data);
    NLR(lb->lc);
    NLR(lb->rc);
}

void LRN(lbn* lb){
    if(lb==NULL)
        return;
    LRN(lb->lc);
    LRN(lb->rc);
    printf("%d ",lb->data);
}

void LevelOrder(lbn* lb){
    lqueue* Q;
    Q = CreateQueue();
    lbn* p;
    In(Q,lb);
    while(!IsEmpty(Q)){
        p = GetFrontValue(Q);
        printf("%d ",p->data);//访问出队节点
        Out(Q);//队头出
        if(p->lc!=NULL)
            In(Q,p->lc);
        if(p->rc!=NULL)
            In(Q,p->rc);
    }
}

/*
 如何根据前序和中序推出二叉树？（其他类似）
 由于，
 前序 ： 根节点 左子树前序遍历 右子树前序遍历
 中序 ： 左子树中序遍历 根节点 右子树中序遍历
 因此，
 根据根节点的左右子树的数量可求，
 然后递归即可。
 
 总结：无论是前序+中序、后序+中序、层序+中序，关键点是：
 Key:找到树的根节点，并根据中序序列划分左右子树，再找到左右子树根节点。
 */

void CreateTreeByLNRAndNLR(void){
    
}


/*
 查找中序遍历序列的前驱节点
 */
lbn* p;//目标，target
lbn* pre=NULL;//当前访问的前驱
lbn* final=NULL;//最终结果
void LNRs(lbn* lb){//根节点、暂存指针数组
    if(lb!=NULL){
        LNRs(lb->lc);
        if(lb==p)
            final=pre;
        else
            pre=lb;
        LNRs(lb->rc);
    }
}
void getPredecessor(lbn* root,lbn* target){
    p = target;
    LNRs(root);
    printf("\n%d的中序前驱节点是：%d",target->data,final->data);
}



int main(){
    lbn* root = CreateLinkBiTreeRoot(1);
    lbn* n1 = CreateLeftChild(root, 2);
    CreateLeftChild(n1, 4);
    CreateRightChild(n1, 5);
    lbn* n2 = CreateRightChild(root, 3);
    CreateLeftChild(n2, 6);
    CreateRightChild(n2, 7);
    //        1
    //    2       3
    // 4    5   6    7
    
    
    printf("根节点左右孩子：%d,%d\n",getLeftChild(root),getRightChild(root));
    
    printf("中序遍历：");
    LNR(root);
    
    getPredecessor(root,n2);//获取中序前驱节点，输出
    
    printf("\n层序遍历：");
    LevelOrder(root);
}



```



# 18.线索化链式二叉树
## 结构-2022/10/31
```C
typedef struct ThreadLinkBiNode{
    int data;
    struct ThreadLinkBiNode *lc,*rc;
    int ltag,rtag;
    //左右线索标记，tag==0 指向孩子；tag==1 指向线索（遍历序列前驱后继）。
}tlbn;
```

## 线索化链式二叉树代码
```C
//
//  main.c
//  DS18_threadLinkBinaryTree
//
//  Created by Remoo on 2022/10/31.
//

#include <stdio.h>
#include <stdlib.h>

//线索二叉树
//可分为：先序、中序、后序线索二叉树
//在链式二叉树基础上实现即可。

/*
 线索二叉树p节点的：（p->tag==1直接用线索，故以下只考虑p->tag==0）
    1-中序：**左根右**
        后继节点：rtag
            分析：最左下节点
        前驱节点：ltag
            分析：最右下节点
    2-先序：**根左右**
        后继节点：rtag
            分析：p可能有左孩子，一定有右孩子
                若有左，则先序后继节点是左孩子
                若没有，则先序后继节点是右孩子
        前驱节点：ltag
            分析：根据先序（根左右），前驱不可能在左右孩子中
                所以找不到，只能从头开始遍历。或者改为三叉链表。
                那么基于能够找到父节点的情况下，再分为四种情况：
                    1. 如果p是父节点的左孩子，则父节点就是先序前驱
                    2. 如果p是父节点的右孩子，且父节点的左孩子（兄弟节点）为空，则父节点就是先序前驱
                    3. 如果p是父节点的右孩子，左兄弟非空，则先序前驱是左兄弟最后一个被访问的节点
                    4. 如果没有父节点，则没有先序前驱节点。
    3-后序：**左右根**
        前驱节点：ltag
            分析：因为ltag==0，所以p一定有左孩子，不一定有右孩子
                假设**有**右孩子，则**右**子树中最后一个被访问的就是后续前驱节点
                假设**无**右孩子，则**左**子树中最后一个被访问的就是后续前驱节点
        后继节点：rtag
            分析：根据后序（左右根），后驱不可能在左右子树中
                所以找不到，改用三叉链表。
                那么基于能够找到父节点的情况下，再分为四种情况：
                    1. p是父节点的右孩子，则p后继节点是父节点
                    2. p是左节点，右孩子空，则p后继节点是父节点
                    3. p是左孩子，右兄弟非空，则p后继节点是右兄弟第一个读取的节点
                    4. 如果没有父节点，则没有先序后继节点。
            
 */


//线索链式二叉树结构
typedef struct ThreadLinkBiNode{
    int data;
    struct ThreadLinkBiNode *lc,*rc;
    int ltag,rtag;
    //左右线索标记，tag==0 指向孩子；tag==1 指向线索（遍历序列前驱后继）。
}tlbn;

tlbn* CreateThreadLinkBiTreeRoot(int data);
tlbn* CreateLeftChild(tlbn* parent,int data);
tlbn* CreateRightChild(tlbn* parent,int data);

void CreateThreadLinkBiNode_LNR(tlbn* lb);//中序线索化
void LNRThread(tlbn* lb);

void CreateThreadLinkBiNode_NLR(tlbn* lb);//先序线索化
void NLRThread(tlbn* lb);

tlbn* FirstNode(tlbn* lb);//P为根的子树中，第一个被中序遍历的结点
tlbn* getNextNode_LNR(tlbn* lb);//在中序线索二叉树中找到lb后驱节点
void LNR_Nr(tlbn* lb);//利用线索实现非递归中序遍历

tlbn* LastNode(tlbn* lb);//P为根的子树中，最后一个被中序遍历的结点
tlbn* getLastNode_LNR(tlbn* lb);//在中序线索二叉树中找到lb前驱
void Rev_LNR_Nr(tlbn* lb);//利用线索实现非递归中序**逆序**遍历
//Show方法
void LNR(tlbn* lb);
void NLR(tlbn* lb);

tlbn* CreateThreadLinkBiTreeRoot(int data){
    tlbn* root = (tlbn*)malloc(sizeof(tlbn));
    root->data=data;
    root->ltag=root->rtag=1;//默认为线索
    root->lc=NULL;
    root->rc=NULL;
    return root;
}
tlbn* CreateLeftChild(tlbn* parent,int data){
    tlbn* child = (tlbn*)malloc(sizeof(tlbn));
    parent->lc=child;
    parent->ltag=0;//标记为左孩子
    child->data=data;
    child->lc=NULL;
    child->rc=NULL;
    child->ltag=child->rtag=1;//默认为线索
    return child;
}
tlbn* CreateRightChild(tlbn* parent,int data){
    tlbn* child = (tlbn*)malloc(sizeof(tlbn));
    parent->rc=child;
    parent->rtag=0;//标记为右孩子
    child->data=data;
    child->lc=NULL;
    child->rc=NULL;
    child->ltag=child->rtag=1;//默认为线索
    return child;
}

tlbn* pre=NULL;
void LNRThread(tlbn* lb){//中序遍历线索化
    if(lb!=NULL){
        LNRThread(lb->lc);//左孩子

        if(lb->lc==NULL){//如果左孩子是空的，就建立线索前驱
            lb->lc=pre;
            lb->ltag=1;
        }
        if(pre!=NULL&&pre->rc==NULL){
            pre->rc=lb;//建立前驱节点的后继线索
            pre->rtag=1;
        }
        pre=lb;
        
        LNRThread(lb->rc);
    }
}
void CreateThreadLinkBiNode_LNR(tlbn* lb){
    pre=NULL;
    if(lb!=NULL){//非空二叉树才能初始化
        LNRThread(lb);
        pre->rc=NULL;
        pre->rtag=1;//处理最后一个节点
    }
}

void NLRThread(tlbn* lb){//先序遍历线索化
    if(lb!=NULL){
        if(lb->lc==NULL){//如果左孩子是空的，就建立线索前驱
            lb->lc=pre;
            lb->ltag=1;
        }
        if(pre!=NULL&&pre->rc==NULL){
            pre->rc=lb;//建立前驱节点的后继线索
            pre->rtag=1;
        }
        pre=lb;

        if(lb->ltag==0)//左孩子不是前驱线索才继续递归！！！与中序遍历线索化不同
            LNRThread(lb->lc);
        LNRThread(lb->rc);
    }
}
void CreateThreadLinkBiNode_NLR(tlbn* lb){
    pre=NULL;
    if(lb!=NULL){//非空二叉树才能初始化
        LNRThread(lb);
        if(pre->rc==NULL)
            pre->rtag=1;//处理最后一个节点
    }
}

//P为根的子树中，第一个被中序遍历的结点
tlbn* FirstNode(tlbn* lb){
    while (lb->ltag==0) lb=lb->lc;
    return lb;
}
//在中序线索二叉树中找到lb后驱节点
tlbn* getNextNode_LNR(tlbn* lb){//找中序遍历后继
    if(lb->ltag==0)//必有右孩子
        return FirstNode(lb->rc);
    else return lb->rc;
}

void LNR_Nr(tlbn* lb){//利用线索实现非递归中序遍历
    for (tlbn* _lb=FirstNode(lb); _lb!=NULL; _lb=getNextNode_LNR(_lb))
        printf("%d ",_lb->data);
}

//P为根的子树中，最后一个被中序遍历的结点
tlbn* LastNode(tlbn* lb){
    while (lb->rtag==0) lb=lb->rc;
    return lb;
}
//在中序线索二叉树中找到lb前驱
tlbn* getLastNode_LNR(tlbn* lb){//找中序遍历后继
    if(lb->rtag==0)//必有右孩子
        return LastNode(lb->lc);
    else return lb->lc;
}
void Rev_LNR_Nr(tlbn* lb){//利用线索实现非递归中序**逆序**遍历
    for (tlbn* _lb=LastNode(lb); _lb!=NULL; _lb=getLastNode_LNR(_lb))
        printf("%d ",_lb->data);
}


void LNR(tlbn* lb){
    if(lb->ltag==0)
        LNR(lb->lc);
    else if (lb->lc==NULL)printf("前驱线索:NULL ");
    else printf("前驱线索:%d ",lb->lc->data);
    printf("%d ",lb->data);
    if(lb->rtag==0)
        LNR(lb->rc);
    else if (lb->rc==NULL)printf("后驱线索:NULL ");
    else printf("后继线索:%d ",lb->rc->data);
}
void NLR(tlbn* lb){
    printf("%d ",lb->data);
    if(lb->ltag==0)
        LNR(lb->lc);
    else if (lb->lc==NULL)printf("前驱线索:NULL ");
    else printf("前驱线索:%d ",lb->lc->data);
    if(lb->rtag==0)
        LNR(lb->rc);
    else if (lb->rc==NULL)printf("后驱线索:NULL ");
    else printf("后继线索:%d ",lb->rc->data);
}

int main(){
    tlbn* root = CreateThreadLinkBiTreeRoot(1);
    tlbn* n1 = CreateLeftChild(root, 2);
    CreateRightChild(n1, 5);
    tlbn* n2 = CreateRightChild(root, 3);
    CreateLeftChild(n2, 6);
    //        1
    //    2       3
    //  @    5   6 @
    //     @  @ @ @
    
    // 2 5 1 6 3
    
    //lb-2 pre-null @1 = null
    //lb-5 pre-2    @2 = 2
    //lb-1 pre-5    @3 = 1
    //lb-6 pre-1    @4 = 1
    //lb-3 pre-6    @5 = 3
    
//    CreateThreadLinkBiNode_LNR(root);
//    LNR(root);
    CreateThreadLinkBiNode_NLR(root);
    NLR(root);
    
    
}

```




# 总结

未完待续...


  [1]: https://github.com/Remyuu/DataStructureSourceCode
  [2]: http://remoooo.com/usr/uploads/2022/10/3008545722.png

