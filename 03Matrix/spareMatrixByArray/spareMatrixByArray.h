//
// Created by zhouyuqing on 2023/3/15.
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


#ifndef DATASTRUCTURE_SPAREMATRIXBYARRAY_H
#define DATASTRUCTURE_SPAREMATRIXBYARRAY_H

#include<stdio.h>
#include<malloc.h>
#define SPARE_MATRIX_MAX_ARRAY 30 //稀疏矩阵的最大宽度,高度
#define PRINT_SPAN 8

typedef struct _SPAR_MATRIX_NODE{
    void *data; //矩阵节点的数据值
    int row,col; //矩阵节点的位置
}SpareMatrixNode; //稀疏矩阵节点
typedef struct _SPARE_MATRIX{
    //SPARE_MATRIX_MAX_ARRAY*SPARE_MATRIX_MAX_ARRAY,
    // 可以容纳SPARE_MATRIX_MAX_ARRAY行,SPARE_MATRIX_MAX_ARRAY列的满矩阵
    //可以容纳最多SPARE_MATRIX_MAX_ARRAY行，SPARE_MATRIX_MAX_ARRAY列的稀疏矩阵
    SpareMatrixNode *nodes[SPARE_MATRIX_MAX_ARRAY*SPARE_MATRIX_MAX_ARRAY];
    int amount; //矩阵节点的个数
    int rows,cols; //矩阵的行数与列数
}SpareMatrix; //稀疏矩阵(数组实现)

typedef Status (*COPY_DATA)(void *,void **); //在堆上创建个的data数据，内容和原data一样

//清空稀疏矩阵
Status empty_SpareMatrix(SpareMatrix *spareMatrix);
//初始化稀疏矩阵
Status init_SpareMatrix(SpareMatrix **pSpareMatrix,int rows,int cols);

//判断稀疏矩阵是否已满
int isFull_SpareMatrix(SpareMatrix *spareMatrix);
//判断稀疏矩阵是否为空
int isEmpty_SpareMatrix(SpareMatrix *spareMatrix);
//向稀疏矩阵添加节点(节点的行号与列号从1开始计数)
Status appand_SpareMatrix(SpareMatrix *spareMatrix,int row,int col,void *data);
//获取稀疏矩阵row行，col列的节点数据(从1开始计数)
Status pos_SpareMatrix(SpareMatrix *spareMatrix,int row,int col,void **resultData);
//设置转置矩阵row行,col列的节点值
Status set_SpareMatrix(SpareMatrix *spareMatrix,int row,int col,void *data);
//稀疏矩阵转置
Status trans_SpareMatrix(SpareMatrix *spareMatrix,COPY_DATA copyData,SpareMatrix **pSpareMatrixTrans);

//展示稀疏矩阵
Status show_SpareMatrix(SpareMatrix *spareMatrix,PRINT_DATA printData);

//销毁稀疏矩阵
Status destroy_SpareMatrix(SpareMatrix **pSpareMatrix);

#endif //DATASTRUCTURE_SPAREMATRIXBYARRAY_H


#ifdef __cplusplus
}
#endif