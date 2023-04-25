//
// Created by zhouyuqing on 2023/4/22.
//

#include "insertSort.h"


typedef struct{
    int val;
}TestElement_InsertSort;


//打印数据
void print_data_inserotSort(void *data){
    printf(
    "%d ",
            ((TestElement_InsertSort *)data)->val
    );
}

//比较 数据a 与 数据b 的大小
int compare_data_inserotSort(void *a,void *b){
    TestElement_InsertSort *ta=(TestElement_InsertSort *)a;
    TestElement_InsertSort *tb=(TestElement_InsertSort *)b;

    if(ta->val > tb->val)
        return 1;
    else if(ta->val == tb->val)
        return 0;
    else
        return -1;
}


void testInsertSort(
    Status (*sort_Func)(COMPARE_DATA,void **,int,void ***),
    TestElement_InsertSort **unSortedDatas_0,
    TestElement_InsertSort **unSortedDatas_1,
    TestElement_InsertSort **unSortedDatas_2,
    TestElement_InsertSort **unSortedDatas_3){
    //直接插入排序测试程序
    Status opResult=FAIL;
    int unSortedDatasLength=0;

    //对无需序列0进行排序
    TestElement_InsertSort **sortedDatas_0_directInsertSort=NULL;
    unSortedDatasLength=0;
    opResult= sort_Func(
            compare_data_inserotSort,
            (void **)unSortedDatas_0,
            unSortedDatasLength,
            (void ***)&sortedDatas_0_directInsertSort
    );
    printf("\n无序序列为:\n");
    for(int i=0;i<unSortedDatasLength;i++){
        print_data_inserotSort(unSortedDatas_0[i]);
    }
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_inserotSort(sortedDatas_0_directInsertSort[i]);
        }
        free(sortedDatas_0_directInsertSort);
    }

    printf("\n----------------------------0----------------------------\n");

    //对无需序列1进行排序
    TestElement_InsertSort **sortedDatas_1_directInsertSort=NULL;
    unSortedDatasLength=1;
    opResult= sort_Func(
            compare_data_inserotSort,
            (void **)unSortedDatas_1,
            unSortedDatasLength,
            (void ***)&sortedDatas_1_directInsertSort
    );
    printf("\n无序序列为:\n");
    for(int i=0;i<unSortedDatasLength;i++){
        print_data_inserotSort(unSortedDatas_1[i]);
    }
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_inserotSort(sortedDatas_1_directInsertSort[i]);
        }
        free(sortedDatas_1_directInsertSort);
    }

    printf("\n----------------------------1----------------------------\n");

    //对无需序列2进行排序
    TestElement_InsertSort **sortedDatas_2_directInsertSort=NULL;
    unSortedDatasLength=10;
    opResult= sort_Func(
            compare_data_inserotSort,
            (void **)unSortedDatas_2,
            unSortedDatasLength,
            (void ***)&sortedDatas_2_directInsertSort
    );
    printf("\n无序序列为:\n");
    for(int i=0;i<unSortedDatasLength;i++){
        print_data_inserotSort(unSortedDatas_2[i]);
    }
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_inserotSort(sortedDatas_2_directInsertSort[i]);
        }
        free(sortedDatas_2_directInsertSort);
    }

    printf("\n----------------------------2----------------------------\n");

    //对无需序列3进行排序
    TestElement_InsertSort **sortedDatas_3_directInsertSort=NULL;
    unSortedDatasLength=10;
    opResult= sort_Func(
            compare_data_inserotSort,
            (void **)unSortedDatas_3,
            unSortedDatasLength,
            (void ***)&sortedDatas_3_directInsertSort
    );
    printf("\n无序序列为:\n");
    for(int i=0;i<unSortedDatasLength;i++){
        print_data_inserotSort(unSortedDatas_3[i]);
    }
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_inserotSort(sortedDatas_3_directInsertSort[i]);
        }
        free(sortedDatas_3_directInsertSort);
    }

    printf("\n----------------------------3----------------------------\n");

}



/*
 * 插入排序使用测试案例
 */
void usingInsertSort(){

    //测试用 无序序列0
    TestElement_InsertSort **unSortedDatas_0=NULL;

    //测试用 无序序列1
    TestElement_InsertSort **unSortedDatas_1=(TestElement_InsertSort **) malloc(
            sizeof(TestElement_InsertSort *)
            );
    unSortedDatas_1[0]=(TestElement_InsertSort *)malloc(sizeof(TestElement_InsertSort));
    unSortedDatas_1[0]->val=1;

    //测试用 无序序列2
    TestElement_InsertSort **unSortedDatas_2=(TestElement_InsertSort **)malloc(
            sizeof(TestElement_InsertSort *)*10
            );
    for(int i=0;i<10;i++)
        unSortedDatas_2[i]=(TestElement_InsertSort *)malloc(
                sizeof(TestElement_InsertSort));
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
    TestElement_InsertSort **unSortedDatas_3=(TestElement_InsertSort **)malloc(
            sizeof(TestElement_InsertSort *)*10
    );
    for(int i=0;i<10;i++)
        unSortedDatas_3[i]=(TestElement_InsertSort *)malloc(
                sizeof(TestElement_InsertSort));
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

    //测试直接插入排序
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>直接插入排序测试--开始<<<<<<<<<<<<<<<<<<<<<<<<\n");
    testInsertSort(directInsertSort,unSortedDatas_0,unSortedDatas_1,unSortedDatas_2,unSortedDatas_3);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>直接插入排序测试--结束<<<<<<<<<<<<<<<<<<<<<<<<\n");

    //测试折半插入排序
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>折半插入排序测试--开始<<<<<<<<<<<<<<<<<<<<<<<<\n");
    testInsertSort(blusetInsertSort,unSortedDatas_0,unSortedDatas_1,unSortedDatas_2,unSortedDatas_3);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>折半插入排序测试--结束<<<<<<<<<<<<<<<<<<<<<<<<\n");

    //希尔排序测试
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>希尔插入排序测试--开始<<<<<<<<<<<<<<<<<<<<<<<<\n");
    testInsertSort(shellInsertSort,unSortedDatas_0,unSortedDatas_1,unSortedDatas_2,unSortedDatas_3);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>希尔插入排序测试--结束<<<<<<<<<<<<<<<<<<<<<<<<\n");

}


//int main(){
//    usingInsertSort();
//    return 0;
//}

