//
// Created by zhouyuqing on 2023/3/11.
//

#include "queueByLinkList.h"

//清空队列
Status empty_QueueByLinkList(QueueByLinkList *queueByLinkList){
    if(queueByLinkList==NULL)
        return FAIL;
    //清空链表
    Status opResult= empty_LinkList(queueByLinkList);
    return opResult;
}
//初始化队列
Status init_QueueByLinkList(QueueByLinkList **pQueueByLinkList){
    //初始化链表
    Status opResult= init_LinkList(pQueueByLinkList);
    return opResult;
}
//入队
Status enqueue_QueueByLinkList(QueueByLinkList *queueByLinkList,void *data){
    if(queueByLinkList==NULL)
        return FAIL;
    //元素挂到链表尾部
    Status opResult=insertByPos_LinkList(queueByLinkList,queueByLinkList->amountNodes,data);
    return opResult;
}
//出队
Status dequeue_QueueByLinkList(QueueByLinkList *queueByLinkList,void **result){
    if(queueByLinkList==NULL)
        return FAIL;
    //获取链表头部元素并删除
    Status opResult= deleteByPos_LinkList(queueByLinkList,0,result);
    return opResult;
}
//返回队列大小
Status size_QueueByLinkList(const QueueByLinkList *queueByLinkList,int *size){
    if(queueByLinkList==NULL)
        return FAIL;
    else {
        //返回链表大小
        *size = queueByLinkList->amountNodes;
        return SUCCESS;
    }
}
//判断队空
int isEmpty_QueueByLinkList(const QueueByLinkList *queueByLinkList){
    //判断链表大小是否为0
    if(queueByLinkList->amountNodes==0)
        return 1;
    else
        return 0;
}
//获取队尾元素
Status tail_QueueByLinkList(const QueueByLinkList *queueByLinkList,void *result){
    if(queueByLinkList==NULL)
        return FAIL;
    //获取链表尾节点元素
    Status opResult= getByPos_LinkList(queueByLinkList,queueByLinkList->amountNodes-1,result);
    return opResult;
}
//获取队头元素
Status head_QueueByLinkList(const QueueByLinkList *queueByLinkList,void *result){
    if(queueByLinkList==NULL)
        return FAIL;
    //获取链表头节点元素
    Status opResult=getByPos_LinkList(queueByLinkList,0,result);
    return opResult;
}
//展示队列
Status show_QueueByLinkList(const QueueByLinkList *queueByLinkList,PRINT_DATA printData){
    if(queueByLinkList==NULL)
        return FAIL;
    //展示链表头节点元素
    Status opReuslt= show_LinkList(queueByLinkList,printData);
    return opReuslt;
}
//销毁队列
Status destroy_QueueByLinkList(QueueByLinkList **pLinkList){
    //销毁链表
    Status opResult= destory_LinkList(pLinkList);
    return opResult;
}



