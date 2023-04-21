//
// Created by zhouyuqing on 2023/4/18.
//

#include "aovGraphAdjacencyList.h"

void PRINT_DATA_AOV_GRAPH_ADJACENCY_LIST(void *data){
    printf("%s ",(char *)data);
}

void using_AOVGraphAdjacencyList(){
    /*
     * AOVGraphAdjacencyList AOV图的邻接表 使用测试案例
     */
    //当前图的节点数据:5
    //创建节点数据
    void *vertexDatas[MAX_SIZE_AOV_GRAPH_ADJACENCY_LIST];
    for(int i=0;i<5;i++){
        vertexDatas[i]=(char *)malloc(sizeof(char)*60);
        if(vertexDatas[i]==NULL)
            return;
        sprintf(vertexDatas[i],"<NodeId:%d _|_ Data:%c>",i,'A'+i);
    }

    //创建AOV图
    AOVGraphAdjacencyList *aovGraphAdjacencyList=NULL;
    Status opResult= init_AOVGraphAdjacencyList(&aovGraphAdjacencyList,vertexDatas,5);
    if(FAIL==opResult){
        printf("初始化AOV图失败\n");
        return;
    }
    //为AOV图设置有向边
    int startPoint,endPoint;

    startPoint=0;
    endPoint=1;
    opResult= setEdge_AOVGraphAdjacencyList(aovGraphAdjacencyList,startPoint,endPoint);
    if(FAIL==opResult){
        printf("设置AOV图中从 %d 到 %d 的有向边失败\n",startPoint,endPoint);
        return;
    }

    startPoint=0;
    endPoint=2;
    opResult= setEdge_AOVGraphAdjacencyList(aovGraphAdjacencyList,startPoint,endPoint);
    if(FAIL==opResult){
        printf("设置AOV图中从 %d 到 %d 的有向边失败\n",startPoint,endPoint);
        return;
    }

    startPoint=1;
    endPoint=2;
    opResult= setEdge_AOVGraphAdjacencyList(aovGraphAdjacencyList,startPoint,endPoint);
    if(FAIL==opResult){
        printf("设置AOV图中从 %d 到 %d 的有向边失败\n",startPoint,endPoint);
        return;
    }

    startPoint=2;
    endPoint=3;
    opResult= setEdge_AOVGraphAdjacencyList(aovGraphAdjacencyList,startPoint,endPoint);
    if(FAIL==opResult){
        printf("设置AOV图中从 %d 到 %d 的有向边失败\n",startPoint,endPoint);
        return;
    }

    startPoint=2;
    endPoint=4;
    opResult= setEdge_AOVGraphAdjacencyList(aovGraphAdjacencyList,startPoint,endPoint);
    if(FAIL==opResult){
        printf("设置AOV图中从 %d 到 %d 的有向边失败\n",startPoint,endPoint);
        return;
    }

    startPoint=3;
    endPoint=4;
    opResult= setEdge_AOVGraphAdjacencyList(aovGraphAdjacencyList,startPoint,endPoint);
    if(FAIL==opResult){
        printf("设置AOV图中从 %d 到 %d 的有向边失败\n",startPoint,endPoint);
        return;
    }

    opResult= show_AOVGraphAdjacencyList(aovGraphAdjacencyList);
    if(FAIL==opResult){
        printf("展示AOV图中失败\n");
        return;
    }

    printf("\n-----------------------------1-----------------------------\n");

    void **topDatasList=NULL; //拓扑排序列表
    int topDatasListLength=0; //拓扑排序列表长度

    opResult= topSort_AOVGraphAdjacencyList(aovGraphAdjacencyList,
                                &topDatasList,&topDatasListLength);
    if(FAIL==opResult){
        printf("AOV图 拓扑排序失败\n");
        return;
    }else{
        printf("AOV图 拓扑排序成功,排序结果为:\n");
        for(int i=0;i<topDatasListLength;i++)
            PRINT_DATA_AOV_GRAPH_ADJACENCY_LIST(topDatasList[i]);

    }

    printf("\n-----------------------------2-----------------------------\n");

    free(topDatasList);
    opResult=destroy_AOVGraphAdjacencyList(&aovGraphAdjacencyList);
    if(FAIL==opResult){
        printf("释放AOV图的邻接表失败\n");
        return;
    }
    //释放节点数据
    for(int i=0;i<5;i++)
        free(vertexDatas[i]);

    printf("\n-----------------------------全部数据释放完毕-----------------------------\n");
}

//int main(){
//    using_AOVGraphAdjacencyList();
//}
