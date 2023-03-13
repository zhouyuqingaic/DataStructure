//
// Created by zhouyuqing on 2023/3/9.
//

#include "linkList.h"

typedef struct _TESTSTRUCT{
    int data;
}TestStruct;

void printTestStructLinkList(void *data){
    printf("%8d",((TestStruct *)data)->data);
}

void usingLinkList(){
    /*
     * LinkList测试&使用案例
     */
    LinkList *linkList=NULL;
    Status opResult= init_LinkList(&linkList);
    if(opResult==FAIL){
        printf("\n初始化链表失败\n");
        return;
    }


    TestStruct *tempStruct=NULL;
    for(int i=0;i<10;i++) {
        tempStruct = (TestStruct *) malloc(sizeof(TestStruct));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+100;
        opResult= insertByPos_LinkList(linkList,0,tempStruct);
        if(FAIL==opResult){
            printf("\n");
            printf("插入%d位置数据 ",0);
            printTestStructLinkList(tempStruct);
            printf(" 失败\n");
            return;
        }
    }

    opResult=show_LinkList(linkList,printTestStructLinkList);
    if(FAIL==opResult)
        printf("展示链表失败!\n");

    printf("\n1-------------------------------------------\n");

    for(int i=0;i<10;i++){
        tempStruct = (TestStruct *) malloc(sizeof(TestStruct));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+200;
        opResult= insertByPos_LinkList(linkList,i,tempStruct);
        if(FAIL==opResult){
            printf("插入数据到%4d位置 ",i);
            printTestStructLinkList(tempStruct);
            printf(" 失败\n");
            return;
        }
    }

    opResult=show_LinkList(linkList,printTestStructLinkList);
    if(FAIL==opResult)
        printf("展示链表失败!\n");

    printf("\n2-------------------------------------------\n");

    void *temp=NULL;
    for(int i=5;i<15;i++){
        opResult= getByPos_LinkList(linkList,i,&temp);
        if(FAIL==opResult){
            printf("获取%4d位置的数据失败\n",i);
            return;
        }else{
            printf("\n|");
            printTestStructLinkList(temp);
        }
    }

    printf("\n3-------------------------------------------\n");

    for(int i=5;i<15;i++){
        opResult= deleteByPos_LinkList(linkList,i,&temp);
        if(FAIL==opResult){
            printf("\n|删除%4d位置的数据失败\n",i);
        }else{
            printf("\n|删除%4d位置的",i);
            printTestStructLinkList(temp);
            printf(" 成功!\n");
        }
    }

    opResult=show_LinkList(linkList,printTestStructLinkList);
    if(FAIL==opResult)
        printf("展示链表失败!\n");

    printf("\n4--------------------------------------------------\n");

    //清空动态数组
    opResult=destory_LinkList(linkList);
    if(SUCCESS==opResult)
        printf("销毁链表成功");
}

//int main(){
//    usingLinkList();
//    return 0;
//}