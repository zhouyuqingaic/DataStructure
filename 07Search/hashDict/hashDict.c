//
// Created by zhouyuqing on 2023/5/2.
//
#include "hashDict.h"


//清空 哈希表
Status empty_HashDict(HashDict *hashDict){
    if(hashDict==NULL)
        return FAIL;
    //清空哈希表中所有的 keyVal_HashDict
    KeyVal_HashDict *currentKeyVal=NULL,*tempKeyVal=NULL;
    for(int i=0;i<hashDict->hashTableLengh;i++){
        //清除key的哈希值为i的 所有keyVal对
        if(hashDict->keyValList[i]!=NULL){
            currentKeyVal=hashDict->keyValList[i];
            while(currentKeyVal!=NULL){
                tempKeyVal=currentKeyVal;
                currentKeyVal=currentKeyVal->nextKeyVal;
                free(tempKeyVal);
            }
            //键值对链表 头节点置空
            hashDict->keyValList[i]=NULL;
        }
    }
    //哈希表元素个数为0
    hashDict->amount=0;
    return SUCCESS;
}

//初始化 哈希表
Status init_HashDict(HashDict **pHashDict,int hashDictLength){
    //哈希表已存在
    if(*pHashDict!=NULL) {
        //清空哈希表
        empty_HashDict(*pHashDict);
        //释放键值对头节点列表
        free((*pHashDict)->keyValList);
        //释放哈希表
        free(*pHashDict);
    }
    //创建哈希表
    *pHashDict=(HashDict *)malloc(sizeof(HashDict));
    if(*pHashDict==NULL)
        return FAIL;
    //初始化哈希表
    (*pHashDict)->hashTableLengh=hashDictLength;
    (*pHashDict)->keyValList=(KeyVal_HashDict **)malloc(
            sizeof(KeyVal_HashDict *)*hashDictLength
        );
    (*pHashDict)->amount=0;
    return SUCCESS;
}

//返回 key的哈希值
int hash_HashDict(HashDict *hashDict,int key){
    if(hashDict==NULL)
        return FAIL;
    //除留余数法获取 哈希值
    return key%(hashDict->hashTableLengh);
}

//设置 哈希表 中key-val对
Status set_HashDict(HashDict *hashDict,int key,void *val){
    if(hashDict==NULL)
        return FAIL;
    int keyHash=hash_HashDict(hashDict,key);
    KeyVal_HashDict *currentKeyVal=hashDict->keyValList[keyHash];
    if(currentKeyVal==NULL){
        //当前 keyVal对 为 key哈希值 为 keyHash的第一个节点
        hashDict->keyValList[keyHash]=(KeyVal_HashDict *)malloc(sizeof(KeyVal_HashDict));
        if(hashDict->keyValList[keyHash]==NULL)
            return FAIL;
        hashDict->keyValList[keyHash]->key=key;
        hashDict->keyValList[keyHash]->val=val;
        hashDict->keyValList[keyHash]->nextKeyVal=NULL;

        return SUCCESS;
    }else{
        //遍历key为hashKey的所有键值对
        while(currentKeyVal!=NULL){
            //如果存在key为key的keyVal对，修改该keyVal的值val
            if(currentKeyVal->key==key){
                currentKeyVal->val=val;
                return SUCCESS;
            }
            currentKeyVal=currentKeyVal->nextKeyVal;
        }
        //没有找到key为key的keyVal对,
        // 将新keyVal对挂到最后一个keyHash的最后一个keyVal对后面
        currentKeyVal=hashDict->keyValList[keyHash];
        while(currentKeyVal->nextKeyVal!=NULL){
            currentKeyVal=currentKeyVal->nextKeyVal;
        }
        currentKeyVal->nextKeyVal=(KeyVal_HashDict *)malloc(sizeof(KeyVal_HashDict));
        if(currentKeyVal->nextKeyVal==NULL)
            return FAIL;

        currentKeyVal->nextKeyVal->key=key;
        currentKeyVal->nextKeyVal->val=val;
        currentKeyVal->nextKeyVal->nextKeyVal=NULL;
        return SUCCESS;
    }
}

//删除 哈希表 中key-val对
Status del_HashDict(HashDict *hashDict,int key){
    if(hashDict==NULL)
        return FAIL;
    int keyHash=hash_HashDict(hashDict,key);
    KeyVal_HashDict *preKeyVal=NULL,
            *currentKeyVal=hashDict->keyValList[keyHash];

    //探查keyHash的所有keyVal对
    while(currentKeyVal!=NULL){
        //keyHash值的第一个keyVal对的key就是目标节点
        if(currentKeyVal->key==key && preKeyVal==NULL){
            hashDict->keyValList[keyHash]=
                    currentKeyVal->nextKeyVal;
            hashDict->amount--;
            return SUCCESS;
        }
        //找到keyHash 的 keyVal键值对链表中 键为key的keyVal对
        if(currentKeyVal->key==key){
            preKeyVal->nextKeyVal=currentKeyVal->nextKeyVal;
            free(currentKeyVal);
            hashDict->amount--;
            return SUCCESS;
        }
        //探查下一个keyVal对
        preKeyVal=currentKeyVal;
        currentKeyVal=currentKeyVal->nextKeyVal;
    }
    //没有找到hashKey的keyVal列表中 键为key的键值对
    return FAIL;
}

//获取 哈希表 key对应的val
Status get_HashDict(HashDict *hashDict,int key,void **val){
    if(hashDict==NULL)
        return FAIL;
    int keyHash= hash_HashDict(hashDict,key);
    KeyVal_HashDict *currentKeyVal=hashDict->keyValList[keyHash];

    //探查keyHash的所有keyVal对
    while(currentKeyVal!=NULL) {
        //找到key对应的val
        if(currentKeyVal->key==key){
            *val=currentKeyVal->val;
            return SUCCESS;
        }
        currentKeyVal=currentKeyVal->nextKeyVal;
    }
    //没有找到 keyHash的所有keyVal对中键为key 的 keyVal对
    return FAIL;
}
