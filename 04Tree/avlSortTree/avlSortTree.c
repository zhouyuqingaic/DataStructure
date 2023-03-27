//
// Created by zhouyuqing on 2023/3/23.
//

#include "avlSortTree.h"

//清空平衡二叉树
Status empty_AVLSortTree(AVLSortTree *avlSortTree){
    return empty_BinarySortTree(avlSortTree);
}
//初始化平衡二叉树
Status init_AVLSortTree(AVLSortTree **pAvlSortTree){
    return init_BinarySortTree(pAvlSortTree);
}
//搜索平衡二叉树
Status getNode_AVLSortTree(AVLSortTree *avlSortTree,COMPARE_DATA_AVL_SORT_TREE compare_data,void *data,AVLSortTreeNode **resultNode){
    return getNode_BinarySortTree(avlSortTree,compare_data,data,resultNode);
}

//LL情况,右单旋转操作
//在*pRootNode的左孩子的左子树下加入了新节点，导致*pRootNode的平衡因子由1变成2
Status R_Rotate(AVLSortTreeNode **pRootNode){
    //对以 *pRootNode 为根的二叉排序子树执行右旋操作
    //获取根左节点
    AVLSortTreeNode *lChildRootNode=(*pRootNode)->lChild;
    //必须要根左节点不空，才能正常右旋
    if(lChildRootNode==NULL)
        return FAIL;
    //根节点的左节点 指向 根左节点的右节点
    (*pRootNode)->lChild=lChildRootNode->rChild;
    //根左节点 的右节点 指向 根节点
    lChildRootNode->rChild=(*pRootNode);
    //将根左节点 作为 新的根(更新指向子树根的 父节点的左或右指针 所指向的位置)
    *pRootNode=lChildRootNode;
//
//    //设置平衡因子值
//    (*pRootNode)->bf=0;
//    (*pRootNode)->rChild->bf=0;
//
    return SUCCESS;
}
//RR情况,左单旋转操作
//在*pRootNode的右孩子的右子树下加入了新节点，导致*pRootNode的平衡因子由-1变成-2
Status L_Rotate(AVLSortTreeNode **pRootNode){
    //对以 *pRootNode 为根的二叉排序子树执行左旋操作
    //获取根右节点
    AVLSortTreeNode *rChildRootNode=(*pRootNode)->rChild;
    //必须要根右节点不空，才能正常左旋
    if(rChildRootNode==NULL)
        return FAIL;
    //根节点的右节点 指向 根右节点的左节点
    (*pRootNode)->lChild=rChildRootNode->lChild;
    //根右节点 的左节点 指向 根节点
    rChildRootNode->lChild=(*pRootNode);
    //将根右节点 作为 新的根(更新指向子树根的 父节点的左或右指针 所指向的位置)
    *pRootNode=rChildRootNode;
//
//    //设置平衡因子值
//    (*pRootNode)->bf=0;
//    (*pRootNode)->lChild->bf=0;
//
    return SUCCESS;
}
//LR情况,先左旋后右旋
//在*pRootNode的左孩子的右子树下加入了新节点，导致*pRootNode的平衡因子由1变成2
Status LR_Rotate(AVLSortTreeNode **pRootNode){
    //对 根左节点 为根 构成的子树 进行左旋操作
    Status opResult=L_Rotate(&( (*pRootNode)->lChild ) );
    if(FAIL==opResult)
        return FAIL;
    //对 当前子树(根节点为根的子树) 进行右旋操作
    opResult=R_Rotate(pRootNode);
    if(FAIL==opResult)
        return FAIL;
    return SUCCESS;
}
//RL情况,先右旋后左旋
//在*pRootNode的右孩子的左子树下加入了新节点，导致*pRootNode的平衡因子由-1变成-2
Status RL_Rotate(AVLSortTreeNode **pRootNode){
    //对 根右节点 为根 构成的子树 进行右旋操作
    Status opResult= R_Rotate(&( (*pRootNode)->rChild ));
    if(FAIL==opResult)
        return FAIL;
    //对 当前子树(根节点为根的子树) 进行左旋操作
    opResult= L_Rotate(pRootNode);
    if(FAIL==opResult)
        return FAIL;
    return SUCCESS;
}



//添加节点
Status append(AVLSortTreeNode **pAvlSortTreeNode,COMPARE_DATA_AVL_SORT_TREE compare_data,AVLSortTreeNode *dataNode){
    if(*pAvlSortTreeNode==NULL){ //找到叶节点位置，插入data节点
        *pAvlSortTreeNode=dataNode;
        return SUCCESS;
    }else{
        int compareResult=compare_data( (*pAvlSortTreeNode)->data,dataNode->data);
        AVLSortTreeNode **temp=NULL;

    }
}


//添加data节点到平衡二叉树
Status appendNode_AVLSortTree(AVLSortTree *avlSortTree,COMPARE_DATA_AVL_SORT_TREE compare_data,void *data){
    if(avlSortTree==NULL)
        return FAIL;
    AVLSortTreeNode *avlSortTreeNode=NULL;
    if(avlSortTree->rootNode==NULL){ //平衡二叉树为空，直接添加节点
        //创建平衡二叉树节点
        avlSortTreeNode=(AVLSortTreeNode *)malloc(sizeof(AVLSortTreeNode));
        if(avlSortTreeNode==NULL)
            return FAIL;
        avlSortTreeNode->data=data;
//        avlSortTreeNode->testingData=*((int *)data);
        avlSortTreeNode->rChild=NULL;
        avlSortTreeNode->lChild=NULL;
        avlSortTreeNode->bf=0;

        //将其作为树的根节点
        avlSortTree->rootNode=avlSortTreeNode;
        avlSortTree->amountNodes++;

        return SUCCESS;
    }else{ //树不为空

        //查找data节点是否存在
        Status opResult= getNode_AVLSortTree(avlSortTree,compare_data,data,&avlSortTreeNode);
        if(FAIL==opResult) {
            //data节点在二叉排序树中不存在,加入data节点
            avlSortTreeNode=(AVLSortTreeNode *)malloc(sizeof(AVLSortTreeNode));
            if(avlSortTreeNode==NULL)
                return FAIL;
            avlSortTreeNode->data=data;
            avlSortTreeNode->testingData=*((int *)data);
            avlSortTreeNode->rChild=NULL;
            avlSortTreeNode->lChild=NULL;

            //data节点插入目标叶节点位置


        }else{
            //data节点在二叉树中存在，加入失败
            return FAIL;
        }
    }
}
//删除data节点
Status deleteNode_AVLSortTree(AVLSortTree *avlSortTree,COMPARE_DATA_AVL_SORT_TREE compare_data,void *data){
    return deleteNode_BinarySortTree(avlSortTree,compare_data,data);
}
//获取排序后的data
Status sortedDatas_AVLSortTree(AVLSortTree *avlSortTree,void ***pSortedDatas){
    return sortedDatas_BinarySortTree(avlSortTree,pSortedDatas);
}
//通过传入data列表创建平衡二叉树
Status create_AVLSortTree(AVLSortTree **pAvlSortTree,COMPARE_DATA_AVL_SORT_TREE compare_data,void *dates[],int n){
    //初始化平衡二叉树
    Status opResult= init_AVLSortTree(pAvlSortTree);
    if(opResult==FAIL)
        return FAIL;
    AVLSortTree *avlSortTree=*pAvlSortTree;
    //将data数据加入平衡二叉树中
    for(int i=0;i<n;i++){
        opResult= appendNode_AVLSortTree(avlSortTree,compare_data,dates[i]);
        if(FAIL==opResult)
            return FAIL;
    }
    //全部数据添加成功
    return SUCCESS;
}
//销毁平衡二叉树
Status destroy_AVLSortTree(AVLSortTree **pAvlSortTree){
    return destroy_BinarySortTree(pAvlSortTree);
}



