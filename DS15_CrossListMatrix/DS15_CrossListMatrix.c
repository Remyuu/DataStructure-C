//
//  main.c
//  DS15_CrossListMatrix
//
//  Created by Remoo on 2022/10/19.
//

#include <stdio.h>
#include <stdlib.h>


int fun(int n){
    if(n!=1)return n*fun(n-1);
    return 1;
}
int main(){
    int a = fun(3);
    printf("%d\n",a);
}
