//
// Created by zhouyuqing on 2023/3/16.
//

#include"spareMatrixByCrossLink.h"

//清空稀疏矩阵
Status empty_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink){
    if(spareMatrixByCrossLink==NULL)
        return FAIL;
    if(isEmpty_SpareMatrixByCrossLink(spareMatrixByCrossLink)) //稀疏矩阵为空，无需操作直接返回
        return SUCCESS;
    //清空矩阵中的所有十字链表节点
    CrossLinkNode *rowCurrentLinkNode;
    //遍历每行元素,释放所有十字链表节点
    for(int i=0;i<spareMatrixByCrossLink->rows;i++){
        rowCurrentLinkNode=spareMatrixByCrossLink->rowsHead[i].right; //获取当前行的头结点
        //当前行不为空，则释放当前行的所有节点
        while(rowCurrentLinkNode!=NULL){
            free(rowCurrentLinkNode);
            rowCurrentLinkNode=rowCurrentLinkNode->right;
        }
        spareMatrixByCrossLink->rowsHead[i].right=NULL; //置空当前行指针
    }
    //置空所有列指针
    for(int i=0;i<spareMatrixByCrossLink->cols;i++)
        spareMatrixByCrossLink->colsHead[i].down=NULL;
    //修改矩阵属性
    spareMatrixByCrossLink->amount=0;
    return SUCCESS;
}
//初始化稀疏矩阵
Status init_SpareMatrixByCrossLink(SpareMatrixByCrossLink **pSpareMatrixByCrossLink,int rows,int cols){
    //判断稀疏矩阵的行数,列数是否在合法范围内 1~SPARE_MATRIX_MAX_ARRAY
    if(cols<1 || cols>MAX_SIZE_SPARE_MATRIX_CROSS_LINK)
        return FAIL;
    if(rows<1 || rows>MAX_SIZE_SPARE_MATRIX_CROSS_LINK)
        return FAIL;

    if(*pSpareMatrixByCrossLink==NULL){ //稀疏矩阵不存在，则创建
        *pSpareMatrixByCrossLink=(SpareMatrixByCrossLink *)malloc(sizeof(SpareMatrixByCrossLink));
        if(*pSpareMatrixByCrossLink==NULL)
            return FAIL;
    }else{ //矩阵存在
        //清空原矩阵
        Status opResult= empty_SpareMatrixByCrossLink(*pSpareMatrixByCrossLink);
        if(FAIL==opResult)
            return FAIL;
        //释放行头结点数组 与 列头结点数组
        free((*pSpareMatrixByCrossLink)->rowsHead);
        (*pSpareMatrixByCrossLink)->rowsHead=NULL;
        free((*pSpareMatrixByCrossLink)->colsHead);
        (*pSpareMatrixByCrossLink)->colsHead=NULL;
    }
    //创建行头结点列表
    (*pSpareMatrixByCrossLink)->rowsHead=(CrossLinkNode *)malloc(sizeof(CrossLinkNode)*rows);
    if((*pSpareMatrixByCrossLink)->rowsHead==NULL)
        return FAIL;
    for(int i=0;i<rows;i++){
        (*pSpareMatrixByCrossLink)->rowsHead[i].right=NULL;
        (*pSpareMatrixByCrossLink)->rowsHead[i].down=NULL;
    }
    //创建列头结点列表
    (*pSpareMatrixByCrossLink)->colsHead=(CrossLinkNode *)malloc(sizeof(CrossLinkNode)*cols);
    if((*pSpareMatrixByCrossLink)->colsHead==NULL)
        return FAIL;
    for(int i=0;i<cols;i++){
        (*pSpareMatrixByCrossLink)->colsHead[i].right=NULL;
        (*pSpareMatrixByCrossLink)->colsHead[i].down=NULL;
    }
    //设置矩阵参数
    (*pSpareMatrixByCrossLink)->rows=rows;
    (*pSpareMatrixByCrossLink)->cols=cols;
    (*pSpareMatrixByCrossLink)->amount=0;

    return SUCCESS;
}

//判断稀疏矩阵是否已满
int isFull_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink){
    if(spareMatrixByCrossLink->amount == spareMatrixByCrossLink->cols*spareMatrixByCrossLink->rows)
        return 1;
    else
        return 0;
}

//判断稀疏矩阵是否为空
int isEmpty_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink){
    if(spareMatrixByCrossLink->amount == 0)
        return 1;
    else
        return 0;
}
//向稀疏矩阵添加节点(节点的行号与列号从1开始计数)
Status appand_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,int row,int col,void *data){
    if(spareMatrixByCrossLink==NULL)
        return FAIL;

    //判断节点的行号与列号是否在合法范围内
    if(col<1 || col>spareMatrixByCrossLink->cols)
        return FAIL;
    if(row<1 || row>spareMatrixByCrossLink->rows)
        return FAIL;

    //判断row行，col列是否有数据，如果有就覆盖
    void *posVal=NULL;
    Status opResult= pos_SpareMatrixByCrossLink(spareMatrixByCrossLink,row,col,&posVal);
    if(SUCCESS==opResult){ //在pos位置上有元素，则修改元素
        return set_SpareMatrixByCrossLink(spareMatrixByCrossLink,row,col,data);
    }else{ //在pos位置上没有元素，则添加元素

        //创建data节点
        CrossLinkNode *dataCrossLinkNode=(CrossLinkNode *)malloc(sizeof(CrossLinkNode));
        if(dataCrossLinkNode==NULL)
            return FAIL;
        //设置data节点参数
        dataCrossLinkNode->data=data;
        dataCrossLinkNode->row=row;
        dataCrossLinkNode->col=col;
        dataCrossLinkNode->right=NULL;
        dataCrossLinkNode->down=NULL;

        //找到data节点在row行的前一个节点，并将data节点挂在其右边,
        // 在row行的前一个节点的右边节点挂在data节点的右边
        CrossLinkNode *rowCurrentLinkNode=spareMatrixByCrossLink->rowsHead[row].right; //当前行的第一个节点
        CrossLinkNode *preRowCurrentLinkNode=rowCurrentLinkNode;
        if(rowCurrentLinkNode==NULL){ //当前行为空，data元素为当前行元素的第一个节点
            spareMatrixByCrossLink->rowsHead[row].right=dataCrossLinkNode;
        }else{ //当前行不为空
            if(rowCurrentLinkNode->col > col){ //data在当前行第一个节点的左边,则data节点变为当前行的第一个节点
                dataCrossLinkNode->right=rowCurrentLinkNode;
                spareMatrixByCrossLink->rowsHead[row].right=dataCrossLinkNode;
            }else{ //(不可能出现row行列为col列的元素,即rowCurrentLinkNode->col==col)目标节点应插入row行 第一个节点的右边 ,即col > spareMatrixByCrossLink->rowsHead[row].right->col
                //找到第一个比dataCrossLinkNode->col大的元素，dataCrossLinkNode元素插入在它之左
                //或者找不到比dataCrossLinkNode->col大的元素,就挂到本行最后一个元素之右
                while(rowCurrentLinkNode!=NULL){
                    if(rowCurrentLinkNode->col > col)
                        break;
                    //preRowCurrentLinkNode指向rowCurrentLinkNode的前一个节点
                    preRowCurrentLinkNode=rowCurrentLinkNode;
                    rowCurrentLinkNode=rowCurrentLinkNode->right;
                }
                dataCrossLinkNode->right=preRowCurrentLinkNode->right;
                preRowCurrentLinkNode->right=dataCrossLinkNode;
            }
        }

        //找到data节点在col列的上一个节点，并将data节点挂在其下边,
        // 在col列的上一个节点的下一个节点挂在data节点的下边
        CrossLinkNode *colCurrentLinkNode=spareMatrixByCrossLink->colsHead[col].down; //当前列的第一个节点
        CrossLinkNode *preColCurrentLinkNode=colCurrentLinkNode;
        if(colCurrentLinkNode==NULL){ //当前列为空，data节点为当前列第一个节点
            spareMatrixByCrossLink->colsHead[col].down=dataCrossLinkNode;
        }else{ //当前列不空
            if(colCurrentLinkNode->row > row){ //data在当前行的第一个节点的上边 ,则data节点变为当前的第一个节点
                dataCrossLinkNode->down=colCurrentLinkNode;
                spareMatrixByCrossLink->rowsHead[row].down=dataCrossLinkNode;
            }else{ //(不可能出现col列为row行的元素,即rowCurrentLinkNode->row==row)目标节点应插入row行 第一个节点的下 ,即row > spareMatrixByCrossLink->rowsHead[col].down->row
                //找到第一个比dataCrossLinkNode->row大的元素，dataCrossLinkNode元素插入在它之上
                //或者找不到比dataCrossLinkNode->row大的元素,就挂到本列最后一个元素之下
                while(colCurrentLinkNode!=NULL){
                    if(rowCurrentLinkNode->row > row)
                        break;
                    //preColCurrentLinkNode指向colCurrentLinkNode的上一个节点
                    preColCurrentLinkNode=colCurrentLinkNode;
                    colCurrentLinkNode=colCurrentLinkNode->down;
                }
                dataCrossLinkNode->down=preColCurrentLinkNode->down;
                preColCurrentLinkNode->down=dataCrossLinkNode;
            }
        }

        spareMatrixByCrossLink->amount++;
        return SUCCESS;
    }
}

//通过传入二维数组构建十字链表
Status create_SpareMatrixByCrossLink(SpareMatrixByCrossLink **pSpareMatrixByCrossLink,int row,int col,void *data[][MAX_SIZE_SPARE_MATRIX_CROSS_LINK]){
    if(*pSpareMatrixByCrossLink==NULL)
        return FAIL;

    //判断节点的二维数组的行数与列数是否在合法范围内
    if(row<1 || row>MAX_SIZE_SPARE_MATRIX_CROSS_LINK)
        return FAIL;
    if(col<1 || col>MAX_SIZE_SPARE_MATRIX_CROSS_LINK)
        return FAIL;

    //将矩阵初始化为row行col列
    Status opResult= init_SpareMatrixByCrossLink(pSpareMatrixByCrossLink,row,col);
    CrossLinkNode *rowCurrentCrossLinkNode=NULL;

    //列列表，记录当前列的最下面一个节点
    CrossLinkNode **current_col_list=(CrossLinkNode *)malloc(sizeof(CrossLinkNode *)*col);
    for(int i=0;i<col;i++)
        current_col_list[i]=NULL;

    SpareMatrixByCrossLink *spareMatrixByCrossLink=*pSpareMatrixByCrossLink;
    CrossLinkNode *dataCrossLinkNode=NULL;
    //向稀疏矩阵填充数据
    for(int i=0;i<row;i++){
        rowCurrentCrossLinkNode=spareMatrixByCrossLink->rowsHead[i].right;
        for(int j=0;j<col;j++){
            //i行j列的元素非空，则创建
            if(data[i][j]!=NULL){
                //创建数据十字链表节点
                dataCrossLinkNode=(CrossLinkNode *)malloc(sizeof(CrossLinkNode));
                //设置节点参数
                dataCrossLinkNode->data=data;
                dataCrossLinkNode->col=col;
                dataCrossLinkNode->row=row;
                dataCrossLinkNode->down=NULL;
                dataCrossLinkNode->right=NULL;


                if(rowCurrentCrossLinkNode!=NULL){//当前元素为当前行的第一个元素
                    spareMatrixByCrossLink->rowsHead[i].right=dataCrossLinkNode;
                    rowCurrentCrossLinkNode=dataCrossLinkNode;
                }else{ //将data挂在当前行的最右边元素后面
                    rowCurrentCrossLinkNode->right=dataCrossLinkNode;
                    rowCurrentCrossLinkNode=dataCrossLinkNode;
                }

                //将当前元素挂在当前列节点下
                if(current_col_list[col]==NULL){ //当前元素为当前列的第一个元素
                    spareMatrixByCrossLink->colsHead[col].down=dataCrossLinkNode;
                    current_col_list[col]=dataCrossLinkNode;
                }else{ //将data挂在当前列最下面元素后面
                    current_col_list[col]->down=dataCrossLinkNode;
                    current_col_list[col]=dataCrossLinkNode;
                }

                spareMatrixByCrossLink->amount++;
            }
        }
    }

    return SUCCESS;

}

//获取稀疏矩阵row行，col列的节点数据(从1开始计数)
Status pos_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,int row,int col,void **resultData) {
    if (spareMatrixByCrossLink == NULL)
        return FAIL;

    //判断节点的行号与列号是否在合法范围内
    if(col<1 || col>spareMatrixByCrossLink->cols)
        return FAIL;
    if(row<1 || row>spareMatrixByCrossLink->rows)
        return FAIL;

    if (isEmpty_SpareMatrixByCrossLink(spareMatrixByCrossLink)) //矩阵为空，获取失败
        return FAIL;

    //遍历所有十字链表节点
    CrossLinkNode *rowCurrentLinkNode;
    //遍历每行
    for (int i = 0; i < spareMatrixByCrossLink->cols; i++) {
        //探查当前行的所有十字链表节点
        rowCurrentLinkNode = spareMatrixByCrossLink->rowsHead[i].right; //获取当前行的头结点
        while(rowCurrentLinkNode!=NULL){
            //找到目标行列的十字链表节点
            if(rowCurrentLinkNode->row==row && rowCurrentLinkNode->col==col){
                *resultData=rowCurrentLinkNode->data;
                return SUCCESS;
            }
            //继续探查本行的下个节点
            rowCurrentLinkNode=rowCurrentLinkNode->right;
        }
    }
    //探查完所有十字链表节点后还没找到
    return FAIL;
}
//设置稀疏矩阵row行,col列的节点值
Status set_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,int row,int col,void *data){
    if(spareMatrixByCrossLink==NULL)
        return FAIL;
    //判断节点的行号与列号是否在合法范围内
    if(col<1 || col>spareMatrixByCrossLink->cols)
        return FAIL;
    if(row<1 || row>spareMatrixByCrossLink->rows)
        return FAIL;
    //判断row行，col列是否有数据，如果有就覆盖
    void *posVal=NULL;
    Status opResult= pos_SpareMatrixByCrossLink(spareMatrixByCrossLink,row,col,&posVal);
    if(SUCCESS==opResult){ //在pos位置上有元素，则修改元素

        //遍历所有十字链表节点
        CrossLinkNode *rowCurrentLinkNode;
        //遍历每行
        for (int i = 0; i < spareMatrixByCrossLink->cols; i++) {
            //探查当前行的所有十字链表节点
            rowCurrentLinkNode = spareMatrixByCrossLink->rowsHead[i].right; //获取当前行的头结点
            while(rowCurrentLinkNode!=NULL){
                //找到目标行列的十字链表节点,并修改其节点值
                if(rowCurrentLinkNode->row==row && rowCurrentLinkNode->col==col){
                    rowCurrentLinkNode->data=data;
                    return SUCCESS;
                }
                //继续探查本行的下个节点
                rowCurrentLinkNode=rowCurrentLinkNode->right;
            }
        }
        return FAIL;
    }else{ //pos位置没有数据,则添加该数据
        return appand_SpareMatrixByCrossLink(spareMatrixByCrossLink,row,col,data);
    }
}
//稀疏矩阵转置
Status trans_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,COPY_DATA copyData,SpareMatrixByCrossLink **pSpareMatrixByCrossLink){
    if(spareMatrixByCrossLink==NULL)
        return FAIL;
    //将 转置矩阵初始化为 spareMatrixByCrossLink->cols行,spareMatrixByCrossLink->rows列的矩阵
    Status opResult=init_SpareMatrixByCrossLink(pSpareMatrixByCrossLink,spareMatrixByCrossLink->cols,spareMatrixByCrossLink->rows);
    if(FAIL==opResult)
        return FAIL;
    //向转置矩阵填充元素
    for(int i=0;i<spareMatrixByCrossLink->rows;i++){
        for(int j=0;j<spareMatrixByCrossLink->cols;j++){

        }
    }
}

//展示稀疏矩阵
Status show_SpareMatrixByCrossLink(SpareMatrixByCrossLink *spareMatrixByCrossLink,PRINT_DATA printData){
    if(spareMatrixByCrossLink==NULL)
        return FAIL;

    void *data=NULL;
    Status opResult=FAIL;
    //打印矩阵
    printf("\n\n");
    for(int i=0;i<spareMatrixByCrossLink->cols*(PRINT_SPAN+2)+2;i++)
        printf("_");
    printf("\n");
    for(int i=1;i<=spareMatrixByCrossLink->rows;i++){
        printf("|");
        for(int j=1;j<=spareMatrixByCrossLink->cols;j++){
            //获取矩阵i行,j列的元素
            opResult=pos_SpareMatrixByCrossLink(spareMatrixByCrossLink,i,j,&data);
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
    for(int i=0;i<spareMatrixByCrossLink->cols*(PRINT_SPAN+2)+2;i++)
        printf("_");
    printf("\n");
    printf("\n\n");
    return SUCCESS;
}

//销毁稀疏矩阵
Status destroy_SpareMatrixByCrossLink(SpareMatrixByCrossLink **pSpareMatrixByCrossLink){
    if(*pSpareMatrixByCrossLink==NULL) //稀疏矩阵不存在，无需操作直接返回
        return SUCCESS;
    //稀疏矩阵存在，清空矩阵
    Status opResult=empty_SpareMatrixByCrossLink(*pSpareMatrixByCrossLink);
    if(opResult==FAIL)
        return FAIL;
    //释放行头结点数组 与 列头结点数组
    free((*pSpareMatrixByCrossLink)->rowsHead);
    (*pSpareMatrixByCrossLink)->rowsHead=NULL;
    free((*pSpareMatrixByCrossLink)->colsHead);
    (*pSpareMatrixByCrossLink)->colsHead=NULL;
    //释放矩阵空间
    free(*pSpareMatrixByCrossLink);
    *pSpareMatrixByCrossLink=NULL;
    return SUCCESS;
}
