//
//  main.c
//  DS19_BalancedBinaryTree
//
//  Created by Remoo on 2022/11/3.
//

/*
 Balance Binary Tree 平衡二叉树，简称AVL树。
 **树上任意节点左子树和右子树的高度不超过1**
 
 平衡因子 = 左子树高 - 右子树高
 则一棵平衡的树平衡因子只可能是：-1 0 1
 
 让一棵二叉排序树保持平衡，即可使查找效率达到　O(log_2(n))
 
 当插入节点使树不平衡后，只需要调整最小不平衡子树即可
 
 调整最小不平衡子树（教科书方法）：
    1. LL       root->lc=root_lc->rc;root_lc->rc=root;root_parent->lc(rc)=root->lc;
    2. RR
    3. RL       右旋加左旋
    4. LR       左旋加右旋
 总结：先找最小不平衡子树，然后左孩子右旋、右孩子左旋。
 
 最大深度:O(log_2(n)) 平均查找长度、时间复杂度:O(log_2(n))
 */


#include <stdio.h>
#include <stdlib.h>


typedef struct AVLNode{
    int key;//数据域
    int balance;//平衡因子
    struct AVLNode* lc,*rc;
}avln;

int main(){
    
}
