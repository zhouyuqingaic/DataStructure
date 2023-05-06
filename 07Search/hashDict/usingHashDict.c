//
// Created by zhouyuqing on 2023/5/2.
//
#include "hashDict.h"

//输出 data数据
void print_data_hash_dict(void *data){
    printf("%s",(char *)data);
}

void using_HashDict(){
    /*
     * hashDict哈希表使用测试案例
     */
    HashDict *hashDict=NULL;
    //设置哈希表长度为3
    Status opResult=init_HashDict(&hashDict,3);
    if(opResult==FAIL){
        printf("初始化哈希表失败\n");
        return;
    }
    //创建数据列表
    char *datas[10];
    for(int i=0;i<10;i++) {
        datas[i] = (char *) malloc(sizeof(char) * 20);
        sprintf(datas[i],"<key:%d,val:%d>",i,i);
    }

    for(int i=0;i<10;i++){
        opResult=set_HashDict(hashDict,i,datas[i]);
        if(opResult==FAIL){
            printf("设置key:%d val:%s 失败\n",i,datas[i]);
        }
    }

    char *val=NULL;
    for(int i=0;i<15;i++){
        opResult= get_HashDict(hashDict,i,(void **)&val);
        if(FAIL==opResult){
            printf("获取key:%d的元素失败!\n",i);
        }else{
            printf("获取key:%d val:%s 成功\n",i,val);
        }
    }

    printf("\n---------------------------------------------1---------------------------------------------\n");

    //重新初始化哈希表，并设置哈希表长度为5
    //设置哈希表长度为3
    opResult=init_HashDict(&hashDict,5);
    if(opResult==FAIL){
        printf("初始化哈希表失败\n");
        return;
    }

    for(int i=0;i<10;i++){
        opResult=set_HashDict(hashDict,i,datas[i]);
        if(opResult==FAIL){
            printf("设置key:%d val:%s 失败\n",i,datas[i]);
        }
    }

    for(int i=0;i<11;i++){
        opResult= get_HashDict(hashDict,i,(void **)&val);
        if(FAIL==opResult){
            printf("获取key:%d的元素失败!\n",i);
        }else{
            printf("获取key:%d val:%s 成功\n",i,val);
        }
    }

    opResult=del_HashDict(hashDict,3);
    if(opResult==FAIL)
        return;
    opResult=del_HashDict(hashDict,0);
    if(opResult==FAIL)
        return;
    opResult=del_HashDict(hashDict,5);
    if(opResult==FAIL)
        return;
    opResult=del_HashDict(hashDict,9);
    if(opResult==FAIL)
        return;

    printf("\n\n>>>>>>>>>>>>>>删除key:3,key:0,key:5,key:9 后\n\n");

    for(int i=0;i<10;i++){
        opResult= get_HashDict(hashDict,i,(void **)&val);
        if(FAIL==opResult){
            printf("获取key:%d的元素失败!\n",i);
        }else{
            printf("获取key:%d val:%s 成功\n",i,val);
        }
    }

    printf("\n---------------------------------------------2---------------------------------------------\n");

    opResult= empty_HashDict(hashDict);
    if(FAIL==opResult){
        printf("\n清空哈希表失败\n");
        return;
    }else{
        //释放哈希表
        free(hashDict);
    }

    //清空测试数据
    for(int i=0;i<10;i++)
        free(datas[i]);

    printf("成功清空所有数据");

}

//int main(){
//
//    using_HashDict();
//
//    return 0;
//}