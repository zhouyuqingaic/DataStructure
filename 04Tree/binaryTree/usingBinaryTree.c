//
// Created by zhouyuqing on 2023/3/18.
//

#include "binaryTree.h"

void printItemBinaryTree(void *data){
    printf("%8d",*( (int *)data ));
}

void usingBinayrTree(){
    /*
     * 二叉树使用&测试 案例
     */
    BinaryTree *binaryTree01=NULL;
    Status opResult=init_BinaryTree(&binaryTree01);
    if(FAIL==opResult){
        perror("初始化二叉树失败\n");
        return;
    }

    //创建测试数据队列
    int **intList=(int *)malloc(sizeof(int *)*10);
    for(int i=0;i<10;i++){
        intList[i]=(int *)malloc(sizeof(int));
        if(intList[i]==NULL)
            return;
        *(intList[i])=i+100;
    }

    opResult= generate_BinaryTree(&binaryTree01,intList,10);
    if(FAIL==opResult)
        return;

    printf("\nbinaryTree01->amountNodes:%d\n",binaryTree01->amountNodes);

    void **orderList=NULL;

    //获取并展示层次遍历序列
    opResult=levelOrder_BinaryTree(binaryTree01,&orderList);
    if(FAIL==opResult) {
        perror("获取层次遍历序列失败\n");
        return;
    }else {
        printf("层次遍历序列为:\n\t");
        for (int i = 0; i < binaryTree01->amountNodes; i++)
            printItemBinaryTree(orderList[i]);
        printf("\n");
    }

    //获取并展示先序遍历序列(递归法)
    opResult= preOrder_R_BinaryTree(binaryTree01,&orderList);
    if(FAIL==opResult) {
        perror("获取先序遍历序列(递归法)失败\n");
        return;
    }else {
        printf("先序遍历序列(递归法)为:\n\t");
        for (int i = 0; i < binaryTree01->amountNodes; i++)
            printItemBinaryTree(orderList[i]);
        printf("\n");
    }

    //获取并展示中序遍历序列(递归法)
    opResult= inOrder_R_BinaryTree(binaryTree01,&orderList);
    if(FAIL==opResult) {
        perror("获取中序遍历序列(递归法)失败\n");
        return;
    }else {
        printf("中序遍历序列(递归法)为:\n\t");
        for (int i = 0; i < binaryTree01->amountNodes; i++)
            printItemBinaryTree(orderList[i]);
        printf("\n");
    }

    //获取并展示后序遍历序列(递归法)
    opResult= postOrder_R_BinaryTree(binaryTree01,&orderList);
    if(FAIL==opResult) {
        perror("获取后序遍历序列(递归法)失败\n");
        return;
    }else {
        printf("后序遍历序列(递归法)为:\n\t");
        for (int i = 0; i < binaryTree01->amountNodes; i++)
            printItemBinaryTree(orderList[i]);
        printf("\n");
    }

    printf("\n------------------------------------1------------------------------------\n");

    //获取并展示先序遍历序列(非递归法)
    opResult= preOrder_BinaryTree(binaryTree01,&orderList);
    if(FAIL==opResult) {
        perror("获取先序遍历序列(非递归法)失败\n");
        return;
    }else {
        printf("先序遍历序列(非递归法)为:\n\t");
        for (int i = 0; i < binaryTree01->amountNodes; i++)
            printItemBinaryTree(orderList[i]);
        printf("\n");
    }

    //获取并展示中序遍历序列(非递归法)
    opResult= inOrder_BinaryTree(binaryTree01,&orderList);
    if(FAIL==opResult) {
        perror("获取中序遍历序列(非递归法)失败\n");
        return;
    }else {
        printf("中序遍历序列(非递归法)为:\n\t");
        for (int i = 0; i < binaryTree01->amountNodes; i++)
            printItemBinaryTree(orderList[i]);
        printf("\n");
    }

    //获取并展示后序遍历序列(非递归法)
    opResult= postOrder_BinaryTree(binaryTree01,&orderList);
    if(FAIL==opResult) {
        perror("获取后序遍历序列(非递归法)失败\n");
        return;
    }else {
        printf("后序遍历序列(非递归法)为:\n\t");
        for (int i = 0; i < binaryTree01->amountNodes; i++)
            printItemBinaryTree(orderList[i]);
        printf("\n");
    }

    printf("\n------------------------------------1------------------------------------\n");

    //释放访问列表
    free(orderList);
    orderList=NULL;

    //释放所有数据
    for(int i=0;i<10;i++)
        free(intList[i]);

    opResult= destroy_BinaryTree(&binaryTree01);
    if(FAIL==opResult){
        perror("销毁二叉树失败");
        return;
    }else{
        printf("销毁二叉树成功!\n");
        return;
    }
}




//void main(){
//
//    usingBinayrTree();
//}
