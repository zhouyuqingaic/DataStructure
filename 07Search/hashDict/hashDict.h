//
// Created by zhouyuqing on 2023/5/2.
//

#ifdef __cplusplus
extern "C"{
#endif

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态


typedef void (*PRINT_DATA)(void *); //打印数据

#endif


#ifndef DATASTRUCTURE_HASHDICT_H
#define DATASTRUCTURE_HASHDICT_H

#include "stdio.h"
#include "malloc.h"

//哈希表 键值对
typedef struct __NODE_HASHDICT{
    int key;
    void *val;
    struct __NODE_HASHDICT *nextKeyVal;
}KeyVal_HashDict;


//该哈希表使用除留余数法创建数据
typedef struct{
    KeyVal_HashDict **keyValList; //键值对头节点列表
    int hashTableLengh; //哈希表长度
    int amount; //哈希表元素个数
}HashDict;

//清空 哈希表
Status empty_HashDict(HashDict *hashDict);
//初始化 哈希表
Status init_HashDict(HashDict **pHashDict,int hashDictLength);
//设置 哈希表 中key-val对
Status set_HashDict(HashDict *hashDict,int key,void *val);
//删除 哈希表 中key-val对
Status del_HashDict(HashDict *hashDict,int key);
//获取 哈希表 key对应的val
Status get_HashDict(HashDict *hashDict,int key,void **val);


#endif //DATASTRUCTURE_HASHDICT_H

#ifdef __cplusplus
}
#endif
