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

#ifndef DATASTRUCTURE_DIRECTGRAPHADJACENCYLIST_H
#define DATASTRUCTURE_DIRECTGRAPHADJACENCYLIST_H

#define MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST 100

typedef struct _ARC_NODE{
    int adjVex; //该边指向节点的位置
    struct ArcNode *nextArc; //指向下一条边的指针
    int lengthArc; //边的长度(权值)
}ArcNode; //邻接表边

typedef struct{
    int id; //节点id
    void *data; //节点数据
    ArcNode *firstArc; //节点指向第一条边
}VNode; //邻接表节点

typedef struct{
    VNode adjlist[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST]; //邻接口表节点列表
    int vertexNum; //节点个数
    int edgeNum; //边个数
}DirectedGraphAdjancecyList;

//清空有向图邻接矩阵
Status empty_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList);
//初始有向图化邻接矩阵
Status init_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList **directedGraphAdjancecyList,void );
Status init_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList **pDirectedGraphAdjacencyMatrix,
                                         void *vertexDatas[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX],
                                         int vertexNum,int edgeNum);
//为有向图邻接矩阵添加边
Status appendEdge_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix,
                                               int startPoint,int endPoint,
                                               int edgeLength);
//删除有向图邻接矩阵的边
Status deleteEdge_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix,
                                               int startPoint,int endPoint);
//广度遍历有向图邻接矩阵
Status BFS_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                        void **listData);
//深度遍历有向图邻接矩阵
Status DFS_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix,
                                        void **listData);
//通过传入二维矩阵创建有向图邻接口矩阵
Status create_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix,
                                           int edges[][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX],
                                           int vertexNum);
//销毁有向图邻接矩阵
Status destroy_DirectedGraphAdjacencyMatrix(DirectedGraphAdjacencyMatrix **pDirectedGraphAdjacencyMatrix);



#endif //DATASTRUCTURE_DIRECTGRAPHADJACENCYLIST_H

#ifdef __cplusplus
}
#endif