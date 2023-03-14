//
// Created by zhouyuqing on 2023/3/11.
//

#ifdef __cplusplus
extern "C"{
#endif


#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态

typedef void (*PRINT_DATA)(void *);

#endif

#ifndef DATASTRUCTURE_QUEUEBYLINKLIST_H
#define DATASTRUCTURE_QUEUEBYLINKLIST_H

#include "../linkList/linkList.h"

typedef LinkList QueueByLinkList; //利用链表实现队列

//清空队列
Status empty_QueueByLinkList(QueueByLinkList *queueByLinkList);

//初始化队列
Status init_QueueByLinkList(QueueByLinkList **pQueueByLinkList);

//入队
Status enqueue_QueueByLinkList(QueueByLinkList *queueByLinkList, void *data);

//出队
Status dequeue_QueueByLinkList(QueueByLinkList *queueByLinkList, void **result);

//返回队列大小
Status size_QueueByLinkList(const QueueByLinkList *queueSequence, int *size);

//判断队空
int isEmpty_QueueByLinkList(const QueueByLinkList *queueSequence);

//获取队尾元素
Status tail_QueueByLinkList(const QueueByLinkList *queueSequence, void *result);

//获取队头元素
Status head_QueueByLinkList(const QueueByLinkList *queueSequence, void *result);

//展示队列
Status show_QueueByLinkList(const QueueByLinkList *queueSequence, PRINT_DATA printData);

//销毁队列
Status destroy_QueueByLinkList(QueueByLinkList **pQueueSequence);


#endif //DATASTRUCTURE_QUEUEBYLINKLIST_H


#ifdef __cplusplus
}
#endif