//
// Created by zhouyuqing on 2023/4/3.
//

#include "undirectGraphAdjacencyMatrix.h"

//清空无向图邻接矩阵(即清空所有边)
Status empty_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix){
    return empty_DirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix);
}
//初始为有vertexsNum个节点的无向图邻接矩阵
Status init_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix,
                                           void *vertexsData[],int vertexsNum){
    return init_DirectedGraphAdjacencyMatrix(pUnDirectedGraphAdjacencyMatrix,vertexsData,vertexsNum);
}
//展示无向图邻接矩阵
Status showAdjacencyMatrix__UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix){
    return showAdjacencyMatrix__DirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix);
}

//为有无图邻接矩阵设置边
Status setEdge_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                              int aVertex,int bVertex,
                                              int edgeLength){
    if(unDirectedGraphAdjacencyMatrix==NULL)
        return FAIL;

    //判断两点是否在合法范围内(0~unDirectedGraphAdjacencyMatrix->vertexNum-1)
    if(aVertex<0 || aVertex>=unDirectedGraphAdjacencyMatrix->vertexsNum)
        return FAIL;
    if(bVertex<0 || bVertex>=unDirectedGraphAdjacencyMatrix->vertexsNum)
        return FAIL;

    if(edgeLength==NO_EDGE && unDirectedGraphAdjacencyMatrix->edges[aVertex][bVertex]!=NO_EDGE){
        //原来边存在不为NO_EDGE,现在将边设置为NO_EDGE消去边
        unDirectedGraphAdjacencyMatrix->edgesNum-=1;
    }else if(edgeLength!=NO_EDGE && unDirectedGraphAdjacencyMatrix->edges[aVertex][bVertex]==NO_EDGE){
        //原来边NO_EDGE不存在,将边设置为存在的情况，边数+1
        unDirectedGraphAdjacencyMatrix->edgesNum+=1;
    }else{
        //其他情况
        //原来边存在，且也不将边设置为NO_EDGE,则总边数不变
        //原来边不存在，且也将边设置为NO_EDGE,则总边数不变
    }

    //无向图的边为双向
    //设置从startVertex到endVertex的边
    unDirectedGraphAdjacencyMatrix->edges[aVertex][bVertex]=edgeLength;
    //设置从endVertex到startVertex的边
    unDirectedGraphAdjacencyMatrix->edges[bVertex][aVertex]=edgeLength;

    return SUCCESS;
}
//设置无向图节点data
Status setVertex_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                                int id,void *data){
    return setVertex_DirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,id,data);
}

typedef struct{
    int  aVertex,bVertex; //边连接的两个顶点
    int edgeLength; //边的长度
}Edge_UnDirectedGraphAdjacencyMatrix;

//通过普里姆算法生成最小生成树，返回表示最小生成树的无向图邻接矩阵pUnDirectedGraphAdjacencyMatrix_Result
Status primMinimumSpanningTree_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                           int startVertex,UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix_Result){
    if(unDirectedGraphAdjacencyMatrix==NULL)
        return FAIL;
    //获取原无向图的节点data数据
    int datasLength=0;
    void *datas[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    for(datasLength=0;datasLength<unDirectedGraphAdjacencyMatrix->vertexsNum;datasLength++)
        datas[datasLength]=unDirectedGraphAdjacencyMatrix->vertexs[datasLength].data;
    //创建与原无向图的节点数相同的空无向图(表示最小生成树的无向图)
    Status opResult=init_UnDirectedGraphAdjacencyMatrix(pUnDirectedGraphAdjacencyMatrix_Result,
                                                        datas,datasLength);
    if(FAIL==opResult)
        return FAIL;

    int v=startVertex;
    Edge_UnDirectedGraphAdjacencyMatrix lowCost_Edge[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX]; //当前生成树到剩余节点的最短边长
    int vSet[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX]; //已经并入树中的节点集合
    //将v节点加入最小生成树，并设置最小生成树到剩余节点的最短边长
    for(int i=0;i<unDirectedGraphAdjacencyMatrix->vertexsNum;i++){

        lowCost_Edge[i].aVertex=v;
        lowCost_Edge[i].bVertex=i;
        lowCost_Edge[i].edgeLength=unDirectedGraphAdjacencyMatrix->edges[v][i];

        if(i==v)
            vSet[i]=1;
        else
            vSet[i]=0;
    }

    //将剩余unDirectedGraphAdjacencyMatrix->vertexsNum-1个节点加入最小生成树中
    int min;
    for(int i=0;i<unDirectedGraphAdjacencyMatrix->vertexsNum-1;i++){
        //选出当前生成树到剩余节点的最短边
        min=NO_EDGE;
        for(int j=0;j<unDirectedGraphAdjacencyMatrix->vertexsNum;j++){
            if(vSet[j]==0 && lowCost_Edge[j].edgeLength!=NO_EDGE){
                //当前最小生成树到剩余节点j的边存在
                if(min==NO_EDGE){
                    min=lowCost_Edge[j].edgeLength;
                    v=j;
                }else{
                    if(min>lowCost_Edge[j].edgeLength){
                        min=lowCost_Edge[j].edgeLength;
                        v=j;
                    }
                }
            }
        }
        if(min==NO_EDGE){
            //到剩余节点没有边，剩余节点不可达，图错误
            //销毁结果图
            opResult=destroy_UnDirectedGraphAdjacencyMatrix(pUnDirectedGraphAdjacencyMatrix_Result);
            if(FAIL==opResult){
                perror("销毁结果图失败!");
            }
            return FAIL;
        }
        //最短边连接的剩余节点加入树中
        vSet[v]=1;

        //向表示最小生成树的无向图添加边
        opResult= setEdge_UnDirectedGraphAdjacencyMatrix(*pUnDirectedGraphAdjacencyMatrix_Result,
                                                 lowCost_Edge[v].aVertex,lowCost_Edge[v].bVertex,lowCost_Edge[v].edgeLength);
        if(FAIL==opResult){
            opResult=destroy_UnDirectedGraphAdjacencyMatrix(pUnDirectedGraphAdjacencyMatrix_Result);
            if(FAIL==opResult){
                perror("销毁结果图失败!");
            }
            return FAIL;
        }


        //以新并入树的v节点，探查是否有到剩余节点的更短边，来更新lowCost数据
        for(int j=0;j<unDirectedGraphAdjacencyMatrix->vertexsNum;j++){
            if(vSet[j]==0){
                if(lowCost_Edge[j].edgeLength==NO_EDGE){
                    //原来生成树到j不可达，而v到j节点有边，则将其更
                    if(unDirectedGraphAdjacencyMatrix->edges[v][j]!=NO_EDGE) {
                        lowCost_Edge[j].edgeLength = unDirectedGraphAdjacencyMatrix->edges[v][j];
                        lowCost_Edge[j].aVertex=v;
                        lowCost_Edge[j].bVertex=j;
                    }
                }else{
                    //原来生成树到j可达，而v到j节点有边且边比原来生成树到j的距离更短，则将其更
                    if(unDirectedGraphAdjacencyMatrix->edges[v][j]!=NO_EDGE &&
                        unDirectedGraphAdjacencyMatrix->edges[v][j]<lowCost_Edge[j].edgeLength){
                        lowCost_Edge[j].edgeLength = unDirectedGraphAdjacencyMatrix->edges[v][j];
                        lowCost_Edge[j].aVertex=v;
                        lowCost_Edge[j].bVertex=j;
                    }
                }
            }
        }



    }

    return SUCCESS;
}


int getRoot_SearchUnionSet(int *searchUnionSet,int a){
    //在并查集中寻找a的根节点
    while(a!=searchUnionSet[a])
        a=searchUnionSet[a];
    return a;
}

//通过克鲁斯卡尔算法生成最小生成树，返回表示最小生成树的无向图邻接矩阵pUnDirectedGraphAdjacencyMatrix_Result
Status kruskalMinimumSpanningTree_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                                 UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix_Result){
    if(unDirectedGraphAdjacencyMatrix==NULL)
        return FAIL;
    //获取原无向图的节点data数据
    int datasLength=0;
    void *datas[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    for(datasLength=0;datasLength<unDirectedGraphAdjacencyMatrix->vertexsNum;datasLength++)
        datas[datasLength]=unDirectedGraphAdjacencyMatrix->vertexs[datasLength].data;
    //创建与原无向图节点数相同的空无向图(表示最小生成树的无向图)
    Status opResult= init_UnDirectedGraphAdjacencyMatrix(pUnDirectedGraphAdjacencyMatrix_Result,
                                                         datas,datasLength);
    if(FAIL==opResult)
        return FAIL;

    Edge_UnDirectedGraphAdjacencyMatrix sorted_edge[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX]; //创建所有边的数组
    int sorted_edge_size=0;

    //将所有存在的边加入sorted_edge中
    //以从i到j的边如果存在就加入sorted_edge,有向量图关于主对角线对称，所以只用考虑了主对角线下方的
    for(int i=0;i<unDirectedGraphAdjacencyMatrix->vertexsNum;i++)
        for(int j=0;j<i;j++)
            if(unDirectedGraphAdjacencyMatrix->edges[i][j]!=NO_EDGE){
                sorted_edge[sorted_edge_size].edgeLength=unDirectedGraphAdjacencyMatrix->edges[i][j];
                sorted_edge[sorted_edge_size].aVertex=i;
                sorted_edge[sorted_edge_size].bVertex=j;
                sorted_edge_size++;
            }

    //利用插入排序,对加入边数组的边进行排序
    Edge_UnDirectedGraphAdjacencyMatrix tempEdge;
    for(int i=1;i<sorted_edge_size;i++){
        //记录待插入的元素
        tempEdge=sorted_edge[i];
        //将待插入的元素插入到索引为:0~i-1 的有序序列中
        int j=i-1;
        while(j>=0 && tempEdge.edgeLength<sorted_edge[j].edgeLength) {
            sorted_edge[j + 1] = sorted_edge[j];
            j--;
        }
        sorted_edge[j+1]=tempEdge;
    }

    //初始化并查集
    int searchUnionSet[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX]; //并查集数组
    for(int i=0;i<sorted_edge_size;i++)
        searchUnionSet[i]=i;

    //遍历从小到大,如果不形成环，就将边加入边集中
    int aSetRoot,bSetRoot;
    for(int i=0;i<sorted_edge_size;i++){
        //获取前边两个端点所属集合的根
        aSetRoot= getRoot_SearchUnionSet(searchUnionSet,sorted_edge[i].aVertex);
        bSetRoot= getRoot_SearchUnionSet(searchUnionSet,sorted_edge[i].bVertex);
        //如果两个节点各自所属的集合不同，则加入该边到树中不会形成环
        if(aSetRoot!=bSetRoot){
            //将边加入到树中
            opResult=setEdge_UnDirectedGraphAdjacencyMatrix(*pUnDirectedGraphAdjacencyMatrix_Result,
                                                   sorted_edge[i].aVertex,sorted_edge[i].bVertex,sorted_edge[i].edgeLength);
            if(FAIL==opResult)
                return FAIL;
            //该边加入树后，两端点各自所属的集合合并成一个
            searchUnionSet[aSetRoot]=bSetRoot;
        }
    }

    return SUCCESS;
}

//在无向图的最小生成树中，获取从aVertex到bVertex的路径
Status pathMinimumSpanningTree_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                                              int aVertex,int bVertex,void ***pDataList,int *lengthDataList){
    if(unDirectedGraphAdjacencyMatrix==NULL)
        return FAIL;

    int path[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX]; //路径数组,从aVertex节点开始到各节点的路径,元素i的值为i节点在该路径上的上个节点
    int vSet[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX]; //访问节点集合
    for(int i=0;i<unDirectedGraphAdjacencyMatrix->vertexsNum;i++) {
        vSet[i] = 0; //标记为未访问过
        path[i]=-1; //路径数组中，i在路径上的上的上个节点不存在
    }
    //a节点加入访问集合
    vSet[aVertex]=1;
    path[aVertex]=-1;

    //寻找通往剩余unDirectedGraphAdjacencyMatrix->vertexsNum-1个节点的路径
    for(int i=0;i<unDirectedGraphAdjacencyMatrix->vertexsNum-1;i++){
        for(int j=0;j<unDirectedGraphAdjacencyMatrix->vertexsNum;j++){
            if(vSet[i]==1 && vSet[j]==0 && unDirectedGraphAdjacencyMatrix->edges[i][j]!=NO_EDGE){
                //最小生成树中 有从到访问过的i节点到 没访问过的j节点的边
                //将该边加入路径中,并访问
                path[j]=i;
                vSet[j]=1;
            }
        }
    }

    //通过path数组获取到从aVertex到bVertex的路径
    int topStack=-1;
    int stack[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    int currentVertex=bVertex;

    //到bVertex节点的短路径不存在，则获取最小生成树上的节点之间的路径失败
    if(path[bVertex]==-1)
        return FAIL;

    //通过path获取从aVertex到bVertex在最小生成树
    while(path[currentVertex]!=-1){
        stack[++topStack]=currentVertex;
        currentVertex=path[currentVertex]; //获取当前节点在路径中的上个节点
    }
    //将current(即aVertex)源点加入栈中
    stack[++topStack]=currentVertex;

    //返回路径节点的data的数据列表
    if(*pDataList!=NULL)
        free(*pDataList);
    *pDataList=(void **)malloc(sizeof(void *)*(topStack+1));
    *lengthDataList=topStack+1;

    //路径序列退栈，并将路径节点data加入data列表中
    int indexDatas=0;
    while(topStack!=-1){
        currentVertex=stack[topStack--];
        (*pDataList)[indexDatas++]=unDirectedGraphAdjacencyMatrix->vertexs[currentVertex].data;
    }

    return SUCCESS;
}

//通过传入二维矩阵创建有无向图邻接矩阵
Status create_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix,
                                             int edges[][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX],
                                             void *vertexsData[],int vertexsNum){
    Status opResult= create_DirectedGraphAdjacencyMatrix(pUnDirectedGraphAdjacencyMatrix,
                                                 edges,vertexsData,vertexsNum);
    if(FAIL==opResult)
        return FAIL;
    //由于传入的矩阵是无向图邻接矩阵，所有无向图的边数为将其视为有向图边数的 一半
    (*pUnDirectedGraphAdjacencyMatrix)->edgesNum/=2;
    return SUCCESS;
}

//销毁无向图邻接矩阵
Status destroy_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix){
    return destroy_DirectedGraphAdjacencyMatrix(pUnDirectedGraphAdjacencyMatrix);
}
