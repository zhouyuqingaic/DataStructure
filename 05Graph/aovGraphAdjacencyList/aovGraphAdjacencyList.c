//
// Created by zhouyuqing on 2023/4/18.
//

#include "aovGraphAdjacencyList.h"
#include "../../01SerialList/queueByLinkList/queueByLinkList.h"
#include "../directGraphAdjacencyMatrix/directGraphAdjacencyMatrix.h"

//清空AOV图的邻接表
Status empty_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList){
    if(aovGraphAdjacencyList==NULL)
        return FAIL;
    //遍历AOV图的邻接表的每个节点
    for(int i=0;i<aovGraphAdjacencyList->vertexsNum;i++){
        //遍历当前节点发出的所有边，并释放边
        Arc_AOVGraphAdjacencyList *current_Arc=aovGraphAdjacencyList->vertexs[i].firstArc;
        Arc_AOVGraphAdjacencyList *temp=NULL;
        while(current_Arc!=NULL){
            temp=current_Arc;
            current_Arc=current_Arc->nextArc;
            free(temp);
        }
        //当前节点的发出边置空
        aovGraphAdjacencyList->vertexs[i].firstArc=NULL;
        //当前节点的入度为0
        aovGraphAdjacencyList->vertexs[i].enArcAmount=0;
    }
    //AOV图的邻接表的边数全部为0
    aovGraphAdjacencyList->edgesNum=0;
    return SUCCESS;
}
//初始化AOV图的邻接表
Status init_AOVGraphAdjacencyList(AOVGraphAdjacencyList **pAovGraphAdjacencyList,
                                  void *vertexDatas[],
                                  int vertexsNum){
    //判断节点个数是否在合法范围内(1~MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST)
    if(vertexsNum<0 || vertexsNum>MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST)
        return FAIL;
    //AOV图的邻接表不存在，则创建
    if((*pAovGraphAdjacencyList)==NULL){
        *pAovGraphAdjacencyList=(AOVGraphAdjacencyList *)malloc(sizeof(AOVGraphAdjacencyList));
        if(*pAovGraphAdjacencyList==NULL)
            return FAIL;
        //将所有节点的第一条边置空
        for(int i=0;i<MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST;i++)
            (*pAovGraphAdjacencyList)->vertexs[i].firstArc=NULL;
    }else{
        //AOV图的邻接表不存在，则清空AOV图
        Status opResult= empty_AOVGraphAdjacencyList(*pAovGraphAdjacencyList);
        if(opResult==FAIL)
            return FAIL;
    }
    //设置边数，顶点数
    (*pAovGraphAdjacencyList)->edgesNum=0;
    (*pAovGraphAdjacencyList)->vertexsNum=vertexsNum;

    //设置结点数据
    for(int i=0;i<(*pAovGraphAdjacencyList)->vertexsNum;i++){
        (*pAovGraphAdjacencyList)->vertexs[i].id=i;
        (*pAovGraphAdjacencyList)->vertexs[i].data=vertexDatas[i];
        //i节点发出的入度为0
        (*pAovGraphAdjacencyList)->vertexs[i].enArcAmount=0;
    }

    return SUCCESS;
}
//为AOV图的邻接表设置边(边的值为负数或者0表示该边不存在，不用设置 直接返回)
Status setEdge_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList,
                                     int startPoint,int endPoint){
    if(aovGraphAdjacencyList==NULL)
        return FAIL;

    //判断边的起点与终点是否在合理范围内(0~aovGraphAdjacencyList->vertexsNum-1)
    if(startPoint<0 || startPoint>=aovGraphAdjacencyList->vertexsNum)
        return FAIL;
    if(endPoint<0 || endPoint>=aovGraphAdjacencyList->vertexsNum)
        return FAIL;

    //探查startPoint节点发出的所有边
    Arc_AOVGraphAdjacencyList *currentArc=aovGraphAdjacencyList->vertexs[startPoint].firstArc;
    Arc_AOVGraphAdjacencyList *preCurrentArc=NULL;
    while(currentArc!=NULL){
        //如果找到从startPoint指向endPoint的边,则无需添加边操作，直接返回
        if(currentArc->adjVex==endPoint)
            return SUCCESS;
        preCurrentArc=currentArc;
        currentArc=currentArc->nextArc;
    }

    //没有找到从startPoint指向endPoint的边
    //创建新的边
    Arc_AOVGraphAdjacencyList *newArc=(Arc_AOVGraphAdjacencyList *)malloc(sizeof(Arc_AOVGraphAdjacencyList));
    if(NULL==newArc)
        return FAIL;

    newArc->nextArc=NULL;
    newArc->adjVex=endPoint;

    if(preCurrentArc==NULL){
        //由于preCurrentArc为空，则preCurrentArc为startPoint发出的第一条边
        aovGraphAdjacencyList->vertexs[startPoint].firstArc=newArc;
    }else{
        //由于preCurrentArc不为空，则preCurrentArc指向从startPoint节点边列表的最后一条边，边newArc挂在preCurrentArc后面
        preCurrentArc->nextArc=newArc;
    }
    //endPoint节点的入度1
    aovGraphAdjacencyList->vertexs[startPoint].enArcAmount+=1;

    return SUCCESS;
}

//获取AOV图的邻接表中从startPoint到endPoint有向边是否存在,Status==FAIL表示没有从startPoint到endPoint的有向边
Status existsEdge_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList,
                                     int startPoint,int endPoint){
    if(aovGraphAdjacencyList==NULL)
        return FAIL;

    //判断边的起点与终点是否在合理范围内(0~aovGraphAdjacencyList->vertexsNum-1)
    if(startPoint<0 || startPoint>=aovGraphAdjacencyList->vertexsNum)
        return FAIL;
    if(endPoint<0 || endPoint>=aovGraphAdjacencyList->vertexsNum)
        return FAIL;

    //探查从startPoint发出的所有边,查看其是否连接到endPoint
    Arc_AOVGraphAdjacencyList *currentArc=aovGraphAdjacencyList->vertexs[startPoint].firstArc;
    while(currentArc!=NULL){
        if(currentArc->adjVex==endPoint)
            return SUCCESS;
        currentArc=currentArc->nextArc;
    }
    //没有从startPoint发出到endPoint的边
    return FAIL;
}

//对AOV图的邻接表进行拓扑排序,排序结果存入pListData
Status topSort_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList,
                                     void ***pListData,int *lengthListData){
    if(aovGraphAdjacencyList==NULL)
        return FAIL;

    if(*pListData!=NULL)
        free(*pListData);
    *pListData=(void **)malloc(sizeof(void *)*aovGraphAdjacencyList->vertexsNum);
    if(*pListData==NULL)
        return FAIL;

    //创建辅助队列(队列中存储的都是入度为0的节点)
    QueueByLinkList *queueByLinkList=NULL;
    Status opResult= init_QueueByLinkList(&queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    *lengthListData=0;
    //将图中所有入度为0节点入队列
    for(int i=0;i<aovGraphAdjacencyList->vertexsNum;i++){
        if(aovGraphAdjacencyList->vertexs[i].enArcAmount==0) {
            opResult = enqueue_QueueByLinkList(
                    queueByLinkList, &(aovGraphAdjacencyList->vertexs[i])
            );
            if(FAIL==opResult)
                return FAIL;
        }
    }
    //开始拓扑排序
    Vertex_AOVGraphAdjacencyList *currentVertex=NULL;
    Arc_AOVGraphAdjacencyList *currentArc=NULL;
    while(!isEmpty_QueueByLinkList(queueByLinkList)){
        //元素出队
        opResult=dequeue_QueueByLinkList(queueByLinkList,(void *)&currentVertex);
        if(FAIL==opResult)
            return FAIL;
        //访问出队节点，并将出队列节点的数据加入结果序列中
        (*pListData)[(*lengthListData)++]=currentVertex->data;
        //访问过的节点从AOV图的屏蔽，即将其发出的边连接的节点的入度-1
        currentArc=currentVertex->firstArc;
        while(currentArc!=NULL){
            aovGraphAdjacencyList->vertexs[currentArc->adjVex].enArcAmount-=1;
            if(aovGraphAdjacencyList->vertexs[currentArc->adjVex].enArcAmount==0){
                //如果入度减1后，边所连接的节点currentArc->adjVex入度为0，
                // 则将新的入度为0的currentArc->adjVex节点加入队列中
                opResult= enqueue_QueueByLinkList(
                        queueByLinkList,&(aovGraphAdjacencyList->vertexs[currentArc->adjVex])
                );
                if(FAIL==opResult)
                    return FAIL;
            }
            currentArc=currentArc->nextArc;
        }

    }

    //如果所有节点都加入拓扑排序序列，则拓扑排序成功
    if(lengthListData==aovGraphAdjacencyList->vertexsNum)
        return SUCCESS;
    else
        //如果有剩余节点没有加入拓扑排序序列，则拓扑排序失败
        return FAIL;
}


//通过邻接矩阵的形式展示AOV图的邻接表
Status show_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList){
    if(aovGraphAdjacencyList==NULL)
        return FAIL;

    Status opResult=FAIL;
    int edgeLength=NO_EDGE;
    printf("\n\t\t当前AOV图的节点数:%d 图的边数:%d\n",aovGraphAdjacencyList->vertexsNum,
           aovGraphAdjacencyList->edgesNum);
    printf("\t\t");
    for(int i=0;i<aovGraphAdjacencyList->vertexsNum;i++)
        printf("%4d",i);
    printf("\n\n");

    for(int i=0;i<aovGraphAdjacencyList->vertexsNum;i++) {
        printf("%4d\t", i);

        for (int j = 0; j < aovGraphAdjacencyList->vertexsNum; j++) {
            //获取所有从i节点 连接到 j节点的边的长度
            opResult = existsEdge_AOVGraphAdjacencyList(aovGraphAdjacencyList,
                                                        i, j);
            if (FAIL == opResult) {
                //从i节点 到 j节点没有边
                printf("%4d", NO_EDGE);
            } else {
                //从i节点 到 j节点有边
                printf("%4d", 1);
            }
        }
        printf("\n");
    }
    printf("\n");
    return SUCCESS;
}

//通过传入二维矩阵创建AOV图的邻接表
Status create_AOVGraphAdjacencyList(AOVGraphAdjacencyList **pAovGraphAdjacencyList,
                                    int edges[][MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST],
                                    void *vertexDatas[],int vertexNum){
    //初始化有vertexNum个结点的AOV图的邻接表
    Status opResult= init_AOVGraphAdjacencyList(pAovGraphAdjacencyList,vertexDatas,vertexNum);
    if(FAIL==opResult)
        return FAIL;
    //为*pAovGraphAdjacencyList AOV图的邻接表设置从i到j的边
    for(int i=0;i<vertexNum;i++)
        for(int j=0;j<vertexNum;j++)
            if(edges[i][j]!=NO_EDGE){
                opResult= setEdge_AOVGraphAdjacencyList(*pAovGraphAdjacencyList,
                                                        i,j);
                if(opResult==FAIL)
                    return FAIL;
            }

    return SUCCESS;
}

//销毁有AOV图的邻接表
Status destroy_AOVGraphAdjacencyList(AOVGraphAdjacencyList **pAovGraphAdjacencyList){
    //AOV图的邻接表为空，直接返回
    if(*pAovGraphAdjacencyList==NULL)
        return SUCCESS;
    //清空所有边
    Status opResult= empty_AOVGraphAdjacencyList(*pAovGraphAdjacencyList);
    if(FAIL==opResult)
        return FAIL;
    //释放AOV图的邻接表
    free(*pAovGraphAdjacencyList);
    *pAovGraphAdjacencyList=NULL;
    return SUCCESS;
}

