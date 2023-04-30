//
// Created by zhouyuqing on 2023/4/30.
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

#ifndef DATASTRUCTURE_MERGESORT_H
#define DATASTRUCTURE_MERGESORT_H



#include<stdio.h>
#include<malloc.h>

#ifndef COMPARE_DATA_FUNC
#define COMPARE_DATA_FUNC
typedef int (*COMPARE_DATA)(void *,void *); //比较数据 1:a>b,0:a=b,-1:a<b
#endif

//归并排序
Status mergeSort(COMPARE_DATA compareData,void **unSortedDatas,
                 int unSortedDatasLength,void ***pSortedDatas);

#endif //DATASTRUCTURE_MERGESORT_H

#ifdef __cplusplus
}
#endif