//
// Created by zhouyuqing on 2023/3/26.
//

#include "directGraphAdjacencyMatrix.h"

void PRINT_DATA_DIRECT_GRAPH_ADJACENCY_MATRIX(void *data){
    printf("%s",(char *)data);
}

void using_directGraphAdjacencyMatrix(){
    /*
     * DirectedGraphAdjacencyMatrix有向图邻接矩阵,使用&测试案例
     */
    DirectedGraphAdjacencyMatrix *directedGraphAdjacencyMatrix=NULL;
    //创建节点数据列表
    void *datas[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    int datasLength=7;
    for(int i=0;i<datasLength;i++){
        datas[i]=(char *)malloc(sizeof(char)*40);
        sprintf(datas[i],"<NodeId:%d NodeData:%c>",i,'A'+i);
    }
    Status opResult=init_DirectedGraphAdjacencyMatrix(&directedGraphAdjacencyMatrix,datas,datasLength);
    if(FAIL==opResult){
        perror("初始化有向图矩阵失败!");
        return;
    }

    //为图设置有向量边
    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,0,1,4);
    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,0,2,6);
    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,0,3,6);

    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,1,2,1);
    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,1,4,7);

    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,2,4,6);
    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,2,5,4);

    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,3,2,2);
    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,3,5,5);

    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,4,6,6);

    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,5,4,1);
    setEdge_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,5,6,8);

    printf("设置边完成");
    opResult= showAdjacencyMatrix__DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix);
    if(FAIL==opResult){
        perror("展示邻接矩阵失败\n");
        return;
    }

    printf("\n---------------------------------1---------------------------------\n");

    void **bfsList=NULL;
    int lengthBFSList=0;
    opResult=BFS_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,0,&bfsList,&lengthBFSList);
    if(FAIL==opResult){
        perror("广度遍历有向图失败!");
        return;
    }
    printf("广度遍历结果:\n");
    for(int i=0;i<lengthBFSList;i++) {
        PRINT_DATA_DIRECT_GRAPH_ADJACENCY_MATRIX(bfsList[i]);
        printf("  ");
    }
    printf("\n");
    //释放遍历队列
    free(bfsList);

    void **dfsList=NULL;
    int lengthDFSList=0;
    opResult= DFS_DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix,0,&dfsList,&lengthDFSList);
    if(FAIL==opResult){
        perror("深度遍历有向图失败!");
        return;
    }
    printf("深度遍历结果:\n");
    for(int i=0;i<lengthDFSList;i++){
        PRINT_DATA_DIRECT_GRAPH_ADJACENCY_MATRIX(dfsList[i]);
        printf("  ");
    }
    printf("\n");
    //释放遍历队列
    free(dfsList);

    printf("\n---------------------------------2---------------------------------\n");

    //通过传入二维矩阵创建数据
    int edges[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX][MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    for(int i=0;i<directedGraphAdjacencyMatrix->vertexsNum;i++)
        for(int j=0;j<directedGraphAdjacencyMatrix->vertexsNum;j++)
            edges[i][j]=directedGraphAdjacencyMatrix->edges[i][j];

    //创建节点数据列表
    void *datas01[MAX_SIZE_DIRCTED_GRAPH_ADJACENCY_MATRIX];
    int datasLength01=7;
    for(int i=0;i<datasLength01;i++){
        datas01[i]=(char *)malloc(sizeof(char)*60);
        sprintf(datas01[i],"<NEWGRAPH_|_ NodeId:%d NodeData:%c>",i,'A'+i);
    }

    int currentVal=edges[1][2];
    opResult=create_DirectedGraphAdjacencyMatrix(&directedGraphAdjacencyMatrix,edges,datas01,datasLength01);
    if(FAIL==opResult){
        perror("通过邻接矩阵创建有向图失败!");
        return;
    }

    printf("通过邻接矩阵创建的有向图为:\n");
    opResult=showAdjacencyMatrix__DirectedGraphAdjacencyMatrix(directedGraphAdjacencyMatrix);
    if(FAIL==opResult){
        perror("展示邻接矩阵失败\n");
        return;
    }

    printf("\n---------------------------------3---------------------------------\n");


}

int main(){
    using_directGraphAdjacencyMatrix();
    return 0;
}