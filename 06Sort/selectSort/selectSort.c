//
// Created by zhouyuqing on 2023/4/27.
//
#include "selectSort.h"

//直接选择排序
Status directSelectSort(COMPARE_DATA compareData,void **unSortedDatas,
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

    //开始选择排序
    void *tempData=NULL;
    int minIndex;
    for(int i=0;i<unSortedDatasLength;i++){
        //选出从i~unSortedDatasLength-1位置上的元素中的最小值
        minIndex=i;
        for(int j=i+1;j<unSortedDatasLength;j++){
            if(
                1==compareData((*pSortedDatas)[minIndex],(*pSortedDatas)[j])
            ) {
                minIndex = j;
            }
        }
        //将 最小值 与 i位置上的元素交换
        tempData=(*pSortedDatas)[minIndex];
        (*pSortedDatas)[minIndex]=(*pSortedDatas)[i];
        (*pSortedDatas)[i]=tempData;
    }

    return SUCCESS;
}

//调用该函数的前提，已知low到high中的记录的大顶堆，除了堆顶元素low外都符合大顶堆的定义
//对除了除了堆顶元素low外都符合大顶堆的定义的失序堆进行调整，使其符合大顶堆定义
void *shift(COMPARE_DATA compareData,void **sortedDatas,int low,int high){
    int i=low,j=2*i; //j指向i的左子节点
    void *tempData=sortedDatas[i]; //记录失序的堆顶
    //找到失序堆顶元素的位置
    while(j<=high){ //沿着孩子节向下筛选
        //如果i两个孩子，则找出比较大那个孩子节点
        if(
            j<high
            &&
            -1==compareData(sortedDatas[j],sortedDatas[j+1])
        )
            ++j;
        //堆顶元素 比 孩子节点小，将比较大的孩子节点放到父节点位置上
        if( -1==compareData(tempData,sortedDatas[j]) ){
            sortedDatas[i]=sortedDatas[j];
            i=j; //更新父节点 继续往下寻找
            j=2*i; //根据新的父节点更新子节指向
        }else {
            //堆顶元素 比 孩子节点大，孩子的父节点就是堆顶元素的有序位置
            break;
        }
    }
    sortedDatas[i]=tempData; //将失序的堆顶元素放入最终位置
}

//堆选择排序
Status heapSelectSort(COMPARE_DATA compareData,void **unSortedDatas,
                      int unSortedDatasLength,void ***pSortedDatas){
    if(unSortedDatas==NULL || unSortedDatasLength<=0)
        return FAIL;
    //初始化 排序结果 串
    if(*pSortedDatas!=NULL)
        free(*pSortedDatas);
    *pSortedDatas=(void **)malloc(
            sizeof(void *)*(unSortedDatasLength+1)
            );
    if(*pSortedDatas==NULL)
        return FAIL;

    //将原始数据复制到 排序结果串 中
    for(int i=0;i<unSortedDatasLength;i++)
        (*pSortedDatas)[i+1]=unSortedDatas[i];

//    //查看排序数据,测试用
//    int unSortedDatas_Vals[unSortedDatasLength];
//    int sortedDatas_Vals[unSortedDatasLength];
//    for(int i=0;i<unSortedDatasLength;i++){
//        unSortedDatas_Vals[i]=
//                (
//                    (TestElement_SelectSort *)( unSortedDatas[i] )
//                )->val;
//        sortedDatas_Vals[i]=
//                (
//                    (TestElement_SelectSort *)( (*pSortedDatas)[i+1] )
//                )->val;
//    }

    //开始堆排序
    //对无需序列构建堆
    for(int i=unSortedDatasLength/2;i>=1;i--)
        shift(compareData,*pSortedDatas,i,unSortedDatasLength);

    //进行unSortedDatasLength-1次循环完成堆排序
    void *tempData=NULL;
    for(int i=unSortedDatasLength;i>1;i--){
        //堆顶元素出堆，并用堆中最后一个元素填充空缺的堆顶
        tempData=(*pSortedDatas)[1];
        (*pSortedDatas)[1]=(*pSortedDatas)[i];
        (*pSortedDatas)[i]=tempData;
        //堆少了一个元素，且除了堆顶元素，其余都符合大顶堆的定义
        //将大顶堆恢复有序
        shift(compareData,*pSortedDatas,1,i-1);
    }

    //处理有序数组，使其从下标0开始计数
    for(int i=0;i<unSortedDatasLength;i++)
        (*pSortedDatas)[i] = (*pSortedDatas)[i + 1];

    return SUCCESS;
}



