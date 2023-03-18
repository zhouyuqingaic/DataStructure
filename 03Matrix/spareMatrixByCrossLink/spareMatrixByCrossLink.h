//
// Created by zhouyuqing on 2023/3/16.
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

#ifndef DATASTRUCTURE_SPAREMATRIXBYCROSSLINK_H
#define DATASTRUCTURE_SPAREMATRIXBYCROSSLINK_H

#define MAX_SIZE_SPARE_MATRIX_CROSS_LINK 100
#define PRINT_SPAN 8

#include<stdio.h>
#include<malloc.h>

typedef struct _CROSS_LINK_NODE{
    void *data; //矩阵十字链表节点的数据
    int row,col; //节点所处的矩阵行列号
    struct _CROSS_LINK_NODE *right,*down; //矩阵十字链表节点的 左侧节点 与 下侧节点
}CrossLinkNode; //矩阵的十字链表节点

typedef struct _SPARE_MATRIX_CROSS_LINK{
    CrossLinkNode *rowsHead,*colsHead; //指向行头节点数组 与 列头结点数组的指针
    int amount;  //矩阵的节点个数
    int rows,cols; //矩阵的行数,列数
}SpareMatrixByCrossLink; //稀疏矩阵，十字链表实现

typedef Status (*COPY_DATA)(void *,void **); //在堆上创建个的data数据，内容和原data一样

//清空稀疏矩阵
Status empty_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink);
//初始化稀疏矩阵
Status init_SpareMatrixByCrossLink(SpareMatrixByCrossLink **pSpareMatrixByCrossLink,int rows,int cols);

//判断稀疏矩阵是否已满
int isFull_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink);
//判断稀疏矩阵是否为空
int isEmpty_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink);
//向稀疏矩阵添加节点(节点的行号与列号从1开始计数)
Status appand_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,int row,int col,void *data);

//通过传入二维数组构建十字链表
Status assign_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,int row,int col,void *data[][MAX_SIZE_SPARE_MATRIX_CROSS_LINK]);

//获取稀疏矩阵row行，col列的节点数据(从1开始计数)
Status pos_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,int row,int col,void **resultData);
//设置稀疏矩阵row行,col列的节点值
Status set_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,int row,int col,void *data);
//稀疏矩阵转置
Status trans_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,COPY_DATA copyData,SpareMatrixByCrossLink **pSpareMatrixByCrossLink);

//展示稀疏矩阵
Status show_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,PRINT_DATA printData);

//销毁稀疏矩阵
Status destroy_SpareMatrixByCrossLink(SpareMatrixByCrossLink **pSpareMatrixByCrossLink);


#endif //DATASTRUCTURE_SPAREMATRIXBYCROSSLINK_H

#ifdef __cplusplus
}
#endif