//
// Created by zhouyuqing on 2023/3/21.
//

#include "dictByBinarySortTree.h"

//设置字典key对应的值
//设置节点为data为id的节点的值为value 到二叉排序树
//Status setNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_ID_BINARY_SORT_TREE compare_id,void *id,void *value){
//    if(binarySortTree==NULL)
//        return FAIL;
//    if(binarySortTree->amountNodes==0) //树为空，设置节点值失败
//        return FAIL;
//
//    //查找data为id的节点
//    BinarySortTreeNode *binarySortTreeNode= search(binarySortTree->rootNode,compare_id,id);
//    //如果data为id的节点存在则修改值
//    if(binarySortTreeNode!=NULL){
//        binarySortTreeNode->value=value;
//        return SUCCESS;
//    }else
//        return FAIL;
//}

