//
// Created by zhouyuqing on 2023/3/13.
//

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态

typedef void (*PRINT_DATA)(void *);

#endif

#ifndef DATASTRUCTURE_STRINGDYNAMIC_H
#define DATASTRUCTURE_STRINGDYNAMIC_H

#include<stdio.h>
#include<malloc.h>

typedef struct _STRING_DYNAMIC{
    char *str; //指向堆上字符数组
    int lengthStr; //字符串长度(不含结束标志位)
}StringDynamic; //动态数组

//清空变长字符串
Status empty_StringDynamic(StringDynamic *stringDynamic);
//初始化变长字符串
Status init_StringDynamic(StringDynamic **pStringDynamic);
//为变长字符串赋值
Status assign_StringDynamic(StringDynamic *stringDynamic, char *str);
//两字符串比较
Status compare_StringDynamic(const StringDynamic *str1,const StringDynamic *str2,int *result);
//两字将str2内容追加str1中
Status append_StringDynamic(StringDynamic *str1,const StringDynamic *str2);
//获取主串中从pos开始len长度的子串(pos位置从0开始计数)
Status sub_StringDynamic(const StringDynamic *str,int pos,int len,StringDynamic *subStr);
//展示字符串
Status show_StringDynamic(const StringDynamic *stringDynamic);
//销毁字符串
Status destroy_StringDynamic(StringDynamic **pStringDynamic);

//模式匹配,找到subStr在str中的匹配位置(pos从0开始计数)
Status index_StringDynamic(const StringDynamic *str,const StringDynamic *subStr,int *pos);

//根据str生成next数组(从下标0开始)
Status nextArray_StringDynamic(const StringDynamic *subStr,int **nextArray);
//模式匹配(利用KMP算法),找到subStr在str中的匹配位置(从下标0开始)
Status indexKMP_StringDynamic(const StringDynamic *str,const StringDynamic *subStr,int *pos);


#endif //DATASTRUCTURE_STRINGDYNAMIC_H
