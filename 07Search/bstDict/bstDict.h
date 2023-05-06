//
// Created by zhouyuqing on 2023/5/2.
//

#ifdef __cplusplus
extern "C"{
#endif

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态


typedef void (*PRINT_DATA)(void *); //打印数据

#endif


#ifndef DATASTRUCTURE_HASHDICT_H
#define DATASTRUCTURE_HASHDICT_H

#include "../../04Tree/binarySortTree/binarySortTree.h"

//键值对 元素
typedef struct{
    int key;
    void *val;
}KeyVal_BSTDict;

typedef BinarySortTree Bst_Dict;
typedef BinarySortTreeNode Bst_Node;

//清空 二叉排序树字典
Status empty_BSTDict(Bst_Dict *bstDict);
//初始化 二叉排序树字典
Status init_BSTDict(Bst_Dict **pBstDict);
//设置 二叉排序树字典 中key-val对
Status set_BSTDict(Bst_Dict *bstDict,int key,void *val);
//删除 二叉排序树字典 中key-val对
Status del_BSTDict(Bst_Dict *bstDict,int key);
//获取 二叉排序树字典 中key-val对
Status get_BSTDict(Bst_Dict *bstDict,int key,void **val);

#endif //DATASTRUCTURE_HASHDICT_H

#ifdef __cplusplus
}
#endif