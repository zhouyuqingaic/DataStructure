//
// Created by zhouyuqing on 2023/3/18.
//

#include "../../01SerialList/queueByLinkList/queueByLinkList.h"
#include "../../01SerialList/stackLinkList/stackLinkList.h"
#include "binaryTree.h"

//清空二叉树
Status empty_BinaryTree(BinaryTree *binaryTree){
    if(binaryTree==NULL)
        return FAIL;
    if(binaryTree->amountNodes==0) //当前树为空，直接返回
        return SUCCESS;

    //创建辅助栈
    StackLinkList *stackLinkList=NULL;
    Status opResult= init_StackLinkList(&stackLinkList);
    if(FAIL==opResult)
        return FAIL;

    //创建节点列表
    BinaryTreeNode **btNodeList=(BinaryTreeNode **)malloc(sizeof(BinaryTreeNode *)*binaryTree->amountNodes);
    if(btNodeList==NULL)
        return FAIL;
    int indexBtNodeList=0;

    //通过中序遍历获取所有节点
    //currentBTNode指向当前要遍历的节点
    BinaryTreeNode *currentBTNode=binaryTree->rootNode;
    void *temp=NULL;
    while(currentBTNode!=NULL || !isEmpty_StackLinkList(stackLinkList)){
        if(currentBTNode){
            //访问节点，并将节点数据入访问序列
            btNodeList[indexBtNodeList++]=currentBTNode;

            push_StackLinkList(stackLinkList,currentBTNode);
            currentBTNode=currentBTNode->lChild;
        }else{
            pop_StackLinkList(stackLinkList,&temp);
            currentBTNode=(BinaryTreeNode *)temp;
            currentBTNode=currentBTNode->rChild;
        }
    }
    //销毁辅助栈
    opResult= destroy_StackLinkList(&stackLinkList);
    if(opResult==FAIL)
        return FAIL;

    //释放获取到的所有二叉树节点
    for(int i=0;i<binaryTree->amountNodes;i++) {
        free(btNodeList[i]);
        btNodeList[i]=NULL;
    }
    //释放节点数组
    free(btNodeList);
    btNodeList=NULL;

    //置空根节点与二叉树容量
    binaryTree->rootNode=NULL;
    binaryTree->amountNodes=0;

    return SUCCESS;
}
//初始化二叉树
Status init_BinaryTree(BinaryTree **pBinaryTree){
    if(*pBinaryTree!=NULL){ //二叉树存在则清空
        return empty_BinaryTree(*pBinaryTree);
    }else{ //二叉树不存在则创建
        *pBinaryTree=(BinaryTree *) malloc(sizeof(BinaryTreeNode));
        //修改二叉树参数
        (*pBinaryTree)->rootNode=NULL;
        (*pBinaryTree)->amountNodes=0;
        return SUCCESS;
    }
}

//将dataList视为完全二叉树遍历的结果，来创建完全二叉树
Status generate_BinaryTree(BinaryTree **pBinaryTree,void **dataList,int lengthDataList){
    if(dataList==NULL || lengthDataList==0) //如果访问序列为空或者长度为0，则生成二叉树失败
        return FAIL;

    //初始化树
    Status opResult=init_BinaryTree(pBinaryTree);
    if(FAIL==opResult)
        return FAIL;


    //创建辅助队列
    QueueByLinkList *queueByLinkList=NULL;
    opResult=init_QueueByLinkList(&queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    //访问序列的索引
    int indexDataList=0;

    //创建树的根节点并入队
    BinaryTreeNode *currentBtNode=(BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    if(currentBtNode==NULL)
        return FAIL;
    currentBtNode->data=dataList[indexDataList++];
    currentBtNode->lChild=NULL;
    currentBtNode->rChild=NULL;
    (*pBinaryTree)->rootNode=currentBtNode;
    (*pBinaryTree)->amountNodes++;

    //根节点入队
    opResult= enqueue_QueueByLinkList(queueByLinkList,(*pBinaryTree)->rootNode);
    if(FAIL==opResult)
        return FAIL;

    //判断dataList是否填充完毕
    if(indexDataList>lengthDataList-1) {
        opResult= destroy_QueueByLinkList(&queueByLinkList);
        if(FAIL==opResult)
            return FAIL;
        return SUCCESS;
    }

    //将dataList中的所有节点加入树中
    void *temp;
    while(!isEmpty_QueueByLinkList(queueByLinkList)){
        //栈顶元素出栈并访问
        opResult=dequeue_QueueByLinkList(queueByLinkList,&temp);
        if(FAIL==opResult)
            return FAIL;
        currentBtNode=(BinaryTreeNode *)temp;

        //判断是否需要继续填充
        if(indexDataList<=lengthDataList-1) {
            //填充出栈元素的左子树
            currentBtNode->lChild = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
            if (currentBtNode->lChild==NULL)
                return FAIL;

            (*pBinaryTree)->amountNodes++;
            currentBtNode->lChild->data=dataList[indexDataList++];
            currentBtNode->lChild->lChild=NULL;
            currentBtNode->lChild->rChild=NULL;

            //左子树入队
            enqueue_QueueByLinkList(queueByLinkList,currentBtNode->lChild);

        }else{
            //销毁辅助队列
            opResult= destroy_QueueByLinkList(&queueByLinkList);
            if(FAIL==opResult)
                return FAIL;
            return SUCCESS;
        }

        if(indexDataList<=lengthDataList-1) {
            //填充出栈元素的右子树
            currentBtNode->rChild = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
            if(currentBtNode->rChild==NULL)
                return FAIL;

            (*pBinaryTree)->amountNodes++;
            currentBtNode->rChild->data=dataList[indexDataList++];
            currentBtNode->rChild->lChild=NULL;
            currentBtNode->rChild->rChild=NULL;

            //右子树入队
            enqueue_QueueByLinkList(queueByLinkList,currentBtNode->rChild);

        }else{
            //销毁辅助队列
            opResult= destroy_QueueByLinkList(&queueByLinkList);
            if(FAIL==opResult)
                return FAIL;
            return SUCCESS;
        }
    }

    //销毁辅助队列
    opResult= destroy_QueueByLinkList(&queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    return SUCCESS;

}

//二叉树非递归先序遍历,orderList返回遍历data序列
Status preOrder_BinaryTree(BinaryTree *binaryTree,void ***pOrderList){
    if(binaryTree==NULL)
        return FAIL;
    //如果树为空，则遍历失败
    if(binaryTree->amountNodes==0)
        return FAIL;

    //创建辅助栈
    StackLinkList *stackLinkList=NULL;
    Status opResult= init_StackLinkList(&stackLinkList);
    if(FAIL==opResult)
        return FAIL;


    //创建访问列表
    if(*pOrderList!=NULL)
        free(*pOrderList);
    *pOrderList=(void *)malloc(sizeof(void *)*binaryTree->amountNodes);
    if(*pOrderList==NULL)
        return FAIL;
    int indexOrderList=0;

    //currentBTNode指向当前要遍历的节点
    BinaryTreeNode *currentBTNode=binaryTree->rootNode;
    void *temp=NULL;
    //此处增加currentBTNode!=NULL判断是为了处理:
    //情况1:刚进入while时，栈空currentBtNode!=NULL
    //情况2:当根节点出栈时,此时栈空，，currentBtNode指向根的右边节点,由currentBtNode是否为空决定是否继续遍历
    while(currentBTNode!=NULL || !isEmpty_StackLinkList(stackLinkList)){
        if(currentBTNode){
            //访问节点，并将节点数据入访问序列
            (*pOrderList)[indexOrderList++]=currentBTNode->data;

            push_StackLinkList(stackLinkList,currentBTNode);
            currentBTNode=currentBTNode->lChild;
        }else{
            pop_StackLinkList(stackLinkList,&temp);
            currentBTNode=(BinaryTreeNode *)temp;
            currentBTNode=currentBTNode->rChild;
        }
    }

    //销毁辅助栈
    opResult= destroy_StackLinkList(&stackLinkList);
    if(opResult==FAIL)
        return FAIL;

    return SUCCESS;
}
//二叉树非递归中序遍历,orderList返回遍历data序列
Status inOrder_BinaryTree(BinaryTree *binaryTree,void ***pOrderList){
    if(binaryTree==NULL)
        return FAIL;
    //如果树为空,则遍历失败
    if(binaryTree->amountNodes==0)
        return FAIL;

    //创建辅助栈
    StackLinkList *stackLinkList=NULL;
    Status opResult= init_StackLinkList(&stackLinkList);
    if(FAIL==opResult)
        return FAIL;


    //创建访问列表
    if(*pOrderList!=NULL)
        free(*pOrderList);
    *pOrderList=(void *)malloc(sizeof(void *)*binaryTree->amountNodes);
    if(*pOrderList==NULL)
        return FAIL;
    int indexOrderList=0;

    //currentBTNode指向当前要遍历的节点
    BinaryTreeNode *currentBTNode=binaryTree->rootNode;
    void *temp=NULL;
    //此处增加currentBTNode!=NULL判断是为了处理:
    //情况1:刚进入while时，栈空currentBtNode!=NULL
    //情况2:当根节点出栈时,此时栈空，，currentBtNode指向根的右边节点,由currentBtNode是否为空决定是否继续遍历
    while(currentBTNode!=NULL || !isEmpty_StackLinkList(stackLinkList)){
        if(currentBTNode){
            push_StackLinkList(stackLinkList,currentBTNode);
            currentBTNode=currentBTNode->lChild;
        }else{
            pop_StackLinkList(stackLinkList,&temp);
            currentBTNode=(BinaryTreeNode *)temp;
            //访问节点，将节点数据入访问序列
            (*pOrderList)[indexOrderList++]=currentBTNode->data;

            currentBTNode=currentBTNode->rChild;
        }
    }

    //销毁辅助栈
    opResult= destroy_StackLinkList(&stackLinkList);
    if(opResult==FAIL)
        return FAIL;

    return SUCCESS;
}
//二叉树非递归后序遍历,orderList返回遍历data序列
Status postOrder_BinaryTree(BinaryTree *binaryTree,void ***pOrderList){
    if(binaryTree==NULL)
        return FAIL;
    //如果树为空,则遍历失败
    if(binaryTree->amountNodes==0)
        return FAIL;

    //创建辅助栈
    StackLinkList *stackLinkList=NULL;
    Status opResult= init_StackLinkList(&stackLinkList);
    if(FAIL==opResult)
        return FAIL;

    //创建访问列表
    if(*pOrderList!=NULL)
        free(*pOrderList);
    *pOrderList=(void *)malloc(sizeof(void *)*binaryTree->amountNodes);
    if(*pOrderList==NULL)
        return FAIL;
    int indexOrderList=0;

    //currentBTNode指向当前要遍历的节点
    BinaryTreeNode *currentBTNode=binaryTree->rootNode;
    //preCurrentBTNode指向currentBTNode的前一个被访问的节点
    BinaryTreeNode *preCurrentBTNode=NULL;

    void *temp;
    //此处增加currentBTNode!=NULL判断是为了处理:
    //情况1:刚进入while时，栈空currentBtNode!=NULL
    //情况2:当根节点出栈时,此时栈空，，currentBtNode指向根的右边节点,由currentBtNode是否为空决定是否继续遍历
    while(currentBTNode!=NULL || !isEmpty_StackLinkList(stackLinkList)){
        if(currentBTNode){ //走到最左边，即当前栈顶元素没有左子树
            push_StackLinkList(stackLinkList,currentBTNode);
            currentBTNode=currentBTNode->lChild;
        }else{
            //获取栈顶元素
            opResult=peek_StackLinkList(stackLinkList,&temp);
            if(FAIL==opResult)
                return FAIL;
            currentBTNode=(BinaryTreeNode *)temp;
            //如果当前栈顶元素的右子树存在且未被访问过，探查右子树
            if(currentBTNode->rChild!=NULL && currentBTNode->rChild!=preCurrentBTNode)
                currentBTNode=currentBTNode->rChild;
            else{ //当前栈顶元素的右子树不存在，则直接访问当前栈顶元素
                pop_StackLinkList(stackLinkList,&temp);
                if(FAIL==opResult)
                    return FAIL;
                currentBTNode=(BinaryTreeNode *)temp;
                //加入访问序列
                (*pOrderList)[indexOrderList++]=currentBTNode->data;

                //更新最近访问节点,即对下轮while来说上次访问的节点
                preCurrentBTNode=currentBTNode;
                //currentBtNode访问完成后，相当于一当前currentBTNode为根的子树，全部被遍历完
                currentBTNode=NULL;
            }
        }
    }


    //销毁辅助栈
    opResult= destroy_StackLinkList(&stackLinkList);
    if(opResult==FAIL)
        return FAIL;

    return SUCCESS;
}



//递归先序遍历,将结果存入orderList中
void preOrder(BinaryTreeNode *binaryTreeNode,void **orderList,int *indexOrderList){
    if(binaryTreeNode!=NULL){
        //将当前访问的节点存入遍历列表中
        orderList[*indexOrderList]=binaryTreeNode->data;
        (*indexOrderList)++;

        //访问当前节点的左右节点
        preOrder(binaryTreeNode->lChild,orderList,indexOrderList);
        preOrder(binaryTreeNode->rChild,orderList,indexOrderList);
    }
}
//二叉树递归先序遍历,orderList返回遍历data序列
Status preOrder_R_BinaryTree(BinaryTree *binaryTree,void ***pOrderList){
    if(binaryTree==NULL)
        return FAIL;

    //创建访问列表
    if(*pOrderList!=NULL)
        free(*pOrderList);
    *pOrderList=(void *)malloc(sizeof(void *)*binaryTree->amountNodes);
    if(*pOrderList==NULL)
        return FAIL;
    int indexOrderList=0;

    //获取前序递归遍历结果
    preOrder(binaryTree->rootNode,*pOrderList,&indexOrderList);
    return SUCCESS;
}

//递归中序遍历,将结果存入orderList中
void inOrder(BinaryTreeNode *binaryTreeNode,void **orderList,int *indexOrderList){
    if(binaryTreeNode!=NULL){
        //访问当前节点的左节点
        inOrder(binaryTreeNode->lChild,orderList,indexOrderList);

        //将当前访问的节点存入遍历列表中
        orderList[*indexOrderList]=binaryTreeNode->data;
        (*indexOrderList)++;

        //访问当前节点的左节点
        inOrder(binaryTreeNode->rChild,orderList,indexOrderList);
    }
}
//二叉树递归中序遍历,orderList返回遍历data序列
Status inOrder_R_BinaryTree(BinaryTree *binaryTree,void ***pOrderList){
    if(binaryTree==NULL)
        return FAIL;

    //创建访问列表
    if(*pOrderList!=NULL)
        free(*pOrderList);
    *pOrderList=(void *)malloc(sizeof(void *)*binaryTree->amountNodes);
    if(*pOrderList==NULL)
        return FAIL;
    int indexOrderList=0;

    //获取中序递归遍历结果
    inOrder(binaryTree->rootNode,*pOrderList,&indexOrderList);
    return SUCCESS;
}

//递归后序遍历,将结果存入orderList中
void postOrder(BinaryTreeNode *binaryTreeNode,void **orderList,int *indexOrderList){
    if(binaryTreeNode!=NULL){
        //访问当前节点的左,右节点
        postOrder(binaryTreeNode->lChild,orderList,indexOrderList);
        postOrder(binaryTreeNode->rChild,orderList,indexOrderList);

        //将当前访问的节点存入遍历列表中
        orderList[*indexOrderList]=binaryTreeNode->data;
        (*indexOrderList)++;

    }
}
//二叉树递归后序遍历,orderList返回遍历data序列
Status postOrder_R_BinaryTree(BinaryTree *binaryTree,void ***pOrderList){
    if(binaryTree==NULL)
        return FAIL;

    //创建访问列表
    if(*pOrderList!=NULL)
        free(*pOrderList);
    *pOrderList=(void *)malloc(sizeof(void *)*binaryTree->amountNodes);
    if(*pOrderList==NULL)
        return FAIL;
    int indexOrderList=0;

    //获取中序递归遍历结果
    postOrder(binaryTree->rootNode,*pOrderList,&indexOrderList);
    return SUCCESS;
}

//二叉树层次遍历,orderList返回遍历data序列
Status levelOrder_BinaryTree(BinaryTree *binaryTree,void ***pOrderList){
    if(binaryTree==NULL)
        return FAIL;

    //如果树为空,则遍历失败
    if(binaryTree->amountNodes==0)
        return FAIL;

    //创建辅助队列
    QueueByLinkList *queueByLinkList=NULL;
    Status opResult=init_QueueByLinkList(&queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    //创建访问列表
    if(*pOrderList!=NULL)
        free(*pOrderList);
    *pOrderList=(void *)malloc(sizeof(void *)*binaryTree->amountNodes);
    if(*pOrderList==NULL)
        return FAIL;
    int indexOrderList=0;

    //根节点入队
    opResult= enqueue_QueueByLinkList(queueByLinkList,binaryTree->rootNode);
    if(FAIL==opResult)
        return FAIL;
    //currentBTNode指向当前要遍历的节点
    BinaryTreeNode *currentBTNode=NULL;
    void *temp;
    //直到当前队列为空，则所有节点访问完毕
    while(!isEmpty_QueueByLinkList(queueByLinkList)){
        //队头节点出队列并访问
        opResult=dequeue_QueueByLinkList(queueByLinkList,&temp);
        if(FAIL==opResult)
            return FAIL;
        currentBTNode=(BinaryTreeNode *)temp;
        //将出队节点加入访问队列
        (*pOrderList)[indexOrderList++]=currentBTNode->data;
        //如果出队节点有左右子树 则入队
        if(currentBTNode->lChild!=NULL) {
            opResult = enqueue_QueueByLinkList(queueByLinkList, currentBTNode->lChild);
            if(FAIL==opResult)
                return FAIL;
        }
        if(currentBTNode->rChild!=NULL){
            opResult= enqueue_QueueByLinkList(queueByLinkList,currentBTNode->rChild);
            if(FAIL==opResult)
                return FAIL;
        }
    }

    //销毁辅助队列
    opResult=destroy_QueueByLinkList(queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    return SUCCESS;
}

//销毁二叉树
Status destroy_BinaryTree(BinaryTree **pBinaryTree){
    if(*pBinaryTree==NULL) //二叉树不存在直接返回
        return SUCCESS;
    //清空当前二叉树
    Status opResult=empty_BinaryTree(*pBinaryTree);
    if(FAIL==opResult)
        return FAIL;
    //释放树
    free(*pBinaryTree);
    *pBinaryTree=NULL;
    return SUCCESS;
}
