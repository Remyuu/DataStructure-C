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


