//
// Created by zhouyuqing on 2023/3/12.
//
#ifdef __cplusplus
extern "C"{
#endif

#ifndef COMMON_DEFINE_H
#define COMMON_DEFINE_H

#define SUCCESS 1
#define FAIL 0
typedef int Status; //函数执行状态

typedef void (*PRINT_DATA)(void *);

#endif

#ifndef DATASTRUCTURE_STRINGFIXEDLENGTH_H
#define DATASTRUCTURE_STRINGFIXEDLENGTH_H

#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define MAX_LENGTH_STR 120

typedef struct {
    char str[MAX_LENGTH_STR]; //指堆上的字符数组
    int lengthStr; //字符串长度(实际str指向的字符数组长度必须为lengthStr+1,为了包含最后一位结束标志位)
} StringFixedLength; //定长字符串

//清空定长字符串
Status empty_StringFixedLength(StringFixedLength *stringFixedLength);

//初始化指定长度的字符串
Status init_StringFixedLength(StringFixedLength **pStringFixedLength);

//为定长字符串赋值
Status assign_StringFixedLength(StringFixedLength *stringFixedLength, char *str);

//两字符串比较
Status compare_StringFixedLength(const StringFixedLength *str1, const StringFixedLength *str2, int *result);

//两字将str2内容追加str1中
Status append_StringFixedLength(StringFixedLength *str1, const StringFixedLength *str2);

//获取主串中从pos开始len长度的子串(pos位置从0开始计数)
Status sub_StringFixedLength(const StringFixedLength *str, int pos, int len, StringFixedLength *subStr);

//展示字符串
Status show_StringFixedLength(const StringFixedLength *stringFixedLength);

//销毁字符串
Status destroy_StringFixedLength(StringFixedLength **pStringFixedLength);

//模式匹配,找到subStr在str中的匹配位置(pos从0开始计数)
Status index_StringFixedLength(const StringFixedLength *str, const StringFixedLength *subStr, int *pos);

//根据str生成next数组(从下标0开始)
Status nextArray_StringFixedLength(const StringFixedLength *subStr, int **nextArray);

//模式匹配(利用KMP算法),找到subStr在str中的匹配位置(从下标0开始)
Status indexKMP_StringFixedLength(const StringFixedLength *str, const StringFixedLength *subStr, int *pos);


#endif //DATASTRUCTURE_STRINGFIXEDLENGTH_H

#ifdef __cplusplus
}
#endif