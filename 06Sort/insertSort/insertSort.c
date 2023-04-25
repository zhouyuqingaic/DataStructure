//
// Created by zhouyuqing on 2023/4/22.
//

#include "insertSort.h"

//直接插入排序
Status directInsertSort(COMPARE_DATA compareData,void **unSortedDatas,
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

    //开始直接插入排序
    void *tempData=NULL;
    int j;
    //对剩余unSortedDatasLength-1个元素进行 直接插入排序
    for(int i=1;i<unSortedDatasLength;i++){

        //待插入关键字存储在tempData中
        tempData=(*pSortedDatas)[i];
        //从待插入关键字位置开始 向前扫描，
        // 将所有大于待插入关键字的有序部分元素后移一位
        // 直到遇到 小于等于 待插关键字的元素，
        //     或
        //         者j变成-1(待插关键字小于有序部分所有元素的情况)
        j=i-1;
        while(
            j>=0
                &&
            compareData( (*pSortedDatas)[j], tempData)==1
        ){
            (*pSortedDatas)[j+1]=(*pSortedDatas)[j];
            j--;
        }
        //找到插入位置，插入到有序部分 小于等于 待插入关键字的 元素的后面
        (*pSortedDatas)[j+1]=tempData;
    }

    return SUCCESS;
}

//折半插入排序
Status blusetInsertSort(COMPARE_DATA compareData,void **unSortedDatas,
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

    //开始折半插入排序
    void *tempData=NULL;
    int compareResult,low,high,mid;
    //对剩余 unSortedDatasLength-1个元素进行 折半插入排序
    for(int i=1;i<unSortedDatasLength;i++){
        //待插元素存储在tempData中
        tempData=(*pSortedDatas)[i];
        //运用折半查找法
        //寻找待插入元素 在有序序列部分 的 插入位置
        low=0;
        high=i-1;
        while(low<=high){
            mid=(low+high)/2;
            compareResult=compareData(
                    (*pSortedDatas)[mid],
                    tempData
                );
            if(-1==compareResult){
                //mid元素 小于 待插元素，在高半区查找
                low=mid+1;
            }else{
                //mid元素 小于等于 待插元素，在低半区查找
                high=mid-1;
            }
        }
        //将hight+1到i-1位置上的元素全部后移一位
        for(int j=i-1;j>=high+1;j--)
            (*pSortedDatas)[j+1]=(*pSortedDatas)[j];
        //将tempData插入high+1的位置
        (*pSortedDatas)[high+1]=tempData;
    }

    return SUCCESS;
}


//希尔排序(缩小增量排序)
Status shellInsertSort(COMPARE_DATA compareData,void **unSortedDatas,
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

    //每次增量为原来增量的 1/3
    int skips[unSortedDatasLength];
    int skipsLength=0;
    int currentSkip=unSortedDatasLength/2+1;
    skips[skipsLength++]=currentSkip;
    while(currentSkip>1){
        skips[skipsLength++]=currentSkip;
        currentSkip=currentSkip/3+1;
    }


    //开始缩小增量排序
    void *tempData=NULL;
    int k=0;
    //按照增量序列的增量进行插入排序
    for(int i=0;i<skipsLength;i++){
        //从0开始,以增量 skips[i] 进行一趟插入排序
        currentSkip=skips[i];
        for(int j=currentSkip;j<unSortedDatasLength;j++){
            //待插入关键字存储在tempData中
            tempData=(*pSortedDatas)[j];
            k=j-currentSkip;
            //插入j前面跨度为skips[i]的有序子列中
            while(
                k>=0
                    &&
                compareData((*pSortedDatas)[k],tempData)==1
            ){
                (*pSortedDatas)[k+currentSkip]=(*pSortedDatas)[k];
                k-=currentSkip;
            }
            //找到插入位置 将待插入关键字放到插入位置
            (*pSortedDatas)[k+currentSkip]=tempData;
        }
    }


    return SUCCESS;
}










