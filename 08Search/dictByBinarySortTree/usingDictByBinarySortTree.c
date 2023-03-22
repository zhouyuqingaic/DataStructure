//
// Created by zhouyuqing on 2023/3/21.
//

#include"dictByBinarySortTree.h"

//比较键值对d1与键值对d2 (此处key用的是int *,随用户自定义变化而变化)
int compare_data_dict_by_binary_sort_tree(void *d1,void *d2){
    KeyAndVal *k1=(KeyAndVal *)d1,*k2=(KeyAndVal *)d2;
    int a=*( (int *)(k1->key) ),b=*( (int *)(k2->key) );
    if(a>b)
        return 1;
    else if(a<b)
        return -1;
    else
        return 0;
}