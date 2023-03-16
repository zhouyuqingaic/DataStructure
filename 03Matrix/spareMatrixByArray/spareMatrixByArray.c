//
// Created by zhouyuqing on 2023/3/15.
//

#include"spareMatrixByArray.h"

//清空稀疏矩阵
Status empty_SpareMatrix(SpareMatrix *spareMatrix){
    if(spareMatrix==NULL)
        return FAIL;
    //清空稀疏矩阵节点
    for(int i=0;i<spareMatrix->amount;i++){
        free(spareMatrix->nodes[i]);
        spareMatrix->nodes[i]=NULL;
    }
    spareMatrix->amount=0;
    return SUCCESS;
}
//初始化稀疏矩阵
Status init_SpareMatrix(SpareMatrix **pSpareMatrix,int rows,int cols){
    //判断稀疏矩阵的行数,列数是否在合法范围内 1~SPARE_MATRIX_MAX_ARRAY
    if(cols<1 || cols>SPARE_MATRIX_MAX_ARRAY)
        return FAIL;
    if(rows<1 || rows>SPARE_MATRIX_MAX_ARRAY)
        return FAIL;

    if(*pSpareMatrix==NULL){ //稀疏矩阵不存在，则创建
        *pSpareMatrix=(SpareMatrix *)malloc(sizeof(SpareMatrix));
        if(*pSpareMatrix==NULL)
            return FAIL;
        //稀疏矩阵节点指针全部置空
        for(int i=0;i<SPARE_MATRIX_MAX_ARRAY*SPARE_MATRIX_MAX_ARRAY;i++)
            (*pSpareMatrix)->nodes[i]=NULL;
        //设置稀疏矩阵参数
        (*pSpareMatrix)->amount=0;
        (*pSpareMatrix)->rows=rows;
        (*pSpareMatrix)->cols=cols;
        return SUCCESS;
    }else{ //稀疏矩阵存在，先清空节点
        Status opResult=empty_SpareMatrix(*pSpareMatrix);
        if(opResult==FAIL)
            return FAIL;
        //设置稀疏矩阵参数
        (*pSpareMatrix)->rows=rows;
        (*pSpareMatrix)->cols=cols;
        return SUCCESS;
    }
}
//判断稀疏矩阵是否已满
int isFull_SpareMatrix(SpareMatrix *spareMatrix){
    if(spareMatrix->amount==SPARE_MATRIX_MAX_ARRAY*SPARE_MATRIX_MAX_ARRAY)
        return 1;
    else
        return 0;
}
//判断稀疏矩阵是否为空
int isEmpty_SpareMatrix(SpareMatrix *spareMatrix){
    if(spareMatrix->amount==0)
        return 1;
    else
        return 0;
}

//向稀疏矩阵添加节点(节点的行号与列号从1开始计数)
Status appand_SpareMatrix(SpareMatrix *spareMatrix,int row,int col,void *data){
    if(spareMatrix==NULL)
        return FAIL;

    //判断节点的行号与列号是否在合法范围内
    if(col<1 || col>spareMatrix->cols)
        return FAIL;
    if(row<1 || row>spareMatrix->rows)
        return FAIL;

    //如果节点row行,col列的节点已经存在，修改节点
    for(int i=0;i<spareMatrix->amount;i++){
        if(spareMatrix->nodes[i]->col==col && spareMatrix->nodes[i]->row==row){
            //释放节点原数据
            free( spareMatrix->nodes[i]->data );
            //修改节点数据
            spareMatrix->nodes[i]->data=data;
            return SUCCESS;
        }
    }

    //row行，col列的节点不存在
    //创建稀疏矩阵节点
    SpareMatrixNode *spareMatrixNode=(SpareMatrixNode *)malloc(sizeof(SpareMatrixNode));
    if(spareMatrix==NULL)
        return FAIL;
    //设置稀疏矩阵节点参数
    spareMatrixNode->data=data;
    spareMatrixNode->row=row;
    spareMatrixNode->col=col;

    //加入稀疏矩阵
    spareMatrix->nodes[spareMatrix->amount]=spareMatrixNode;
    spareMatrix->amount++;

    return SUCCESS;
}
//获取稀疏矩阵row行，cols列的节点数据(从1开始结束)
Status pos_SpareMatrix(SpareMatrix *spareMatrix,int row,int col,void **resultData){
    if(spareMatrix==NULL)
        return FAIL;

    //矩阵为空则获取失败
    if(isEmpty_SpareMatrix(spareMatrix))
        return FAIL;

    //判断节点的行号与列号是否在合法范围内
    if(col<1 || col>spareMatrix->cols)
        return FAIL;
    if(row<1 || row>spareMatrix->rows)
        return FAIL;

    //寻找row行，col列上的节点 并返回
    for(int i=0;i<spareMatrix->amount;i++){
        if(spareMatrix->nodes[i]->col==col && spareMatrix->nodes[i]->row==row){
            *resultData=spareMatrix->nodes[i]->data;
            return SUCCESS;
        }
    }
    //寻找row行，col列上的节点失败
    return FAIL;
}
//设置转置矩阵row行,col列的节点值
Status set_SpareMatrix(SpareMatrix *spareMatrix,int row,int col,void *data){
    if(spareMatrix==NULL)
        return FAIL;

    //判断节点的行号与列号是否在合法范围内
    if(col<1 || col>spareMatrix->cols)
        return FAIL;
    if(row<1 || row>spareMatrix->rows)
        return FAIL;

    //寻找row行，col列上的节点 并修改
    for(int i=0;i<spareMatrix->amount;i++){
        if(spareMatrix->nodes[i]->col==col && spareMatrix->nodes[i]->row==row){
            //释放节点原数据
            free( spareMatrix->nodes[i]->data );
            //修改节点数据
            spareMatrix->nodes[i]->data=data;
            return SUCCESS;
        }
    }

    //没有找到row行，col列的节点，则将该节点添加到矩阵中
    Status opResult=appand_SpareMatrix(spareMatrix,row,col,data);
    if(FAIL==opResult)
        return FAIL;
    else
        return SUCCESS;
}

//稀疏矩阵转置
Status trans_SpareMatrix(SpareMatrix *spareMatrix,COPY_DATA copyData,SpareMatrix **pSpareMatrixTrans){
    if(spareMatrix==NULL)
        return FAIL;
    //创建转置矩阵为spareMatrix->cols行,spareMatrix->rows列
    Status opResult= init_SpareMatrix(pSpareMatrixTrans,spareMatrix->cols,spareMatrix->rows);
    if(opResult==FAIL)
        return FAIL;
    //向转置矩阵填充数据
    void *origin_data=NULL;
    void *data=NULL;
    //遍历原稀疏矩阵中的所有节点
    for(int i=1;i<=spareMatrix->rows;i++)
        for(int j=1;j<=spareMatrix->cols;j++){
            //获取原矩阵(i,j)位置的原始数据
            opResult= pos_SpareMatrix(spareMatrix,i,j,&origin_data);
            if(FAIL==opResult) //该位置数据为空，直接探查下一个数据
                continue;
            //在堆上复制原数origin_data到data
            opResult=copyData(origin_data,&data);
            if(FAIL==opResult)
                return FAIL;
            //向转置矩阵添加 j行,i列,值为data的节点
            opResult= appand_SpareMatrix(*pSpareMatrixTrans,j,i,data);
            if(FAIL==opResult)
                return FAIL;
        }

    return SUCCESS;

}

//展示稀疏矩阵
Status show_SpareMatrix(SpareMatrix *spareMatrix,PRINT_DATA printData){
    if(spareMatrix==NULL)
        return FAIL;
    void *data=NULL;
    Status opResult=FAIL;
    //打印矩阵
    printf("\n\n");
    for(int i=0;i<spareMatrix->cols*(PRINT_SPAN+2)+2;i++)
        printf("_");
    printf("\n");
    for(int i=1;i<=spareMatrix->rows;i++){
        printf("|");
        for(int j=1;j<=spareMatrix->cols;j++){
            //获取矩阵i行,j列的元素
            opResult=pos_SpareMatrix(spareMatrix,i,j,&data);
            if(opResult==FAIL){ //获取失败打印空
                printf(" ");
                for(int z=0;z<PRINT_SPAN;z++)
                    printf("_");
                printf(" ");
            }else{ //获取成功，打印获取到的值
                printData(data);
            }
        }
        printf("|\n");
    }
    for(int i=0;i<spareMatrix->cols*(PRINT_SPAN+2)+2;i++)
        printf("_");
    printf("\n");
    printf("\n\n");
    return SUCCESS;
}

//销毁稀疏矩阵
Status destroy_SpareMatrix(SpareMatrix **pSpareMatrix){
    if(*pSpareMatrix==NULL) //矩阵为空 直接返回
        return SUCCESS;
    //清空稀疏矩阵
    Status opResult=empty_SpareMatrix(*pSpareMatrix);
    if(FAIL==opResult)
        return FAIL;
    //释放稀疏矩阵
    free(*pSpareMatrix);
    *pSpareMatrix=NULL;
    return SUCCESS;
}
