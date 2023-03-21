//
// Created by zhouyuqing on 2023/3/21.
//

#include"binarySortTree.h"


//清空二叉排序树
Status empty_BinarySortTree(BinarySortTree *binarySortTree){
    return empty_BinaryTree(binarySortTree);
}
//初始化二叉排序树
Status init_BinarySortTree(BinarySortTree **binarySortTree){
    return init_BinaryTree(binarySortTree);
}

//搜索节点
BinaryTreeNode *search(BinarySortTreeNode *binarySortTreeNode,COMPAR_ID_BINARY_SORT_TREE compare_id,void *id){
    if(binarySortTreeNode!=NULL){
        //比较id与当前元素
        int compareResult=compare_id(id,binarySortTreeNode->data);
        if( 1==compareResult ){  //data值小于id,到节点的右子树上寻找
            return search(binarySortTreeNode->rChild,id,compare_id);
        }else if( -1==compareResult ){ //data值大于id,到节点的左子树上寻找
            return search(binarySortTreeNode->lChild,id,compare_id);
        }else{ //找到data值等于id的节点
            return binarySortTreeNode;
        }
    }else
        return binarySortTreeNode;
}
//搜索二叉排序树
Status searchNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_ID_BINARY_SORT_TREE compare_id,void *id,void **value){
    if(binarySortTree==NULL)
        return FAIL;
    if(binarySortTree->amountNodes==0) //二叉排序树为空，则查找失败
        return FAIL;
    //搜索data为id的节点
    BinaryTreeNode *resultNode= search(binarySortTree->rootNode,compare_id,id);
    if(resultNode==NULL)
        return FAIL;
    //查找成功，则返回id对应的value值
    *value=resultNode->value;
    return SUCCESS;
}

//添加节点
Status append(BinarySortTreeNode **pBinarySortTreeNode,COMPAR_ID_BINARY_SORT_TREE compare_id,BinarySortTreeNode *dataNode){
    if(*pBinarySortTreeNode==NULL){ //找到叶节点插入位置,将数据节点放到叶节点位置上
        *pBinarySortTreeNode=dataNode;
        return SUCCESS;
    }else{
        int compareResult=compare_id( (*pBinarySortTreeNode)->data , dataNode->data );
        BinarySortTreeNode **temp=NULL;
        if(compareResult==1){ //compareResult==1  当前节点数据大于 dataNode,将dataNode放到当前节点的左子树上
            temp=&((*pBinarySortTreeNode)->lChild);
            return append(temp,compare_id,dataNode);
        }else if(compareResult==-1){ //compareResult==-1  当前节点数据小于 dataNode,将dataNode放到当前节点的右子树上
            temp=&((*pBinarySortTreeNode)->rChild);
            return append(temp,compare_id,dataNode);
        }else{
            return FAIL;
        }
    }
}
//添加{id:value}的节点到二叉排序树
Status appendNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_ID_BINARY_SORT_TREE compare_id,void *id,void *value){
    if(binarySortTree==NULL)
        return FAIL;
    BinarySortTreeNode *binarySortTreeNode=NULL;
    if(binarySortTree->rootNode==NULL){ //二叉排序树为空，直接添加节点
        //创建排序树节点
        binarySortTreeNode=(BinarySortTreeNode *)malloc(sizeof(BinarySortTreeNode));
        if(binarySortTreeNode==NULL)
            return FAIL;
        binarySortTreeNode->data=id;
        binarySortTreeNode->value=value;
        binarySortTreeNode->rChild=NULL;
        binarySortTreeNode->lChild=NULL;

        //将其作为树的根节点
        binarySortTree->rootNode=binarySortTreeNode;
        binarySortTree->amountNodes++;

        return SUCCESS;
    }else { //树不为空

        //查找data为id的节点是否存在
        binarySortTreeNode= search(binarySortTree->rootNode,compare_id,id);

        if (binarySortTreeNode!=NULL){
            //data为id的节点已经存在
            //修改目标节点的value值为value
            binarySortTreeNode->value=value;
            return SUCCESS;
        }else{
            //data为id的节点不存在
            //创建节点，并为节点赋值
            binarySortTreeNode=(BinarySortTreeNode *)malloc(sizeof(BinarySortTreeNode));
            binarySortTreeNode->data=id;
            binarySortTreeNode->value=value;
            binarySortTreeNode->rChild=NULL;
            binarySortTreeNode->lChild=NULL;

            //id节点插入到目标叶节点位置
            return append(&(binarySortTree->rootNode),compare_id,binarySortTreeNode);
        }
    }
}
//设置节点为data为id的节点的值为value 到二叉排序树
Status setNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_ID_BINARY_SORT_TREE compare_id,void *id,void *value){
    if(binarySortTree==NULL)
        return FAIL;
    if(binarySortTree->amountNodes==0) //树为空，设置节点值失败
        return FAIL;

    //查找data为id的节点
    BinarySortTreeNode *binarySortTreeNode= search(binarySortTree->rootNode,compare_id,id);
    //如果data为id的节点存在则修改值
    if(binarySortTreeNode!=NULL){
        binarySortTreeNode->value=value;
        return SUCCESS;
    }else
        return FAIL;
}

//删除data为id的节点
Status deleteNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_ID_BINARY_SORT_TREE compare_id,void *id,void **value){
    if(binarySortTree==NULL)
        return FAIL;
    //找到要删除的目标节点
    BinarySortTreeNode *deleteNode= search(binarySortTree->rootNode,compare_id,id);
    if(deleteNode==NULL) //要删除节点不存在,删除失败
        return FAIL;


    //情况1,待删节点有左右子树
    if(deleteNode->rChild!=NULL && deleteNode->lChild!=NULL){


    }else if(deleteNode->rChild!=NULL || deleteNode->lChild!=NULL){ //情况2，待删节 只有左子树 或 右子树



    }else{ //情况3,待删节点 为叶节点，没有左子树，也没有右子树
        if(binarySortTree->rootNode==deleteNode){ //若待删节点为根节点，则删除
            //删除待删节点，将根节点置空
            free(deleteNode);
            deleteNode=NULL;
            binarySortTree->rootNode=NULL;
        }else{
        }

    }


    binarySortTree->amountNodes--;
    return SUCCESS;

}

//创建二叉排序树
Status create_BinarySortTree(BinarySortTree **pBinarySortTree,COMPAR_ID_BINARY_SORT_TREE compare_id,int *id[],int *value[],int n){
    //初始化排序树
    Status opReuslt= init_BinaryTree(pBinarySortTree);
    if(opReuslt==FAIL)
        return FAIL;
    BinarySortTree *binarySortTree=*pBinarySortTree;

    //将n对{id:value}加入树中
    for(int i=0;i<n;i++){
        opReuslt=appendNode_BinarySortTree(binarySortTree,compare_id,id[i],value[i]);
        if(FAIL==opReuslt)
            return FAIL;
    }
    //添加完毕
    return SUCCESS;
}




//销毁二叉排序树
Status destroy_BinarySortTree(BinarySortTree **binarySortTree){
    return destroy_BinaryTree(binarySortTree);
}

