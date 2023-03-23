//
// Created by zhouyuqing on 2023/3/23.
//

#include "avlSortTree.h"

void printItemAVLSortTree(void *data){
    printf("%8d",*( (int *)data ));
}


//比较data1与data2
//data1>data2 返回1
//data1=data2 返回0
//data1<data2 返回-1
int compareAVLSortTree(void *data1,void *data2){
    int d1_data=*((int *)data1);
    int d2_data=*((int *)data2);

    if(d1_data>d2_data)
        return 1;
    else if(d1_data<d2_data)
        return -1;
    else
        return 0;
}


void usingAVLSortTree(){
    /*
     * AVLSortTree使用测试案例
     */

}

void main(){
    usingAVLSortTree();
}


