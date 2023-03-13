//
// Created by zhouyuqing on 2023/3/7.
//

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0

typedef int Status; //函数执行状态

typedef void (*PRINT_DATA)(void *);

#endif


#ifndef DATASTRUCTURE_DYNAMICARRAY_H
#define DATASTRUCTURE_DYNAMICARRAY_H

#include<stdio.h>
#include<malloc.h>

typedef struct _DYNAMIC_ARRAY{
    void **pArray; //指向在堆区间创建的void *类型数组的指针
    int capacityArray; //数组容量
    int amountArray; //数组当前大小
}DynamicArray; //动态数组结构体


//清空capacity大小的动态数组
Status empty_DynamicArray(DynamicArray *dynamicArray);
//初始化动态数组
Status init_DynamicArray(DynamicArray **pDynamicArray,int capacity);
//插入数组,在pos位置上插入data(pos位置从0开始计数)
Status insertByPos_DynamicArray(DynamicArray *dynamicArray,int pos,void *data);
//添加data到数组末尾
Status append_DynamicArray(DynamicArray *dynamicArray,void *data);
//修改数组中pos位置上的元素值
Status setByPos_DynamicArray(DynamicArray *dynamicArray,int pos,void *data);
//获取数组中pos位置上的元素值
Status getByPos_DynamicArray(const DynamicArray *dynamicArray,int pos,void **result);
//展示数组中所有元素
Status show_DynamicArray(const DynamicArray *dynamicArray,PRINT_DATA printData);
//删除数组指定位置的元素
Status removeByPos_DynamicArray(DynamicArray *dynamicArray,int pos,void **result);
//销毁数组
Status destory_DynamicArray(DynamicArray **pDynamicArray);

#endif //DATASTRUCTURE_DYNAMICARRAY_H
