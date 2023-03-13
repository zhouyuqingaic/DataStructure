//
// Created by zhouyuqing on 2023/3/11.
//

#include "queueByLinkList.h"

typedef struct _TESTSTRUCTQUEUELINKLIST{
    int data;
}TestStructQueueLinkList;

void printTestStructQueueLinkList(void *data){
    printf("%8d",((TestStructQueueLinkList *)data)->data);
}

void usingTestStructQueueLinkList(){
    /*
     * TestStructQueueLinkList测试&使用案例
     */
    QueueByLinkList *queueByLinkList=NULL;
    Status opResult= init_QueueByLinkList(&queueByLinkList);
    if(opResult==FAIL){
        printf("\n初始化动态数组失败\n");
        return;
    }

    TestStructQueueLinkList *tempStruct=NULL;
    for(int i=0;i<10;i++){
        tempStruct=(TestStructQueueLinkList *)malloc(sizeof(TestStructQueueLinkList));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+800;
        opResult= enqueue_QueueByLinkList(queueByLinkList,tempStruct);
        if(opResult==FAIL){
            printf("\n");
            printTestStructQueueLinkList(tempStruct);
            printf("入队列失败\n");
            return;
        }
    }


    opResult=show_QueueByLinkList(queueByLinkList,printTestStructQueueLinkList);
    if(FAIL==opResult)
        printf("展示队列失败!\n");

    printf("\n---------------------------------1-----------------------------------\n");

    void *temp=NULL;
    while(!isEmpty_QueueByLinkList(queueByLinkList)){
        opResult= dequeue_QueueByLinkList(queueByLinkList,&temp);

        if(FAIL==opResult){
            printf("出队列失败\n");
            return;
        }else{
            printf("出队成功!出队元素为:");
            printTestStructQueueLinkList(temp);
            printf("\n");

            //清空出队元素
            free(temp);
            temp==NULL;
        }
    }

    int size=0;
    opResult= size_QueueByLinkList(queueByLinkList,&size);
    if(SUCCESS==opResult)
        printf("获取队列大小为:%d\n",size);
    else
        printf("获取队列大小失败\n");

    opResult= show_QueueByLinkList(queueByLinkList,printTestStructQueueLinkList);
    if(FAIL==opResult)
        printf("展示队列失败!\n");

    printf("\n---------------------------------2-----------------------------------\n");


    for(int i=0;i<5;i++){
        tempStruct=(TestStructQueueLinkList *)malloc(sizeof(TestStructQueueLinkList));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+1990;
        opResult= enqueue_QueueByLinkList(queueByLinkList,tempStruct);
        if(opResult==FAIL){
            printf("\n");
            printTestStructQueueLinkList(tempStruct);
            printf("入队列失败\n");
            return;
        }
    }

    opResult= show_QueueByLinkList(queueByLinkList,printTestStructQueueLinkList);
    if(FAIL==opResult)
        printf("展示队列失败!\n");

    void *head,*tail;
    opResult= head_QueueByLinkList(queueByLinkList,&head);
    if(SUCCESS==opResult) {
        printf("队头元素为:");
        printTestStructQueueLinkList(head);
        printf("\n");
    }else{
        printf("获取队头元素失败\n");
    }

    opResult= tail_QueueByLinkList(queueByLinkList,&tail);
    if(SUCCESS==opResult) {
        printf("队尾元素为:");
        printTestStructQueueLinkList(tail);
        printf("\n");
    }else{
        printf("获取队尾元素失败\n");
    }

    opResult= empty_QueueByLinkList(queueByLinkList);
    if(FAIL==opResult)
        printf("清空队列失败!\n");

    opResult= size_QueueByLinkList(queueByLinkList,&size);
    if(SUCCESS==opResult)
        printf("获取队列大小为:%d\n",size);
    else
        printf("获取队列大小失败\n");


    printf("\n---------------------------------3-----------------------------------\n");

    opResult= destroy_QueueByLinkList(&queueByLinkList);
    if(opResult==SUCCESS)
        printf("销毁队列成功");
    else
        printf("销毁队列失败");
}

//int main(){
//    usingTestStructQueueLinkList();
//}

