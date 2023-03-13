//
// Created by zhouyuqing on 2023/3/10.
//

#include "queueSequenceByDynamicArray.h"

typedef struct _TESTSTRUCT_QUEUESEQUENCEBYDYNAMICARRAY{
    int data;
}TestStructQueueSequenceByDynamicArray;

void printTestStructQueueSequenceByDynamicArray(void *data){
    printf("%8d",((TestStructQueueSequenceByDynamicArray *)data)->data);
}

void usingTestStructQueueSequenceByDynamicArray(){
    /*
     * TestStructQueueSequenceByDynamicArray测试&使用案例
     */
    QueueSequenceByDynamicArray *queueSequenceByDynamicArray=NULL;
    Status opResult= init_QueueSequenceByDynamicArray(&queueSequenceByDynamicArray);
    if(opResult==FAIL){
        printf("\n初始化动态数组失败\n");
        return;
    }

    TestStructQueueSequenceByDynamicArray *tempStruct=NULL;
    for(int i=0;i<10;i++){
        tempStruct=(TestStructQueueSequenceByDynamicArray *)malloc(sizeof(TestStructQueueSequenceByDynamicArray));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+800;
        opResult= enqueue_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,tempStruct);
        if(opResult==FAIL){
            printf("\n");
            printTestStructQueueSequenceByDynamicArray(tempStruct);
            printf("入队列失败\n");
            return;
        }
    }

    opResult= show_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,printTestStructQueueSequenceByDynamicArray);
    if(FAIL==opResult)
        printf("展示队列失败!\n");

    printf("\n---------------------------------1-----------------------------------\n");

    void *temp=NULL;
    while(!isEmpty_QueueSequenceByDynamicArray(queueSequenceByDynamicArray)){
        opResult= dequeue_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,&temp);
        if(FAIL==opResult){
            printf("出队列失败\n");
            return;
        }else{
            printf("出队成功!出队元素为:");
            printTestStructQueueSequenceByDynamicArray(temp);
            printf("\n");

            //清空出队元素
            free(temp);
            temp==NULL;
        }
    }


    int size=0;
    opResult= size_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,&size);
    if(SUCCESS==opResult)
        printf("获取队列大小为:%d\n",size);
    else
        printf("获取队列大小失败\n");

    opResult= show_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,printTestStructQueueSequenceByDynamicArray);
    if(FAIL==opResult)
        printf("展示队列失败!\n");

    printf("\n---------------------------------2-----------------------------------\n");

    for(int i=0;i<5;i++){
        tempStruct=(TestStructQueueSequenceByDynamicArray *)malloc(sizeof(TestStructQueueSequenceByDynamicArray));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+1990;
        opResult= enqueue_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,tempStruct);
        if(opResult==FAIL){
            printf("\n");
            printTestStructQueueSequenceByDynamicArray(tempStruct);
            printf("入队列失败\n");
            return;
        }
    }

    opResult= show_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,printTestStructQueueSequenceByDynamicArray);
    if(FAIL==opResult)
        printf("展示队列失败!\n");

    void *head,*tail;
    opResult= head_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,&head);
    if(SUCCESS==opResult) {
        printf("队头元素为:");
        printTestStructQueueSequenceByDynamicArray(head);
        printf("\n");
    }else{
        printf("获取队头元素失败\n");
    }

    opResult= tail_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,&tail);
    if(SUCCESS==opResult) {
        printf("队尾元素为:");
        printTestStructQueueSequenceByDynamicArray(tail);
        printf("\n");
    }else{
        printf("获取队尾元素失败\n");
    }

    opResult= empty_QueueSequeueByDynamicArray(queueSequenceByDynamicArray);
    if(FAIL==opResult)
        printf("清空队列失败!\n");

    opResult= size_QueueSequenceByDynamicArray(queueSequenceByDynamicArray,&size);
    if(SUCCESS==opResult)
        printf("获取队列大小为:%d\n",size);
    else
        printf("获取队列大小失败\n");


    printf("\n---------------------------------3-----------------------------------\n");

    opResult= destroy_QueueSequenceByDynamicArray(&queueSequenceByDynamicArray);
    if(opResult==SUCCESS)
        printf("销毁队列成功");
    else
        printf("销毁队列失败");
}

//int main(){
//    usingTestStructQueueSequenceByDynamicArray();
//}



