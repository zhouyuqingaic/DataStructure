//
// Created by zhouyuqing on 2023/3/14.
//

#include "matrixByArray.h"

ElemType add_MatrixItem(ElemType a,ElemType b){
    return a+b;
}
ElemType mut_MatrixItem(ElemType a,ElemType b){
    return a*b;
}
void printItem(void *data){
    printf("%8d",*( (int *)data ) );
}

void usingMatrixByArray(){
    /*
     * MatrixByArray测试&使用案例
     */
    MatrixByArray *matrix01 = NULL;
    ElemType data[][MATRIX_MAX_ARRAY] = {
            {10, 11, 12, 13, 14, 15, 16},
            {20, 21, 22, 23, 24, 25, 26},
            {30, 31, 32, 33, 34, 35, 36},
            {40, 41, 42, 43, 44, 45, 46}
    };
    if (FAIL == assign_MatrixByArray(data, 4, 7,&matrix01)) {
        printf("创建矩阵失败!\n");
        return;
    }
    if (FAIL == show_MatrixByArray(matrix01,printItem) ) {
        printf("展示矩阵失败!\n");
        return;
    }

    printf("\n1-------------------------------------------\n");
    printf("\n第一次转置\n");
    MatrixByArray *matrix01trans = NULL;
    if (FAIL == trans_MatrixByArray(matrix01, &matrix01trans)) {
        printf("矩阵转置失败!\n");
        return;
    }
    if (FAIL == show_MatrixByArray(matrix01trans,printItem)) {
        printf("展示转置矩阵失败!\n");
        return;
    }

    printf("\n第二次转置\n");
    MatrixByArray *matrix02trans = NULL;
    if (FAIL == trans_MatrixByArray(matrix01trans, &matrix02trans)) {
        printf("矩阵转置失败!\n");
        return;
    }
    if (FAIL == show_MatrixByArray(matrix02trans,printItem)) {
        printf("展示转置矩阵失败!\n");
        return;
    }

    printf("\n2-------------------------------------------\n");

    MatrixByArray *matrixData02 = NULL;
    ElemType data02[][MATRIX_MAX_ARRAY] = {
            {11, 21, 31, 41},
            {12, 22, 32, 42},
            {13, 23, 33, 43}
    };
    if (FAIL == assign_MatrixByArray(data02, 3, 4,&matrixData02)) {
        printf("创建矩阵失败");
        return;
    }

    MatrixByArray *matrixData03=NULL;
    ElemType data03[][MATRIX_MAX_ARRAY]={
            {1100,1200,1300,1400},
            {2100,2200,2300,2400},
            {3100,3200,3300,3400}
    };
    if(FAIL== assign_MatrixByArray(data03,3,4,&matrixData03)){
        printf("创建矩阵失败");
        return;
    }
    MatrixByArray *addResult=NULL;
    if(FAIL==add_MatrixByArray(matrixData02,matrixData03, add_MatrixItem,&addResult)){
        printf("相加失败");
        return;
    }

    show_MatrixByArray(matrixData02,printItem);
    show_MatrixByArray(matrixData03,printItem);
    printf("\n相加结果\n");
    show_MatrixByArray(addResult,printItem);

    printf("\n3-------------------------------------------\n");

    MatrixByArray *matrixData04=NULL;
    ElemType data04[][MATRIX_MAX_ARRAY]={
            {1,2,3,4},
            {5,6,7,8},
            {10,11,12,13}
    };
    assign_MatrixByArray(data04,3,4,&matrixData04);

    MatrixByArray *matrixData05=NULL;
    ElemType data05[][MATRIX_MAX_ARRAY]={
            {1,5},
            {2,6},
            {3,7},
            {4,8}
    };
    assign_MatrixByArray(data05,4,2,&matrixData05);

    MatrixByArray *mutResult=NULL;
    mut_MatrixByArray(matrixData04,matrixData05,add_MatrixItem,mut_MatrixItem,&mutResult);

    show_MatrixByArray(matrixData04,printItem);
    show_MatrixByArray(matrixData05,printItem);
    printf("\n相乘结果\n");
    show_MatrixByArray(mutResult,printItem);

    printf("\n4-------------------------------------------\n");

    printf("获取数据各位置元素\n");
    int temp=0;
    for(int i=1;i<=mutResult->rows;i++){
        printf("\t\t");
        for(int j=1;j<=mutResult->cols;j++){
            Status opResult= pos_MatrixByArray(mutResult,i,j,&temp);
            printf("%8d",temp);
        }
        printf("\n");
    }

    Status opResult= destroy_MatrixByArray(&matrix01);
    if(opResult==FAIL)
        printf("销毁matrix01失败\n");
    opResult= destroy_MatrixByArray(&matrixData02);
    if(opResult==FAIL)
        printf("销毁matrixData02失败\n");
    opResult= destroy_MatrixByArray(&matrixData03);
    if(opResult==FAIL)
        printf("销毁matrixData03失败\n");
    opResult= destroy_MatrixByArray(&matrixData04);
    if(opResult==FAIL)
        printf("销毁matrixData04失败\n");
    opResult= destroy_MatrixByArray(&matrixData05);
    if(opResult==FAIL)
        printf("销毁matrixData05失败\n");
    opResult= destroy_MatrixByArray(&addResult);
    if(opResult==FAIL)
        printf("销毁addResult失败\n");
    opResult= destroy_MatrixByArray(&mutResult);
    if(opResult==FAIL)
        printf("销毁mutResult失败\n");

    printf("\n全部销毁完毕!!!!\n");
}

//
//void main(){
//    usingMatrixByArray();
//}