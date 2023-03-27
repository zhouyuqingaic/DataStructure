//
// Created by zhouyuqing on 2023/3/26.
//

#include "directGraphAdjacencyMatrix.h"
#include "../../01SerialList/queueByLinkList/queueByLinkList.h"

//清空有向图邻接矩阵(即清空所有边)
Status empty_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix){
    if(directedGraphAdjacencyMatrix==NULL)
        return FAIL;
    //清空所有边
    int i,j;
    for(i=0;i<directedGraphAdjacencyMatrix->vertexsNum;i++)
        for(j=0;j<directedGraphAdjacencyMatrix->vertexsNum;j++)
            directedGraphAdjacencyMatrix->edges[i][j]=NO_EDGE;
    return SUCCESS;
}
//初始为有datasLenght个节点的有向图化邻接矩阵
Status init_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix,
                                         void *datas[],int datasLength){
    //判断节点个数是否在最大值范围内(1 ~ MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX)
    if(datasLength<0 || datasLength>MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX)
        return FAIL;

    if((*pDirectedGraphAdjacencyMatrix)==NULL) //有向图不存在，则创建
        *pDirectedGraphAdjacencyMatrix=(DirectedGraphAdjacencyMatrix *)malloc(sizeof(DirectedGraphAdjacencyMatrix));

    if(*pDirectedGraphAdjacencyMatrix==NULL)
        return FAIL;

    //设置边数,顶点数
    (*pDirectedGraphAdjacencyMatrix)->edgesNum=0;
    (*pDirectedGraphAdjacencyMatrix)->vertexsNum=datasLength;

    //清空所有边
    Status opResult = empty_DirectedGraphAdjacencyMatrix(*pDirectedGraphAdjacencyMatrix);
    if (opResult == FAIL)
        return FAIL;

    //设置边节点的数据
    for(int i=0;i<(*pDirectedGraphAdjacencyMatrix)->vertexsNum;i++)
        (*pDirectedGraphAdjacencyMatrix)->vertexs[i].data=datas[i];

    return SUCCESS;
}

//展示有向图邻接矩阵
Status showAdjacencyMatrix__DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix){
    if(directedGraphAdjacencyMatrix==NULL)
        return FAIL;
    printf("\n\t\t当前图的节点数:%d 图的边数:%d\n",directedGraphAdjacencyMatrix->vertexsNum,
           directedGraphAdjacencyMatrix->edgesNum);
    printf("\t\t");
    for(int i=0;i< directedGraphAdjacencyMatrix->vertexsNum;i++)
        printf("%4d",i);
    printf("\n");
    for(int i=0;i<directedGraphAdjacencyMatrix->vertexsNum;i++){
        printf("%4d\t",i);
        for(int j=0;j<directedGraphAdjacencyMatrix->vertexsNum;j++)
            printf("%4d",directedGraphAdjacencyMatrix->edges[i][j]);
        printf("\n");
    }
    printf("\n");
    return SUCCESS;
}

//为有向图邻接矩阵设置边
Status setEdge_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                               int startPoint,int endPoint,
                                               int edgeLength){
    //有向量图不存在，设置边失败
    if(directedGraphAdjacencyMatrix==NULL)
        return FAIL;
    //判断边的起点与终点是否在合理范围内(0~directedGraphAdjacencyMatrix->vertexNum-1)
    if(startPoint<0 || startPoint>=directedGraphAdjacencyMatrix->vertexsNum)
        return FAIL;
    if(endPoint<0 || endPoint>=directedGraphAdjacencyMatrix->vertexsNum)
        return FAIL;
    if(edgeLength==NO_EDGE && directedGraphAdjacencyMatrix->edges[startPoint][endPoint]!=NO_EDGE){
        //将原来存在的边设置为NO_EDGE,为消去边的情况，边数-1
        directedGraphAdjacencyMatrix->edgesNum-=1;
    }else if(edgeLength!=NO_EDGE && directedGraphAdjacencyMatrix->edges[startPoint][endPoint]==NO_EDGE){
        //将原来存在的边NO_EDGE不存在,将边设置为存在的情况，边数+1
        directedGraphAdjacencyMatrix->edgesNum+=1;
    }else{
        //原来边存在，且也不将边设置为NO_EDGE,则总边数不变
    }

    directedGraphAdjacencyMatrix->edges[startPoint][endPoint]=edgeLength;
    return SUCCESS;
}
//删除有向图邻接矩阵的边
Status deleteEdge_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                               int startPoint,int endPoint){
    //删除边就是将边权值设置为NO_EDGE
    return setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,startPoint,endPoint,NO_EDGE);
}
//设置节点data
Status setVertex_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                              int id,void *data){
    //有向图不存在，则设置节点数据失败
    if(directedGraphAdjacencyMatrix==NULL)
        return FAIL;
    //id合法范围(0~directedGraphAdjacencyMatrix->vertexNum-1)
    if(id<0 || id>=directedGraphAdjacencyMatrix->vertexsNum)
        return FAIL;
    directedGraphAdjacencyMatrix->vertexs[id].data=data;
    return SUCCESS;
}


//广度遍历
Status BFS(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,int vertexId,
           DirctedGraphAdjacencyMatrixNode *nodeList,int *indexNodeList,
           int visited[]){
    //创建辅助队列
    QueueByLinkList *queueByLinkList=NULL;
    Status opResult= init_QueueByLinkList(&queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    int currentId;
    //当前节点入队列
    int *currentVertexId=(int *)malloc(sizeof(int));
    *currentVertexId=vertexId;
    opResult=enqueue_QueueByLinkList(queueByLinkList,currentVertexId);
    if(FAIL==opResult)
        return FAIL;
    //访问入队节点并加入访问队列
    visited[*currentVertexId]=1;
    nodeList[*indexNodeList]=directedGraphAdjacencyMatrix->vertexs[*currentVertexId];
    (*indexNodeList)++;

    //广度数遍历所有节点
    while(!isEmpty_QueueByLinkList(queueByLinkList)){
        //队列头元素出队
        opResult=dequeue_QueueByLinkList(queueByLinkList,(void **)&currentVertexId);
        if(FAIL==opResult)
            return FAIL;
        currentId=*currentVertexId;
        free(currentVertexId); //释放出队元素

        //currentId节点所连接所有未被访问的节点入队列,并访问
        //没有被访问过则入队并访问
        for(int i=0;i< directedGraphAdjacencyMatrix->vertexsNum;i++){
            if(directedGraphAdjacencyMatrix->edges[currentId][i]!=NO_EDGE && visited[i]==0){
                //当前currentId节点所连接的i节点没有被访问过,则入队并访问
                currentVertexId=(int *)malloc(sizeof(int));
                *currentVertexId=i;
                opResult=enqueue_QueueByLinkList(queueByLinkList,currentVertexId);
                if(FAIL==opResult)
                    return FAIL;
                //访问入队节点并加入访问队列
                visited[*currentVertexId]=1;
                nodeList[*indexNodeList]=directedGraphAdjacencyMatrix->vertexs[*currentVertexId];
                (*indexNodeList)++;
            }
        }
    }

    //销毁辅助队列
    opResult=destroy_QueueByLinkList(queueByLinkList);
    if(FAIL==opResult)
        return FAIL;

    return SUCCESS;
}
//从vertexId广度遍历有向图邻接矩阵
Status BFS_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                        int vertexId,void ***pListData,int *lengthListData){
    if(directedGraphAdjacencyMatrix==NULL)
        return FAIL;
    //设置节点访问数组
    int visited[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    for(int i=0;i<directedGraphAdjacencyMatrix->vertexsNum;i++)
        visited[i]=0;
    DirctedGraphAdjacencyMatrixNode nodeList[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    int indexNodeList=0;

    //开始广度遍历邻接矩阵
    BFS(directedGraphAdjacencyMatrix,vertexId,nodeList,&indexNodeList,visited);

    //返回遍历出来的data数据
    if(*pListData!=NULL)
        free(*pListData);
    *pListData=(void **)malloc(sizeof(void *)*indexNodeList);
    *lengthListData=indexNodeList;

    for(int i=0;i<indexNodeList;i++)
        (*pListData)[i]=nodeList[i].data;

    return SUCCESS;
}


//深度遍历
Status DFS(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,int vertexId,
                                        DirctedGraphAdjacencyMatrixNode *nodeList,int *indexNodeList,
                                        int *visited){
    if(visited[vertexId]==0){
        //当前vertexId节点没有被访问过
        //直接加入访问序列
        nodeList[*indexNodeList]=directedGraphAdjacencyMatrix->vertexs[vertexId];
        (*indexNodeList)++;
        //将该节点标记已访问
        visited[vertexId]=1;
    }
    //当前vertexId节点已经被访问过
    //找到从该节点发出的边连接的没有被访问过的节点
    for(int i=0;i<directedGraphAdjacencyMatrix->vertexsNum;i++)
        if(directedGraphAdjacencyMatrix->edges[vertexId][i]!=NO_EDGE && visited[i]==0)
            DFS(directedGraphAdjacencyMatrix,i,nodeList,indexNodeList,visited);
    return SUCCESS;
}
//从vertexId深度遍历有向图邻接矩阵
Status DFS_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                        int vertexId,void ***pListData,int *lengthListData){
    if(directedGraphAdjacencyMatrix==NULL)
        return FAIL;
    //设置节点访问数组
    int visited[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    for(int i=0;i<directedGraphAdjacencyMatrix->vertexsNum;i++)
        visited[i]=0;
    DirctedGraphAdjacencyMatrixNode nodeList[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    int indexNodeList=0;
    //开始深度遍历有向图邻接矩阵
    DFS(directedGraphAdjacencyMatrix,vertexId,nodeList,&indexNodeList,visited);

    //返回遍历出来的data数据
    if(*pListData!=NULL)
        free(*pListData);
    *pListData=(void **)malloc(sizeof(void *)*indexNodeList);
    *lengthListData=indexNodeList;

    for(int i=0;i<indexNodeList;i++)
        (*pListData)[i]=nodeList[i].data;

    return SUCCESS;
}

//通过传入二维矩阵创建有向图邻接矩阵
Status create_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix,
                                           int edges[][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX],
                                           void *datas[],int datasLength){
    //初始化为有datasLength个节点邻接矩阵
    Status opResult= init_DirectedGraphAdjacencyMatrix(pDirectedGraphAdjacencyMatrix,datas,datasLength);
    if(FAIL==opResult)
        return FAIL;
    //为邻接矩阵设置边,并统计边数
    for(int i=0;i<(*pDirectedGraphAdjacencyMatrix)->vertexsNum;i++)
        for(int j=0;j<(*pDirectedGraphAdjacencyMatrix)->vertexsNum;j++) {
            (*pDirectedGraphAdjacencyMatrix)->edges[i][j] = edges[i][j];
            if(edges[i][j]!=NO_EDGE)
                (*pDirectedGraphAdjacencyMatrix)->edgesNum++;
        }
    return SUCCESS;
}


//迪杰斯特拉算法，求从vertexId开始到其余节点的最短路径
Status Dijkstra(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,int vertexId,int **pDist,int **pPath){
    if(directedGraphAdjacencyMatrix==NULL)
        return FAIL;

    //最短路径集
    int *set=(int *)malloc(sizeof(int)*directedGraphAdjacencyMatrix->vertexsNum);

    //路径列表
    if(*pPath!=NULL)
        free(*pPath);
    *pPath=(int *)malloc(sizeof(int)*directedGraphAdjacencyMatrix->vertexsNum);
    int *path=*pPath;

    //通往所有节点的最短路径长度
    if(*pDist!=NULL)
        free(*pDist);
    *pDist=(int *)malloc(sizeof(int)*directedGraphAdjacencyMatrix->vertexsNum);
    int *dist=*pDist;

    //设置各数组数据
    for(int i=0;i<directedGraphAdjacencyMatrix->vertexsNum;i++){
        set[i]=0;
        dist[i]=directedGraphAdjacencyMatrix->edges[vertexId][i];
        if(dist[i]!=NO_EDGE){ //如果从vetexId到i有边，就将i的上个节点设置为vertexId
            path[i]=vertexId;
        }else{
            path[i]=-1; //i节点暂时没有最短路径的上个节点
        }
    }
    //将vertexId作为最短路径的第一个节点
    set[vertexId]=1;
    path[vertexId]=-1;

    int MIN=NO_EDGE,u=0;
    //开始构建到剩余directedGraphAdjacencyMatrix->vertexsNum-1个节点的最短路径
    for(int i=0;i<directedGraphAdjacencyMatrix->vertexsNum-1;i++){
        //选出通往剩余节点的最短路径
        for(int j=0;j<directedGraphAdjacencyMatrix->vertexsNum;j++){
            if(set[j]==0 &&  dist[j]!=NO_EDGE){ //当前存在到j的最短路径
                //记录最短路径
                if(MIN==NO_EDGE) {
                    u=j;
                    MIN = dist[j];
                }else {
                    if (MIN>dist[j]){
                        u=j;
                        MIN=dist[j];
                    }
                }
            }
        }
        //将选出的顶点并入最短路径中
        set[u]=1;
        //通过刚选出的顶点作为中间节点，更新到剩余节点的最短路径
        for(int j=0;j<directedGraphAdjacencyMatrix->vertexsNum;j++){
            //判断从顶点u出发到剩余未并入最短路径的节点的，是否有更短路径，
            // 有的话就更新原来的路径长度dist与路径path
            if(set[j]==0){
                if(dist[j]!=NO_EDGE && directedGraphAdjacencyMatrix->edges[u][j]!=NO_EDGE){
                    //原本存在到j的路径 且存在u到j的路径
                    //将u到j路径 与 原来到j的路径 比较更新
                    if(dist[j]>dist[u]+directedGraphAdjacencyMatrix->edges[u][j]){
                        dist[j]=dist[u]+directedGraphAdjacencyMatrix->edges[u][j];
                        path[j]=u;
                    }
                }else{
                    if(dist[j]==NO_EDGE && directedGraphAdjacencyMatrix->edges[u][j]!=NO_EDGE){
                        //原本不存在到j的路径 但存在u到j的路径
                        //原来到j的路径 更新为u到j的路径
                        dist[j]=dist[u]+directedGraphAdjacencyMatrix->edges[u][j];
                        path[j]=u;
                    }
                }
            }
        }
    }

    free(set);
    return SUCCESS;
}

//利用向图邻接矩阵的地杰斯特拉算法，得到从startVertex到endVertex最短路径
Status dijkstra_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,int startVertex,int endVertex,void ***pListData,int *lengthListData){
    if(directedGraphAdjacencyMatrix==NULL)
        return FAIL;

    int *dist=NULL;
    int *path=NULL;
    //构建从startVertex到剩余顶点最短路径
    Status opResult= Dijkstra(directedGraphAdjacencyMatrix,startVertex,&dist,&path);

    int stack[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX],top=-1,current=endVertex;
    //到endVetex的最短路径不存在，则寻路算法失败
    if(path[endVertex]==-1)
        return FAIL;

    //通过path获取从startVertex到endVertex最短路径的序列
    while(path[current]!=-1){
        stack[++top]=current;
        current=path[current];
    }
    //将current(即startPoint)源点加入栈中
    stack[++top]=current;

    //返回路径节点的data数据列表
    if(*pListData!=NULL)
        free(*pListData);
    *pListData=(void **)malloc(sizeof(void *)*top);
    *lengthListData=top;

    //路径序列退栈，并将路径节点data加入data列表中
    int indexDatas=0;
    while(top!=-1){
        current=stack[top--];
        (*pListData)[indexDatas++]=directedGraphAdjacencyMatrix->edges[current];
    }

    return SUCCESS;
}

//销毁有向图邻接矩阵
Status destroy_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix){
    //邻接矩阵为空 ，直接返回
    if(*pDirectedGraphAdjacencyMatrix==NULL)
        return SUCCESS;
    //清空所有边
    Status opResult=empty_DirectedGraphAdjacencyMatrix(*pDirectedGraphAdjacencyMatrix);
    if(FAIL==opResult)
        return FAIL;
    //释放邻接矩阵
    free(*pDirectedGraphAdjacencyMatrix);
    *pDirectedGraphAdjacencyMatrix=NULL;
    return SUCCESS;
}