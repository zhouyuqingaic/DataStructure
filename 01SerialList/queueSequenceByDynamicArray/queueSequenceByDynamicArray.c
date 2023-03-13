//
// Created by zhouyuqing on 2023/3/10.
//

#include"queueSequenceByDynamicArray.h"

//清空队列
Status empty_QueueSequeueByDynamicArray(QueueSequenceByDynamicArray *queueSequence){
    if(queueSequence==NULL)
        return FAIL;
    //清空动态数组
    Status opResult= empty_DynamicArray(queueSequence);
    return opResult;
}
//初始化队列
Status init_QueueSequenceByDynamicArray(QueueSequenceByDynamicArray **pQueueSequence){
    //初始化动态数组
    Status opResult= init_DynamicArray(pQueueSequence,QUEUE_SEQUENCE_BY_DYNAMIC_ARRAY_CAPCITY);
    return opResult;
}
//入队
Status enqueue_QueueSequenceByDynamicArray(QueueSequenceByDynamicArray *queueSequence,void *data){
    if(queueSequence==NULL)
        return FAIL;
    //将新元素插到动态数组尾部
    Status opResult=insertByPos_DynamicArray(queueSequence,queueSequence->amountArray,data);
    return opResult;
}
//出队
Status dequeue_QueueSequenceByDynamicArray(QueueSequenceByDynamicArray *queueSequence,void **result){
    if(queueSequence==NULL)
        return FAIL;
    //获取并删除动态数组头部的元素
    Status opResult= removeByPos_DynamicArray(queueSequence,0,result);
    return opResult;
}
//返回队列大小
Status size_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence,int *size){
    if(queueSequence==NULL)
        return FAIL;
    else {
        *size=queueSequence->amountArray;
        return SUCCESS;
    }
}
//判断队空
int isEmpty_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence){
    if(queueSequence->amountArray==0)
        return 1;
    else
        return 0;
}
//获取队尾元素
Status tail_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence,void *result){
    if(queueSequence==NULL)
        return FAIL;
    //获取动态数组的尾部节点
    Status opResult= getByPos_DynamicArray(queueSequence,queueSequence->amountArray-1,result);
    return opResult;
}
//获取队头元素
Status head_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence,void *result){
    if(queueSequence==NULL)
        return FAIL;
    //获取动态数组的头部节点
    Status opResult=getByPos_DynamicArray(queueSequence,0,result);
    return opResult;
}
//展示队列
Status show_QueueSequenceByDynamicArray(const QueueSequenceByDynamicArray *queueSequence,PRINT_DATA printData){
    if(queueSequence==NULL)
        return FAIL;
    //展示动态数组
    Status opResult=show_DynamicArray(queueSequence,printData);
    return opResult;
}
//销毁队列
Status destroy_QueueSequenceByDynamicArray(QueueSequenceByDynamicArray **pQueueSequence){
    //销毁动态数组
    Status opResult=destory_DynamicArray(pQueueSequence);
    return opResult;
}
