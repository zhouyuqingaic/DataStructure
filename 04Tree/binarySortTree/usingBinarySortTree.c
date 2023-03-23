//
// Created by zhouyuqing on 2023/3/21.
//

#include"binarySortTree.h"


void printItemBinarySortTree(void *data){
    printf("%8d",*( (int *)data ));
}

//比较data1与data2
//data1>data2 返回1
//data1=data2 返回0
//data1<data2 返回-1
int compareDataBinarySortTree(void *data1,void *data2){
    int d1_data=*((int *)data1);
    int d2_data=*((int *)data2);

    if(d1_data>d2_data)
        return 1;
    else if(d1_data<d2_data)
        return -1;
    else
        return 0;
}


void usingBinarySortTree(){
    /*
     * 二叉排序树BinarySortTree 使用&测试 案例
     */
    BinarySortTree *binarySortTree=NULL;

    Status opResult=init_BinarySortTree(&binarySortTree);
    if(FAIL==opResult){
        perror("初始化二叉排序树失败!\n");
        return;
    }

    //填充测试数据
    int *dataList[10];
    for(int i=0;i<10;i+=2){
        dataList[i]=(int *)malloc(sizeof(int));
        *(dataList[i])=i+100;
    }
    for(int i=1;i<10;i+=2){
        dataList[i]=(int *)malloc(sizeof(int));
        *(dataList[i])=i+50;
    }

    printf("原始data数据:\n\t");
    for(int i=0;i<10;i++)
        printItemBinarySortTree(dataList[i]);
    printf("\n");

    for(int i=0;i<10;i++){
        opResult= appendNode_BinarySortTree(binarySortTree,compareDataBinarySortTree,dataList[i]);
        if(opResult==FAIL){
            printf("添加");
            printItemBinarySortTree(dataList[i]);
            printf("节点到二叉排序树失败!\n");
        }
    }

    printf("\n获取二叉排序树结果:\n\t");
    void **sortedDatas=NULL;
    opResult= sortedDatas_BinarySortTree(binarySortTree,&sortedDatas);
    if(FAIL==opResult)
        printf("获取二叉排序树 排序结果失败\n");
    else{
        for(int i=0;i<binarySortTree->amountNodes;i++)
            printItemBinarySortTree(sortedDatas[i]);
        printf("\n");
    }

    printf("\n按照data获取二叉排序树节点:\n\t");
    BinarySortTreeNode *tempNode=NULL;
    for(int i=0;i<binarySortTree->amountNodes;i++){
        opResult=getNode_BinarySortTree(binarySortTree,compareDataBinarySortTree,sortedDatas[i],&tempNode);
        if(FAIL==opResult){
            printf("\n从二叉排序树获取");
            printItemBinarySortTree(dataList[i]);
            printf("节点失败!\n");
        }else
            printItemBinarySortTree(tempNode->data);
    }
    printf("\n");

    printf("\n-----------------------------------1-----------------------------------\n");

    //填充测试数据02
    int *dataList02[10];
    int tempList02[10]={29,24,35,33,19,27,26,28,39,34};
    for(int i=0;i<10;i++){
        dataList02[i]=(int *)malloc(sizeof(int));
        *(dataList02[i])=tempList02[i];
    }
    printf("原始data数据:\n\t");
    for(int i=0;i<10;i++)
        printItemBinarySortTree(dataList02[i]);
    printf("\n");

    opResult= create_BinarySortTree(&binarySortTree,compareDataBinarySortTree,dataList02,10);
    if(FAIL==opResult){
        printf("利用dataList创建数据失败\n");
        return;
    }

    printf("\n获取二叉排序树结果:\n\t");
    opResult= sortedDatas_BinarySortTree(binarySortTree,&sortedDatas);
    if(FAIL==opResult)
        printf("获取二叉排序树 排序结果失败\n");
    else{
        for(int i=0;i<binarySortTree->amountNodes;i++)
            printItemBinarySortTree(sortedDatas[i]);
        printf("\n");
    }

    printf("\n-----------------------------------2-----------------------------------\n");


    void *temp=NULL;
    for(int i=0;i<4;i++) {
        temp=dataList[i];
        opResult = deleteNode_BinarySortTree(binarySortTree, compareDataBinarySortTree, temp);
        if (SUCCESS == opResult) {
            printf("销毁");
            printItemBinarySortTree(temp);
            printf("节点成功\n");
        } else {
            printf("销毁");
            printItemBinarySortTree(temp);
            printf("节点失败\n");
        }

        printf("\n获取删除节点后二叉排序树结果:\n\t");
        opResult = sortedDatas_BinarySortTree(binarySortTree, &sortedDatas);
        if (FAIL == opResult)
            printf("获取删除节点后二叉排序树 排序结果失败\n");
        else {
            for (int i = 0; i < binarySortTree->amountNodes; i++)
                printItemBinarySortTree(sortedDatas[i]);
            printf("\n");
        }
        printf("\n-----*-----\n");
    }

    for(int i=0;i<10;i++) {
        temp=dataList02[i];
        int testingData=*((int *)temp);
        opResult = deleteNode_BinarySortTree(binarySortTree, compareDataBinarySortTree, temp);
        if (SUCCESS == opResult) {
            printf("销毁");
            printItemBinarySortTree(temp);
            printf("节点成功\n");
        } else {
            printf("销毁");
            printItemBinarySortTree(temp);
            printf("节点失败\n");
        }

        printf("\n获取删除节点后二叉排序树结果:\n\t");
        opResult = sortedDatas_BinarySortTree(binarySortTree, &sortedDatas);
        if (FAIL == opResult)
            printf("获取删除节点后二叉排序树 排序结果失败\n");
        else {
            for (int i = 0; i < binarySortTree->amountNodes; i++)
                printItemBinarySortTree(sortedDatas[i]);
            printf("\n");
        }
        printf("\n-----*-----\n");
    }

    printf("\n-----------------------------------3-----------------------------------\n");

    //填充测试数据03
    int *dataList03[10];
    int tempList03[10]={4,9,5,12,1,2,6,11,14,15};

    //填充测试数据
    for(int i=0;i<10;i++){
        dataList03[i]=(int *)malloc(sizeof(int));
        *(dataList03[i])=tempList03[i];
    }

    printf("原始data数据:\n\t");
    for(int i=0;i<10;i++)
        printItemBinarySortTree(dataList03[i]);
    printf("\n");

    opResult= create_BinarySortTree(&binarySortTree,compareDataBinarySortTree,dataList03,10);
    if(FAIL==opResult){
        printf("利用dataList创建数据失败\n");
        return;
    }

    printf("\n获取二叉排序树结果:\n\t");
    opResult= sortedDatas_BinarySortTree(binarySortTree,&sortedDatas);
    if(FAIL==opResult)
        printf("获取二叉排序树 排序结果失败\n");
    else{
        for(int i=0;i<binarySortTree->amountNodes;i++)
            printItemBinarySortTree(sortedDatas[i]);
        printf("\n");
    }



    for(int i=0;i<4;i++) {
        temp=dataList02[i];
        opResult = deleteNode_BinarySortTree(binarySortTree, compareDataBinarySortTree, temp);
        if (SUCCESS == opResult) {
            printf("(递归方式)销毁");
            printItemBinarySortTree(temp);
            printf("节点成功\n");
        } else {
            printf("(递归方式)销毁");
            printItemBinarySortTree(temp);
            printf("节点失败\n");
        }

        printf("\n获取删除节点后二叉排序树结果:\n\t");
        opResult = sortedDatas_BinarySortTree(binarySortTree, &sortedDatas);
        if (FAIL == opResult)
            printf("获取删除节点后二叉排序树 排序结果失败\n");
        else {
            for (int i = 0; i < binarySortTree->amountNodes; i++)
                printItemBinarySortTree(sortedDatas[i]);
            printf("\n");
        }
        printf("\n-----*-----\n");
    }

    for(int i=0;i<10;i++) {
        temp=dataList03[i];
        opResult = deleteNode_BinarySortTree(binarySortTree, compareDataBinarySortTree, temp);
        if (SUCCESS == opResult) {
            printf("(递归方式)销毁");
            printItemBinarySortTree(temp);
            printf("节点成功\n");
        } else {
            printf("(递归方式)销毁");
            printItemBinarySortTree(temp);
            printf("节点失败\n");
        }

        printf("\n获取删除节点后二叉排序树结果:\n\t");
        opResult = sortedDatas_BinarySortTree(binarySortTree, &sortedDatas);
        if (FAIL == opResult)
            printf("获取删除节点后二叉排序树 排序结果失败\n");
        else {
            for (int i = 0; i < binarySortTree->amountNodes; i++)
                printItemBinarySortTree(sortedDatas[i]);
            printf("\n");
        }
        printf("\n-----*-----\n");
    }


    printf("\n-----------------------------------4-----------------------------------\n");

    //销毁数据data
    for(int i=0;i<10;i++){
        free(dataList[i]);
        free(dataList02[i]);
    }
    //销毁排序列表
    free(sortedDatas);
    //销毁二叉排序树
    opResult= destroy_BinarySortTree(&binarySortTree);
    if(FAIL==opResult){
        printf("销毁二叉排序树失败!\n");
    }
    printf("销毁所有创建数据成功!");
}

//void main(){
//    usingBinarySortTree();
//}