//
// Created by zhouyuqing on 2023/4/25.
//
#include "swipSort.h"

//冒泡交换排序
Status bubbleSwipSort(COMPARE_DATA compareData,void **unSortedDatas,
                      int unSortedDatasLength,void ***pSortedDatas){
    if(unSortedDatas==NULL || unSortedDatasLength<=0)
        return FAIL;

    //初始化 排序结果 串
    if(*pSortedDatas!=NULL)
        free(*pSortedDatas);
    *pSortedDatas=(void **)malloc(sizeof(void *)*unSortedDatasLength);
    if(*pSortedDatas==NULL)
        return FAIL;

    //将原始数据复制到 排序结果串 中
    for(int i=0;i<unSortedDatasLength;i++)
        (*pSortedDatas)[i]=unSortedDatas[i];

    //开始冒泡排序
    void *tempData=NULL; //存储冒泡排序的交换变量
    for(int i=unSortedDatasLength-1;i>=1;--i){
        //完成一趟冒泡, 0~i位置上 的最大元素 冒泡到 i位置
        for(int j=0;j<i;j++){
            if(
                compareData( (*pSortedDatas)[j] , (*pSortedDatas)[j+1] )==1
            ){
                tempData=(*pSortedDatas)[j];
                (*pSortedDatas)[j]=(*pSortedDatas)[j+1];
                (*pSortedDatas)[j+1]=tempData;
            }
        }
    }

    return SUCCESS;
}

//快速排序
void quickSort(COMPARE_DATA compareData,void **sortedDatas,
               int low,int high){

    void *splitData=NULL; //快速排序划分无需数组用的变量
    int i=low,j=high;
    //如果low和high没有相交
    if(low<high){
        splitData=sortedDatas[i];
        while(i<j){
            //从后往前扫描，找到第一个小于splitData的 关键字的位置
            while(
                i<j
                &&
                (
                    compareData(sortedDatas[j],splitData)==1
                    ||
                    compareData(sortedDatas[j],splitData)==0
                )
            )--j;
            //如果i和j没有相交,小于splitData的值 sortedDatas[j] 存在
            if(i<j){
                sortedDatas[i]=sortedDatas[j]; //放在splitData的前面
                i++; //i后移动一位
            }
            //从前往后扫描，找到第一个大于splitData的 关键字的位置
            while(
                i<j
                &&
                compareData(sortedDatas[i],splitData)==-1
            )++i;
            //如果i和j没有相交,大于splitData的值 sortedDatas[i] 存在
            if(i<j){
                sortedDatas[j]=sortedDatas[i]; //放在splitData的后面
                j--; //j前移动一位
            }

        }
        //i==j时,将splitData,划分数据 放到数列中最终位置
        sortedDatas[i]=splitData;
        //对splitData前的部分进行排序
        quickSort(compareData,sortedDatas,low,i-1);
        //对splitData后的部分进行排序
        quickSort(compareData,sortedDatas,i+1,high);
    }
}

//快速交换排序
Status quickSwipSort(COMPARE_DATA compareData,void **unSortedDatas,
                     int unSortedDatasLength,void ***pSortedDatas){
    if(unSortedDatas==NULL || unSortedDatasLength<=0)
        return FAIL;

    //初始化 排序结果 串
    if(*pSortedDatas!=NULL)
        free(*pSortedDatas);
    *pSortedDatas=(void **)malloc(sizeof(void *)*unSortedDatasLength);
    if(*pSortedDatas==NULL)
        return FAIL;

    //将原始数据复制到 排序结果串 中
    for(int i=0;i<unSortedDatasLength;i++)
        (*pSortedDatas)[i]=unSortedDatas[i];

    //开始快速排序
    quickSort(compareData,*pSortedDatas,0,unSortedDatasLength-1);

    return SUCCESS;
}
