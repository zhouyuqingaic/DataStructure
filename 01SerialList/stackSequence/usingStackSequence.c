//
// Created by zhouyuqing on 2023/3/10.
//

#include "stackSequence.h"

typedef struct{
    int data;
}TestStructStackSequence;

void printfTestStructStackSequence(void *data){
    printf("%5d\n",((TestStructStackSequence *)data)->data);
}

void usingStackSequence(){
    StackSequence *stackSequence=NULL;
    Status opResult= init_StackSequence(&stackSequence);
    if(FAIL==opResult){
        printf("初始化链栈失败!\n");
        return;
    }

    void *tempNode=NULL;
    for(int i=0;i<10;i++){
        if(isFull_StackSequence(stackSequence)){
            printf("顺序栈满，入栈失败\n");
        }else{
            printf("顺序栈未满，可以入栈\n");
        }
        tempNode=(TestStructStackSequence *)malloc(sizeof(TestStructStackSequence));
        if(tempNode==NULL){
            printf("创建入栈数据失败");
            return;
        }
        ((TestStructStackSequence *)tempNode)->data=i+100;
        opResult= push_StackSequence(stackSequence,tempNode);
        if(opResult==SUCCESS){
            printf("\n\t");
            printfTestStructStackSequence(tempNode);
            printf("入栈成功\n");
        }
    }

    printf("\n1.----------------------------------------------------\n");

    while(!isEmpty_StackSequence(stackSequence)){
        opResult= pop_StackSequence(stackSequence,&tempNode);
        if(opResult==SUCCESS){
            printfTestStructStackSequence(tempNode);
            printf("数据出栈成功\n");

            //清空出栈元素
            free(tempNode);
            tempNode=NULL;


        }else{
            printf("数据出栈失败\n");
            return;
        }
    }

    printf("\n2.----------------------------------------------------\n");

    opResult= destroy_StackSequence(&stackSequence);
    if(opResult==SUCCESS)
        printf("销毁顺序栈成功!\n");
    else
        printf("销毁顺序栈失败!\n");


}
//
//void main(){
//    usingStackSequence();
//}