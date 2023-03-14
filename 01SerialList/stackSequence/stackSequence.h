//
// Created by zhouyuqing on 2023/3/9.
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


#ifndef DATASTRUCTURE_SEQUENCESTACK_H
#define DATASTRUCTURE_SEQUENCESTACK_H

#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define MAXSIZE_STACKLINKLIST 1024


typedef struct _STACKSEQUENCE {
    void *data[MAXSIZE_STACKLINKLIST]; //栈存储空间
    int top; //栈顶指针
} StackSequence; //顺序栈

//清空栈
Status empty_StackSequence(StackSequence *stackSequence);

//初始化栈
Status init_StackSequence(StackSequence **pStackSequence);

//数据入栈
Status push_StackSequence(StackSequence *stackSequence, void *data);

//数据出栈
Status pop_StackSequence(StackSequence *stackSequence, void **result);

//获取栈顶元素
Status peek_StackSequence(const StackSequence *stackSequence, void **result);

//获取当前栈大小
Status size_StackSequence(const StackSequence *stackSequence, int *size);

//判断栈是否为空
int isEmpty_StackSequence(const StackSequence *stackSequence);

//判断栈是否满
int isFull_StackSequence(const StackSequence *stackSequence);

//销毁栈
Status destroy_StackSequence(StackSequence **pStackSequence);


#endif //DATASTRUCTURE_SEQUENCESTACK_H

#ifdef __cplusplus
}
#endif