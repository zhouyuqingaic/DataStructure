//
// Created by zhouyuqing on 2023/3/9.
//

#include "linkList.h"

// 清空单连表
Status empty_LinkList(LinkList *linkList){
    if(linkList==NULL)
        return FAIL;
    //清空单链表每个节点
    LinkListNode *currentNode=linkList->headNode,*tempNode=NULL;
    while(currentNode!=NULL){
        tempNode=currentNode;
        currentNode=currentNode->next;

        free(tempNode);
        tempNode=NULL;
    }
    //设置链表参数
    linkList->headNode=NULL;
    linkList->amountNodes=0;
    return SUCCESS;
}
// 初始化单链表
Status init_LinkList(LinkList **pLinkList){
    if(*pLinkList==NULL){ //传入链表为空,创建链表,并设置相关属性
        LinkList *linkList=(LinkList *)malloc(sizeof(LinkList));
        if(linkList==NULL)
            return FAIL;
        linkList->amountNodes=0;
        linkList->headNode=NULL;
        //设置单链表
        *pLinkList=linkList;
        return SUCCESS;
    }else{ //传入链表不为空，清空链表
        Status opResult=empty_LinkList(*pLinkList);
        return opResult;
    }
}
//插入单链表pos位置
Status insertByPos_LinkList(LinkList *linkList,int pos,void *data){
    if(linkList==NULL || data==NULL)
        return FAIL;
    //如果pos不在0~linkList->amountNodes 之间,则非法
    //如果pos=linkList->amountNodes则相当于尾插法插入data
    //如果pos=0则相当于头插法插入data
    if(pos<0 || pos>linkList->amountNodes)
        return FAIL;

    //创建data节点
    LinkListNode *dataNode=(LinkListNode *)malloc(sizeof(LinkList));
    dataNode->data=data;
    dataNode->next=NULL;

    //找到pos的前驱动
    LinkListNode *preNode=linkList->headNode;
    LinkListNode *currentNode=linkList->headNode;
    int index=0;
    while(1){
        if(index>=pos)
            break;
        preNode=currentNode;
        currentNode=currentNode->next;
        index++;
    }
    //preNode==currentNode==linkList->headNode
    //pos为0 或 链表中为空(这种情况下pos只能为0)
    if(preNode==currentNode){
        dataNode->next=currentNode;
        linkList->headNode=dataNode;
    }else{
        dataNode->next=currentNode;
        preNode->next=dataNode;
    }
    //链表长度自增
    linkList->amountNodes++;
    return SUCCESS;
}
//删除pos位置上的元素
Status deleteByPos_LinkList(LinkList *linkList,int pos,void **result){
    if(linkList==NULL)
        return FAIL;
    //如果pos不在0~linkList->amountNodes-1 合法范围之间
    if(pos<0 || pos>linkList->amountNodes-1)
        return FAIL;
    LinkListNode *preNode=linkList->headNode;
    LinkListNode *currentNode=linkList->headNode;
    //找到pos元素的前驱
    int index=0;
    while(1){
        if(index>=pos)
            break;
        preNode=currentNode;
        currentNode=currentNode->next;
        index++;
    }
    *result=currentNode->data;
    //preNode==currentNode==linkList->headNode
    //pos为0 或 链表中只有一个元素(这种情况下pos只能为0)
    if(preNode==currentNode){
        linkList->headNode=currentNode->next;
        free(currentNode);
        currentNode=NULL;
    }else{
        preNode->next=currentNode->next;
        free(currentNode);
        currentNode=NULL;
    }

    //链表长度-1
    linkList->amountNodes--;
    return SUCCESS;
}
//获取pos位置上的元素
Status getByPos_LinkList(const LinkList *linksList,int pos,void **result){
    if(linksList==NULL)
        return FAIL;
    //如果pos不在0~linkList->amountNodes-1 合法范围之间
    if(pos<0 || pos>linksList->amountNodes-1)
        return FAIL;
    //找到pos位置上的元素并返回
    LinkListNode *currentNode=linksList->headNode;
    for(int i=0;i<pos;i++)
        currentNode=currentNode->next;
    *result=currentNode->data;
    return SUCCESS;
}
// 展示链表所有元素
Status show_LinkList(const LinkList *linkList,PRINT_DATA printData){
    if(linkList==NULL)
        return FAIL;
    LinkListNode *currentNode=linkList->headNode;
    printf("\n-----------LinkList------------------\n");
    while(currentNode!=NULL){
        printf("\n|");
        printData(currentNode->data);
        currentNode=currentNode->next;
    }
    printf("\n_____________________________________\n");
    return SUCCESS;
}
//销毁链表
Status destory_LinkList(LinkList **pLinkList){
    if(*pLinkList==NULL) //传入链表不存在，直接返回成功
        return SUCCESS;
    //清空链表
    Status opResult=empty_LinkList(*pLinkList);
    if(opResult==FAIL)
        return FAIL;
    //销毁并重置链表
    free(*pLinkList);
    *pLinkList=NULL;
    return SUCCESS;
}
