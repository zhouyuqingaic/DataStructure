//
// Created by zhouyuqing on 2023/5/2.
//
#include "bstDict.h"

//比较两个键值对元素,第一个key 大于 第二个key 则返回1，等于0，小于-1
int compare_keyval_bst_dict(void *a,void *b){
    KeyVal_BSTDict *keyVal_1=(KeyVal_BSTDict *)a;
    KeyVal_BSTDict *keyVal_2=(KeyVal_BSTDict *)b;
    if(keyVal_1->key > keyVal_2->key)
        return 1;
    else if(keyVal_1->key < keyVal_2->key)
        return -1;
    else
        return 0;
}

//清空 二叉排序树字典
Status empty_BSTDict(Bst_Dict *bstDict){
    return empty_BinarySortTree(bstDict);
}

//初始化 二叉排序树字典
Status init_BSTDict(Bst_Dict **pBstDict){
    return init_BinarySortTree(pBstDict);
}

//搜索节点
BinarySortTreeNode *search_bst_dict(BinarySortTreeNode *rootNode,void *data){
    while(
        rootNode!=NULL
        &&
        compare_keyval_bst_dict(rootNode->data,data)!=0
    ){
        if(
            compare_keyval_bst_dict(rootNode->data,data)==1
        )
            rootNode=rootNode->lChild;
        else
            rootNode=rootNode->rChild;
    }
    return rootNode;
}

//添加节点
Status insert_bst_dict(BinarySortTreeNode **pBinarySortTreeNode,void *data){
    //找到插入的叶节点位置
    if(*pBinarySortTreeNode==NULL){
        *pBinarySortTreeNode=(BinarySortTreeNode *)malloc(sizeof(BinarySortTreeNode));
        if(*pBinarySortTreeNode==NULL)
            return FAIL;
        (*pBinarySortTreeNode)->data=data;
        (*pBinarySortTreeNode)->lChild=NULL;
        (*pBinarySortTreeNode)->rChild=NULL;
        return SUCCESS;
    }else{
        int compareResult= compare_keyval_bst_dict((*pBinarySortTreeNode)->data,data);
        if(compareResult==1){ //compareResult==1 当前节点的数据 大于 data
            return insert_bst_dict(
                    &((*pBinarySortTreeNode)->lChild),
                    data);
        }else if(compareResult==-1){ //compareResult==-1 当前节点的数据 小于 data
            return insert_bst_dict(
                    &((*pBinarySortTreeNode)->rChild),
                    data);
        }else{
            //当前数组为data的节点已经存在，加入排序树失败
            return FAIL;
        }
    }
}

//设置 二叉排序树字典 中key-val对
Status set_BSTDict(Bst_Dict *bstDict,int key,void *val){
    if(bstDict==NULL)
        return FAIL;
    BinarySortTreeNode  *binarySortTreeNode=NULL;

    if(bstDict->rootNode==NULL){ //如果二叉排序树为空,直接添加节点
        //创建排序树节点
        binarySortTreeNode=(BinarySortTreeNode *)malloc(sizeof(BinarySortTreeNode));
        if(binarySortTreeNode==NULL)
            return FAIL;
        binarySortTreeNode->data=(KeyVal_BSTDict *)malloc(sizeof(KeyVal_BSTDict));
        if(binarySortTreeNode->data==NULL)
            return FAIL;
        binarySortTreeNode->rChild=NULL;
        binarySortTreeNode->lChild=NULL;

        //将其作为树的根节点
        bstDict->rootNode=binarySortTreeNode;
        bstDict->amountNodes++;

        return SUCCESS;
    }else{
        //树不空
        //查找keyVal中的key节点是否存在
        KeyVal_BSTDict *tempKeyVal=(KeyVal_BSTDict *)malloc(sizeof(KeyVal_BSTDict));
        if(tempKeyVal==NULL)
            return FAIL;
        tempKeyVal->key=key;
        tempKeyVal->val=val;

        binarySortTreeNode=search_bst_dict(bstDict->rootNode,tempKeyVal);

        if(binarySortTreeNode==NULL){
            //keyVal中的key节点不存在
            //插入keyVal到二叉排序树中
            bstDict->amountNodes++; //总节点数增加1
            return insert_bst_dict(&(bstDict->rootNode),tempKeyVal);
        }else{
            //keyVal中的key节点存在
            //直接修改节点的data
            //总节点数不变
            binarySortTreeNode->data=tempKeyVal;
            return SUCCESS;
        }
    }
}

//删除 二叉排序树字典 中key-val对
Status del_BSTDict(Bst_Dict *bstDict,int key){
    if(bstDict==NULL)
        return FAIL;
    KeyVal_BSTDict keyVal;
    keyVal.key=key;
    return deleteNode_BinarySortTree(bstDict,compare_keyval_bst_dict,&keyVal);
}

//获取 二叉排序树字典 中key-val对
Status get_BSTDict(Bst_Dict *bstDict,int key,void **val){
    if(bstDict==NULL)
        return FAIL;
    Bst_Node *bstNode=NULL;
    KeyVal_BSTDict keyVal;
    keyVal.key=key;
    Status opResult= getNode_BinarySortTree(
    bstDict,
    compare_keyval_bst_dict,
            &keyVal,
        &bstNode
        );
    if(FAIL==opResult)
        return FAIL;
    else{
        *val= ( (KeyVal_BSTDict *)(bstNode->data) )->val;
        return SUCCESS;
    }
}
