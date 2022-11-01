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

void LNR(sbt* seqbt,int index);//中序遍历 左中右
void LNR(sbt* seqbt,int index);//先序遍历 中左右
void LNR(sbt* seqbt,int index);//后序遍历 左右中

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

void LNR(sbt* seqbt,int index){
    if(index<=seqbt->length){
        LNR(seqbt,index*2);
        printf("%d ",seqbt->data[index]);
        LNR(seqbt,index*2+1);
    }
}

void NLR(sbt* seqbt,int index){
    if(index<=seqbt->length){
        printf("%d ",seqbt->data[index]);
        NLR(seqbt,index*2);
        NLR(seqbt,index*2+1);
    }
}

void LRN(sbt* seqbt,int index){
    if(index<=seqbt->length){
        LRN(seqbt,index*2);
        LRN(seqbt,index*2+1);
        printf("%d ",seqbt->data[index]);
    }
}

int main(){
    sbt* bt= CreateSeqBiTree(10);
    //setBiTree(bt);
    setBiTreeAuto(bt);
    printf("\n左孩子：%d\n右孩子：%d\n父亲：%d\n",
           getLeftChild(bt, 2),
           getRightChild(bt, 2),
           getParent(bt, 2));
    LDR(bt, 1);
}


