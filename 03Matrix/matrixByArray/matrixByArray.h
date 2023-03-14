//
// Created by zhouyuqing on 2023/3/14.
//

#ifdef __cplusplus
extern "C"{
#endif

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态

typedef void (*PRINT_DATA)(void *);

#endif

#ifndef DATASTRUCTURE_MATRIXBYARRAY_H
#define DATASTRUCTURE_MATRIXBYARRAY_H

#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define PRINT_SPAN 8
#define MATRIX_MAX_ARRAY 30

typedef int ElemType;

typedef struct _MATRIC_BY_ARRAY {
    ElemType data[MATRIX_MAX_ARRAY][MATRIX_MAX_ARRAY]; //用来存储矩阵元素的二维数组
    int rows, cols; //矩阵的行数与列数
} MatrixByArray;

typedef ElemType (*Add_ELEMTYPE)(ElemType a, ElemType b);

typedef ElemType (*Mul_ELETYPE)(ElemType a, ElemType b);


//清空矩阵
Status empty_MatrixByArray(MatrixByArray *matrix);

//初始化矩阵
Status init_MatrixByArray(MatrixByArray **matrix, int rows, int cols);

//获取矩阵row行,col列的元素(从1开始)
Status pos_MatrixByArray(MatrixByArray *matrix, int row, int col, ElemType *result);

//用二维数组为矩阵赋值
Status assign_MatrixByArray(ElemType data[][MATRIX_MAX_ARRAY], int rowsData, int colsData, MatrixByArray **pMatrix);

//获取转置矩阵
Status trans_MatrixByArray(const MatrixByArray *matrix, MatrixByArray **pResult);

//矩阵相加
Status add_MatrixByArray(const MatrixByArray *matrix1, const MatrixByArray *matrix2, Add_ELEMTYPE addElemtype,
                         MatrixByArray **pResult);

//矩阵相乘
Status mut_MatrixByArray(const MatrixByArray *matrix1, const MatrixByArray *matrix2, Add_ELEMTYPE addElemtype,
                         Mul_ELETYPE mulEletype, MatrixByArray **pResult);

//展示矩阵
Status show_MatrixByArray(const MatrixByArray *matrix, PRINT_DATA printData);

//销毁矩阵
Status destroy_MatrixByArray(MatrixByArray **pMatrix);


#endif //DATASTRUCTURE_MATRIXBYARRAY_H

#ifdef __cplusplus
}
#endif