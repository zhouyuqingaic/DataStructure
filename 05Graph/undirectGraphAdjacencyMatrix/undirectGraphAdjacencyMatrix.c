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
