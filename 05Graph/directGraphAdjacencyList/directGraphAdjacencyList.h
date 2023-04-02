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

#include<stdio.h>
#include<malloc.h>


#define MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST 100

typedef struct _ARC_DIRECTEDGRAPHADJANCECYLIST{
    int adjVex; //该边指向节点的位置
    struct _ARC_DIRECTEDGRAPHADJANCECYLIST *nextArc; //指向从同一节点发出另一条边
    int lengthArc; //边的长度(权值)
}Arc_DirectedGraphAdjancecyList; //边元素
typedef struct{
    int id; //节点id
    void *data; //节点数据
    Arc_DirectedGraphAdjancecyList *firstArc; //从该节点发出第一条边
}Vertex_DirectedGraphAdjancecyList; //邻接表结点
typedef struct{
    Vertex_DirectedGraphAdjancecyList vertexs[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST]; //邻接表结点
    int vertexsNum; //节点个数
    int edgesNum; //边个数
}DirectedGraphAdjancecyList; //邻接表


//清空有向图邻接
Status empty_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList);
//初始有向图邻接表
Status init_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList **pDirectedGraphAdjacencyList,
                                         void *vertexDatas[],
                                         int vertexsNum);
//为有向图邻接表设置边(边的值为负数或者0表示该边不存在，不用设置 直接返回)
Status setEdge_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                             int startPoint,int endPoint,
                                             int lengthArc);

//获取有向量邻接表中从startPoint到endPoint有向边的权值,Status==FAIL表示没有从startPoint到endPoint的有向边
Status getEdge_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                          int startPoint,int endPoint,
                                          int *lengthArc);

//通过邻接矩阵的形式展示矩阵邻接表
Status show_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList);

//删除有向图邻接表的边
Status deleteEdge_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                          int startPoint,int endPoint);

//广度遍历有向图邻接表
//从vertexId广度遍历有向图邻接表
Status BFS_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                        int vertexId,void ***pListData,int *lengthListData);
//深度遍历有向图邻接表
//从vertexId深度遍历有向图邻接表
Status DFS_DirectedGraphAdjancecyList(DirectedGraphAdjancecyList *directedGraphAdjancecyList,
                                      int startVertex,void ***pListData,int *lengthListData);

//通过传入二维矩阵创建有向图邻接表
Status create_DirectedGraphAdjacencyList(DirectedGraphAdjancecyList **pDirectedGraphAdjancecyList,
                                           int edges[][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST],
                                           void *vertexDatas[],int vertexNum);

//销毁有向图邻接矩阵
Status destroy_DirectedGraphAdjacencyList(DirectedGraphAdjancecyList **pDirectedGraphAdjancecyList);


#endif //DATASTRUCTURE_DIRECTGRAPHADJACENCYLIST_H

#ifdef __cplusplus
}
#endif