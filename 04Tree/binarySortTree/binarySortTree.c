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
BinaryTreeNode *search(BinarySortTreeNode *binarySortTreeNode,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *data){
    if(binarySortTreeNode!=NULL){
        //比较id与当前元素
        int compareResult=compare_data(binarySortTreeNode->data,data);
        if( 1==compareResult ){  //当前节点大于data,到节点的左子树上寻找data
            return search(binarySortTreeNode->lChild,compare_data,data);
        }else if( -1==compareResult ){ //当前节点小于data,到节点的右子树上寻找
            return search(binarySortTreeNode->rChild,compare_data,data);
        }else{ //找到data值等于id的节点
            return binarySortTreeNode;
        }
    }else
        return binarySortTreeNode;
}
//搜索二叉排序树中为data的节点
Status getNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *data,BinarySortTreeNode **resultNode){
    if(binarySortTree==NULL)
        return FAIL;
    if(binarySortTree->amountNodes==0) //二叉排序树为空，则查找失败
        return FAIL;
    //搜索data节点
    BinaryTreeNode *result= search(binarySortTree->rootNode,compare_data,data);
    if(result==NULL)
        return FAIL;
    else {
        //查找成功，则返回id对应的value值
        *resultNode = result;
        return SUCCESS;
    }
}

//添加节点
Status append(BinarySortTreeNode **pBinarySortTreeNode,COMPAR_DATA_BINARY_SORT_TREE compare_data,BinarySortTreeNode *dataNode){
    if(*pBinarySortTreeNode==NULL){ //找到叶节点插入位置,将数据节点放到叶节点位置上
        *pBinarySortTreeNode=dataNode;
        return SUCCESS;
    }else{
        int compareResult=compare_data( (*pBinarySortTreeNode)->data , dataNode->data );
        BinarySortTreeNode **temp=NULL;
        if(compareResult==1){ //compareResult==1  当前节点数据大于 dataNode,将dataNode放到当前节点的左子树上
            temp=&((*pBinarySortTreeNode)->lChild);
            return append(temp,compare_data,dataNode);
        }else if(compareResult==-1){ //compareResult==-1  当前节点数据小于 dataNode,将dataNode放到当前节点的右子树上
            temp=&((*pBinarySortTreeNode)->rChild);
            return append(temp,compare_data,dataNode);
        }else{
            //当前数据为data的节点已经存在，加入排序树失败
            return FAIL;
        }
    }
}
//添加data节点到二叉排序树
Status appendNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *data){
    if(binarySortTree==NULL)
        return FAIL;
    BinarySortTreeNode *binarySortTreeNode=NULL;
    if(binarySortTree->rootNode==NULL){ //二叉排序树为空，直接添加节点
        //创建排序树节点
        binarySortTreeNode=(BinarySortTreeNode *)malloc(sizeof(BinarySortTreeNode));
        if(binarySortTreeNode==NULL)
            return FAIL;
        binarySortTreeNode->data=data;
        binarySortTreeNode->rChild=NULL;
        binarySortTreeNode->lChild=NULL;

        //将其作为树的根节点
        binarySortTree->rootNode=binarySortTreeNode;
        binarySortTree->amountNodes++;

        return SUCCESS;
    }else { //树不为空

        //查找data节点是否存在
        binarySortTreeNode= search(binarySortTree->rootNode,compare_data,data);

        if (binarySortTreeNode==NULL){
            //data为id的节点不存在
            //创建节点，并为节点赋值
            binarySortTreeNode=(BinarySortTreeNode *)malloc(sizeof(BinarySortTreeNode));
            if(binarySortTreeNode==NULL)
                return FAIL;
            binarySortTreeNode->data=data;
            binarySortTreeNode->rChild=NULL;
            binarySortTreeNode->lChild=NULL;

            //id节点插入到目标叶节点位置
            Status opRsult=append(&(binarySortTree->rootNode),compare_data,binarySortTreeNode);
            if(FAIL==opRsult){ //插入失败
                //释放创建的临时节点
                free(binarySortTreeNode);
                return FAIL;
            }else {
                binarySortTree->amountNodes++;
                return SUCCESS;
            }
        }else{
            //data节点已存在，加入排序树失败
            return FAIL;
        }
    }
}

//返回binarSortTreeNode为根的树，中序遍历的第一个节点
BinarySortTreeNode *dirctFollowUp(BinarySortTreeNode *binarySortTreeNode){
    while(binarySortTreeNode->lChild!=NULL)
        binarySortTreeNode=binarySortTreeNode->lChild;
    return binarySortTreeNode;
}

//在rootNode为根的树上移除(而非删除)dirctFollowUpNode节点
//dirctFollowUpNode节点只能为 叶子节点 ，或则右子树不为空的节点
Status removeDirectFollowUp(BinarySortTreeNode **pRootNode,BinarySortTreeNode *dirctFollowUpNode,COMPAR_DATA_BINARY_SORT_TREE compar_data){
    BinarySortTreeNode *rootNode=*pRootNode;

    //找到dirctFollowUpNode节点的父节点
    BinarySortTreeNode *preCurrentNode=rootNode;
    BinarySortTreeNode *curretnNode=rootNode;
    while(1){
        int compareResult=compar_data(curretnNode->data,dirctFollowUpNode->data);
        if(compareResult==1){ //直接后继节点dirctFollowUpNode在当前节点的左子树上
            //更新dirctFollowUpNode父节点
            preCurrentNode=curretnNode;

            curretnNode=curretnNode->lChild;

        }else if(compareResult==-1){ //直接后继节点dirctFollowUpNode在当前节点右子树上
            //更新dirctFollowUpNode父节点
            preCurrentNode=curretnNode;

            curretnNode=curretnNode->rChild;

        }else{ //直接后继节点dirctFollowUpNode就是当前节点
            break;
        }
    }

    if(dirctFollowUpNode->lChild==NULL && dirctFollowUpNode->rChild==NULL){
        //情况1： dirctFollowUpNode直接后继节点为叶子节点
        if(curretnNode==preCurrentNode){ //待移除节点为叶子节点,且为根节点
            *pRootNode=NULL;
        }else{ //待移除节点为叶子节点且非根节点
            if(preCurrentNode->lChild==dirctFollowUpNode){
                //待移出叶子节点在父节点的左子树上
                preCurrentNode->lChild=NULL;
            }else{
                //待移出叶子节点在父节点的右子树上
                preCurrentNode->rChild=NULL;
            }
        }
    }else{
        //情况2：dirctFollowUpNode直接后继节点的右节点非空
        if(curretnNode==preCurrentNode){ //待移除节点的右节点非空，且为根节点
            *pRootNode=dirctFollowUpNode->rChild;
        }else{ //待移除节点的右节点非空，且非根节点
            if(preCurrentNode->lChild==dirctFollowUpNode){
                //待移出叶子节点在父节点的左子树上
                preCurrentNode->lChild=dirctFollowUpNode->rChild;
            }else{
                //待移出叶子节点在父节点的右子树上
                preCurrentNode->rChild=dirctFollowUpNode->rChild;
            }
        }
    }

    return SUCCESS;
}

//删除data节点
Status deleteNode_BinarySortTree(BinarySortTree *binarySortTree,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *data){
    if(binarySortTree==NULL)
        return FAIL;
    if(binarySortTree->amountNodes==0) //树为空 删除失败
        return FAIL;
    //找到要删除的目标节点
    BinarySortTreeNode *deleteNode= search(binarySortTree->rootNode,compare_data,data);
    if(deleteNode==NULL) //要删除节点不存在,删除失败
        return FAIL;

    /*
     找到待删节点的父节点
        有一种特殊情况为:preTreeNode == currentTreeNode == binarySortTree->rootNode,
         (即待删节点为树的根节点才会出现这种情况)
     */
    //指向当前节点的父节点
    BinarySortTreeNode *preTreeNode=binarySortTree->rootNode;
    //指向当前节点
    BinarySortTreeNode *currentTreeNode=binarySortTree->rootNode;

    //找到删除节点的父节点
    while(1){
        //比较当前节点与待删节点
        int compareResult=compare_data(currentTreeNode->data,deleteNode->data);
        if(compareResult==-1) { //当前节点小于待删节点
            //更新父节点
            preTreeNode=currentTreeNode;
            //待删节点在当前节点的右边
            currentTreeNode=currentTreeNode->rChild;
        }else if(compareResult==1){ //当前节点大于待删节点
            //更新父节点
            preTreeNode=currentTreeNode;
            // 待删节点在当前节点的左边
            currentTreeNode=currentTreeNode->lChild;
        }else{ //当前节点等于待删节点,
            // 找到当前节点的父节点，跳出循环
            break;
        }
    }

    if(deleteNode->rChild!=NULL && deleteNode->lChild!=NULL){
        //情况1,待删节点有左右子树

        //获取待删节点的直接后继节点(待删节点右子树中序遍历的第一个节点)
        //直接后继节点 为叶子节点 或 只有右子节点不空
        BinarySortTreeNode *directFollowUpNode=dirctFollowUp(deleteNode->rChild);

        if(preTreeNode==currentTreeNode){
            //特殊情况:待删节点为根节点，且根节点有左子树和右子树

            //在以为deleteNode->rChild子树上移除directFollowUpNode节点
            //该节点只能为叶子节点 或  只有右子树的节点
            Status opResult= removeDirectFollowUp(
                    &(deleteNode->rChild),directFollowUpNode,compare_data);
            if(opResult==FAIL)
                return FAIL;

            //将directFollowUpNode直接后继节点放到待删节点位置(根节点位置)
            binarySortTree->rootNode=directFollowUpNode;
            directFollowUpNode->lChild=deleteNode->lChild;
            directFollowUpNode->rChild=deleteNode->rChild;

            //释放待删节点
            free(deleteNode);
        }else {
            //普通情况，待删节点非根节点，为有左子树和右子树 的普通节点
            //更新待删节点父节点的 左 或 右子节点
            if (preTreeNode->lChild == deleteNode) {
                //待删节点在其父节点的左子节点

                //在以为deleteNode->lChild右树上移除directFollowUpNode节点
                //该节点只能为叶子节点 或  只有右子树的节点
                Status opResult= removeDirectFollowUp(
                        &(deleteNode->rChild),directFollowUpNode,compare_data);

                if(opResult==FAIL)
                    return FAIL;

                //将directFollowUpNode直接后继节点放到待删节点位置(其父节点的左子节点节点位置)
                preTreeNode->lChild=directFollowUpNode;
                directFollowUpNode->lChild=deleteNode->lChild;
                directFollowUpNode->rChild=deleteNode->rChild;

                //释放待删节点
                free(deleteNode);
            }else{
                //待删节点在其父节点的右子节点

                //在以为deleteNode->rChild子树上移除directFollowUpNode节点
                //该节点只能为叶子节点 或  只有右子树的节点
                Status opResult= removeDirectFollowUp(
                        &(deleteNode->rChild),directFollowUpNode,compare_data);

                if(opResult==FAIL)
                    return FAIL;

                //将directFollowUpNode直接后继节点放到待删节点位置(其父节点的左子节点节点位置)
                preTreeNode->lChild=directFollowUpNode;
                directFollowUpNode->lChild=deleteNode->lChild;
                directFollowUpNode->rChild=deleteNode->rChild;

                //释放待删节点
                free(deleteNode);
            }
        }
    }else if(deleteNode->rChild!=NULL || deleteNode->lChild!=NULL){
        //情况2，待删节 只有左子树 或 右子树
        if(preTreeNode==currentTreeNode){
            //特殊情况:待删节点为根节点，且根节点只有左子树 或 右子树
            if(currentTreeNode->lChild!=NULL){
                //待删节点的左子树不空

                //更新根节点
                binarySortTree->rootNode=currentTreeNode->lChild;
                //删除待删节点
                free(currentTreeNode);
            }else{
                //待删节点的右子树不空

                //更新根节点
                binarySortTree->rootNode=currentTreeNode->rChild;
                //删除待删节点
                free(currentTreeNode);
            }
        }else{
            //普通情况，待删节点非根节点，为只有左子树 或 右子树 的普通节点

            //更新待删节点父节点的 左 或 右子节点
            if(preTreeNode->lChild==currentTreeNode){
                //待删节点在其父节点的左子节点

                if(currentTreeNode->lChild!=NULL) { //待删节点的左子树不空
                    //将父节点的左节点指向 待删节点的左子树
                    preTreeNode->lChild = currentTreeNode->lChild;
                }else { //待删节点的右子树不空
                    //将父节点的左节点指向 待删节点的右子树
                    preTreeNode->lChild = currentTreeNode->rChild;
                }
            }else{
                //待删节点在其父节点的右子节点

                if(currentTreeNode->lChild!=NULL) { //待删节点的左子树不空
                    //将父节点的右节点指向 待删节点的左子树
                    preTreeNode->rChild = currentTreeNode->lChild;
                }else { //待删节点的右子树不空
                    //将父节点的右节点指向 待删节点的右子树
                    preTreeNode->rChild = currentTreeNode->rChild;
                }
            }

            //释放待删节点
            free(currentTreeNode);
        }

    }else{
        //情况3,待删节点 为叶节点，没有左子树，也没有右子树
        if(preTreeNode==currentTreeNode){
            //特殊情况:待删节点为根节点，且根节点为叶子节点
            free(binarySortTree->rootNode);

            binarySortTree->rootNode=NULL;
        }else{
            //普通情况，待删节点非根节点，只是普通叶子节点

            //更新待删节点父节点的 左 或 右子节点
            if(preTreeNode->lChild==currentTreeNode){
                //待删节点在其父节点的左子节点上
                preTreeNode->lChild=NULL;
            }else{
                //待删节点在其父节点的右子节点
                preTreeNode->rChild=NULL;
            }

            //释放待删节点
            free(currentTreeNode);
        }
    }

    //删除后树的节点数减少1个
    binarySortTree->amountNodes--;

    return SUCCESS;
}


//获取排序后的data
Status sortedDatas_BinarySortTree(BinarySortTree *binarySortTree,void ***sortedDatas){
    if(binarySortTree==NULL)
        return FAIL;
    //排序树为空，执行失败
    if(binarySortTree->amountNodes==0)
        return FAIL;

    //二叉排序数，中间序列遍历序列即为排序结果
    return inOrder_R_BinaryTree(binarySortTree,sortedDatas);
}


//创建二叉排序树
Status create_BinarySortTree(BinarySortTree **pBinarySortTree,COMPAR_DATA_BINARY_SORT_TREE compare_data,void *datas[],int n){
    //初始化排序树
    Status opReuslt= init_BinaryTree(pBinarySortTree);
    if(opReuslt==FAIL)
        return FAIL;
    BinarySortTree *binarySortTree=*pBinarySortTree;

    //将data数据加入树中
    for(int i=0;i<n;i++){
        opReuslt=appendNode_BinarySortTree(binarySortTree,compare_data,datas[i]);
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

