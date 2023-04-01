//
// Created by zhouyuqing on 2023/4/1.
//

#include "directGraphAdjacencyList.h"
#include "../../01SerialList/queueByLinkList/queueByLinkList.h"

//清空有向图邻接表
Status empty_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList){
    if(directedGraphAdjancecyList==NULL)
        return FAIL;
    //遍历每个节点
    for(int i=0;i<directedGraphAdjancecyList->vertexsNum;i++){
        //遍历当前节点发出是所有边，并释放
        Arc_DirectedGraphAdjancecyList *current_Arc=directedGraphAdjancecyList->vertexs[i].firstArc;
        Arc_DirectedGraphAdjancecyList *temp=NULL;
        while(current_Arc!=NULL){
            temp=current_Arc;
            current_Arc=current_Arc->nextArc;
            free(temp);
        }
        //当前节点发出边置空
        directedGraphAdjancecyList->vertexs[i].firstArc=NULL;
    }
    //有向量邻接表的边数全部为0
    directedGraphAdjancecyList->vertexsNum=0;
    return SUCCESS;
}

//初始有向图邻接表
Status init_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList **pDirectedGraphAdjacencyList,
                                       void *vertexDatas[],
                                       int vertexsNum){
    //判断节点个数是否在合法范围内(1~MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST)
    if(vertexsNum<0 || vertexsNum>MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST)
        return FAIL;

    //有向图不存在，则创建
    if((*pDirectedGraphAdjacencyList)==NULL) {
        //有向图不存在则创建
        *pDirectedGraphAdjacencyList = (DirectedGraphAdjancecyList *) malloc(sizeof(DirectedGraphAdjancecyList));
        if(*pDirectedGraphAdjacencyList==NULL)
            return FAIL;
    }else{
        //存在则清空所有边
        Status opResult= empty_DirectedGraphAdjancecyList(*pDirectedGraphAdjacencyList);
        if(opResult==FAIL)
            return FAIL;
    }

    //设置边数，顶点数
    (*pDirectedGraphAdjacencyList)->edgesNum=0;
    (*pDirectedGraphAdjacencyList)->vertexsNum=vertexsNum;

    //设置结点数据
    for(int i=0;i<(*pDirectedGraphAdjacencyList)->vertexsNum;i++)
        (*pDirectedGraphAdjacencyList)->vertexs[i].data=vertexDatas[i];

    return SUCCESS;
}

//为有向图邻接表设置边
Status setEdge_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                             int startPoint,int endPoint,
                                             int lengthArc){
    if(directedGraphAdjancecyList==NULL)
        return FAIL;

    //判断边的起点与终点是否在合理范围内(0~directedGraphAdjacencyList->vertexNum-1)
    if(startPoint<0 || startPoint>=directedGraphAdjancecyList->vertexsNum)
        return FAIL;
    if(endPoint<0 || endPoint>=directedGraphAdjancecyList->vertexsNum)
        return FAIL;
    //探查startPoint节点发出的所有边
    Arc_DirectedGraphAdjancecyList *currentArc=
            directedGraphAdjancecyList->vertexs[startPoint].firstArc;
    Arc_DirectedGraphAdjancecyList *preCurrentArc=NULL;
    while(currentArc!=NULL){
        //如果找到从startPoint指向endPoint的边，则修改边的权值为lengthArc
        if(currentArc->adjVex==endPoint) {
            currentArc->lengthArc = lengthArc;
            return SUCCESS;
        }
        preCurrentArc=currentArc;
        currentArc=currentArc->nextArc;
    }
    //没有找到从startPoint指向endPoint的边，创建权值为lengthArc,且指向endPoint的边
    // 挂到startPoint节点发出的边列表的后面
    Arc_DirectedGraphAdjancecyList *newArc=(Arc_DirectedGraphAdjancecyList *)malloc(sizeof(Arc_DirectedGraphAdjancecyList));
    if(NULL==newArc)
        return FAIL;
    newArc->nextArc=NULL;
    newArc->lengthArc=lengthArc;
    newArc->adjVex=endPoint;

    preCurrentArc->nextArc=newArc;

    return SUCCESS;
}
//删除有向图邻接表的边
Status deleteEdge_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                          int startPoint,int endPoint){
    if(directedGraphAdjancecyList==NULL)
        return FAIL;
    //判断边的起点与终点是否在合理范围内(0~directedGraphAdjacencyList->vertexNum-1)
    if(startPoint<0 || startPoint>=directedGraphAdjancecyList->vertexsNum)
        return FAIL;
    if(endPoint<0 || endPoint>=directedGraphAdjancecyList->vertexsNum)
        return FAIL;
    //探查startPoint节点发出的所有边
    Arc_DirectedGraphAdjancecyList *currentArc=
            directedGraphAdjancecyList->vertexs[startPoint].firstArc;
    Arc_DirectedGraphAdjancecyList *preCurrentArc=NULL;
    while(currentArc!=NULL){
        //如果找到从startPoint指向endPoint的边，则跳出循环，currentArc指向的就是当前节点指向的边
        if(currentArc->adjVex==endPoint)
            break;
        preCurrentArc=currentArc;
        currentArc=currentArc->nextArc;
    }

    if(currentArc==NULL){
        //没有找到从startPoint指向endPoint的边，无需操作直接返回删除成功
        return SUCCESS;
    }else{
        //currentArc指向当前要删除的 从startPoint到endPoint的边
        if(preCurrentArc==NULL){
            //待删边是节点边列表的头节点
            directedGraphAdjancecyList->vertexs[startPoint].firstArc=currentArc->nextArc;
            free(currentArc);
        }else{
            //待删边不是节点边列表的头节点
            preCurrentArc->nextArc=currentArc->nextArc;
            free(currentArc);
        }

        directedGraphAdjancecyList->edgesNum-=1;
        return SUCCESS;
    }
}

//广度遍历
Status BFS_DGAL(DirectedGraphAdjancecyList *directedGraphAdjancecyList,int visited[],
           int startVertex,void ***pListData,int *lengthListData){

    //创建辅助队列
    QueueByLinkList *queueByLinkList=NULL;
    Status opResult= init_QueueByLinkList(&queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    //获取当前节点并入队
    Vertex_DirectedGraphAdjancecyList currentVertex=directedGraphAdjancecyList->vertexs[startVertex];
    opResult= enqueue_QueueByLinkList(queueByLinkList,&currentVertex);
    if(FAIL==opResult)
        return FAIL;
    //访问入队节点并加入访问序列
    (*pListData)[(*lengthListData)++]=currentVertex.data;
    visited[startVertex]=1;

    //广度遍历所有节点
    while(!isEmpty_QueueByLinkList(queueByLinkList)){
        //队列头元素出队列
        opResult= dequeue_QueueByLinkList(queueByLinkList,(void *)&currentVertex);
        if(FAIL==opResult)
            return FAIL;

        //当期出队列节点所连接的所有未被访问的节点入队列，并访问
        Arc_DirectedGraphAdjancecyList *arcCurrent=currentVertex.firstArc;
        while(arcCurrent!=NULL){
            if(visited[arcCurrent->adjVex]==0){
                //当前所连接的节点arcCurrent->adjVex节点没有被访问过，则节点入队列并加入访问队列
                opResult= enqueue_QueueByLinkList(
                        queueByLinkList,
                        &(directedGraphAdjancecyList->vertexs[arcCurrent->adjVex])
                );
                if(FAIL==opResult)
                    return FAIL;
                //访问入队节点，并加入访问序列
                (*pListData)[(*lengthListData)++]=
                        directedGraphAdjancecyList->vertexs[arcCurrent->adjVex].data;
                visited[arcCurrent->adjVex]=1;
            }
            arcCurrent=arcCurrent->nextArc;
        }
    }

    //销毁辅助队列
    opResult=destroy_QueueByLinkList(&queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    return SUCCESS;

}

//广度遍历有向图邻接表
//从vertexId广度遍历有向图邻接表
Status BFS_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                      int startVertex,void ***pListData,int *lengthListData){
    if(directedGraphAdjancecyList==NULL)
        return FAIL;
    //判断边的起点是否在合理范围内(0~directedGraphAdjacencyMatrix->vertexNum-1)
    if(startVertex<0 || startVertex>=directedGraphAdjancecyList->vertexsNum)
        return FAIL;

    //定义访问数组
    int visited[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST];
    for(int i=0;i<directedGraphAdjancecyList->vertexsNum;i++)
        visited[i]=0;

    if(*pListData!=NULL)
        free(*pListData);
    *pListData=(void **)malloc(sizeof(void *)*directedGraphAdjancecyList->vertexsNum);
    if(*pListData==NULL)
        return FAIL;

    return BFS_DGAL(directedGraphAdjancecyList,visited,startVertex,pListData,lengthListData);
}

//深度遍历
void DFS_DGAL(DirectedGraphAdjancecyList *directedGraphAdjancecyList,int visited[],
           int startVertex,void ***pListData,int *lengthListData){
    if(visited[startVertex]==0){
        //当前startVertex节点没有被访问过
        //直接加入访问序列
        (*pListData)[(*lengthListData)++]=directedGraphAdjancecyList->vertexs[startVertex].data;
        visited[startVertex]=1;
    }

    //找到从该节点发出的边连接的没有被访问过的节点
    Arc_DirectedGraphAdjancecyList *currentArc=
            directedGraphAdjancecyList->vertexs[startVertex].firstArc;
    while(currentArc!=NULL){
        if(visited[currentArc->adjVex]==0){
            //当前所连接的节点arcCurrent->adjVex节点没有被访问过，则继续深度遍历该节点
            DFS_DGAL(directedGraphAdjancecyList,visited,currentArc->adjVex,pListData,lengthListData);
        }
        currentArc=currentArc->nextArc;
    }

}
//深度遍历有向图邻接表
//从vertexId深度遍历有向图邻接表
Status DFS_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                      int startVertex,void ***pListData,int *lengthListData){
    if(directedGraphAdjancecyList==NULL)
        return FAIL;
    //判断边的起点是否在合理范围内(0~directedGraphAdjacencyMatrix->vertexNum-1)
    if(startVertex<0 || startVertex>=directedGraphAdjancecyList->vertexsNum)
        return FAIL;

    //定义访问数组
    int visited[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST];
    for(int i=0;i<directedGraphAdjancecyList->vertexsNum;i++)
        visited[i]=0;

    if(*pListData!=NULL)
        free(*pListData);
    *pListData=(void **)malloc(sizeof(void *)*directedGraphAdjancecyList->vertexsNum);
    if(*pListData==NULL)
        return FAIL;

    DFS_DGAL(directedGraphAdjancecyList,visited,startVertex,pListData,lengthListData);

    //遍历结果长度不为0时遍历成功
    if((*lengthListData)==0)
        return FAIL;
    else
        return SUCCESS;
}

//通过传入二维矩阵创建有向图邻接表
Status create_DirectedGraphAdjacencyList(DirectedGraphAdjancecyList **pDirectedGraphAdjancecyList,
                                         int edges[][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST],
                                         void *vertexDatas[],int vertexNum){

}

//销毁有向图邻接矩阵
Status destroy_DirectedGraphAdjacencyList(DirectedGraphAdjancecyList **pDirectedGraphAdjancecyList){
    //邻接表为空 ，直接返回
    if(*pDirectedGraphAdjancecyList==NULL)
        return SUCCESS;
    //清空所有边
    Status opResult=empty_DirectedGraphAdjancecyList(*pDirectedGraphAdjancecyList);
    if(FAIL==opResult)
        return FAIL;
    //释放邻接矩阵
    free(*pDirectedGraphAdjancecyList);
    *pDirectedGraphAdjancecyList=NULL;
    return SUCCESS;
}

