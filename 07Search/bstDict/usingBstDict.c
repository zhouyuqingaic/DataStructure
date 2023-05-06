//
// Created by zhouyuqing on 2023/5/2.
//

#include "bstDict.h"

//输出 data数据
void print_data_bst_dict(void *data){
    printf("%s",(char *)data);
}

void using_BstDict(){
    /*
     * BstDict二叉排序树使用案例
     */
    Bst_Dict *bstDict=NULL;
    Status opResult= init_BSTDict(&bstDict);
    if(FAIL==opResult){
        printf("初始化二叉排序树字典失败\n");
        return;
    }
    //创建数据列表
    char *datas[10];
    for(int i=0;i<10;i++){
        datas[i]=(char *)malloc(sizeof(char)*20);
        sprintf(datas[i],"<key:%d,val:%d>",i,i);
    }

    for(int i=0;i<10;i++){
        opResult= set_BSTDict(bstDict,i,datas[i]);
        if(FAIL==opResult)
            printf("设置key:%d val:%s 失败\n",i,datas[i]);
    }

    char *val=NULL;
    for(int i=0;i<15;i++){
        opResult= get_BSTDict(bstDict,i,(void **)&val);
        if(FAIL==opResult){
            printf("获取key:%d的元素失败!\n",i);
        }else{
            printf("获取key:%d val:%s 成功\n",i,val);
        }
    }

    printf("\n---------------------------------------------1---------------------------------------------\n");


    opResult= init_BSTDict(&bstDict);
    if(FAIL==opResult){
        printf("初始化二叉排序树字典失败\n");
        return;
    }


    for(int i=2;i<=9;i++){
        opResult= set_BSTDict(bstDict,i,datas[i]);
        if(opResult==FAIL)
            printf("设置key:%d val:%s 失败\n",i,datas[i]);
    }

    for(int i=0;i<15;i++){
        opResult= get_BSTDict(bstDict,i,(void **)&val);
        if(FAIL==opResult){
            printf("获取key:%d的元素失败!\n",i);
        }else{
            printf("获取key:%d val:%s 成功\n",i,val);
        }
    }


    opResult=del_BSTDict(bstDict,3);
    if(opResult==FAIL)
        return;
    opResult=del_BSTDict(bstDict,7);
    if(opResult==FAIL)
        return;
    opResult=del_BSTDict(bstDict,5);
    if(opResult==FAIL)
        return;
    opResult=del_BSTDict(bstDict,9);
    if(opResult==FAIL)
        return;

    printf("\n\n>>>>>>>>>>>>>>删除key:3,key:7,key:5,key:9 后\n\n");

    for(int i=0;i<10;i++){
        opResult= get_BSTDict(bstDict,i,(void **)&val);
        if(FAIL==opResult){
            printf("获取key:%d的元素失败!\n",i);
        }else{
            printf("获取key:%d val:%s 成功\n",i,val);
        }
    }

    printf("\n---------------------------------------------2---------------------------------------------\n");

    opResult= empty_BinarySortTree(bstDict);
    if(FAIL==opResult){
        printf("\n清空二叉排序树字典失败\n");
        return;
    }else{
        //释放二叉排序树空间
        free(bstDict);
    }

    //清空测试数据
    for(int i=0;i<10;i++)
        free(datas[i]);

    printf("成功清空所有数据");
}

int main(){
    using_BstDict();
    return 0;
}
