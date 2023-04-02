//
// Created by zhouyuqing on 2023/4/1.
//

#include "directGraphAdjacencyList.h"

void PRINT_DATA_DIRECT_GRAPH_ADJACENCY_LIST(void *data){
    printf("%s ",(char *)data);
}

void using_directGraphAdjacencyList(){
    /*
     * directGraphAdjacencyList有向邻接表 使用测试案例
     */
    //当前图的节点数:7 图的边数:12
    int temp[7][7]= {
            {-1,  4,  6,  6, -1, -1, -1},
            {-1, -1,  1, -1,  7, -1, -1},
            {-1, -1, -1, -1,  6,  4, -1},
            {-1, -1,  2, -1, -1,  5, -1},
            {-1, -1, -1, -1, -1, -1,  6},
            {-1, -1, -1, -1,  1, -1,  8},
            {-1, -1, -1, -1, -1, -1, -1}
    };
    //创建边矩阵
    int edges[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST];
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            edges[i][j]=temp[i][j];
        }
    }
    //创建节点数据
    void *vertexDatas[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_LIST];
    for(int i=0;i<7;i++){
        vertexDatas[i]=(char *)malloc(sizeof(char)*60);
        if(vertexDatas[i]==NULL)
            return;
        sprintf(vertexDatas[i],"<NodeId:%d _|_ Data:%c>",i,'A'+i);
    }

    //通过传入二维矩阵创建有向图邻接表
    DirectedGraphAdjancecyList *directedGraphAdjancecyList=NULL;
    Status opResult=create_DirectedGraphAdjacencyList(&directedGraphAdjancecyList,edges,vertexDatas,7);
    if(FAIL==opResult) {
        perror("通过二维数组创建邻接表失败");
        return;
    }

    opResult=show_DirectedGraphAdjancecyList(directedGraphAdjancecyList);
    if(FAIL==opResult){
        perror("展示邻接表失败");
        return;
    }

    printf("\n----------------------------1----------------------------\n");

    int dfsStartVertex=0;
    void **dfsDataList=NULL;
    int dfsDataListLength=0;
    opResult= DFS_DirectedGraphAdjancecyList(directedGraphAdjancecyList,
                                             dfsStartVertex,&dfsDataList,&dfsDataListLength);
    if(FAIL==opResult){
        perror("深度遍历失败!\n");
        return;
    }else{
        printf("深度遍历成功,遍历结果为:\n\t");
        for(int i=0;i<dfsDataListLength;i++)
            PRINT_DATA_DIRECT_GRAPH_ADJACENCY_LIST(dfsDataList[i]);
    }

    printf("\n\n");

    int bfsStartVertex=0;
    void **bfsDataList=NULL;
    int bfsDataListLength=0;
    opResult= BFS_DirectedGraphAdjancecyList(directedGraphAdjancecyList,
         bfsStartVertex,&bfsDataList,&bfsDataListLength);
    if(FAIL==opResult){
        perror("广度遍历失败!\n");
        return;
    }else{
        printf("广度遍历成功,遍历结果为:\n\t");
        for(int i=0;i<bfsDataListLength;i++)
            PRINT_DATA_DIRECT_GRAPH_ADJACENCY_LIST(bfsDataList[i]);
    }

    printf("\n----------------------------2----------------------------\n");

    DirectedGraphAdjancecyList *directedGraphAdjancecyList01=NULL;
    opResult= init_DirectedGraphAdjancecyList(&directedGraphAdjancecyList01,vertexDatas,7);
    if(FAIL==opResult){
        perror("初始化7个结点的邻接表有向图失败");
        return;
    }
    //为邻接表有向图设置边
    int currentEdgeLength=0;
    for(int i=0;i<directedGraphAdjancecyList01->vertexsNum;i++)
        for(int j=0;j<directedGraphAdjancecyList01->vertexsNum;j++){
            opResult= getEdge_DirectedGraphAdjancecyList(directedGraphAdjancecyList,
                                         i,j,&currentEdgeLength);
            if(opResult==SUCCESS){
                //存在从i到j的边，为directedGraphAdjancecyList01设置从i到j的边
                opResult= setEdge_DirectedGraphAdjancecyList(directedGraphAdjancecyList01,
                                         i,j,currentEdgeLength);
                if(FAIL==opResult){
                    perror("设置directedGraphAdjancecyList01中i到j的边失败");
                    return;
                }
            }
        }
    //展示新 有向图
    printf("\n有向图directedGraphAdjancecyList01为:\n");
    opResult=show_DirectedGraphAdjancecyList(directedGraphAdjancecyList01);
    if(FAIL==opResult){
        perror("展示有向图directedGraphAdjancecyList01失败");
        return;
    }

    printf("\n----------------------------3----------------------------\n");

    opResult= deleteEdge_DirectedGraphAdjancecyList(directedGraphAdjancecyList01,4,6);
    if(FAIL==opResult){
        printf("删除4到6的边失败\n");
    }
    opResult= deleteEdge_DirectedGraphAdjancecyList(directedGraphAdjancecyList01,4,5);
    if(FAIL==opResult){
        printf("删除4到5的边失败\n");
    }

    //展示删除后 有向图
    printf("\n有向图directedGraphAdjancecyList01为:\n");
    opResult=show_DirectedGraphAdjancecyList(directedGraphAdjancecyList01);
    if(FAIL==opResult){
        perror("展示有向图directedGraphAdjancecyList01失败");
        return;
    }

    //销毁有向图
    opResult= destroy_DirectedGraphAdjacencyList(&directedGraphAdjancecyList01);
    if(FAIL==opResult){
        printf("销毁有向图directedGraphAdjancecyList01失败");
        return;
    }
    opResult= destroy_DirectedGraphAdjacencyList(&directedGraphAdjancecyList);
    if(FAIL==opResult){
        printf("销毁有向图directedGraphAdjancecyList失败");
        return;
    }
    for(int i=0;i<7;i++)
        free(vertexDatas[i]);

    printf("\n----------------------------全部数据销毁完毕----------------------------\n");
}

int main(){
    using_directGraphAdjacencyList();

    return 0;
}