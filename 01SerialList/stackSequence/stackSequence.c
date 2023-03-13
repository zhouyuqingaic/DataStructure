//
// Created by zhouyuqing on 2023/3/9.
//
#include "stackSequence.h"

//清空栈
Status empty_StackSequence(StackSequence *stackSequence){
    if(stackSequence==NULL)
        return FAIL;
    if(stackSequence->top==-1) //链栈长度为0
        return SUCCESS;
    //栈非空，清空栈
    memset(stackSequence->data,0,sizeof(void *)*MAXSIZE_STACKLINKLIST);
    stackSequence->top=-1;
    return SUCCESS;
}
//初始化栈
Status init_StackSequence(StackSequence **pStackSequence){
    if(*pStackSequence==NULL){
        //栈不存在，创建栈
        StackSequence *stackSequence=(StackSequence *)malloc(sizeof(StackSequence));
        stackSequence->top=-1;
        //清空栈存储空间
        memset(stackSequence->data,0,sizeof(void *)*MAXSIZE_STACKLINKLIST);
        *pStackSequence=stackSequence;
        return SUCCESS;
    }else{
        //栈存在，则清空栈
        Status opResult= empty_StackSequence(*pStackSequence);
        return opResult;
    }

}
//数据入栈
Status push_StackSequence(StackSequence *stackSequence,void *data){
    if(stackSequence==NULL)
        return FAIL;
    if(isFull_StackSequence(stackSequence)) //栈满则失败
        return FAIL;

    //data入栈
    stackSequence->top++;
    stackSequence->data[stackSequence->top]=data;
    return SUCCESS;
}
//数据出栈
Status pop_StackSequence(StackSequence *stackSequence,void **result){
    if(stackSequence==NULL)
        return FAIL;
    if(isEmpty_StackSequence(stackSequence)) //栈为空则失败
        return FAIL;

    //获取栈顶元素
    *result=stackSequence->data[stackSequence->top];
    //栈顶元素出栈
    stackSequence->data[stackSequence->top]=NULL;
    stackSequence->top--;
    return SUCCESS;
}
//获取栈顶元素
Status peek_StackSequence(const StackSequence *stackSequence,void **result){
    if(stackSequence==NULL)
        return FAIL;
    if(isEmpty_StackSequence(stackSequence)) //栈为空则失败
        return FAIL;

    //获取栈顶元素
    *result=stackSequence->data[stackSequence->top];
    return SUCCESS;
}
//获取当前栈大小
Status size_StackSequence(const StackSequence *stackSequence,int *size){
    if(stackSequence==NULL)
        return FAIL;
    *size=stackSequence->top+1;
    return SUCCESS;
}
//判断栈是否为空
int isEmpty_StackSequence(const StackSequence *stackSequence){
    if(stackSequence->top==-1)
        return 1;
    else
        return 0;
}
//判断栈是否满
int isFull_StackSequence(const StackSequence *stackSequence){
    if(stackSequence->top==MAXSIZE_STACKLINKLIST-1)
        return 1;
    else
        return 0;
}
//销毁栈
Status destroy_StackSequence(StackSequence **pStackSequence){
    if(*pStackSequence==NULL) //栈不存在，直接返回
        return SUCCESS;
    //栈存在，清空栈
    Status opReulst= empty_StackSequence(*pStackSequence);
    if(FAIL==opReulst)
        return FAIL;
    //删除栈
    free(*pStackSequence);
    *pStackSequence=NULL;
    return SUCCESS;
}
