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

