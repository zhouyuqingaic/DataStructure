//
// Created by zhouyuqing on 2023/4/18.
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


#ifndef DATASTRUCTURE_AOVGRAPHADJACENCYLIST_H
#define DATASTRUCTURE_AOVGRAPHADJACENCYLIST_H

#include<stdio.h>
#include<malloc.h>

#define MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST 100

typedef struct _ARC_AOVGRAPHADJACENCYLIST{
    int adjVex; //该边指向节点的位置
    struct _ARC_AOVGRAPHADJACENCYLIST *nextArc; //指向从同一节点出发的另一条边
}Arc_AOVGraphAdjacencyList; //AOV图的邻接表节边元素

typedef struct{
    int id; //节点id
    void *data; //节点数据
    int enArcAmount; //从该节点入度个数
    Arc_AOVGraphAdjacencyList *firstArc; //从该节点发出的第一条边
}Vertex_AOVGraphAdjacencyList; //AOV图的邻接表节点元素

typedef struct{
    Vertex_AOVGraphAdjacencyList vertexs[MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST]; //邻接表结点
    int vertexsNum; //节点个数
    int edgesNum; //边个数
}AOVGraphAdjacencyList; //AOV图的邻接表

//清空AOV图的邻接表
Status empty_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList);
//初始化AOV图的邻接表
Status init_AOVGraphAdjacencyList(AOVGraphAdjacencyList **pAovGraphAdjacencyList,
                                  void *vertexDatas[],
                                  int vertexsNum);
//为AOV图的邻接表设置边(边的值为负数或者0表示该边不存在，不用设置 直接返回)
Status setEdge_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList,
                                          int startPoint,int endPoint);

//获取AOV图的邻接表中从startPoint到endPoint有向边的权值,Status==FAIL表示没有从startPoint到endPoint的有向边
Status existsEdge_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList,
                                          int startPoint,int endPoint);

//对AOV图的邻接表进行拓扑排序,排序结果存入pListData
Status topSort_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList,
                                     void ***pListData,int *lengthListData);

//通过邻接矩阵的形式展示AOV图的邻接表
Status show_AOVGraphAdjacencyList(AOVGraphAdjacencyList *aovGraphAdjacencyList);

//通过传入二维矩阵创建AOV图的邻接表
Status create_AOVGraphAdjacencyList(AOVGraphAdjacencyList **pAovGraphAdjacencyList,
                                         int edges[][MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST],
                                         void *vertexDatas[],int vertexNum);

//销毁有AOV图的邻接表
Status destroy_AOVGraphAdjacencyList(AOVGraphAdjacencyList **pAovGraphAdjacencyList);



#endif //DATASTRUCTURE_AOVGRAPHADJACENCYLIST_H

#ifdef __cplusplus
}
#endif