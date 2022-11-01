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
