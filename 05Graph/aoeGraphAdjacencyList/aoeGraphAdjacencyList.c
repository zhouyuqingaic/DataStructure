//
// Created by zhouyuqing on 2023/4/19.
//

#include "aoeGraphAdjacencyList.h"
#include "../../01SerialList/stackLinkList/stackLinkList.h"
#include "../directGraphAdjacencyMatrix/directGraphAdjacencyMatrix.h"

//清空AOE图的邻接表
Status empty_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList){
    return empty_AOVGraphAdjacencyList(aoeGraphAdjacencyList);
}
//初始化AOE图的邻接表
Status init_AOEGraphAdjacencyList(AOEGraphAdjacencyList **pAoeGraphAdjacencyList,
                                  void *vertexDatas[],
                                  int vertexsNum){
    return init_AOVGraphAdjacencyList(pAoeGraphAdjacencyList,vertexDatas,vertexsNum);
}
//为AOE图的邻接表设置边,长度为length
Status setEdge_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList,
                                     int startPoint,int endPoint,int length){
    if(length<=0)
        //边的值为负数或者0表示该边不存在，不用设置 直接返回
        return SUCCESS;

    //设置从startPoint到endPoint的边
    Status opResult=setEdge_AOVGraphAdjacencyList(aoeGraphAdjacencyList,startPoint,endPoint);
    if(FAIL==opResult)
        return FAIL;
    //探查从startPoint发出的所有边
    Arc_AOEGraphAdjacencyList *currentArc=aoeGraphAdjacencyList->vertexs[startPoint].firstArc;
    while(currentArc!=NULL){
        //找到从startPoint发出且指向endPoint的边，则设置边的权值，表明设置成功
        if(currentArc->adjVex==endPoint){
            currentArc->length=length;
            return SUCCESS;
        }
        currentArc=currentArc->nextArc;
    }
    return FAIL;
}

//获取AOE图的邻接表中从startPoint到endPoint的边的权值length
Status getEdge_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList,
                                     int startPoint,int endPoint,int *length){
    //探查从startPoint到endPoint的边是否存在
    Status opResult= existsEdge_AOVGraphAdjacencyList(aoeGraphAdjacencyList,startPoint,endPoint);
    if(FAIL==opResult)
        return FAIL;
    else{
        //探查从startPoint发出的所有边
        Arc_AOEGraphAdjacencyList *currentArc=aoeGraphAdjacencyList->vertexs[startPoint].firstArc;
        while(currentArc!=NULL){
            //当前边从startPoint发出连接到endPoint节点
            if(currentArc->adjVex==endPoint) {
                //获取边的权值，返回成功
                *length=currentArc->length;
                return SUCCESS;
            }
            currentArc=currentArc->nextArc;
        }
        //没有从startPoint连接到endPoint的边
        return FAIL;
    }
}

//获取AOE图的邻接表中etv 事件最早发生数组(每个节点表示一个事件) 和 逆拓扑排序序列
Status getEtvAndUnTop_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList,
                                    int **pEtvList,int **pUnTopList){
    if(aoeGraphAdjacencyList==NULL)
        return FAIL;

    //创建etv数组
    if(*pEtvList!=NULL)
        free(*pEtvList);
    *pEtvList=(int *)malloc(sizeof(int)*aoeGraphAdjacencyList->vertexsNum);
    if(*pEtvList==NULL)
        return FAIL;
    //初始化etv
    for(int i=0;i<aoeGraphAdjacencyList->vertexsNum;i++)
        pEtvList[i]=0;

    //创建upTopList逆拓扑排序数组
    if(*pUnTopList!=NULL)
        free(*pUnTopList);
    *pUnTopList=(int *)malloc(sizeof(int)*aoeGraphAdjacencyList->vertexsNum);
    if(*pUnTopList==NULL)
        return FAIL;
    //初始化upTopList逆拓扑排序数组
    for(int i=0;i<aoeGraphAdjacencyList->vertexsNum;i++)
        (*pUnTopList)[i]=-1;

    //创建辅助栈
    StackLinkList *stackLinkList=NULL;
    Status opResult= init_StackLinkList(&stackLinkList);
    if(FAIL==opResult)
        return FAIL;

    //创建辅助栈02
    StackLinkList *stackLinkList02=NULL;
    opResult= init_StackLinkList(&stackLinkList02);
    if(FAIL==opResult)
        return FAIL;

    //将AOE图中所有入度为0节点入栈
    for(int i=0;i<aoeGraphAdjacencyList->vertexsNum;i++){
        if(aoeGraphAdjacencyList->vertexs[i].enArcAmount==0){
            opResult= push_StackLinkList(
                stackLinkList,&(aoeGraphAdjacencyList->vertexs[i])
            );
            if(FAIL==opResult)
                return FAIL;
        }
    }
    //开始拓扑排序并设置etv数组
    Vertex_AOEGraphAdjacencyList *currentVertex=NULL;
    Arc_AOEGraphAdjacencyList *currentArc=NULL;
    while(!isEmpty_StackLinkList(stackLinkList)){
        //元素出栈
        opResult= pop_StackLinkList(stackLinkList,(void *)&currentVertex);
        if(FAIL==opResult)
            return FAIL;

        //将出栈元素加入 辅助栈02中(用于获取逆拓扑排序序列)
        opResult= push_StackLinkList(stackLinkList02,(void *)&currentVertex);
        if(FAIL==opResult)
            return FAIL;

        //访问过的节点从AOE图屏蔽，将其发出的边连接的节点的入度-1
        currentArc=currentVertex->firstArc;
        while(currentArc!=NULL){
            //更新当前边所指向的节点(currentVertex->firstArc)的etv
            //即该节点的所代表事件的最早发生时间(etv)
            if( (*pEtvList)[currentArc->adjVex]
                <
                (*pEtvList)[currentVertex->id]+currentArc->length ){
                (*pEtvList)[currentArc->adjVex]=(*pEtvList)[currentVertex->id]+currentArc->length;
            }
            aoeGraphAdjacencyList->vertexs[currentArc->adjVex].enArcAmount-=1;
            if(aoeGraphAdjacencyList->vertexs[currentArc->adjVex].enArcAmount==0){
                //如果入度减1后，边所连接的节点currentArc->adjVex入度为0,
                //则将新的入度为0的currentArc-adjVex节点加入栈
                opResult= push_StackLinkList(
                        stackLinkList,&(aoeGraphAdjacencyList->vertexs[currentArc->adjVex])
                );
                if(FAIL==opResult)
                    return FAIL;
            }
            currentArc=currentArc->nextArc;
        }
    }

    //辅助栈02所有元素出栈
    //出栈序列就是 逆拓扑排序序列
    int i=0;
    while(!isEmpty_StackLinkList(stackLinkList02)){
        //元素出栈
        opResult= pop_StackLinkList(stackLinkList,(void *)&currentVertex);
        if(FAIL==opResult)
            return FAIL;
        //将出栈元素加入逆拓扑排序列表
        (*pUnTopList)[i]=currentVertex->id;
    }

    //销毁辅助栈
    opResult= destroy_StackLinkList(&stackLinkList);
    if(FAIL==opResult)
        return FAIL;
    opResult= destroy_StackLinkList(&stackLinkList02);
    if(FAIL==opResult)
        return FAIL;

    return SUCCESS;
}


//获取AOE图的邻接表的关键路径(关键路径的边列表)
Status getCriticalPath_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList,
                                             Arc_AOEGraphAdjacencyList ***pCriticalPathList,
                                             int *criticalPathListLength){
    if(aoeGraphAdjacencyList==NULL)
        return FAIL;

    //重置关键路径边列表
    if(*pCriticalPathList!=NULL)
        free(*pCriticalPathList);
    //边数最多为
    //aoeGraphAdjacencyList->vertexsNum * (aoeGraphAdjacencyList->vertexsNum-1)
    //即每个节点都与其他aoeGraphAdjacencyList->vertexsNum-1 个节点相连
    *pCriticalPathList=(Arc_AOEGraphAdjacencyList **)malloc(
            sizeof(Arc_AOEGraphAdjacencyList *)
            *
            (
                aoeGraphAdjacencyList->vertexsNum*(aoeGraphAdjacencyList->vertexsNum-1)
            )
        );
    *criticalPathListLength=0;


    //获取 AOE图邻接表 的etv表 和 逆拓扑排序序列
    int *etvList=NULL;
    int *unTopList=NULL;
    Status opResult=getEtvAndUnTop_AOEGraphAdjacencyList(
            aoeGraphAdjacencyList,&etvList,&unTopList
        );
    if(FAIL==opResult)
        return FAIL;

    //创建ltv数组(事件最晚发生表)
    int *ltvList=(int *)malloc(sizeof(int)*aoeGraphAdjacencyList->vertexsNum);
    if(*ltvList==NULL)
        return FAIL;
    //初始化ltv表
    for(int i=0;i<aoeGraphAdjacencyList->vertexsNum;i++)
        ltvList[i]=etvList[i];

    //利用逆拓扑排序序列 构建 ltv事件最晚发生时间表
    Vertex_AOEGraphAdjacencyList currentVertex;
    Arc_AOEGraphAdjacencyList *currentArc=NULL;
    //遍历逆拓扑排序序列的每个节点
    for(int i=0;i<aoeGraphAdjacencyList->vertexsNum;i++){
        //获取当前节点
        currentVertex=aoeGraphAdjacencyList->vertexs[unTopList[i]];
        //遍历当前节点的每条边
        currentArc=currentVertex.firstArc;
        while(currentArc!=NULL){
            //利用从该节点发出的所有边
            //更新当前节点事件的最迟发生事件的ltv
            //即该节点的所代表事件的最迟发生时间(ltv)
            if( ltvList[currentVertex.id]
                >
                ltvList[currentArc->adjVex]-currentArc->length   ){
                ltvList[currentVertex.id]=ltvList[currentArc->adjVex]-currentArc->length;
            }
            currentArc=currentArc->nextArc;
        }
    }



    //求各边所代表的 活动 的最早开始事件ete,活动 的最晚开始事件lte
    int ete,lte;
    *criticalPathListLength=0;
    for(int i=0;i<aoeGraphAdjacencyList->vertexsNum;i++){
        //获取当前节点
        currentVertex=aoeGraphAdjacencyList->vertexs[unTopList[i]];
        //遍历当前节点的每条边
        currentArc=currentVertex.firstArc;
        while(currentArc!=NULL){
            //求当前边代表活动的最早开始时间 的ete
            ete=etvList[currentVertex.id]; //即i
            //求当前边代表活动的最晚开始时间 的lte
            lte=ltvList[currentArc->adjVex]-currentArc->length;

            //如果lte和vte相等表示活动为关键活动，改边为关键路径的边
            if(ete==lte){
                *pCriticalPathList[*criticalPathListLength]=currentArc;
                (*criticalPathListLength)++;
            }

            currentArc=currentArc->nextArc;
        }
    }


    return SUCCESS;
}


//通过邻接矩阵的形式展示AOE图的邻接表
Status show_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList){
    if(aoeGraphAdjacencyList==NULL)
        return FAIL;

    Status opResult=FAIL;
    int edgeLength=NO_EDGE;
    printf("\n\t\t当前AOE图的节点数:%d 图的边数:%d\n",aoeGraphAdjacencyList->vertexsNum,
           aoeGraphAdjacencyList->edgesNum);
    printf("\t\t");
    for(int i=0;i<aoeGraphAdjacencyList->vertexsNum;i++)
        printf("%4d",i);
    printf("\n\n");

    for(int i=0;i<aoeGraphAdjacencyList->vertexsNum;i++) {
        printf("%4d\t", i);

        for (int j = 0; j < aoeGraphAdjacencyList->vertexsNum; j++) {
            //获取所有从i节点 连接到 j节点的边的长度
            opResult = getEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                                        i, j,&edgeLength);
            if (FAIL == opResult) {
                //从i节点 到 j节点没有边
                printf("%4d", NO_EDGE);
            } else {
                //从i节点 到 j节点有边
                printf("%4d", edgeLength);
            }
        }
        printf("\n");
    }
    printf("\n");
    return SUCCESS;
}

//通过传入二维矩阵创建AOE图的邻接表
Status create_AOEGraphAdjacencyList(AOEGraphAdjacencyList **pAoeGraphAdjacencyList,
                                    int edges[][MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST],
                                    void *vertexDatas[],int vertexNum){
    //初始化有vertexNum个结点的AOE图的邻接表
    Status opResult= init_AOEGraphAdjacencyList(pAoeGraphAdjacencyList,vertexDatas,vertexNum);
    if(FAIL==opResult)
        return FAIL;
    //为*pAoeGraphAdjacencyList AOE图的邻接表设置从i到j的边
    for(int i=0;i<vertexNum;i++)
        for(int j=0;j<vertexNum;j++)
            if(edges[i][j]!=NO_EDGE){
                opResult= setEdge_AOEGraphAdjacencyList(*pAoeGraphAdjacencyList,
                                                        i,j,edges[i][j]);
                if(opResult==FAIL)
                    return FAIL;
            }

    return SUCCESS;
}

//销毁有AOV图的邻接表
Status destroy_AOEGraphAdjacencyList(AOEGraphAdjacencyList **pAoeGraphAdjacencyList){
    return destroy_AOVGraphAdjacencyList(pAoeGraphAdjacencyList);
}
