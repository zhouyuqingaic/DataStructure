//
// Created by zhouyuqing on 2023/3/10.
//

#ifdef __cplusplus
extern "C"{
#endif

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态

typedef void(*PRINT_DATA)(void *);

#endif

#ifndef DATASTRUCTURE_QUEUESEQUENCE_H
#define DATASTRUCTURE_QUEUESEQUENCE_H

#include "../dynamicArray/dynamicArray.h"

#define QUEUE_SEQUENCE_BY_DYNAMIC_ARRAY_CAPCITY 100

typedef DynamicArray QueueSequenceByDynamicArray; //利用动态数组实现队列

//清空队列
Status empty_QueueSequeueByDynamicArray(QueueSequenceByDynamicArray *queueSequence);

//初始化队列
Status init_QueueSequenceByDynamicArray(QueueSequenceByDynamicArray **queueSequence);

//入队
Status enqueue_QueueSequenceByDynamicArray(QueueSequenceByDynamicArray *queueSequence, void *data);

//出队
Status dequeue_QueueSequenceByDynamicArray(QueueSequenceByDynamicArray *queueSequence, void **result);

//返回队列大小
Status size_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence, int *size);

//判断队空
int isEmpty_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence);

//获取队尾元素
Status tail_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence, void *result);

//获取队头元素
Status head_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence, void *result);

//展示队列
Status show_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence, PRINT_DATA printData);

//销毁队列
Status destroy_QueueSequenceByDynamicArray(QueueSequenceByDynamicArray **pQueueSequence);

#endif //DATASTRUCTURE_QUEUESEQUENCE_H

#ifdef __cplusplus
}
#endif