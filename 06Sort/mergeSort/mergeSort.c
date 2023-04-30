//
// Created by zhouyuqing on 2023/4/30.
//
#include "mergeSort.h"

//合并有序数组
//low~mid 为有序组
//mid+1~high 为有序组
//将两个有序组合并为一个新的有序组
void merge_MergeSort(COMPARE_DATA compareData,void **sortedDatas,
          int low,int mid,int high){
    //存储 low~high 的有序数组零时数组
    int tempListLength=high-low+1;
    void **tempList[tempListLength];

    //将两个有序数组合并为一个
    int indexA=low; //有序数组A的索引
    int indexB=mid+1; //有序数组B的索引

    int compareResult;
    int indexTempList=0;
    while(indexA<=mid && indexB<=high){
        //将两个有序数组中较小的元素加入有序组中
        compareResult=compareData(
                sortedDatas[indexA],
                sortedDatas[indexB]
            );
        if(-1==compareResult){
            tempList[indexTempList++]=sortedDatas[indexA++];
        }else{
            tempList[indexTempList++]=sortedDatas[indexB++];
        }
    }
    //将剩余元素加入有序组中
    while(indexA<=mid){
        tempList[indexTempList++]=sortedDatas[indexA++];
    }
    while(indexB<=high){
        tempList[indexTempList++]=sortedDatas[indexB++];
    }

    //利用零时数组 更新 原有序数组(tempList是从0开始计数的)
    for(int i=low;i<=high;i++)
        sortedDatas[i]=tempList[i-low];
}

//归并
int mSort_mergeSort(COMPARE_DATA compareData,void **sortedDatas,
                    int low,int high){
    int mid;
    if(low<high){
        mid=(low+high)/2;
        //对数组的low~mid进行归并
        mSort_mergeSort(compareData,sortedDatas,low,mid);
        //对数组的mid+1~high进行归并
        mSort_mergeSort(compareData,sortedDatas,mid+1,high);
        //将low~mid的有序数组和 mid+1~high的有序数组合并
        merge_MergeSort(compareData,sortedDatas,low,mid,high);
    }
}

//归并排序
Status mergeSort(COMPARE_DATA compareData,void **unSortedDatas,
                 int unSortedDatasLength,void ***pSortedDatas){
    if(unSortedDatas==NULL || unSortedDatasLength<=0)
        return FAIL;
    //初始化 排序结果串
    if(*pSortedDatas!=NULL)
        free(*pSortedDatas);
    *pSortedDatas=(void **)malloc(
            sizeof(void *)*unSortedDatasLength
            );
    if(*pSortedDatas==NULL)
        return FAIL;

    //将原始无序数据 复制到 排序结果串中
    for(int i=0;i<unSortedDatasLength;i++)
        (*pSortedDatas)[i]=unSortedDatas[i];

    //归并排序
    //对 0 ~ unSortedDatasLength-1  位置上的元素进行归并排序
    mSort_mergeSort(compareData,*pSortedDatas,
                    0,unSortedDatasLength-1);

    return SUCCESS;
}