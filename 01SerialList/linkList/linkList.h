//
// Created by zhouyuqing on 2023/3/9.
//

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态

typedef void (*PRINT_DATA)(void *);

#endif

#ifndef DATASTRUCTURE_LINKLIST_H
#define DATASTRUCTURE_LINKLIST_H

#include<stdio.h>
#include<malloc.h>

typedef struct _LINKLISTNODE{
    void *data; //链表节点的数据部分
    struct _LINKLISTNODE *next;
}LinkListNode; //链表节点

typedef struct _LINKLIST{
    LinkListNode *headNode; //链表头节点指针
    int amountNodes; //节点总数
}LinkList;

// 清空单连表
Status empty_LinkList(LinkList *linkList);
// 初始化单链表
Status init_LinkList(LinkList **pLinkList);
//插入单链表pos位置
Status insertByPos_LinkList(LinkList *linkList,int pos,void *data);
//删除pos位置上的元素
Status deleteByPos_LinkList(LinkList *linkList,int pos,void **result);
//获取pos位置上的元素
Status getByPos_LinkList(const LinkList *linksList,int pos,void **result);
// 展示链表所有元素
Status show_LinkList(const LinkList *linkList,PRINT_DATA printData);
//销毁链表
Status destory_LinkList(LinkList **linkList);

#endif //DATASTRUCTURE_LINKLIST_H
