//
// Created by zhouyuqing on 2023/3/18.
//

#include "binaryTree.h"

void func(void ***tempList,int a,int b){
    if(*tempList!=NULL)
        free(*tempList);

    void **temps=(void **)malloc( sizeof(void *)*2 );

    temps[0]=(int *)malloc(sizeof(int));
    *((int *)temps[0])=a;

    temps[1]=(int *)malloc(sizeof(int));
    *((int *)temps[1])=b;

    if(*tempList!=NULL)
        free(*tempList);
    *tempList=temps;

}

void main(){

    int **iList=NULL;

    func(&iList,1997,1998);


    printf("%d\n",*(iList[0]));
    printf("%d\n",*(iList[1]));

}
