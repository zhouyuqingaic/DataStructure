//
// Created by zhouyuqing on 2023/4/25.
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


#ifndef DATASTRUCTURE_SWIPSORT_H
#define DATASTRUCTURE_SWIPSORT_H

#include<stdio.h>
#include<malloc.h>

typedef int (*COMPARE_DATA)(void *,void *); //比较数据 1:a>b,0:a=b,-1:a<b

//冒泡交换排序
Status bubbleSwipSort(COMPARE_DATA compareData,void **unSortedDatas,
                        int unSortedDatasLength,void ***pSortedDatas);

//快速交换排序
Status quickSwipSort(COMPARE_DATA compareData,void **unSortedDatas,
                      int unSortedDatasLength,void ***pSortedDatas);


#endif //DATASTRUCTURE_SWIPSORT_H

#ifdef __cplusplus
}
#endif