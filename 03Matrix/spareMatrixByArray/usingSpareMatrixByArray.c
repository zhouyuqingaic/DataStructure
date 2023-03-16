//
// Created by zhouyuqing on 2023/3/15.
//

#include"spareMatrixByArray.h"


void printItemSpareMatrixByArray(void *data){
    printf(" val:%4d ",*((int *)data) );
}

//复制data到result
Status copyItemSpareMatrixByArray(void *data,void **result){
    if(data==NULL)
        return FAIL;

    //创建数据空间
    int *resultData=(int *)malloc(sizeof(int));
    if(resultData==NULL)
        return FAIL;
    *resultData=*( (int *)data );
    //返回结果
    *result=resultData;
    return SUCCESS;
}

void usingSpareMatrixByArray(){
    /*
     * SpareMatrixByArray测试&使用案例
     */
    SpareMatrix *spareMatrix=NULL;
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

    Status opResult=init_SpareMatrix(&spareMatrix,4,5);
    if(FAIL==opResult){
        printf("初始化稀疏矩阵失败\n");
        return;
    }

    opResult= appand_SpareMatrix(spareMatrix,1,1,d1_1);
    if(FAIL==opResult)
        printf("稀疏矩阵添加%d失败\n",*d1_1);
    opResult= appand_SpareMatrix(spareMatrix,3,1,d3_1);
    if(FAIL==opResult)
        printf("稀疏矩阵添加%d失败\n",*d3_1);
    opResult= appand_SpareMatrix(spareMatrix,3,1,d2_3);
    if(FAIL==opResult)
        printf("稀疏矩阵添加%d失败\n",*d2_3);
    opResult= appand_SpareMatrix(spareMatrix,3,4,d3_4);
    if(FAIL==opResult)
        printf("稀疏矩阵添加%d失败\n",*d3_4);

    opResult= show_SpareMatrix(spareMatrix,printItemSpareMatrixByArray);
    if(FAIL==opResult){
        printf("展示稀疏矩阵失败\n");
        return;
    }

    printf("\n--------------------------------------1------------------------------------------\n");

    SpareMatrix *spareMatrixTrans=NULL;
    opResult= trans_SpareMatrix(spareMatrix,copyItemSpareMatrixByArray,&spareMatrixTrans);
    if(FAIL==opResult){
        printf("矩阵转置失败\n");
        return;
    }

    int *d5_1=(int *)malloc(sizeof(int));
    pList[indexPList++]=d5_1;
    *d5_1=51;
    int *d5_3=(int *)malloc(sizeof(int));
    pList[indexPList++]=d5_3;
    *d5_3=53;


    opResult= appand_SpareMatrix(spareMatrix,5,1,d5_1);
    if(FAIL==opResult)
        printf("稀疏矩阵spareMatrix添加%d失败\n",*d5_1);

    opResult= appand_SpareMatrix(spareMatrixTrans,5,1,d5_1);
    if(FAIL==opResult)
        printf("稀疏矩阵spareMatrixTrans添加%d失败\n",*d5_1);
    opResult= appand_SpareMatrix(spareMatrixTrans,5,3,d5_3);
    if(FAIL==opResult)
        printf("稀疏矩阵spareMatrixTrans添加%d失败\n",*d5_3);


    opResult= show_SpareMatrix(spareMatrixTrans,printItemSpareMatrixByArray);
    if(FAIL==opResult){
        printf("展示转置稀疏矩阵失败\n");
        return;
    }

    printf("\n--------------------------------------2------------------------------------------\n");

    opResult= trans_SpareMatrix(spareMatrixTrans,copyItemSpareMatrixByArray,&spareMatrix);
    if(FAIL==opResult){
        printf("矩阵转置失败\n");
        return;
    }
    opResult= show_SpareMatrix(spareMatrix,printItemSpareMatrixByArray);
    if(FAIL==opResult){
        printf("展示转置稀疏矩阵失败\n");
        return;
    }

    printf("\n--------------------------------------3------------------------------------------\n");

    int *d2_3_new=(int *)malloc(sizeof(int));
    pList[indexPList++]=d2_3_new;
    *d2_3_new=2300;
    opResult= set_SpareMatrix(spareMatrix,2,3,d2_3_new);
    if(FAIL==opResult){
        printf("设置spareMatrix矩阵%d行%d列的值为%d失败\n",2,3,*d2_3_new);
        return;
    }
    int *d3_4_new=(int *)malloc(sizeof(int));
    pList[indexPList++]=d3_4_new;
    *d3_4_new=3400;
    opResult= set_SpareMatrix(spareMatrix,3,4,d3_4_new);
    if(FAIL==opResult){
        printf("设置spareMatrix矩阵%d行%d列的值为%d失败\n",3,4,*d3_4_new);
    }
    int *d1_2=(int *)malloc(sizeof(int));
    pList[indexPList++]=d1_2;
    *d1_2=12;
    opResult= set_SpareMatrix(spareMatrix,1,2,d1_2);
    if(FAIL==opResult){
        printf("设置spareMatrix矩阵%d行%d列的值为%d失败\n",1,2,*d1_2);
    }
    int *d9_9=(int *)malloc(sizeof(int));
    pList[indexPList++]=d9_9;
    *d9_9=99;
    opResult= set_SpareMatrix(spareMatrix,9,9,d9_9);
    if(FAIL==opResult){
        printf("设置spareMatrix矩阵%d行%d列的值为%d失败\n",9,9,*d9_9);
    }

    opResult= show_SpareMatrix(spareMatrix,printItemSpareMatrixByArray);
    if(FAIL==opResult){
        printf("展示转置稀疏矩阵失败\n");
        return;
    }

    printf("\n--------------------------------------4------------------------------------------\n");

    for(int i=0;i<indexPList;i++) {
        free(pList[i]);
        pList[i]=NULL;
    }

    opResult=destroy_SpareMatrix(&spareMatrix);
    if(opResult==FAIL){
        printf("销毁spareMatrix失败\n");
        return;
    }
    opResult=destroy_SpareMatrix(&spareMatrixTrans);
    if(opResult==FAIL){
        printf("销毁spareMatrixTrans失败\n");
        return;
    }
    if(spareMatrix==NULL && spareMatrixTrans==NULL)
        printf("结束\n");

}

void main(){
    usingSpareMatrixByArray();
}


