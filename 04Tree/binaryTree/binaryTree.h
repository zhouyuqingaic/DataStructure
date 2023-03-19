//
// Created by zhouyuqing on 2023/3/18.
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



#ifndef DATASTRUCTURE_BINARYTREE_H
#define DATASTRUCTURE_BINARYTREE_H

#include<malloc.h>


typedef struct _BINARY_TREE_NODE{
    void *data;     //节点的数据
    struct _BINARY_TREE_NODE *lChild;  //二叉树节点的右孩子
    struct _BINARY_TREE_NODE *rChild;  //二叉树节点的左孩子
}BinaryTreeNode; //二叉树节点

typedef struct{
     BinaryTreeNode *rootNode; //二叉树根节点
     int amountNodes; //二叉树节点个数
}BinaryTree; //二叉树

//清空二叉树
Status empty_BinaryTree(BinaryTree *binaryTree);
//初始化二叉树
Status init_BinaryTree(BinaryTree **pBinaryTree);

//将dataList视为完全二叉树遍历的结果，来创建完全二叉树
Status generate_BinaryTree(BinaryTree **pBinaryTree,void **dataList,int lengthDataList);

//二叉树非递归先序遍历,orderList返回遍历data序列
Status preOrder_BinaryTree(BinaryTree *binaryTree,void ***pOrderList);
//二叉树非递归中序遍历,orderList返回遍历data序列
Status inOrder_BinaryTree(BinaryTree *binaryTree,void ***pOrderList);
//二叉树非递归后序遍历,orderList返回遍历data序列
Status postOrder_BinaryTree(BinaryTree *binaryTree,void ***pOrderList);

//二叉树递归先序遍历,orderList返回遍历data序列
Status preOrder_R_BinaryTree(BinaryTree *binaryTree,void ***pOrderList);
//二叉树递归中序遍历,orderList返回遍历data序列
Status inOrder_R_BinaryTree(BinaryTree *binaryTree,void ***pOrderList);
//二叉树递归后序遍历,orderList返回遍历data序列
Status postOrder_R_BinaryTree(BinaryTree *binaryTree,void ***pOrderList);


//二叉树层次遍历,orderList返回遍历data序列
Status levelOrder_BinaryTree(BinaryTree *binaryTree,void ***pOrderList);

//销毁二叉树
Status destroy_BinaryTree(BinaryTree **pBinaryTree);

#endif //DATASTRUCTURE_BINARYTREE_H

#ifdef __cplusplus
}
#endif