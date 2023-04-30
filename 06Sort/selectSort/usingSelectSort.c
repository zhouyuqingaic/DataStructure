//
// Created by zhouyuqing on 2023/4/27.
//

#include "selectSort.h"

typedef struct{
    int val;
}TestElement_SelectSort;

//打印数据
void print_data_selectSort(void *data){
    printf("%d ",
           ((TestElement_SelectSort *)data)->val);
}

//比较数据a与数据b的打下
int compare_data_selectSort(void *a,void *b){
    TestElement_SelectSort *ta=(TestElement_SelectSort *)a;
    TestElement_SelectSort *tb=(TestElement_SelectSort *)b;

    if(ta->val > tb->val)
        return 1;
    else if(ta->val == tb->val)
        return 0;
    else
        return -1;
}

void testSelectSort(
        Status (*sort_Func)(COMPARE_DATA,void **,int,void ***),
        TestElement_SelectSort **unSortedDatas_0,
        TestElement_SelectSort **unSortedDatas_1,
        TestElement_SelectSort **unSortedDatas_2,
        TestElement_SelectSort **unSortedDatas_3){

    //选择排序测试程序
    Status opResult=FAIL;
    int unSortedDatasLength=0;

    //对无需序列0进行排序
    TestElement_SelectSort **sortedDatas_0_selectSort=NULL;
    unSortedDatasLength=0;
    opResult=sort_Func(
        compare_data_selectSort,
        (void **)unSortedDatas_0,
        unSortedDatasLength,
        (void ***)&sortedDatas_0_selectSort
    );
    printf("\n无序序列为\n");
    for(int i=0;i<unSortedDatasLength;i++)
        print_data_selectSort(unSortedDatas_0[i]);
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_selectSort(sortedDatas_0_selectSort[i]);
        }
        free(sortedDatas_0_selectSort);
    }

    printf("\n---------------------------------0---------------------------------\n");

    //对无需序列1进行排序
    TestElement_SelectSort **sortedDatas_1_selectSort=NULL;
    unSortedDatasLength=1;
    opResult=sort_Func(
            compare_data_selectSort,
            (void **)unSortedDatas_1,
            unSortedDatasLength,
            (void ***)&sortedDatas_1_selectSort
    );
    printf("\n无序序列为\n");
    for(int i=0;i<unSortedDatasLength;i++)
        print_data_selectSort(unSortedDatas_1[i]);
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_selectSort(sortedDatas_1_selectSort[i]);
        }
        free(sortedDatas_1_selectSort);
    }

    printf("\n---------------------------------1---------------------------------\n");

    //对无需序列2进行排序
    TestElement_SelectSort **sortedDatas_2_selectSort=NULL;
    unSortedDatasLength=10;
    opResult=sort_Func(
            compare_data_selectSort,
            (void **)unSortedDatas_2,
            unSortedDatasLength,
            (void ***)&sortedDatas_2_selectSort
    );
    printf("\n无序序列为\n");
    for(int i=0;i<unSortedDatasLength;i++)
        print_data_selectSort(unSortedDatas_2[i]);
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_selectSort(sortedDatas_2_selectSort[i]);
        }
        free(sortedDatas_2_selectSort);
    }

    printf("\n---------------------------------2---------------------------------\n");

    //对无需序列2进行排序
    TestElement_SelectSort **sortedDatas_3_selectSort=NULL;
    unSortedDatasLength=10;
    opResult=sort_Func(
            compare_data_selectSort,
            (void **)unSortedDatas_3,
            unSortedDatasLength,
            (void ***)&sortedDatas_3_selectSort
    );
    printf("\n无序序列为\n");
    for(int i=0;i<unSortedDatasLength;i++)
        print_data_selectSort(unSortedDatas_3[i]);
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_selectSort(sortedDatas_3_selectSort[i]);
        }
        free(sortedDatas_3_selectSort);
    }

    printf("\n---------------------------------3---------------------------------\n");

}

/*
 * 选择排序使用测试案例
 */
void usingSelectSort(){
    //测试用 无序序列0
    TestElement_SelectSort **unSortedDatas_0=NULL;

    //测试用 无序序列1
    TestElement_SelectSort **unSortedDatas_1=(TestElement_SelectSort **)malloc(
            sizeof(TestElement_SelectSort *)
            );
    unSortedDatas_1[0]=(TestElement_SelectSort *)malloc(
            sizeof(TestElement_SelectSort)
            );
    unSortedDatas_1[0]->val=1;

    //测试用 无序序列2
    TestElement_SelectSort **unSortedDatas_2=(TestElement_SelectSort **)malloc(
            sizeof(TestElement_SelectSort *)*10
            );
    for(int i=0;i<10;i++)
        unSortedDatas_2[i]=(TestElement_SelectSort *)malloc(
                sizeof(TestElement_SelectSort));
    unSortedDatas_2[0]->val=10;
    unSortedDatas_2[1]->val=9;
    unSortedDatas_2[2]->val=15;
    unSortedDatas_2[3]->val=7;
    unSortedDatas_2[4]->val=12;
    unSortedDatas_2[5]->val=1;
    unSortedDatas_2[6]->val=7;
    unSortedDatas_2[7]->val=17;
    unSortedDatas_2[8]->val=7;
    unSortedDatas_2[9]->val=8;


    //测试用 无序序列3
    TestElement_SelectSort **unSortedDatas_3=(TestElement_SelectSort **)malloc(
            sizeof(TestElement_SelectSort *)*10
    );
    for(int i=0;i<10;i++)
        unSortedDatas_3[i]=(TestElement_SelectSort *)malloc(
                sizeof(TestElement_SelectSort));

    unSortedDatas_3[0]->val=9;
    unSortedDatas_3[1]->val=8;
    unSortedDatas_3[2]->val=7;
    unSortedDatas_3[3]->val=6;
    unSortedDatas_3[4]->val=5;
    unSortedDatas_3[5]->val=4;
    unSortedDatas_3[6]->val=3;
    unSortedDatas_3[7]->val=2;
    unSortedDatas_3[8]->val=1;
    unSortedDatas_3[9]->val=0;

    //测试选择排序
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>选择排序测试--开始<<<<<<<<<<<<<<<<<<<<<<<<\n");
    testSelectSort(directSelectSort,unSortedDatas_0,unSortedDatas_1,unSortedDatas_2,unSortedDatas_3);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>选择排序测试--结束<<<<<<<<<<<<<<<<<<<<<<<<\n");

    //测试堆排序
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>堆排序测试--开始<<<<<<<<<<<<<<<<<<<<<<<<\n");
    testSelectSort(heapSelectSort,unSortedDatas_0,unSortedDatas_1,unSortedDatas_2,unSortedDatas_3);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>堆排序测试--结束<<<<<<<<<<<<<<<<<<<<<<<<\n");

}

//int main(){
//    usingSelectSort();
//    return 0;
//}



