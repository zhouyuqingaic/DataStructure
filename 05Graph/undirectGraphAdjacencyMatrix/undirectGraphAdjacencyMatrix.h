//
// Created by zhouyuqing on 2023/4/3.
//

#ifndef DATASTRUCTURE_UNDIRECTGRAPHADJACENCYMATRIX_H
#define DATASTRUCTURE_UNDIRECTGRAPHADJACENCYMATRIX_H

#include "../directGraphAdjacencyMatrix/directGraphAdjacencyMatrix.h"

typedef DirectedGraphAdjacencyMatrix UnDirectedGraphAdjacencyMatrix;


//清空无向图邻接矩阵(即清空所有边)
Status empty_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix);
//初始为有vertexsNum个节点的无向图邻接矩阵
Status init_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix,
                                         void *vertexsData[],int vertexsNum);
//展示无向图邻接矩阵
Status showAdjacencyMatrix__UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix);

//为有无图邻接矩阵设置边
Status setEdge_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                           int aVertex,int bVertex,
                                           int edgeLength);
//设置无向图节点data
Status setVertex_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                           int id,void *data);

//从startVertex开始通过普里姆算法生成最小生成树，返回表示最小生成树的无向图邻接矩阵pUnDirectedGraphAdjacencyMatrix_Result
Status primMinimumSpanningTree_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                           int startVertex,UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix_Result);

//从startVertex开始通过克鲁斯卡尔算法生成最小生成树，返回表示最小生成树的无向图邻接矩阵pUnDirectedGraphAdjacencyMatrix_Result
Status kruskalMinimumSpanningTree_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                           UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix_Result);

//在无向图的最小生成树中，获取从aVertex到bVertex的路径
Status pathMinimumSpanningTree_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix,
                                           int aVertex,int bVertex,void ***pDataList,int *lengthDataList);

//通过传入二维矩阵创建有无向图邻接矩阵
Status create_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix,
                                           int edges[][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX],
                                           void *vertexsData[],int vertexsNum);

//销毁无向图邻接矩阵
Status destroy_UnDirectedGraphAdjacencyMatrix(UnDirectedGraphAdjacencyMatrix **pUnDirectedGraphAdjacencyMatrix);



#endif //DATASTRUCTURE_UNDIRECTGRAPHADJACENCYMATRIX_H
