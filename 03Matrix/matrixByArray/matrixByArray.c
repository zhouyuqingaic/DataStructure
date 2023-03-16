//
// Created by zhouyuqing on 2023/3/14.
//
#include "matrixByArray.h"

//清空矩阵
Status empty_MatrixByArray(MatrixByArray *matrix){
    if(matrix==NULL)
        return FAIL;
    //重置data数组
    for(int i=0;i<matrix->rows;i++)
        for(int j=0;j<matrix->cols;j++)
            matrix->data[i][j]=0;
    return SUCCESS;
}

//初始化矩阵
Status init_MatrixByArray(MatrixByArray **pMatrix,int rows,int cols){
    //判断传入的行列数是否合法必须都在 1~MATRIX_MAX_ARRAY 之间
    if(cols<1 || cols>MATRIX_MAX_ARRAY)
        return FAIL;
    if(rows<1 || rows>MATRIX_MAX_ARRAY)
        return FAIL;

    if(*pMatrix==NULL){ //矩阵不存在，则创建rows行，cols列的矩阵
        *pMatrix=(MatrixByArray *)malloc(sizeof(MatrixByArray));
        if(*pMatrix==NULL)
            return FAIL;
        //清空data值
        Status opReuslt= empty_MatrixByArray(*pMatrix);
        if(FAIL==opReuslt)
            return FAIL;

        (*pMatrix)->rows=rows;
        (*pMatrix)->cols=cols;
    }else{ //矩阵存在，重置其行列数
        //清空data值
        Status opResult= empty_MatrixByArray(*pMatrix);
        if(FAIL==opResult)
            return FAIL;

        (*pMatrix)->rows=rows;
        (*pMatrix)->cols=cols;
    }
    return SUCCESS;
}


//获取矩阵row行,col列的元素(从1开始)
Status pos_MatrixByArray(MatrixByArray *matrix,int row,int col,ElemType *result){
    if(matrix==NULL)
        return FAIL;
    //row 合法范围1~matrix->rows
    if(row<1 || row>matrix->rows)
        return FAIL;
    //col 合法范围1~matrix->cols
    if(col<1 || col>matrix->cols)
        return FAIL;
    //得到结果元素
    *result=matrix->data[row-1][col-1];
    return SUCCESS;
}

//用二维数组为矩阵赋值
Status assign_MatrixByArray(ElemType data[][MATRIX_MAX_ARRAY],int rowsData,int colsData,MatrixByArray **pMatrix){
    //将矩阵初始化为matrix->cols行，matrix->rows列
    Status opReuslt=init_MatrixByArray(pMatrix,rowsData,colsData);
    if(FAIL==opReuslt)
        return FAIL;
    for(int i=0;i<(*pMatrix)->rows;i++)
        for(int j=0;j<(*pMatrix)->cols;j++)
            (*pMatrix)->data[i][j]=data[i][j];
    return SUCCESS;
}

//获取转置矩阵
Status trans_MatrixByArray(const MatrixByArray *matrix,MatrixByArray **pResult){
    if(matrix==NULL)
        return FAIL;
    //将矩阵初始化为matrix->cols行，matrix->rows列
    Status opReuslt=init_MatrixByArray(pResult,matrix->cols,matrix->rows);
    if(FAIL==opReuslt)
        return FAIL;
    //向结果矩阵填充数据
    for(int i=0;i<matrix->rows;i++)
        for(int j=0;j<matrix->cols;j++)
            (*pResult)->data[j][i]=matrix->data[i][j];
    return SUCCESS;
}
//矩阵相加
Status add_MatrixByArray(const MatrixByArray *matrix1,const MatrixByArray *matrix2,Add_ELEMTYPE addElemtype,MatrixByArray **pResult){
    if(matrix1==NULL || matrix2==NULL)
        return FAIL;
    //判断matrix1与matrix2是否大小相同
    if(matrix1->rows!=matrix2->rows || matrix1->cols!=matrix2->cols)
        return FAIL;
    //将结果矩阵初始化为matrix-rows行，matrix->cols列
    Status opResult= init_MatrixByArray(pResult, matrix1->rows,matrix1->cols);
    if(FAIL==opResult)
        return FAIL;
    //向结果矩阵填充相加结果
    int a,b;
    for(int i=0;i<(*pResult)->rows;i++)
        for(int j=0;j<(*pResult)->cols;j++){
            a=matrix1->data[i][j];
            b=matrix2->data[i][j];
            (*pResult)->data[i][j]=addElemtype(a,b);
        }
    return SUCCESS;
}
//矩阵相乘
Status mut_MatrixByArray(const MatrixByArray *matrix1,const MatrixByArray *matrix2,Add_ELEMTYPE addElemtype,Mul_ELETYPE mulEletype,MatrixByArray **pResult){
    if(matrix1==NULL || matrix2==NULL)
        return FAIL;
    //判断matrix1与matrix2是否符合相乘条件,即    matrix1->cols==matrix2->rows
    if(matrix1->cols!=matrix2->rows)
        return FAIL;
    //将结果矩阵初始化为matrix1->rows行 matrix2->cols列
    Status opResult= init_MatrixByArray(pResult,matrix1->rows,matrix2->cols);
    if(FAIL==opResult)
        return FAIL;
    //向结果矩阵填充相乘结果
    for(int i=0;i<(*pResult)->rows;i++)
        for(int j=0;j<(*pResult)->cols;j++){
            //(*pResult)->data[i][j] =
            //      matrix1->data[i][0]*matrix2->data[0][j] +
            //      matrix1->data[i][1]*matrix2->data[1][j] +
            //      ...... +
            //      matrix1->data[i][matrix1->cols]*matrix2->data[matrix1->cols][j]
            (*pResult)->data[i][j]=0;
            for(int z=0;z<matrix1->cols;z++)
                (*pResult)->data[i][j]=addElemtype(
                        (*pResult)->data[i][j],
                        mulEletype( matrix1->data[i][z] , matrix2->data[z][j] )
                    );
        }
    return SUCCESS;
}
//展示矩阵
Status show_MatrixByArray(const MatrixByArray *matrix,PRINT_DATA printData){
    if(matrix==NULL) //矩阵为空 直接返回
        return FAIL;
    //打印矩阵
    printf("\n\n");
    for(int i=0;i<matrix->cols*PRINT_SPAN+2;i++)
        printf("_");
    printf("\n");
    for(int i=0;i< matrix->rows;i++){
        printf("|");
        for(int j=0;j<matrix->cols;j++){
            printData((void *)&(matrix->data[i][j]));
        }
        printf("|\n");
    }
    for(int i=0;i<matrix->cols*PRINT_SPAN+2;i++)
        printf("_");
    printf("\n");
    printf("\n\n");
    return SUCCESS;
}

//销毁矩阵
Status destroy_MatrixByArray(MatrixByArray **pMatrix){
    if(*pMatrix==NULL) //矩阵为空 直接返回
        return SUCCESS;
    //清空矩阵
    Status opResult= empty_MatrixByArray(*pMatrix);
    if(opResult==FAIL)
        return FAIL;
    //释放矩阵空间
    free(*pMatrix);
    *pMatrix=NULL;

    return SUCCESS;
}
