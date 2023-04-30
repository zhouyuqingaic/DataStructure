//
// Created by zhouyuqing on 2023/4/27.
//

#ifdef __cplusplus
extern "C"{
#endif


#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态


typedef void (*PRINT_DATA)(void *); //打印数据

#endif


#ifndef DATASTRUCTURE_SELECTSORT_H
#define DATASTRUCTURE_SELECTSORT_H

#include<stdio.h>
#include<malloc.h>

//typedef struct{
//    int val;
//}TestElement_SelectSort;

typedef int (*COMPARE_DATA)(void *,void *); //比较数据 1:a>b,0:a=b,-1:a<b

//直接选择排序
Status directSelectSort(COMPARE_DATA compareData,void **unSortedDatas,
                        int unSortedDatasLength,void ***pSortedDatas);
//堆选择排序
Status heapSelectSort(COMPARE_DATA compareData,void **unSortedDatas,
                        int unSortedDatasLength,void ***pSortedDatas);


//堆排序

#endif //DATASTRUCTURE_SELECTSORT_H


#ifdef __cplusplus
}
#endif