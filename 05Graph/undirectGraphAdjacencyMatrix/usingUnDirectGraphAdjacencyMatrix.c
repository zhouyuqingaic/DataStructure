//
// Created by zhouyuqing on 2023/4/3.
//

#include "undirectGraphAdjacencyMatrix.h"

void PRINT_DATA_UNDIRECT_GRAPH_ADJACENCY_MATRIX(void *data){
    printf("%s",(char *)data);
}

void using_undirectGraphAdjacencyMatrix(){
    /*
     * UndirectGraphAdjacencyMatrix无向图邻接矩阵，使用&测试案例
     */
    UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix=NULL;
    //创建数据节点
    void *datas[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    int dataLength=0;
    for(dataLength=0;dataLength<5;dataLength++){
        datas[dataLength]=(char *)malloc(sizeof(char)*60);
        sprintf(datas[dataLength],"<NodeId:%d NodeData:%c>",dataLength,'A'+dataLength);
    }
    Status opResult= init_UnDirectedGraphAdjacencyMatrix(&unDirectedGraphAdjacencyMatrix,
                                                         datas,dataLength);
    if(FAIL==opResult){
        perror("创建有5个节点的无向图邻接矩阵失败!");
        return;
    }

    //为无向图设置边
    int aVertex=0,bVertex=1,edgeLength=5;
    opResult=setEdge_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,aVertex,bVertex,edgeLength);
    if(FAIL==opResult)
        printf("设置边(%d,%d)的权值为 %d 失败",aVertex,bVertex,dataLength);

    aVertex=0,bVertex=2,edgeLength=1;
    opResult=setEdge_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,aVertex,bVertex,edgeLength);
    if(FAIL==opResult)
        printf("设置边(%d,%d)的权值为 %d 失败",aVertex,bVertex,dataLength);

    aVertex=0,bVertex=3,edgeLength=2;
    opResult=setEdge_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,aVertex,bVertex,edgeLength);
    if(FAIL==opResult)
        printf("设置边(%d,%d)的权值为 %d 失败",aVertex,bVertex,dataLength);

    aVertex=1,bVertex=2,edgeLength=3;
    opResult=setEdge_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,aVertex,bVertex,edgeLength);
    if(FAIL==opResult)
        printf("设置边(%d,%d)的权值为 %d 失败",aVertex,bVertex,dataLength);

    aVertex=1,bVertex=4,edgeLength=4;
    opResult=setEdge_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,aVertex,bVertex,edgeLength);
    if(FAIL==opResult)
        printf("设置边(%d,%d)的权值为 %d 失败",aVertex,bVertex,dataLength);

    aVertex=2,bVertex=3,edgeLength=6;
    opResult=setEdge_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,aVertex,bVertex,edgeLength);
    if(FAIL==opResult)
        printf("设置边(%d,%d)的权值为 %d 失败",aVertex,bVertex,dataLength);

    aVertex=2,bVertex=4,edgeLength=2;
    opResult=setEdge_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,aVertex,bVertex,edgeLength);
    if(FAIL==opResult)
        printf("设置边(%d,%d)的权值为 %d 失败",aVertex,bVertex,dataLength);

    aVertex=3,bVertex=4,edgeLength=3;
    opResult=setEdge_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,aVertex,bVertex,edgeLength);
    if(FAIL==opResult)
        printf("设置边(%d,%d)的权值为 %d 失败",aVertex,bVertex,dataLength);


    printf("设置边完成");
    opResult= showAdjacencyMatrix__UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix);
    if(FAIL==opResult){
        perror("展示无向图邻接矩阵失败\n");
        return;
    }

    printf("\n---------------------------------1---------------------------------\n");

    //新建邻接矩阵
    int edges[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    for(int i=0;i<unDirectedGraphAdjacencyMatrix->vertexsNum;i++)
        for(int j=0;j<unDirectedGraphAdjacencyMatrix->vertexsNum;j++){
            edges[i][j]=unDirectedGraphAdjacencyMatrix->edges[i][j];
        }
    //通过邻接矩阵创建无向图
    UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrix02=NULL;
    opResult=create_UnDirectedGraphAdjacencyMatrix(&unDirectedGraphAdjacencyMatrix02,
                                          edges,datas,dataLength);
    if(FAIL==opResult){
        perror("通过邻接矩阵创建有5个节点的无向图邻接矩阵失败!");
        return;
    }
    opResult= showAdjacencyMatrix__UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix02);
    if(FAIL==opResult){
        perror("展示无向图邻接矩阵失败\n");
        return;
    }

    printf("\n---------------------------------2---------------------------------\n");

    UnDirectedGraphAdjacencyMatrix *unDirectedGraphAdjacencyMatrixResult;
    opResult=primMinimumSpanningTree_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix,
                                                           0,&unDirectedGraphAdjacencyMatrix02);
    if(FAIL==opResult){
        perror("生成最小生成树失败");
        return;
    }
    printf("\n展示最小生成树\n");
    opResult=showAdjacencyMatrix__UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix02);
    if(FAIL==opResult){
        perror("展示最小生成树失败");
        return;
    }

    void **DataList=NULL;
    int lengthDataLength=0;
    opResult=pathMinimumSpanningTree_UnDirectedGraphAdjacencyMatrix(unDirectedGraphAdjacencyMatrix02,
                                                            1,4,&DataList,&lengthDataLength);
    if(FAIL==opResult){
        perror("展示最小生成树失败\n");
        return;
    }else{
        for(int i=0;i<lengthDataLength;i++)
            PRINT_DATA_UNDIRECT_GRAPH_ADJACENCY_MATRIX(DataList[i]);
    }

    printf("\n---------------------------------2---------------------------------\n");

    for(int i=0;i<dataLength;i++)
        free(datas[i]);
    opResult= destroy_UnDirectedGraphAdjacencyMatrix(&unDirectedGraphAdjacencyMatrix);
    if(FAIL==opResult) {
        perror("释放unDirectedGraphAdjacencyMatrix失败");
        return;
    }
    opResult= destroy_UnDirectedGraphAdjacencyMatrix(&unDirectedGraphAdjacencyMatrix02);
    if(FAIL==opResult) {
        perror("释放unDirectedGraphAdjacencyMatrix02失败");
        return;
    }

    printf("\n---------------------------------释放所有数据完毕---------------------------------\n");
}


int main() {
    using_undirectGraphAdjacencyMatrix();


    return 0;
}