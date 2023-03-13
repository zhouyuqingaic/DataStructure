//
// Created by zhouyuqing on 2023/3/12.
//

#include "stringFixedLength.h"

//清空定长字符串
Status empty_StringFixedLength(StringFixedLength *stringFixedLength){
    if(stringFixedLength==NULL)
        return FAIL;
    if(stringFixedLength->lengthStr!=0) { //定长字符串不为空时,将其置空
        //字符串全部置0
        memset(stringFixedLength->str, 0, stringFixedLength->lengthStr);
        stringFixedLength->lengthStr = 0;
    }
    return SUCCESS;
}
//初始化指定长度的字符串
Status init_StringFixedLength(StringFixedLength **pStringFixedLength){
    if(*pStringFixedLength==NULL){ //定长字符串不存在则创建
        StringFixedLength *stringFixedLength=(StringFixedLength *)malloc(sizeof(StringFixedLength));
        if(stringFixedLength==NULL)
            return FAIL;
        //重置新创建的定长字符串
        stringFixedLength->lengthStr=0;
        memset(stringFixedLength->str,0,MAX_LENGTH_STR);

        *pStringFixedLength=stringFixedLength;
        return SUCCESS;
    }else{ //定长字符串存在则清空
        Status opResult= empty_StringFixedLength(*pStringFixedLength);
        return opResult;
    }
}
//为定长字符串赋值
Status assign_StringFixedLength(StringFixedLength *stringFixedLength, char *str){
    if(stringFixedLength==NULL)
        return FAIL;
    if(str==NULL) //传入字符串不能为空
        return FAIL;
    //获取str长度
    int lenStr=0;
    while(str[lenStr]!='\0')
        lenStr++;
    lenStr+=1; //再计入最后一位结束标志位'\0'
    // 判断当前定长字符串的长度是否可以容纳str
    if(MAX_LENGTH_STR < lenStr)
        return FAIL;
    //清空定长字符串员原来的值 并为定长字符串赋值
    Status opResult= empty_StringFixedLength(stringFixedLength);
    if(FAIL==opResult)
        return FAIL;
    int index=0;
    while(str[index]!='\0'){
        stringFixedLength->str[index]=str[index];
        index++;
    }
    stringFixedLength->str[index]='\0'; //为定长字符串设置结束标志位
    stringFixedLength->lengthStr=index; //设置定长字符串长度

    return SUCCESS;
}
//两字符串比较
Status compare_StringFixedLength(const StringFixedLength *str1,const StringFixedLength *str2,int *result){
    if(str1==NULL || str2==NULL)
        return FAIL;
    //匹配所有的相同字符
    int i;
    for(i=0;i<str1->lengthStr && i<str2->lengthStr;i++){
        if(str1->str[i] != str2->str[i]) { //两个字符串有不同的部分
            *result = str1->str[i] - str2->str[i];
            return SUCCESS;
        }
    }
    //其中一个为另一个从开头开始的一部分 则返回两字符串长度差
    *result=str1->lengthStr-str2->lengthStr;
    return SUCCESS;
}

//两字将str2内容追加str1中
Status append_StringFixedLength(StringFixedLength *str1,const StringFixedLength *str2){
    if(str1==NULL || str2==NULL)
        return FAIL;
    //判断str1余下的内容是否可以容纳的下str2的内容
    if(MAX_LENGTH_STR-(str1->lengthStr-1) < str2->lengthStr) //(str1->lengthStr-1)因为合并的时候会消去str1中末尾的结束标志位'\0'
        return FAIL;
    for(int i=0;i<str2->lengthStr;i++)
        str1->str[str1->lengthStr+i]=str2->str[i]; //从str1->str[str1->lengthStr]开始填充，覆盖掉原来的'\0'
    //为str1添加结束标志位
    str1->str[str1->lengthStr+str2->lengthStr]='\0';
    str1->lengthStr+=str2->lengthStr;
    return SUCCESS;
}

//获取主串中从pos开始len长度的子串(pos从0开始计数 从0~str->lengthStr-1 )
Status sub_StringFixedLength(const StringFixedLength *str,int pos,int len,StringFixedLength *subStr){
    if(str==NULL || subStr==NULL)
        return FAIL;
    //判断pos和len是否合法
    if(pos < 0 || pos > str->lengthStr-1)
        return FAIL;
    //由于 pos开始长len的下标范围为 pos~pos+(len-1) 判断len是否合法
    if(len<0 || pos+len-1 > str->lengthStr-1)
        return FAIL;
    //向result填充字符
    for(int i=0;i<len;i++)
        subStr->str[i]=str->str[pos+i];
    subStr->lengthStr=len;
    return SUCCESS;
}

//展示字符串
Status show_StringFixedLength(const StringFixedLength *stringFixedLength){
    if(stringFixedLength==NULL)
        return FAIL;
    printf("\n\t%s\n", stringFixedLength->str);
    return SUCCESS;
}

//销毁字符串
Status destroy_StringFixedLength(StringFixedLength **pStringFixedLength){
    if(*pStringFixedLength==NULL)
        return SUCCESS;
    //字符串不空，清空字符串
    Status opResult=empty_StringFixedLength(*pStringFixedLength);
    if(FAIL==opResult)
        return FAIL;
    //释放定长字符串
    free(*pStringFixedLength);
    *pStringFixedLength=NULL;
    return SUCCESS;
}
//模式匹配,找到subStr在str中的匹配位置(pos从0开始计数)
Status index_StringFixedLength(const StringFixedLength *str,const StringFixedLength *subStr,int *pos){
    if(str==NULL || subStr==NULL)
        return FAIL;

    *pos=0; //记录本轮匹配 主串的开始匹配位置
    //主串从本轮匹配的位置开始 和 子串从第一个位置开始匹配
    int indexStr=*pos,indexSubStr=0;
    while(indexStr<str->lengthStr && indexSubStr<subStr->lengthStr){
        if(str->str[indexStr]==subStr->str[indexSubStr]){ //当前元素匹配成功，主串和子串同时开始匹配下一位
            indexStr++;
            indexSubStr++;
        }else{ //匹配失败 主串从本轮开始的下个位置 和 子串的第一个位置开始匹配
            (*pos)++;
            indexStr=*pos;
            indexSubStr=0;
        }
    }

    if(indexSubStr<subStr->lengthStr) //匹配失败，子串没有完全匹配成功
        return FAIL;
    else
        return SUCCESS;
}

//根据str生成next数组(从下标0开始)
Status nextArray_StringFixedLength(const StringFixedLength *subStr,int **nextArray){
    if(subStr==NULL)
        return FAIL;
    int i=0,j=-1; //i标记当前参与比较的位置，从0~subStr->lengt-1
    //创建next数组
    int *next=(int *)malloc(subStr->lengthStr*sizeof(int));
    if(nextArray==NULL)
        return FAIL;
    next[i]=j; //子串0处(开头处)发生不匹配，属于特殊情况，从主串的下个位置与子串的开头进行匹配

    while(i<subStr->lengthStr-1){
        if(j==-1 || subStr->str[j]==subStr->str[i]){ //特殊情况开头发生不匹配 或 者pi=pj,则next[i+1]必等于j+1
            i++;
            j++;
            next[i]=j;
        }else{ //pi与pj不匹配，查找next表找到与pi的下个检查位置j
            j=next[j];
        }
    }

    //返回next数组
    if(*nextArray!=NULL) {
        free(*nextArray);
        *nextArray=NULL;
    }
    *nextArray=next;

    return SUCCESS;
}
//模式匹配(利用KMP算法),找到subStr在str中的匹配位置(从下标0开始)
Status indexKMP_StringFixedLength(const StringFixedLength *str,const StringFixedLength *subStr,int *pos){
    if(str==NULL || subStr==NULL)
        return FAIL;
    //子串或主串长度为0，也匹配失败
    if(str->lengthStr==0 || subStr->lengthStr==0)
        return FAIL;

    //生成子串的next数组
    int *nextArray=NULL;
    Status opResult= nextArray_StringFixedLength(subStr,&nextArray);
    if(opResult==FAIL)
        return FAIL;

    //匹配子串与主串
    int indexStr=0,indexSubStr=0;
    while(indexStr<str->lengthStr && indexSubStr<subStr->lengthStr){
        if(str->str[indexStr]==subStr->str[indexSubStr]){ //主串当前元素和子串当前元素匹配成功，则一起后移一位
            indexStr++;
            indexSubStr++;
        }else{ //主串当前元素与子串当前元素匹配不成功
            indexSubStr=nextArray[indexSubStr]; //获取子串下个与主串当前失配位置比较的元素索引
            // indexSubStr==-1 此时子串F中没有公共前后缀 或者 与子串开头发生不匹配，则主串的当前位置也要移动后一位，子串indexSubStr由-1增加一位变成0
            if(indexSubStr==-1){
                indexStr++;
                indexSubStr++;
            }
        }
    }

    //释放next数组
    free(nextArray);
    nextArray=NULL;

    if(indexSubStr<subStr->lengthStr){ //子串没有完全匹配，匹配失败
        return FAIL;
    }else{ //匹配成功
        *pos=indexStr-subStr->lengthStr;
        return SUCCESS;
    }
}
