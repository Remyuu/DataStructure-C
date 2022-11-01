//
//  main.c
//  SortingAlgorithm
//
//  Created by Remoo on 2022/10/21.
//

/*
 算法指标：
    1. 稳定性 关键字相同元素经排序后相对顺序
    2. 时间、空间复杂度
 
 排序算法分为：
    1. 内部排序 数据内存中 关注时间、空间复杂度
    2. 外部排序 数据量太大，分批放入内存 关于使磁盘读写次数更少
 
 排序算法代码目录：
    1. 插入算法
    2. 希尔排序
    3. 冒泡排序
    4. 快速排序
    5. 简单选择排序
    6. 堆排序
    7. 归并排序
    8. 基数排序
 
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Show(int A[],int n);
int* getRandom(int SAMPLENUM);
//插入排序
void InsertSort(int A[],int n);
//希尔排序
void ShellSort(int A[],int n);
//冒泡排序
void BubbleSort(int A[],int n);
//快速排序
void QuickSort(int A[],int n);
void QuickSortRecursion(int A[],int low,int high);
int partition(int A[],int low,int high);
//简单选择排序
void SelectSort(int A[],int n);
//堆排序
void HeapSort(int A[],int len);
void CreateMaxHeap(int A[],int len);
void HeadAdjust(int A[],int k,int len);
//堆排序带哨兵
void HeapSortWithSentry(int As[],int len);
void CreateMaxHeapWithSentry(int As[],int len);
void HeadAdjustWithSentry(int As[],int k,int len);
//归并排序
void MergeSort(int A[],int len);
void DivideAndMerge(int A[],int B[],int low,int high);
void Merge(int A[],int B[],int low,int mid,int high);
//基数排序
void RadixSort(int A[],int len,int maxradix);
int getNum(int data,int index);




/*
 1. 插入排序(InsertSort)
 稳定的
 算法思路
    每次将一个待排序的记录按关键字大小插入到前面排好的子序列。
 空间复杂度：
    O（1）
 时间复杂度：
    最好：O（n）
    最坏：O（n^2）
    平均：O（n^2）
 折半插入排序需要注意稳定性。
 直接插入可用于顺序表与链表。
 */
void InsertSort(int A[],int n){//n个数据元素
    int i,j,temp;
    for (i=1; i<n; i++) //i从1开始选择，默认索引0元素已排好序
        if(A[i]<A[i-1]){//判断待插入的元素左边大小
            temp=A[i];//暂存待插入元素
            for (j=i; j>0&&A[j-1]>temp; j--)
                A[j]=A[j-1];
            A[j]=temp;//复制插入位置
        }
}

/*
 2. 希尔排序(ShellSort)
 不稳定
 算法思路
    隔step个划分字表分别直接插入排序，缩小step，重复，直到step-1。
 空间复杂度：
    O（1）
 时间复杂度：
    最坏：O（n^2）
    平均：O（n^1.3）
 基于顺序表。
 */
void ShellSort(int A[],int n){
    int step;//步长
    int temp=0;//临时数据
    int i,j;
    for(step=n/2;step>=1;step/=2)//步长变化
        for(i=step;i<n;i++){//为什么i=step，因为插入排序原理就是假设第一个已经排好了，
            temp = A[i];
            for(j=i-step;j>=0 && A[j]>temp;j-=step)
                A[j + step] = A[j];
            A[j + step] = temp;
        }
}

/*
 3. 冒泡排序(BubbleSort)
 稳定
 空间复杂度：
    O（1）
 时间复杂度：
    最好：O（n）
    最坏：O（n^2）
    平均：O（n^2）
 可以用于顺序表、链表。
 */
void BubbleSort(int A[],int n){
    int i,j,temp,IsFinish;
    for (i=0; i<n-1; i++){
        IsFinish = 0;
        for (j=0; j<n-i-1; j++)
            if(A[j] > A[j+1]){
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                IsFinish = 1;//当一轮冒泡都没有交换，则排序完成
            }
        if (!IsFinish)return;
    }
}

/*
 4. 快速排序(QuickSort)
 算法思路
    通过枢轴元素pivot不断划分。涉及递归。
 空间复杂度：
    O（递归层数）
    最好：O（log2n）
    最坏：O（n）
 时间复杂度：
    O（n*递归层数）
    最好：O（nlog2n）
    最坏：O（n^2）
 */
void QuickSort(int A[],int n){
    QuickSortRecursion(A, 0, n-1);
}
void QuickSortRecursion(int A[],int low,int high){
    if(low<high){
        int pivotpos=partition(A, low, high);
        QuickSortRecursion(A, low, pivotpos-1);
        QuickSortRecursion(A, pivotpos+1, high);
    }
}
int partition(int A[],int low,int high){
    int pivot=A[low];//将第一个元素作为枢纽
    while(low<high){
        while(low<high && A[high]>=pivot) high--;
        A[low]=A[high];
        while(low<high && A[low]<=pivot) low++;
        A[high]=A[low];
    }
    A[low]=pivot;
    return low;
}

/*
 5. 简单选择排序(SelectSort)
 不稳定
 算法思路
    每一趟在待排序序列选最大或最小元素加入有序子序列。
 空间复杂度：
    O（1）
 时间复杂度：
    O（n^2）

 */
void SelectSort(int A[],int n){
    int i,min,j,temp;
    for (i=0; i<n-1; i++) {
        min=i;//min是子序列开头
        for (j=i+1; j<n; j++)
            if(A[j]<A[min])min=j;
        if (min!=i) {
            temp = A[i];
            A[i]=A[min];
            A[min]=temp;
        }
    }
}



/*
 6. 堆排序(HeapSort)
 不稳定
 算法思路
     大根堆排序
     (从零开始)
     左孩子:2i+1 右孩子:2i+2
     父节点:int((i-1)/2) 所在层数:int(log_2(n+1))+1=int(log_2(n+2))
     (从1开始)
     左孩子:2i 右孩子:2i+1
     父节点:i/2 所在层数:int(log_2(n))+1=int(log_2(n+1))
 空间复杂度：
    O(1)
 时间复杂度：
    O(n)+O(n·log_2(n))=O(n·log_2(n))

 */
void CreateMaxHeap(int A[],int len){
    int i;
    for (i=len/2-1; i>=0; i--)
        HeadAdjust(A,i,len);
}
//调整以k为根的子树的堆为大根堆
void HeadAdjust(int A[],int k,int len){
    int i,temp;
    temp=A[k];//当前主要调整的节点的值
    for( i=2*k+1 ; i<len ; i=i*2+1 ){//2k+1左孩子
        if( i+1<len && A[i]<A[i+1])
            i++;
        if( temp>=A[i] )break;
        else{
            A[k]=A[i];
            k=i;
        }
    }
    A[k]=temp;
}
void HeapSort(int A[],int len){
    int i,temp;
    CreateMaxHeap(A, len);
    for (i=len-1;i>=0;i--) {
        temp=A[0];
        A[0]=A[i];
        A[i]=temp;
        HeadAdjust(A, 0, i-1);
    }
}

//大根堆排序带哨兵
void CreateMaxHeapWithSentry(int As[],int len){
    int i;
    for (i=len/2; i>0; i--)//从len/2到最前面都是非终端节点
        HeadAdjustWithSentry(As,i,len);
    As[0]=0;
}
//调整以k为根的子树的堆为大根堆
void HeadAdjustWithSentry(int As[],int k,int len){
    int i;
    As[0]=As[k];//存下当前子树的根节点，用于交换。
    for( i=2*k ; i<=len ; i*=2 ){//i=2k,指向当前节点的左孩子
        if (i+1<=len&&As[i]<As[i+1])
            //如果右孩子的值更大，就i++，指向右孩子。i+1<=len，保证是有右孩子
            i++;
        if(As[0]>=As[i])break;//大孩子都没爹大，直接跳出for
        else{//As[i]这个孩子比爹大
            As[k]=As[i];//爹被孩子As[i]占了
            k=i;//k这个节点下移，向下筛查
        }
    }
    As[k]=As[0];
}
//带哨兵大根堆排序
void HeapSortWithSentry(int As[],int len){
    int i,temp;
    CreateMaxHeapWithSentry(As, len);//建立初始的带哨兵大根堆
    for (i=len;i>1;i--) {
        temp=As[1];
        As[1]=As[i];
        As[i]=temp;
        HeadAdjustWithSentry(As, 1, i-1);
    }
    As[0]=0;
}


/*
 7. 归并排序(MergeSort)
 稳定
 算法思路
    把两个或多个已经有序的序列合并到一个。
    m路归并，需对比m-1次关键字，一般2路。
    看作归并树。
 空间复杂度：
    O(n)
    #递归所占空间复杂度为O(log_2(n)),
     但O(log_2(n))+O(n)=O(n)。
 时间复杂度：
    O(n·log_2(n))

 */

void MergeSort(int A[],int len){
    int* B=(int*)malloc(len*sizeof(int));
    DivideAndMerge(A, B, 0, len-1);
    free(B);
}
void DivideAndMerge(int A[],int B[],int low,int high){
    //一直拆分到只有一个元素，即拆到low=high不满足继续拆分的条件，递归终止。
    if(low<high){
        int mid = (high+low)/2;
        DivideAndMerge(A, B, low, mid);
        DivideAndMerge(A, B, mid+1, high);
        Merge(A, B, low, mid, high);
    }
}
void Merge(int A[],int B[],int low,int mid,int high){
    //A[]:k指向low
    //B[]:i指向low，j指向mid+1；B是辅助数组
    int i,j,k;
    for (k=low; k<=high; k++)
        B[k]=A[k];//A[low-high]复制到B相同位置
    k=low;
    i=low;j=mid+1;
    for (; i<=mid&&j<=high; k++) {
        if(B[i]<=B[j])//当两个元素相等，优先使用左边的元素（稳定性）
            A[k]=B[i++];
        else
            A[k]=B[j++];
    }
    while(i<=mid) A[k++]=B[i++];
    while(j<=high)A[k++]=B[j++];
}

/*
 8. 基数排序 RadixSort
 稳定
 算法思路
    用空队列按照数字位数依次进队出队排序。
    初始化：设置0-9空队列（看具体）
    分配：依次按权重（位数）入队
    收集：从高位往低位出列
    重复上述三个步骤。
    不基于“比较”的算法。一般基于链式结构。
 
 */

//链队列数据结构
typedef struct LinkQueueNode{
    int data;
    struct LinkQueueNode* next;
}lqnode;
typedef struct LinkQueue{
    lqnode* front;
    lqnode* rear;
}lqueue;
lqueue* CreateQueue(void){//初始化链队列
    lqueue* lq = (lqueue*)malloc(sizeof(lqueue));
    lq->front=lq->rear=(lqnode*)malloc(sizeof(lqnode));
    lq->front->next=NULL;
    return lq;
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

void RadixSort(int A[],int len,int maxradix){
    lqueue* dataQ=CreateQueue();
    lqueue* Q[10];
    int i,k;
    //将数组转换成链式队列
    for (i=0; i<len; i++) In(dataQ,A[i]);
    //初始化：创建0-9共十个队列
    for (i=0; i<10; i++) Q[i]=CreateQueue();
    for (i=0; i<maxradix; i++) {
        while (!IsEmpty(dataQ)) {//分配：收集数据，分类好
            In(Q[getNum(GetFrontValue(dataQ), i)],GetFrontValue(dataQ));
            Out(dataQ);
        }
        //收集：放进dataQ
        for (k=0; k<=9; k++)
            while(!IsEmpty(Q[k])){
                In(dataQ,GetFrontValue(Q[k]));
                Out(Q[k]);
            }
    }
    for (i=0; i<len; i++) {
        A[i]=GetFrontValue(dataQ);
        Out(dataQ);
    }
}
int getNum(int data,int index){
    for(int i=1;i<index;i++)
        data/=10;
    return data%10;
}


int main() {
    clock_t start_t, end_t;double total_t;
    int SAMPLENUM = 1e3;
    int* sample;
    
    printf("📣程序启动\n");
    
    sample=getRandom(SAMPLENUM);
    printf("🕐开始插入排序...");
    start_t = clock();
    InsertSort(sample,SAMPLENUM);
    end_t = clock();
    printf("✅完成产生\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("📣CPU 占用的总时间：%f s\n\n", total_t );
    free(sample);
    
    
    sample=getRandom(SAMPLENUM);
    printf("🕐开始希尔排序...");
    start_t = clock();
    ShellSort(sample,SAMPLENUM);
    end_t = clock();
    printf("✅完成产生\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("📣CPU 占用的总时间：%f s\n\n", total_t );
    free(sample);
    
    
    sample=getRandom(SAMPLENUM);
    printf("🕐开始冒泡排序...");
    start_t = clock();
    BubbleSort(sample,SAMPLENUM);
    end_t = clock();
    printf("✅完成产生\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("📣CPU 占用的总时间：%f s\n\n", total_t );
    free(sample);
    
    
    sample=getRandom(SAMPLENUM);
    printf("🕐开始快速排序...");
    start_t = clock();
    QuickSort(sample,SAMPLENUM);
    end_t = clock();
    printf("✅完成产生\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("📣CPU 占用的总时间：%f s\n\n", total_t );
    free(sample);
    
    
    sample=getRandom(SAMPLENUM);
    printf("🕐开始简单选择排序...");
    start_t = clock();
    SelectSort(sample,SAMPLENUM);
    end_t = clock();
    printf("✅完成产生\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("📣CPU 占用的总时间：%f s\n\n", total_t );
    free(sample);
    
    
    sample=getRandom(SAMPLENUM);
    printf("🕐开始堆排序...");
    start_t = clock();
    HeapSort(sample,SAMPLENUM);
    end_t = clock();
    printf("✅完成产生\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("📣CPU 占用的总时间：%f s\n\n", total_t );
    free(sample);
    
    
    sample=getRandom(SAMPLENUM);
    printf("🕐开始归并排序...");
    start_t = clock();
    MergeSort(sample,SAMPLENUM);
    end_t = clock();
    printf("✅完成产生\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("📣CPU 占用的总时间：%f s\n\n", total_t );
    free(sample);
    
    
    sample=getRandom(SAMPLENUM);
    printf("🕐开始基数排序...");
    start_t = clock();
    RadixSort(sample,SAMPLENUM,8);
    end_t = clock();
    printf("✅完成产生\n");
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("📣CPU 占用的总时间：%f s\n\n", total_t );

}

void Show(int A[],int n){
    for (int i = 0; i<n; i++)
        printf("%-9d",A[i]);
    printf("\n");
}

int* getRandom(int SAMPLENUM){
    int* sample=(int*)malloc(SAMPLENUM*sizeof(int));
    for (int count=0; count < SAMPLENUM; count++)
        sample[count]=rand()%SAMPLENUM;
    return sample;
}
