//
// Created by zhouyuqing on 2023/3/10.
//
#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态

typedef void (*PRINT_DATA)(void *);

#endif

#ifndef DATASTRUCTURE_STACKLINKLIST_H
#define DATASTRUCTURE_STACKLINKLIST_H

#include<stdio.h>
#include<malloc.h>


typedef struct _STACKLINKLISTNODE{
    void *data;
    struct _STACKLINKLISTNODE *next;
}StackLinkListNode; //链栈节点

typedef struct _STACKLINKLIST{
    StackLinkListNode *headNode;
    int stackSize;
}StackLinkList; //链栈

//清空栈
Status empty_StackLinkList(StackLinkList *stackLinkList);
//初始化栈
Status init_StackLinkList(StackLinkList **pStackLinkList);
//数据入栈
Status push_StackLinkList(StackLinkList *stackLinkList,void *data);
//数据出栈
Status pop_StackLinkList(StackLinkList *stackLinkList,void **result);
//获取栈顶元素
Status peek_StackLinkList(const StackLinkList *stackLinkList,void **result);
//获取当前栈大小
Status size_StackLinkList(const StackLinkList *stackLinkList,int *size);
//判断栈是否为空
int isEmpty_StackLinkList(const StackLinkList *stackLinkList);
//判断栈是否满
int isFull_StackLinkList(const StackLinkList *stackLinkList);
//销毁栈
Status destroy_StackLinkList(StackLinkList **pStackLinkList);



#endif //DATASTRUCTURE_STACKLINKLIST_H
