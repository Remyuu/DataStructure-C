//
//  main.c
//  DS13_StringsPatternMatching
//
//  Created by Remoo on 2022/10/18.
//

//Include Brute_Force & KMP use LinkString
//KMP
//公共前后缀的长度要小于字串的长度

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char* ch;
    int length;
    int stringSize;
}seqStr;

seqStr* CreateString(int StringSize);
void ApplyString(seqStr* seqstr,char* str);
int GetLength(seqStr* seqstr);
void Show(seqStr* ss);

int BF_Search(seqStr* text,seqStr* pattern);
int KMP_Search(seqStr* text,seqStr* pattern);


seqStr* CreateString(int StringSize){
    seqStr* s = (seqStr*)malloc(sizeof(seqStr));
    s->ch=(char*)malloc(sizeof(char)*StringSize);
    s->length=0;s->stringSize=StringSize;
    return s;
}
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
int GetLength(seqStr* seqstr){
    return seqstr->length;
}
void Show(seqStr* ss){
    int i;
    for (i=0; i < GetLength(ss); i++)
        printf("%c",ss->ch[i]);
    printf("\n");
};


int BF_Search(seqStr* text,seqStr* pattern){
    int i,j;
    i=0;j=0;
    while(i<GetLength(text)&&j<GetLength(pattern))//驱动指针前进
        if(text->ch[i]==pattern->ch[j]){
            i++;j++;//继续匹配下一个字符
        }else{
            i=i-j+1;j=0;//text+1
        }
    if (j==GetLength(pattern)) {
        return i-GetLength(pattern)+1;//返回位序
    }else{
        return 0;
    }
}

void GetNext(seqStr* pattern,int next[]){
    int j,k;
    j=0;k=-1;next[0]=-1;
    while(j<GetLength(pattern)){
        if(k==-1||pattern->ch[j]==pattern->ch[k]){
            j++;k++;next[j]=k;
        }else
            k=next[k];//当k不在-1且有不匹配的字，则将k打回原点
    }
}

int KMP_Search(seqStr* text,seqStr* pattern){
    int next[GetLength(pattern)],i,j;
    GetNext(pattern,next);
    i=0;j=0;
    while(i<GetLength(text)&&j<GetLength(pattern))
        if(j==-1||text->ch[i]==pattern->ch[j]){
            i++;j++;
        }else{
            j=next[j];
        }
    if(j>=GetLength(pattern))
        return i-GetLength(pattern)+1;
    return 0;
}

int main(){
    int index1,index2;
    seqStr* text,*pattern;
    text = CreateString(10);pattern = CreateString(10);
    ApplyString(text, "1111113");
    ApplyString(pattern, "13");
    Show(text);Show(pattern);
    
    index1 = BF_Search(text, pattern);
    index2 = KMP_Search(text,pattern);
    
    printf("BF result:%d\nKMP result:%d\n",index1,index2);
}

