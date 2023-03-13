//
// Created by zhouyuqing on 2023/3/7.
//

#include "dynamicArray.h"

//清空动态数组
Status empty_DynamicArray(DynamicArray *dynamicArray){
    if(dynamicArray==NULL)
        return FAIL;
    //清空void*数组指向的堆区对象 ,并将当前数组大小设置为0
    for(int i=0;i<dynamicArray->amountArray;i++){
        free(dynamicArray->pArray[i]);
        dynamicArray->pArray[i]=NULL;
    }
    dynamicArray->amountArray=0;
    return SUCCESS;
}
//初始化capacity大小的动态数组
Status init_DynamicArray(DynamicArray **pDynamicArray,int capacity){
    Status opResult=FAIL;
    if(*pDynamicArray!=NULL){ //传入动态数组非空，清空动态数组
        opResult= empty_DynamicArray(pDynamicArray);
        return opResult;
    }else{ //传入动态数组为空
        //创建并设置动态数组
        DynamicArray *dynamicArray=(DynamicArray *)malloc(sizeof(DynamicArray));
        if(dynamicArray==NULL)
            return FAIL;
        dynamicArray->amountArray=0;
        //创建大小为capcity的void *数组
        dynamicArray->pArray=(void **)malloc(sizeof(void *)*capacity);
        if(dynamicArray->pArray==NULL)
            return FAIL;
        dynamicArray->capacityArray=capacity;
        *pDynamicArray=dynamicArray;
        return SUCCESS;
    }
}
//插入数组,在pos位置上插入data(pos位置从0开始计数)
Status insertByPos_DynamicArray(DynamicArray *dynamicArray,int pos,void *data){
    Status opResult=FAIL;
    if(dynamicArray==NULL || data==NULL)
        return FAIL;
    //pos不在 0~dynamicArray->amountArray 合法范围内
    //注意:若pos为dynamicArray->amountArray,则追加到数组末尾
    if(pos<0 || pos>dynamicArray->amountArray)
        return FAIL;
    //当前数组容量不足容纳data,需要扩容
    if(dynamicArray->amountArray+1>dynamicArray->capacityArray){
        int newCapacity=dynamicArray->capacityArray*2;
        void **tempPArray=(void *)malloc(sizeof(void *)*newCapacity);
        if(tempPArray==NULL)
            return FAIL;
        dynamicArray->capacityArray=newCapacity;
        //原void*数组中的数据 迁移到 *tempPArray数组中
        for(int i=0;i<dynamicArray->amountArray;i++)
            tempPArray[i]=dynamicArray->pArray[i];

        free(dynamicArray->pArray);
        dynamicArray->pArray=NULL;

        dynamicArray->pArray=tempPArray;
    }
    //将 pos~dynamicArray->amountArray-1 范围上的元素后移动一位
    for(int i=dynamicArray->amountArray-1;i>=pos;i--)
        dynamicArray->pArray[i+1]=dynamicArray->pArray[i];
    //将data放到pos位置上
    dynamicArray->pArray[pos]=data;
    //数组大小增加
    dynamicArray->amountArray++;
    return SUCCESS;
}
//添加data到数组末尾
Status append_DynamicArray(DynamicArray *dynamicArray,void *data){
    if(dynamicArray==NULL || data==NULL)
        return FAIL;
    Status opResult=insertByPos_DynamicArray(dynamicArray,dynamicArray->amountArray,data);
    return opResult;
}

//修改数组中pos位置上的元素值
Status setByPos_DynamicArray(DynamicArray *dynamicArray,int pos,void *data){
    if(dynamicArray==NULL || data==NULL)
        return FAIL;
    //pos不在0~dynamicArray->amountArray-1 的合法范围中
    if(pos<0 || pos>=dynamicArray->amountArray)
        return FAIL;

    free(dynamicArray->pArray[pos]);
    dynamicArray->pArray[pos]=NULL;

    dynamicArray->pArray[pos]=data;
    return SUCCESS;
}
//获取数组中pos位置上的元素值
Status getByPos_DynamicArray(const DynamicArray *dynamicArray,int pos,void **result){
    if(dynamicArray==NULL)
        return FAIL;
    //pos不在0~dynamicArray->amountArray-1 的合法范围中
    if(pos<0 || pos>=dynamicArray->amountArray)
        return FAIL;
    *(result)=dynamicArray->pArray[pos];
    return SUCCESS;
}
//展示数组中所有元素
Status show_DynamicArray(const DynamicArray *dynamicArray,PRINT_DATA printData){
    if(dynamicArray==NULL)
        return FAIL;
    printf("\n----------------------------dynamicArray----------------------\n");
    for(int i=0;i<dynamicArray->amountArray;i++) {
        printf("\n|");
        printData(dynamicArray->pArray[i]);
    }
    printf("\n______________________________________________________________\n");
}
//删除数组指定位置的元素
Status removeByPos_DynamicArray(DynamicArray *dynamicArray,int pos,void **result){
    if(dynamicArray==NULL)
        return FAIL;
    //pos不在0~dynamicArray->amountArray-1 的合法范围中
    if(pos<0 || pos>=dynamicArray->amountArray)
        return FAIL;

    *result=dynamicArray->pArray[pos];

    dynamicArray->pArray[pos]=NULL;

    //将pos+1到dynamicArray->amountArray-1位置上的元素前移动一位
    for(int i=pos;i<dynamicArray->amountArray-1;i++)
        dynamicArray->pArray[i]=dynamicArray->pArray[i+1];
    //数组大小-1
    dynamicArray->amountArray--;
    return SUCCESS;
}
//销毁数组
Status destory_DynamicArray(DynamicArray **pDynamicArray){
    if(*pDynamicArray==NULL) //动态数组不存在,直接返回
        return SUCCESS;
    DynamicArray *dynamicArray=*pDynamicArray;
    //清空void*数组
    Status opReuslt=empty_DynamicArray(*pDynamicArray);
    if(FAIL==opReuslt)
        return FAIL;
    //清空pArray
    free(dynamicArray);
    dynamicArray=NULL;
    *pDynamicArray=NULL;
    return SUCCESS;
}
