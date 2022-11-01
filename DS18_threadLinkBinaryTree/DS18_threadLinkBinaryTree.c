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
