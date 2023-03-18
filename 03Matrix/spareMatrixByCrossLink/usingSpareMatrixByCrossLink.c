//
// Created by zhouyuqing on 2023/3/16.
//
#include"spareMatrixByCrossLink.h"

void printItemSpareMatrixByCrossLink(void *data){

    printf(" val:%4d ",*(int *)data );
}

//拷贝data数据
Status copyItemSpareMatricByCrossLink(void *data,void **result){
    if(data==NULL)
        return FAIL;
    *result=data;
    return SUCCESS;
}

void usingSpareMatrixByCrossList(){
    /*
     * SpareMatrixByCrossList测试&使用    printf(" val:%4d ",*((int *)data) );案例
     */
    SpareMatrixByCrossLink *spareMatrixByCrossLink01=NULL;

    int *pList[100];
    int indexPList=0;

    int *d1_1=(int *)malloc(sizeof(int));
    pList[indexPList++]=d1_1;
    *d1_1=11;
    int *d3_1=(int *)malloc(sizeof(int));
    pList[indexPList++]=d3_1;
    *d3_1=31;
    int *d2_3=(int *)malloc(sizeof(int));
    pList[indexPList++]=d2_3;
    *d2_3=23;
    int *d3_4=(int *)malloc(sizeof(int));
    pList[indexPList++]=d3_4;
    *d3_4=34;

    Status opResult= init_SpareMatrixByCrossLink(&spareMatrixByCrossLink01,4,5);
    if(FAIL==opResult){
        printf("初始化十字链表实现的稀疏矩阵失败\n");
        return;
    }

    void *dataMatrix[MAX_SIZE_SPARE_MATRIX_CROSS_LINK][MAX_SIZE_SPARE_MATRIX_CROSS_LINK];
    for(int i=0;i<MAX_SIZE_SPARE_MATRIX_CROSS_LINK;i++)
        for(int j=0;j<MAX_SIZE_SPARE_MATRIX_CROSS_LINK;j++)
            dataMatrix[i][j]=NULL;

    dataMatrix[1-1][1-1]=d1_1;
    dataMatrix[2-1][3-1]=d2_3;
    dataMatrix[3-1][1-1]=d3_1;
    dataMatrix[3-1][4-1]=d3_4;


    opResult= assign_SpareMatrixByCrossLink(spareMatrixByCrossLink01,4,5,dataMatrix);
    if(FAIL==opResult){
        printf("为十字链表赋值失败\n");
        return;
    }

    opResult= show_SpareMatrixByCrossLink(spareMatrixByCrossLink01,printItemSpareMatrixByCrossLink);
    if(FAIL==opResult){
        printf("展示稀疏矩阵失败\n");
        return;
    }


    int *d3_2=(int *)malloc(sizeof(int));
    pList[indexPList++]=d3_2;
    *d3_2=32;
    int *d4_5=(int *)malloc(sizeof(int));
    pList[indexPList++]=d4_5;
    *d4_5=45;
    int *d1_5=(int *)malloc(sizeof(int));
    pList[indexPList++]=d1_5;
    *d1_5=15;
    int *d4_1=(int *)malloc(sizeof(int));
    pList[indexPList++]=d4_1;
    *d4_1=41;


    opResult= set_SpareMatrixByCrossLink(spareMatrixByCrossLink01,3,2,d3_2);
    if(opResult==FAIL){
        printf("设置%d行,%d列的元素%d,失败",3,2,d3_2);
    }
    opResult= set_SpareMatrixByCrossLink(spareMatrixByCrossLink01,4,5,d4_5);
    if(opResult==FAIL){
        printf("设置%d行,%d列的元素%d,失败",4,5,d4_5);
    }
    opResult= set_SpareMatrixByCrossLink(spareMatrixByCrossLink01,1,5,d1_5);
    if(opResult==FAIL){
        printf("设置%d行,%d列的元素%d,失败",1,5,d1_5);
    }
    opResult= set_SpareMatrixByCrossLink(spareMatrixByCrossLink01,4,1,d4_1);
    if(opResult==FAIL){
        printf("设置%d行,%d列的元素%d,失败",4,1,d4_1);
    }


    opResult= show_SpareMatrixByCrossLink(spareMatrixByCrossLink01,printItemSpareMatrixByCrossLink);
    if(FAIL==opResult){
        printf("展示稀疏矩阵失败\n");
        return;
    }

    printf("\n-----------------------------1----------------------------\n");

    SpareMatrixByCrossLink *spareMatrixByCrossLink01_Trans=NULL;
    opResult=trans_SpareMatrixByCrossLink(spareMatrixByCrossLink01,copyItemSpareMatricByCrossLink,&spareMatrixByCrossLink01_Trans);
    if(FAIL==opResult){
        printf("矩阵转置失败\n");
        return;
    }else{
        opResult= show_SpareMatrixByCrossLink(spareMatrixByCrossLink01_Trans,printItemSpareMatrixByCrossLink);
        if(FAIL==opResult){
            printf("展示稀疏矩阵失败\n");
            return;
        }
    }

    printf("\n-----------------------------2----------------------------\n");

    int *d1_2=(int *)malloc(sizeof(int));
    *d1_2=1996;
    pList[indexPList++]=d1_2;
    opResult=set_SpareMatrixByCrossLink(spareMatrixByCrossLink01_Trans,1,2,d1_2);
    if(opResult==FAIL){
        printf("设置%d行,%d列的元素%d,失败",1,2,d1_2);
    }
    int *d3_1_new=(int *)malloc(sizeof(int));
    *d3_1_new=1998;
    pList[indexPList++]=d3_1_new;
    opResult=set_SpareMatrixByCrossLink(spareMatrixByCrossLink01_Trans,3,1,d3_1_new);
    if(opResult==FAIL){
        printf("设置%d行,%d列的元素%d,失败",1,2,d3_1_new);
    }


    opResult= show_SpareMatrixByCrossLink(spareMatrixByCrossLink01_Trans,printItemSpareMatrixByCrossLink);
    if(FAIL==opResult){
        printf("展示稀疏矩阵失败\n");
        return;
    }

    printf("进行转置到原矩阵");
    opResult= trans_SpareMatrixByCrossLink(spareMatrixByCrossLink01_Trans,copyItemSpareMatricByCrossLink,&spareMatrixByCrossLink01);
    if(FAIL==opResult){
        printf("转置失败");
        return;
    }
    opResult= show_SpareMatrixByCrossLink(spareMatrixByCrossLink01,printItemSpareMatrixByCrossLink);
    if(FAIL==opResult){
        printf("展示稀疏矩阵失败\n");
        return;
    }


    printf("\n-----------------------------3----------------------------\n");

    opResult=destroy_SpareMatrixByCrossLink(&spareMatrixByCrossLink01);
    if(FAIL==opResult && spareMatrixByCrossLink01==NULL){
        printf("销毁稀疏矩阵spareMatrixByCrossLink01失败\n");
        return;
    }

    opResult= destroy_SpareMatrixByCrossLink(&spareMatrixByCrossLink01_Trans);
    if(FAIL==opResult && spareMatrixByCrossLink01_Trans==NULL){
        printf("销毁稀疏矩阵spareMatrixByCrossLink01_Trans失败\n");
        return;
    }

    for(int i=0;i<indexPList;i++)
        free(pList[i]);

    printf("销毁数据完毕\n");
}

//void main(){
//    usingSpareMatrixByCrossList();
//
//}