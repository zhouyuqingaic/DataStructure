//
// Created by zhouyuqing on 2023/3/9.
//
#include "dynamicArray.h"

typedef struct _TESTSTRUCT{
    int data;
}TestStruct;

void printTestStruct(void *data){
    printf("%4d",((TestStruct *)data)->data);
}

void usingDynamicArray(){
    /*
     * 动态数组，使用测试案例
     */
    DynamicArray *dynamicArray=NULL;
    Status opResult=init_DynamicArray(&dynamicArray,4);
    if(FAIL==opResult){
        printf("初始化动态数组失败");
        return;
    }
    TestStruct *tempStruct=NULL;
    for(int i=0;i<10;i++) {
        tempStruct = (TestStruct *) malloc(sizeof(TestStruct));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+100;
        opResult=append_DynamicArray(dynamicArray,tempStruct);
        if(FAIL==opResult){
            printf("\n");
            printf("添加数据 ");
            printTestStruct(tempStruct);
            printf(" 失败\n");
            return;
        }
    }

    show_DynamicArray(dynamicArray,printTestStruct);

    printf("\n1--------------------------------------------------\n");

    for(int i=0;i<10;i++){
        tempStruct = (TestStruct *) malloc(sizeof(TestStruct));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+200;
        opResult= insertByPos_DynamicArray(dynamicArray,i,tempStruct);
        if(FAIL==opResult){
            printf("插入数据到%4d位置 ",i);
            printTestStruct(tempStruct);
            printf(" 失败\n");
            return;
        }
    }

    show_DynamicArray(dynamicArray,printTestStruct);

    printf("\n2--------------------------------------------------\n");

    for(int i=0;i<10;i++){
        tempStruct = (TestStruct *) malloc(sizeof(TestStruct));
        if(tempStruct==NULL)
            return;
        tempStruct->data=i+9900;
        opResult= setByPos_DynamicArray(dynamicArray,i,tempStruct);
        if(FAIL==opResult){
            printf("设置%4d位置的数据 ",i);
            printTestStruct(tempStruct);
            printf(" 失败\n");
            return;
        }
    }

    show_DynamicArray(dynamicArray,printTestStruct);

    printf("\n3--------------------------------------------------\n");

    void *temp=NULL;
    for(int i=5;i<15;i++){
        opResult= getByPos_DynamicArray(dynamicArray,i,&temp);
        if(FAIL==opResult){
            printf("获取%4d位置的数据失败\n",i);
            return;
        }else{
            printf("\n|");
            printTestStruct(temp);
        }
    }

    printf("\n4--------------------------------------------------\n");

    for(int i=5;i<15;i++){
        opResult= removeByPos_DynamicArray(dynamicArray,i,&temp);
        if(FAIL==opResult){
            printf("\n|删除%4d位置的数据失败\n",i);
        }else{
            printf("\n|删除");
            printTestStruct(temp);
            printf(" 成功!\n");
        }
    }

    show_DynamicArray(dynamicArray,printTestStruct);

    printf("\n4--------------------------------------------------\n");

    //清空动态数组
    opResult=destory_DynamicArray(&dynamicArray);
    if(SUCCESS==opResult)
        printf("销毁动态数组成功");
}

//int main(){
//    usingDynamicArray();
//    return 0;
//}