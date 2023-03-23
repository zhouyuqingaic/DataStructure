//
// Created by zhouyuqing on 2023/3/21.
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

#ifndef DATASTRUCTURE_BINARYSORTTREE_H
#define DATASTRUCTURE_BINARYSORTTREE_H

#include"../binaryTree/binaryTree.h"

//比较两个DATA大小，第一个大于第二个则返回1，等于0，小于-1
typedef int (*COMPAR_DATA_BINARY_SORT_TREE)(void *,void *);

//二叉排序树节点
typedef BinaryTreeNode BinarySortTreeNode;
//二叉排序树
typedef BinaryTree BinarySortTree;

//清空二叉排序树
Status empty_BinarySortTree(BinarySortTree *binarySortTree);
//初始化二叉排序树
Status init_BinarySortTree(BinarySortTree **binarySortTree);

//搜索二叉排序树
Status getNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *data,BinarySortTreeNode **resultNode);
//添加data节点到二叉排序树
Status appendNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *data);
//删除data节点(递归方法)
Status deleteNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *data);
//获取排序后的data
Status sortedDatas_BinarySortTree(BinarySortTree *binarySortTree,void ***sortedDatas);

//通过传入data列表创建二叉排序树
Status create_BinarySortTree(BinarySortTree **pBinarySortTree,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *datas[],int n);

//销毁二叉排序树
Status destroy_BinarySortTree(BinarySortTree **pBinarySortTree);

#endif //DATASTRUCTURE_BINARYSORTTREE_H

#ifdef __cplusplus
}
#endif