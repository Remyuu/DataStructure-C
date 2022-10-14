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

typedef struct sqlist
{
    int *data;
    int length;
    int listsize;
}sqnode;//表头

void initlist(sqnode *L);
int getlen(sqnode *L);
int getelem(sqnode *L,int i, int *e);
void list(sqnode *L);
int insert(sqnode *L,int i,int x);
int SeqListErase(sqnode* sl, int pos);

int main(void)
{
    printf("DS01_seqList \n");
    sqnode sq_list;
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
void initlist(sqnode *L)
{
    L->data=(int *)malloc(sizeof(int)*INITSIZE);/* 申请存储空间*/
    L->length=0;              /* 初始长度为0 */
    L->listsize=INITSIZE;     /* 容量为初始量 */
}

/* 2. 求表长操作 */
int getlen(sqnode *L)
{return(L->length);}

/* 3. 取元素操作 */
int getelem(sqnode *L,int i, int *e)
{
    if(i<1||i>L->length) return 0;
    *e = L->data[i-1];
    return 1;
}

/* 4.输出操作(输出顺序表L的各数据元素值) */
void list(sqnode *L)
{
    int i;
    for(i=0;i<L->length;i++)
    printf("%5d ",L->data[i]);
    printf("\n");
}
/* 5. 插入操作(在顺序表L中的第i个位序上插入一个值为x的数据元素) */
int insert(sqnode *L,int i,int x)
{
    int j;
    if(i<1||i>L->length+1) return 0;  // 参数i不合理,返回0
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

int SeqListErase(sqnode* sl, int pos){
    if(pos > sl->length)return 0;
    for (int i = pos; i < sl->length; i++){
        sl->data[i - 1] = sl->data[i];
    }
    sl->length--;
    return 1;
}
