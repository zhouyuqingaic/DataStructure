//
// Created by zhouyuqing on 2023/3/23.
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


#ifndef DATASTRUCTURE_AVLTREE_H
#define DATASTRUCTURE_AVLTREE_H

#include "../binaryTree/binaryTree.h"

//比较两个DATA大小，第一个大于第二个则返回1，等于0，小于-1
typedef int (*COMPARE_DATA_AVL_SORT_TREE)(void *,void *);

//二叉排序树节点
//节点平衡因子值为-1,0,1
//只要二叉树上有一个结点的平衡因子绝对值大于1,节点就是不平衡的
typedef BinaryTreeNode AVLSortTreeNode;
//二叉排序树
typedef BinaryTree AVLSortTree;

//清空平衡二叉树
Status empty_AVLSortTree(AVLSortTree *avlSortTree);
//初始化平衡二叉树
Status init_AVLSortTree(AVLSortTree **pAvlSortTree);

//搜索平衡二叉树
Status getNode_AVLSortTree(AVLSortTree *avlSortTree,COMPARE_DATA_AVL_SORT_TREE compare_data,AVLSortTreeNode **resultNode);
//添加data节点到平衡二叉树
Status appendNode_AVLSortTree(AVLSortTree *avlSortTree,COMPARE_DATA_AVL_SORT_TREE compare_data,void *data);
//删除data节点
Status deleteNode_AVLSortTree(AVLSortTree *avlSortTree,COMPARE_DATA_AVL_SORT_TREE compare_data,void *data);
//获取排序后的data
Status sortedDatas_AVLSortTree(AVLSortTree *avlSortTree,void **sortedDatas);

//通过传入data列表创建平衡二叉树
Status create_AVLSortTree(AVLSortTree **pAvlSortTree,COMPARE_DATA_AVL_SORT_TREE compare_data,void *dates[],int n);

//销毁平衡二叉树
Status destroy_AVLSortTree(AVLSortTree **pAvlSortTree);

#endif //DATASTRUCTURE_AVLTREE_H


#ifdef __cplusplus
}
#endif