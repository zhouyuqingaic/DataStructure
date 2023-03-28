//
// Created by zhouyuqing on 2023/3/25.
//

#ifdef __cplusplus
extern "C"{
#endif

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态

typedef void (*PRINT_DATA)(void *);

#endif

#ifndef DATASTRUCTURE_GRAPHADJACENCYMATRIX_H
#define DATASTRUCTURE_GRAPHADJACENCYMATRIX_H

#include<stdio.h>
#include<malloc.h>

//定义 边不存在
#define NO_EDGE -1

#define MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX 100

typedef struct{
    int startPoint; //边的开始节点
    int endPoint; //边的结束节点
    int lengthEdge; //边的长度
}edgeOfDirctedGraphAdjacencyMatrixNode;

typedef struct{
    int id; //节点id(节点id从0开始计数)
    void *data; //节点数据
}DirctedGraphAdjacencyMatrixNode; //有向图邻接矩阵节点
typedef struct{
    int edges[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX]; //邻接矩阵
    int vertexsNum; //节点个数
    int edgesNum; //边个数
    DirctedGraphAdjacencyMatrixNode vertexs[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX]; //节点列表，所有节点都存在节点列表中
}DirectedGraphAdjacencyMatrix; //有向图邻接矩阵

//清空有向图邻接矩阵(即清空所有边)
Status empty_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix);
//初始为有datasLenght个节点的有向图化邻接矩阵
Status init_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix,
                                         void *datas[],int datasLength);
//展示有向图邻接矩阵
Status showAdjacencyMatrix__DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix);

//为有向图邻接矩阵设置边
Status setEdge_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                               int startVertex,int endVertex,
                                               int edgeLength);
//删除有向图邻接矩阵的边
Status deleteEdge_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                               int startVertex,int endVertex);
//设置节点data
Status setVertex_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                              int id,void *data);
//广度遍历有向图邻接矩阵
//从vertexId广度遍历有向图邻接矩阵
Status BFS_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                        int vertexId,void ***pListData,int *lengthListData);
//深度遍历有向图邻接矩阵
Status DFS_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                        int vertexId,void ***listData,int *lengthListData);
//通过传入二维矩阵创建有向图邻接矩阵
Status create_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix,
                                           int edges[][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX],
                                           void *datas[],int datasLength);

//利用向图邻接矩阵的地杰斯特拉算法，得到从startVertex到endVertex最短路径
Status dijkstra_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,int startVertex,int endVertex,void ***pListData,int *lengthListData);

//销毁有向图邻接矩阵
Status destroy_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix);

#endif //DATASTRUCTURE_GRAPHADJACENCYMATRIX_H

#ifdef __cplusplus
}
#endif