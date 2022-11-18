//
//  main.c
//  DS19_BinarySearchTree
//
//  Created by Remoo on 2022/11/4.
//

#include <stdio.h>
#include <stdlib.h>


typedef struct BSTNode{
    int value;
    struct BSTNode* lc,*rc;
}bstn;

//****链队列数据结构：****
typedef struct LinkQueueNode{
    bstn* value;
    struct LinkQueueNode* next;
}lqnode;
typedef struct LinkQueue{
    lqnode* front;
    lqnode* rear;
}lqueue;
lqueue* CreateQueue(void);
int IsEmpty(lqueue* lq);
bstn* GetFrontValue(lqueue* lq);
void In(lqueue* lq,bstn* value);
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
bstn* GetFrontValue(lqueue* lq){
    if(IsEmpty(lq))return 0;
    else return lq->front->next->value;
}
void In(lqueue* lq,bstn* value){
    lqnode* p = (lqnode*)malloc(sizeof(lqueue));
    p->value=value;p->next=NULL;
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
bstn* CreateBST(int str[],int num);

bstn* BST_Search(bstn* T,int value);//非递归查找
bstn* BSTSearch(bstn* T,int value);//递归查找
int BST_Insert(bstn** pt,int k);

void LNR(bstn* T);//中序遍历
void LevelOrder(bstn* T);//层序遍历

bstn* getParent(bstn* T,int value);//获得父节点

void getNextNode_LNR(bstn* root, bstn* T);
bstn* getNext(bstn* root, bstn* T);//传进来一整棵树，找T的中序后继

void Delete(bstn* root,bstn* node);//删除某一个值的节点





bstn* CreateBST(int str[],int num){
    bstn* T=NULL;
    for (int i=0; i<num; i++)
        BST_Insert(&T, str[i]);
    return T;
}

//非递归查找
bstn* BST_Search(bstn* T,int value){
    while(T!=NULL&&value!=T->value)//树空或者等于根节点值
        if(value<T->value)T=T->lc;
            else T=T->rc;
    return T;
}

//递归查找
bstn* BSTSearch(bstn* T,int value){
    if(T==NULL)
        return NULL;//树空，查找不了了
    if(value==T->value)
        return T;
    else if(value<T->value)
        return BSTSearch(T->lc, value);
    else
        return BSTSearch(T->rc, value);
}

//在二叉排序树插入关键字为k的新结点（递归实现）
int BST_Insert(bstn** pt,int k){
    if ((*pt)==NULL){//原树为空，新插入的结点为根结点
        (*pt)=(bstn*)malloc(sizeof(bstn)) ;
        (*pt)->value=k;
        (*pt)->lc=(*pt)->rc=NULL;
        //printf("%d ",(*pt)->value);
        return 1;//返回1，插入成功
    }
    else if (k == (*pt)->value)//树中存在相同关键字的结点，插入失败
        return 0;
    else if (k < (*pt)->value)//插入到T的左子树
        return BST_Insert(&((*pt)->lc),k);
    else //插入到T的右子树
        return BST_Insert(&((*pt)->rc),k);
}

void LNR(bstn* T){
    if(T==NULL)return;
    LNR(T->lc);
    printf("%d ",T->value);
    LNR(T->rc);
}

void LevelOrder(bstn* T){
    lqueue* Q = CreateQueue();
    bstn* p;
    In(Q,T);
    while(!IsEmpty(Q)){
        p = GetFrontValue(Q);
        printf("%d ",p->value);//访问出队节点
        Out(Q);//队头出
        if(p->lc!=NULL)
            In(Q,p->lc);
        if(p->rc!=NULL)
            In(Q,p->rc);
    }
    printf("\n");
}


bstn* getParent(bstn* T,int value){
    bstn* temp=NULL;
    while(T!=NULL&&value!=T->value){//树空或者等于根节点值
        temp=T;
        if(value<T->value)T=T->lc;
        else T=T->rc;
    }
    return temp;
}

bstn* temp=NULL;
bstn* result=NULL;
int flag=0;
void getNextNode_LNR(bstn* root, bstn* T){//传进来一整棵树，找T的中序后继
    if(root!=NULL){
        getNextNode_LNR(root->lc,T);
        if(temp==T)
            flag=1;
        temp=root;
        if(flag==1){
            result=root;
            flag=0;
        }
        getNextNode_LNR(root->rc,T);
    }
}
bstn* getNext(bstn* root, bstn* T){
    temp=NULL;result=NULL;flag=0;
    getNextNode_LNR(root, T);
    return result;
}

/*
 二叉树的删除有三种情况：
 1. 待删除节点是叶子节点 直接删除即可
 2. 待删除节点只有左或右子树 删了要接上后面的
    1-只有左
    2-只有右
 3. 待删除节点既有左子树也有右子树
 */
void Delete(bstn* root,bstn* node){
    //先找到需要删除的节点
    bstn* parent = getParent(root, node->value);
    if(node==NULL)return;//找不到需要删除的东西
    //第一种情况
    if(node->lc==NULL&&node->rc==NULL){//待删除节点是叶子节点
        if(parent->value > node->value) parent->lc=NULL;
        else parent->rc=NULL;
        free(node);
    }//第二种情况
    else if(node->lc!=NULL&node->rc==NULL){//待删除节点只有左孩子
        if(parent->value > node->value) parent->lc=node->lc;//父亲的左孩子
        else parent->rc=node->lc;
        free(node);
    }
    else if(node->lc==NULL&node->rc!=NULL){//待删除节点只有右孩子
        if(parent->value > node->value) parent->lc=node->rc;//父亲的左孩子
        else parent->rc=node->rc;
        free(node);
    }//第三种情况
    else if(node->lc!=NULL&node->rc!=NULL){//待删除节点既有左子树也有右子树
        int next_value=getNext(root,node)->value;
        Delete(root, getNext(root,node));
        node->value=next_value;//把待删除的节点直接覆盖
    }
}


int main(){
    int str1[] = {50,66,60,26,21,30,70,68};
    int str2[] = {26,21,30,50,60,66,68,70};
    int str3[] = {19,13,30,11, 8,26,66,21,60,70,63,65};
    bstn* T1 = CreateBST(str1, 8);
    bstn* T2 = CreateBST(str2, 8);
    bstn* T3 = CreateBST(str3, 12);
    //LNR(T);
    
    bstn* root = BST_Search(T1, 66);
    bstn* parent = getParent(T1, 66);
    printf("%d(%p)的父亲是%d(%p)\n",root->value,root,parent->value,parent);
    LevelOrder(T1);
    LevelOrder(T2);
    LevelOrder(T3);
    
    printf("\n%d的中序后继是%d\n",BST_Search(T3, 30)->value,getNext(T3,BST_Search(T3, 30))->value);
    LevelOrder(T3);
    Delete(T3, BST_Search(T3, 66));
    LevelOrder(T3);
}
