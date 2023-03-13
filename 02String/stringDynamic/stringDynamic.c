//
// Created by zhouyuqing on 2023/3/13.
//

#include"stringDynamic.h"

//清空变长字符串
Status empty_StringDynamic(StringDynamic *stringDynamic){
    if(stringDynamic==NULL)
        return FAIL;
    if(stringDynamic->str!=NULL) {
        free(stringDynamic->str);
        stringDynamic->str=NULL;
    }
    stringDynamic->lengthStr=0;
    return SUCCESS;
}
//初始化变长字符串
Status init_StringDynamic(StringDynamic **pStringDynamic){
    if(*pStringDynamic==NULL){ //变长串不存在，创建变长串
        StringDynamic *str=(StringDynamic *)malloc(sizeof(StringDynamic));
        str->str=NULL;
        str->lengthStr=0;
        *pStringDynamic=str;
        return SUCCESS;
    }else{ //变长串存在，清空变长串
        Status opResult= empty_StringDynamic(*pStringDynamic);
        return opResult;
    }
}
//为变长字符串赋值
Status assign_StringDynamic(StringDynamic *stringDynamic, char *str){
    if(stringDynamic==NULL || str==NULL)
        return FAIL;
    //清空原变长串
    Status opResult= empty_StringDynamic(stringDynamic);
    if(FAIL==opResult)
        return FAIL;

    //获取字符串长度
    int indexStr=0;
    while(str[indexStr]!='\0')
        indexStr++;

    //创建动态字符串(indexStr+1)是为了多出来最后一位放置'\0'结束标志位
    stringDynamic->str=(char *)malloc(sizeof(char)*(indexStr+1));

    //将str中的数据放入变长串中,并添加结束标志位置
    indexStr=0;
    while(str[indexStr]!='\0'){
        stringDynamic->str[indexStr]=str[indexStr];
        indexStr++;
    }
    stringDynamic->str[indexStr]='\0';
    stringDynamic->lengthStr=indexStr;

    return SUCCESS;
}
//两字符串比较
Status compare_StringDynamic(const StringDynamic *str1,const StringDynamic *str2,int *result){
    if(str1==NULL || str2==NULL)
        return FAIL;
    for(int i=0;i<str1->lengthStr && i<str2->lengthStr;i++){
        if(str1->str[i]!=str2->str[i]){
            *result=str1->str[i]-str2->str[i];
            return SUCCESS;
        }
    }
    *result=str1->lengthStr-str2->lengthStr;
    return SUCCESS;
}
//两字将str2内容追加str1中
Status append_StringDynamic(StringDynamic *str1,const StringDynamic *str2){
    if(str1==NULL || str2==NULL)
        return FAIL;
    if(str2->lengthStr==0)
        return SUCCESS;
    Status opResult=FAIL;
    char *str=NULL;
    if(str1->lengthStr==0){ //当被追加变长串为空
        //str2->lengthStr+1为了包含结束标志位
        str=(char *)malloc(sizeof(char)*(str2->lengthStr+1));
        if(str==NULL)
            return FAIL;
        //将str2中全部内容加入str
        for(int i=0;i<str2->lengthStr;i++)
            str[i]=str2->str[i];
        str[str2->lengthStr]='\0'; //添加结束标志位

        //更新追加字符串
        str1->str=str;
        str1->lengthStr=str2->lengthStr;

        return SUCCESS;
    }else{ //当前被追加动态串不为空
        //str1->lengthStr+str2->lengthStr+1为了包含结束标志位'\0'
        str=(char *)malloc(sizeof(char)*(str1->lengthStr+ str2->lengthStr+1) );
        if(str==NULL)
            return FAIL;
        int indexStr=0;
        //将str1加入str
        for(int i=0;i<str1->lengthStr;i++)
            str[indexStr++]=str1->str[i];
        //将str2加入str
        for(int i=0;i<str2->lengthStr;i++)
            str[indexStr++]=str2->str[i];
        str[str1->lengthStr+str2->lengthStr]='\0'; //添加结束标志位


        //清空原来字符串
        free(str1->str);
        str1->str=NULL;
        //更新追加字符串
        str1->str=str;
        //更新长度
        str1->lengthStr=str1->lengthStr+str2->lengthStr;

        return SUCCESS;
    }
}
//获取主串中从pos开始len长度的子串(pos位置从0开始计数)
Status sub_StringDynamic(const StringDynamic *str,int pos,int len,StringDynamic *subStr){
    if(str==NULL || subStr==NULL)
        return FAIL;
    //判断pos和len是否合法
    if(pos < 0 || pos > str->lengthStr-1)
        return FAIL;
    //由于 pos开始长len的下标范围为 pos~pos+(len-1) 判断len是否合法
    if(len<0 || pos+len-1 > str->lengthStr-1)
        return FAIL;
    //清空子串subStr
    Status opResult=empty_StringDynamic(subStr);
    if(FAIL==opResult)
        return FAIL;
    if(len==0)
        return SUCCESS;
    //len+1为了容纳最后一位结束标志位
    subStr->str=(char *)malloc(sizeof(char)*(len+1));
    if(subStr->str==NULL)
        return FAIL;
    //pos~pos+len-1位置上的元素加入str中
    for(int i=0;i<len;i++)
        subStr->str[i]=str->str[i+pos];
    subStr->str[len]='\0';
    subStr->lengthStr=len;

    return SUCCESS;
}
//展示字符串
Status show_StringDynamic(const StringDynamic *stringDynamic){
    if(stringDynamic==NULL)
        return FAIL;
    printf("\n\t%s\n", stringDynamic->str);
    return SUCCESS;
}
//销毁字符串
Status destroy_StringDynamic(StringDynamic **pStringDynamic){
    if(*pStringDynamic==NULL)
        return SUCCESS;
    //字符串不空，清空字符串
    Status opResult=empty_StringDynamic(*pStringDynamic);
    if(FAIL==opResult)
        return FAIL;
    //释放定长字符串
    free(*pStringDynamic);
    *pStringDynamic=NULL;
    return SUCCESS;
}

//模式匹配,找到subStr在str中的匹配位置(pos从0开始计数)
Status index_StringDynamic(const StringDynamic *str,const StringDynamic *subStr,int *pos){
    if(str==NULL || subStr==NULL)
        return FAIL;

    *pos=0; //记录本轮匹配 主串的开始匹配位置
    //主串从本轮匹配的位置开始 和 子串从第一个位置开始匹配
    int indexStr=*pos,indexSubStr=0;
    while(indexStr < str->lengthStr && indexSubStr < subStr->lengthStr){
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
Status nextArray_StringDynamic(const StringDynamic *subStr,int **nextArray){
    if(subStr==NULL)
        return FAIL;
    int i=0,j=-1; //i标记当前参与比较的位置，从0~subStr->lengthStr-1
    //创建next数组
    int *next=(int *)malloc(sizeof(int)*subStr->lengthStr);
    next[i]=j; //子串0处(开头处)发生不匹配，属于特殊情况，从主串的下个位置与子串的开头进行匹配
    if(next==NULL)
        return FAIL;
    while(i<subStr->lengthStr-1){
        if(j==-1 || subStr->str[i]==subStr->str[j]){ //特殊情况开头发生不匹配 或 pi=pj,则next[i+1]必等于j+1
            i++;
            j++;
            next[i]=j;
        }else{ //pi与pj不匹配，查找next表找到与pi进行检查的j
            j=next[j];
        }
    }

    //返回next数组
    if(*nextArray!=NULL){
        free(*nextArray);
        *nextArray=NULL;
    }

    *nextArray=next;

    return SUCCESS;
}
//模式匹配(利用KMP算法),找到subStr在str中的匹配位置(从下标0开始)
Status indexKMP_StringDynamic(const StringDynamic *str,const StringDynamic *subStr,int *pos){
    if(str==NULL || subStr==NULL)
        return FAIL;
    //子串或主串长度为0，也匹配失败
    if(str->lengthStr==0 || subStr->lengthStr==0)
        return FAIL;
    //生成子串的next数组
    int *nextArray=NULL;
    Status opResult= nextArray_StringDynamic(subStr,&nextArray);


    if(FAIL==opResult)
        return FAIL;
    //开始匹配
    int indexStr=0,indexSubStr=0;
    while(indexStr<str->lengthStr && indexSubStr<subStr->lengthStr){
        if(str->str[indexStr]==subStr->str[indexSubStr]){ //主串当前元素与子串当前元素匹配成功，一起后移一位
            indexStr++;
            indexSubStr++;
        }else{ //主串元素与子串当前元素发生不匹配
            indexSubStr=nextArray[indexSubStr]; //获取子串下个与主串当前是配置位置比较的元素索引
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
        *pos= indexStr-subStr->lengthStr;
        return SUCCESS;
    }

}



