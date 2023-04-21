//
// Created by zhouyuqing on 2023/4/19.
//

#include "aoeGraphAdjacencyList.h"

void PRINT_DATA_AOE_GRAPH_ADJACENCY_LIST(void *data){
    printf("%s ",(char *)data);
}

void print_edge_aoe_graph_adjacency_list(Edge_AOEGraphAdjacencyList *edge){
    printf("< %d --> %d  Length:%d>",
           edge->startPoint,edge->endPoint,edge->length);
}

void using_AOEGraphAdjacencyList(){
    /*
     * AOEGraphAdjacencyList AOE图的邻接表 使用测试案例
     */
    //当前图的节点数据:11
    //创建节点数据
    void *vertexDatas[MAX_SIZE_AOE_GRAPH_ADJACENCY_LIST];
    for(int i=0;i<11;i++){
        vertexDatas[i]=(char *)malloc(sizeof(char)*60);
        if(vertexDatas[i]==NULL)
            return;
        sprintf(vertexDatas[i],"<NodeId:%d _|_ Data:%c>",i,'A'+i);
    }

    //创建AOE图
    AOEGraphAdjacencyList *aoeGraphAdjacencyList=NULL;
    Status opResult= init_AOEGraphAdjacencyList(&aoeGraphAdjacencyList,
                                                vertexDatas,11);
    if(FAIL==opResult){
        printf("初始化AOE图失败\n");
        return;
    }

    //为AOE图设置有向边
    int startPoint,endPoint,length;

    startPoint=0;
    endPoint=1;
    length=3;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=0;
    endPoint=2;
    length=4;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=1;
    endPoint=3;
    length=2;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=1;
    endPoint=4;
    length=1;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=2;
    endPoint=4;
    length=3;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=2;
    endPoint=5;
    length=5;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=3;
    endPoint=6;
    length=6;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=4;
    endPoint=7;
    length=4;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=5;
    endPoint=8;
    length=2;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=6;
    endPoint=10;
    length=7;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=7;
    endPoint=8;
    length=10;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=7;
    endPoint=9;
    length=4;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=8;
    endPoint=9;
    length=1;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    startPoint=9;
    endPoint=10;
    length=6;
    opResult= setEdge_AOEGraphAdjacencyList(aoeGraphAdjacencyList,
                                            startPoint,endPoint,length);
    if(FAIL==opResult){
        printf("设置从 %d 到 %d 的长度为:%d的边失败!\n",
               startPoint,endPoint,length);
        return;
    }

    opResult= show_AOEGraphAdjacencyList(aoeGraphAdjacencyList);
    if(FAIL==opResult){
        printf("展示AOE图失败\n");
        return;
    }

    printf("\n-----------------------------1-----------------------------\n");

    Edge_AOEGraphAdjacencyList **cirticalEdgesList=NULL; //关键路径列表
    int cirticalEdgesListLength=0; //关键路径列表长度

    opResult= getCriticalPath_AOEGraphAdjacencyList(
            aoeGraphAdjacencyList,&cirticalEdgesList,&cirticalEdgesListLength
            );
    if(FAIL==opResult){
        printf("获取关键路径失败\n");
        return;
    }else{
        printf("\nAOE网的关键路径为:\n");
        //展示关键路径
        for(int i=0;i<cirticalEdgesListLength;i++){
            print_edge_aoe_graph_adjacency_list(cirticalEdgesList[i]);
            printf("\n");
        }
    }

    printf("\n-----------------------------2-----------------------------\n");
    //释放所有的边
    for(int i=0;i<cirticalEdgesListLength;i++)
        free(cirticalEdgesList[i]);
    //释放关键路径 边列表
    free(cirticalEdgesList);
    //释放节点数据
    for(int i=0;i<11;i++)
        free(vertexDatas[i]);

    opResult=destroy_AOEGraphAdjacencyList(&aoeGraphAdjacencyList);
    if(FAIL==opResult){
        printf("释放AOE图的邻接表失败\n");
        return;
    }

    printf("\n-----------------------------全部数据释放完毕-----------------------------\n");

}

//int main(){
//    using_AOEGraphAdjacencyList();
//}