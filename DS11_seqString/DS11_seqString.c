//
//  main.c
//  DS11_seqString
//
//  Created by Remoo on 2022/10/12.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char* ch;//串的起始地址
    int length;//串的长度，不代表seqStr串所占内存空间
    int stringSize;//当前串所分配的内存空间(未乘sizeof(char))
}seqStr;

seqStr* CreateString(int StringSize);
void ApplyString(seqStr* seqstr,char* str);
int GetLength(seqStr* seqstr);
void Copy(seqStr* ss1,seqStr* ss2);
void Append(seqStr* ss1,seqStr* ss2);
int IsEqual(seqStr* ss1,seqStr* ss2);
void Change(seqStr* ss,int index,char c);
void Insert(seqStr* ss1,int index,seqStr* ss2);
void Delete(seqStr* ss,int start,int end);
void Show(seqStr* ss);

seqStr* CreateString(int StringSize){
    seqStr* s = (seqStr*)malloc(sizeof(seqStr));
    s->ch=(char*)malloc(sizeof(char)*StringSize);
    s->length=0;
    s->stringSize=StringSize;
    return s;
}

//char[]转seqStr
void ApplyString(seqStr* seqstr,char* str){
    int i=0;
    while(str[i]!='\0')i++;//计算str的长度
    if(seqstr->stringSize < i){//如果串不够长，就重新分配内存空间
        seqstr->ch=(char*)realloc(seqstr->ch, (i*sizeof(char)));
        seqstr->stringSize=i;
    }
    seqstr->length=i;
    for (i=0; i < seqstr->length; i++) {//一个一个赋值
        seqstr->ch[i]=str[i];
    }
}

//求串的长度
int GetLength(seqStr* seqstr){
    return seqstr->length;
}

//将ss1的串复制给ss2
void Copy(seqStr* ss1,seqStr* ss2){
    int i;
    if(ss2->stringSize < GetLength(ss1)){
        ss2->ch=(char*)realloc(ss2->ch, GetLength(ss1)*sizeof(char));
        ss2->stringSize=GetLength(ss1);
    }
    ss2->length=GetLength(ss1);
    for (i=0; i < ss2->length; i++) {
        ss2->ch[i]=ss1->ch[i];
    }
}

//两个seqStr拼接，只改变前者的值
void Append(seqStr* ss1,seqStr* ss2){
    int i;
    if(ss1->stringSize < ss2->length){
        ss1->ch=(char*)realloc(ss1->ch, ss2->length*sizeof(char));
        ss1->stringSize=ss2->length;
    }
    for (i = 0; i < ss2->length; i++) {
        ss1->ch[i+ss1->length]=ss2->ch[i];
    }
    ss1->length=ss1->length + ss2->length;
}

//判断两个seqStr对象值是否相等
int IsEqual(seqStr* ss1,seqStr* ss2){
    int i;
    if(GetLength(ss1)!=GetLength(ss2))
        return 0;
    for (i=0; i < GetLength(ss1); i++) {
        if(ss1->ch[i]!=ss2->ch[i])
            return 0;
    }
    return 1;
}

//获得字串
seqStr* GetSubString(seqStr* seqstr,int start,int end){
    int delta;
    //合理性判断
        //i  0 - n 闭
        //j  i - n 闭
    if(start < 0||start>seqstr->length||start>end||end>seqstr->length){//若输入不合法，则原封不动返回。
        //return (seqStr*)malloc(0);
        return seqstr;
    }
    seqStr* string;
    string = CreateString(end-start);
    
    string->length=end-start;
    for (delta=start; start < end; start++) {
        string->ch[start-delta]=seqstr->ch[start];
        //printf("(%d,%c)\t",i-start,string->ch[i-start]);
    }
    return string;
}

void Change(seqStr* ss,int index,char c){
    //合法性修正
    index = index < 0?0:index;
    index = index>GetLength(ss)?GetLength(ss):index;
    ss->ch[index]=c;
}

void Insert(seqStr* ss1,int index,seqStr* ss2){
    int i;
    //合法性修正
    index = index < 0?0:index;
    index = index>GetLength(ss1)?GetLength(ss1):index;
    if(ss1->stringSize<(GetLength(ss1)+GetLength(ss2)))//扩容
        ss1->ch = (char*)realloc(ss1->ch, sizeof(char)*(GetLength(ss1)+GetLength(ss2)));
    ss1->length=GetLength(ss1)+GetLength(ss2);
    ss1->stringSize=ss1->length;
    //将ss1中的后半部分后移
    for(i=0;i < GetLength(ss1)-index-1;i++){
        ss1->ch[i+GetLength(ss2)+index]=ss1->ch[i+index];
    }
    //插入、覆盖
    for (i=0; i < GetLength(ss2); i++) {
        ss1->ch[i+index]=ss2->ch[i];
    }
    //改变长度
    ss1->stringSize=ss1->length;
}

void Delete(seqStr* ss,int start,int end){
    int index;
    if(start < 0||start>ss->length||start>end||end>ss->length)
        return;
    for (index=0; index!=GetLength(ss)-end; index++){
        //printf("(%d,%c)->",start+index,ss->ch[start+index]);
        //Show(ss);
        ss->ch[start+index]=ss->ch[end+index];
        //printf("(%d,%c)\t",start+index,ss->ch[start+index]);
        //Show(ss);
    }
    ss->length=GetLength(ss)-(end-start);
}

void Show(seqStr* ss){
    int i;
    for (i=0; i < GetLength(ss); i++) {
        printf("%c",ss->ch[i]);
    }
    printf("\n");
}

int main(){
    seqStr* ss1 = CreateString(10);
    ApplyString(ss1,"abcdefg");
    ss1 = GetSubString(ss1, 0,7);
    printf("\nLength:%d\n",GetLength(ss1));
    Show(ss1);
    Delete(ss1, 1, 3);
    Show(ss1);
    seqStr* ss2 = CreateString(10);
    Copy(ss1, ss2);
    Show(ss1);
    Show(ss2);
    Insert(ss1, 2, ss2);
    Show(ss1);
}
