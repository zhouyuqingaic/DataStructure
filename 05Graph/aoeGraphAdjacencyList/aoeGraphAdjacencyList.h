//
// Created by zhouyuqing on 2023/4/19.
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

#ifndef DATASTRUCTURE_AOEGRAPHADJACENCYLIST_H
#define DATASTRUCTURE_AOEGRAPHADJACENCYLIST_H

#include "../aovGraphAdjacencyList/aovGraphAdjacencyList.h"

#define MAX_SIZE_AOE_GRAPH_ADJACENCY_LIST 100

typedef AOVGraphAdjacencyList AOEGraphAdjacencyList;
typedef Arc_AOVGraphAdjacencyList Arc_AOEGraphAdjacencyList;
typedef Vertex_AOVGraphAdjacencyList Vertex_AOEGraphAdjacencyList;

typedef struct{
    //边的开始和节点顶点
    int startPoint;
    int endPoint;
    //边的权值长度
    int length;
}Edge_AOEGraphAdjacencyList;

//清空AOE图的邻接表
Status empty_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList);
//初始化AOE图的邻接表
Status init_AOEGraphAdjacencyList(AOEGraphAdjacencyList **pAoeGraphAdjacencyList,
                                  void *vertexDatas[],
                                  int vertexsNum);
//为AOE图的邻接表设置边,长度为length
Status setEdge_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList,
                                     int startPoint,int endPoint,int length);

//获取AOE图的邻接表中从startPoint到endPoint的边的权值length
Status getEdge_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList,
                                     int startPoint,int endPoint,int *length);

//获取AOE图的邻接表的关键路径(关键路径的边列表)
Status getCriticalPath_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList,
                                             Edge_AOEGraphAdjacencyList ***pCriticalPathList,
                                             int *criticalPathListLength);
//通过邻接矩阵的形式展示AOE图的邻接表
Status show_AOEGraphAdjacencyList(AOEGraphAdjacencyList *aoeGraphAdjacencyList);

//通过传入二维矩阵创建AOE图的邻接表
Status create_AOEGraphAdjacencyList(AOEGraphAdjacencyList **pAoeGraphAdjacencyList,
                                    int edges[][MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST],
                                    void *vertexDatas[],int vertexNum);

//销毁有AOV图的邻接表
Status destroy_AOEGraphAdjacencyList(AOEGraphAdjacencyList **pAoeGraphAdjacencyList);




#endif //DATASTRUCTURE_AOEGRAPHADJACENCYLIST_H



#ifdef __cplusplus
}
#endif