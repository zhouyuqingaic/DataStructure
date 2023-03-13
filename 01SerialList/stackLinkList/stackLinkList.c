//
// Created by zhouyuqing on 2023/3/10.
//

#include "stackLinkList.h"

//清空栈
Status empty_StackLinkList(StackLinkList *stackLinkList){
    if(stackLinkList==NULL)
        return FAIL;
    if(isEmpty_StackLinkList(stackLinkList)) //栈为空，无需清空
        return SUCCESS;
    //清空栈链表中的所有节点
    StackLinkListNode *currentNode=stackLinkList->headNode;
    StackLinkListNode *tempNode=NULL;
    while(currentNode!=NULL){
        tempNode=currentNode;
        currentNode=currentNode->next;

        free(tempNode);
        tempNode=NULL;
    }
    //重置链栈参数
    stackLinkList->headNode=NULL;
    stackLinkList->stackSize=0;
    return SUCCESS;
}
//初始化栈
Status init_StackLinkList(StackLinkList **pStackLinkList){
    if(*pStackLinkList==NULL){
        //连栈不存在则创建链栈,并设置链栈参数
        StackLinkList *stackLinkList=(StackLinkList *)malloc(sizeof(StackLinkList));
        if(stackLinkList==NULL)
            return FAIL;
        stackLinkList->headNode=NULL;
        stackLinkList->stackSize=0;
        *pStackLinkList=stackLinkList;
        return SUCCESS;
    }else{
        //链栈存在则清空链栈
        Status opResult=empty_StackLinkList(*pStackLinkList);
        return opResult;
    }
}
//数据入栈
Status push_StackLinkList(StackLinkList *stackLinkList,void *data){
    if(stackLinkList==NULL)
        return FAIL;
    if(isFull_StackLinkList(stackLinkList)) //栈满则无法入栈
        return FAIL;
    //创建data节点
    StackLinkListNode *dataNode=(StackLinkListNode *)malloc(sizeof(StackLinkListNode));
    if(dataNode==NULL)
        return FAIL;
    dataNode->data=data;
    dataNode->next=NULL;
    //利用头插法插入data节点
    dataNode->next=stackLinkList->headNode;
    stackLinkList->headNode=dataNode;
    stackLinkList->stackSize++;
    return SUCCESS;
}
//数据出栈
Status pop_StackLinkList(StackLinkList *stackLinkList,void **result){
    if(stackLinkList==NULL)
        return FAIL;
    if(isEmpty_StackLinkList(stackLinkList)) //栈空则无法出栈
        return FAIL;
    //获取栈顶节点的数据
    *result=stackLinkList->headNode->data;

    //删除链栈表头节点并更新链栈
    StackLinkListNode *tempLinkListNode=stackLinkList->headNode;
    stackLinkList->headNode=stackLinkList->headNode->next;
    stackLinkList->stackSize--;

    free(tempLinkListNode);
    tempLinkListNode=NULL;

    return SUCCESS;
}
//获取栈顶元素
Status peek_StackLinkList(const StackLinkList *stackLinkList,void **result){
    if(stackLinkList==NULL)
        return FAIL;
    if(isEmpty_StackLinkList(stackLinkList)) //栈空获取失败
        return FAIL;
    //获取栈顶节点数据
    *result=stackLinkList->headNode->data;
    return SUCCESS;
}
//获取当前栈大小
Status size_StackLinkList(const StackLinkList *stackLinkList,int *size){
    if(stackLinkList==NULL)
        return FAIL;
    *size=stackLinkList->stackSize;
    return SUCCESS;
}
//判断栈是否为空
int isEmpty_StackLinkList(const StackLinkList *stackLinkList){
    if(0==stackLinkList->stackSize)
        return 1;
    else
        return 0;
}
//判断栈是否满
int isFull_StackLinkList(const StackLinkList *stackLinkList){
    //没有内存空间用来创建节点时就是栈满
    StackLinkListNode *tempNode=malloc(sizeof(StackLinkListNode));
    if(tempNode==NULL)
        return 1;
    else {
        free(tempNode);
        tempNode=NULL;
        return 0;
    }
}
//销毁栈
Status destroy_StackLinkList(StackLinkList **pStackLinkList){
    if(*pStackLinkList==NULL)
        return SUCCESS;
    //清空链栈
    Status opResult=empty_StackLinkList(*pStackLinkList);
    if(FAIL==opResult)
       return FAIL;
    //删除链栈
    free(*pStackLinkList);
    *pStackLinkList=NULL;
    return SUCCESS;
}


