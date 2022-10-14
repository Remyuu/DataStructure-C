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

typedef struct slink{
    int data;
    int cur;
}StaticLink[SIZE];

void CreateList(StaticLink space){
    int i;
    for (i=0; i<SIZE-1; i++) {
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
    if(i<1)return 0;
    j=0;k=head;
    while(k!=0&&j<i){
        j++;k=space[k].cur;
    }
    if(k==0)return 0;
    return space[k].data;
}

int Insert(StaticLink space,int head,int i,int value){
    int j,k,m;
    if(i<1)return 0;
    k=head;j=0;
    while(k!=0&&j<i-1){
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
    if(i<0)return 0;
    k=head;j=0;
    while(k!=0&&j<i-1){
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
    printf("DS06_staticList \n");
}
