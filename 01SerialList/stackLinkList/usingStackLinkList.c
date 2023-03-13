//
// Created by zhouyuqing on 2023/3/10.
//
#include "stackLinkList.h"

typedef struct{
    int data;
}TestStructStackLinkList;

void printfTestStructStackLinkList(void *data){
    printf("%5d\n",((TestStructStackLinkList *)data)->data);
}

void usingStackLinkList(){
    /*
     * StackLinkList测试&使用 案例
     */
    StackLinkList *stackLinkList=NULL;
    Status opReuslt= init_StackLinkList(&stackLinkList);
    if(FAIL==opReuslt){
        printf("初始化链栈失败!\n");
        return;
    }

    void *tempNode=NULL;
    for(int i=0;i<10;i++){
        if(isFull_StackLinkList(stackLinkList)){
            printf("链栈满，入栈失败\n");
        }else{
            printf("链栈未满，可以入栈\n");
        }
        tempNode=(TestStructStackLinkList *)malloc(sizeof(TestStructStackLinkList));
        if(tempNode==NULL){
            printf("创建入栈数据失败");
            return;
        }
        ((TestStructStackLinkList *)tempNode)->data=i+100;
        opReuslt= push_StackLinkList(stackLinkList,tempNode);
        if(opReuslt==SUCCESS){
            printf("\n\t");
            printfTestStructStackLinkList(tempNode);
            printf("入栈成功\n");
        }
    }

    printf("\n1.----------------------------------------------------\n");

    while(!isEmpty_StackLinkList(stackLinkList)){
        opReuslt= pop_StackLinkList(stackLinkList,&tempNode);
        if(opReuslt==SUCCESS){
            printfTestStructStackLinkList(tempNode);
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

    opReuslt= destroy_StackLinkList(&stackLinkList);
    if(opReuslt==SUCCESS)
        printf("销毁链栈成功!\n");
    else
        printf("销毁链栈失败!\n");


}

//void main(){
//    usingStackLinkList();
//}