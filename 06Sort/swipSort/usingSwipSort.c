//
// Created by zhouyuqing on 2023/4/25.
//

#include "swipSort.h"

typedef struct{
    int val;
}TestElement_SwipSort;

//打印数据
void print_data_swipSort(void *data){
    printf("%d ",
           ((TestElement_SwipSort *)data)->val);
}

//比较 数据a 与 数据b 的大小
int compare_data_swipSort(void *a,void *b){
    TestElement_SwipSort *ta=(TestElement_SwipSort *)a;
    TestElement_SwipSort *tb=(TestElement_SwipSort *)b;

    if(ta->val > tb->val)
        return 1;
    else if(ta->val == tb->val)
        return 0;
    else
        return -1;
}


void testSwipSort(
        Status (*sort_Func)(COMPARE_DATA,void **,int,void ***),
        TestElement_SwipSort **unSortedDatas_0,
        TestElement_SwipSort **unSortedDatas_1,
        TestElement_SwipSort **unSortedDatas_2,
        TestElement_SwipSort **unSortedDatas_3) {

    //直接交换排序测试程序
    Status opResult=FAIL;
    int unSortedDatasLength=0;

    //对无需序列0进行排序
    TestElement_SwipSort **sortedDatas_0_directInsertSort=NULL;
    unSortedDatasLength=0;
    opResult= sort_Func(
            compare_data_swipSort,
            (void **)unSortedDatas_0,
            unSortedDatasLength,
            (void ***)&sortedDatas_0_directInsertSort
    );
    printf("\n无序序列为:\n");
    for(int i=0;i<unSortedDatasLength;i++){
        print_data_swipSort(unSortedDatas_0[i]);
    }
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_swipSort(sortedDatas_0_directInsertSort[i]);
        }
        free(sortedDatas_0_directInsertSort);
    }

    printf("\n----------------------------0----------------------------\n");

    //对无需序列1进行排序
    TestElement_SwipSort **sortedDatas_1_directInsertSort=NULL;
    unSortedDatasLength=1;
    opResult= sort_Func(
            compare_data_swipSort,
            (void **)unSortedDatas_1,
            unSortedDatasLength,
            (void ***)&sortedDatas_1_directInsertSort
    );
    printf("\n无序序列为:\n");
    for(int i=0;i<unSortedDatasLength;i++){
        print_data_swipSort(unSortedDatas_1[i]);
    }
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_swipSort(sortedDatas_1_directInsertSort[i]);
        }
        free(sortedDatas_1_directInsertSort);
    }

    printf("\n----------------------------1----------------------------\n");

    //对无需序列2进行排序
    TestElement_SwipSort **sortedDatas_2_directInsertSort=NULL;
    unSortedDatasLength=10;
    opResult= sort_Func(
            compare_data_swipSort,
            (void **)unSortedDatas_2,
            unSortedDatasLength,
            (void ***)&sortedDatas_2_directInsertSort
    );
    printf("\n无序序列为:\n");
    for(int i=0;i<unSortedDatasLength;i++){
        print_data_swipSort(unSortedDatas_2[i]);
    }
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_swipSort(sortedDatas_2_directInsertSort[i]);
        }
        free(sortedDatas_2_directInsertSort);
    }

    printf("\n----------------------------2----------------------------\n");

    //对无需序列3进行排序
    TestElement_SwipSort **sortedDatas_3_directInsertSort=NULL;
    unSortedDatasLength=10;
    opResult= sort_Func(
            compare_data_swipSort,
            (void **)unSortedDatas_3,
            unSortedDatasLength,
            (void ***)&sortedDatas_3_directInsertSort
    );
    printf("\n无序序列为:\n");
    for(int i=0;i<unSortedDatasLength;i++){
        print_data_swipSort(unSortedDatas_3[i]);
    }
    if(opResult==FAIL){
        printf("\n排序失败\n");
    }else{
        printf("\n排序结果:\n");
        for(int i=0;i<unSortedDatasLength;i++){
            print_data_swipSort(sortedDatas_3_directInsertSort[i]);
        }
        free(sortedDatas_3_directInsertSort);
    }

    printf("\n----------------------------3----------------------------\n");

}


/*
 * 交换排序使用测试案例
 */
void usingSwipSort(){
    //测试用 无序序列0
    TestElement_SwipSort **unSortedDatas_0=NULL;

    //测试用 无序序列1
    TestElement_SwipSort **unSortedDatas_1=(TestElement_SwipSort **)malloc(
            sizeof(TestElement_SwipSort *)
            );
    unSortedDatas_1[0]=(TestElement_SwipSort *)malloc(sizeof(TestElement_SwipSort));
    unSortedDatas_1[0]->val=1;

    //测试用 无序序列2
    TestElement_SwipSort **unSortedDatas_2=(TestElement_SwipSort **)malloc(
            sizeof(TestElement_SwipSort *)*10
    );
    for(int i=0;i<10;i++)
        unSortedDatas_2[i]=(TestElement_SwipSort *)malloc(
                sizeof(TestElement_SwipSort));
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
    TestElement_SwipSort **unSortedDatas_3=(TestElement_SwipSort **)malloc(
            sizeof(TestElement_SwipSort *)*10
    );
    for(int i=0;i<10;i++)
        unSortedDatas_3[i]=(TestElement_SwipSort *)malloc(
                sizeof(TestElement_SwipSort));
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

    //测试冒泡排序
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>冒泡排序测试--开始<<<<<<<<<<<<<<<<<<<<<<<<\n");
    testSwipSort(bubbleSwipSort,unSortedDatas_0,unSortedDatas_1,unSortedDatas_2,unSortedDatas_3);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>冒泡排序测试--结束<<<<<<<<<<<<<<<<<<<<<<<<\n");

    //测试快速排序
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>快速排序测试--开始<<<<<<<<<<<<<<<<<<<<<<<<\n");
    testSwipSort(quickSwipSort,unSortedDatas_0,unSortedDatas_1,unSortedDatas_2,unSortedDatas_3);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>快速排序测试--结束<<<<<<<<<<<<<<<<<<<<<<<<\n");

}


//int main(){
//    usingSwipSort();
//    return 0;
//}
