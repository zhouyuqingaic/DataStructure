//
// Created by zhouyuqing on 2023/3/13.
//
#include "stringDynamic.h"


void usingStringDynamic(){
    /*
     * StringDynamic测试&使用案例
     */
    StringDynamic *stringDynamic=NULL;
    Status opResult=init_StringDynamic(&stringDynamic);
    if(FAIL==opResult){
        printf("初始化定长字符串失败!\n");
        return;
    }
    opResult=assign_StringDynamic(stringDynamic,"fajifdosajofisaojzhouyuqingdfajiofjdoisafj");
    if(FAIL==opResult){
        printf("为定长字符串赋值失败\n");
        return;
    }
    opResult= show_StringDynamic(stringDynamic);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    StringDynamic *stringDynamic01=NULL;
    opResult=init_StringDynamic(&stringDynamic01);
    if(FAIL==opResult){
        printf("初始化定长字符串失败!\n");
        return;
    }
    opResult=assign_StringDynamic(stringDynamic01,"fajifdosajofisaojzhouyuqinijipoueoiwpqjfl;dsjaklvopdsajb[sajefwq;fe/zjklvjc[xz]vqe]wkl;dsajfdsoapfdjiasf;dsagaicf"
                                                          "jfdsafjdsaoifdsijaodioajfiodoaafdsajfpoidsajifpodsajifpodsaiifdusiaofjdsal;fjdiospajfidsajf;ldsajfposapfjio"
                                                          "dsajoifjaiosojoifjeiwqfjkld;sajofjidosajoifpueoiwqjlbjsa;jiodspuoidavlmfewqoipfsajfds;lafjdslaoifpaifaejfdsajfi"
                                                          "fdsafdsajfiodsaijfjdisafjsdalkfafjdsaiofjdoisafjdsalfkdsafjdkslafdjskalfdjsalkfjklsafljaodsafsjafewfewqfdsajfklsa");
    if(FAIL==opResult){
        printf("为定长字符串赋值失败\n");
    }
    opResult= show_StringDynamic(stringDynamic01);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    printf("\n---------------1-------------------\n");

    StringDynamic *subStr;
    opResult=init_StringDynamic(&subStr);
    if(FAIL==opResult){
        printf("初始化定长字符串失败!\n");
        return;
    }
    opResult= sub_StringDynamic(stringDynamic,7,10,subStr);
    if(FAIL==opResult){
        printf("获取定长字符串子串失败!\n");
        return;
    }
    opResult= show_StringDynamic(subStr);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    int pos=0;
    opResult= index_StringDynamic(stringDynamic,subStr,&pos);
    if(FAIL==opResult)
        printf("普通模式:匹配模式串失败\n");
    else
        printf("普通模式:匹配模式串成功,匹配位置为:%d\n",pos);

    opResult= indexKMP_StringDynamic(stringDynamic,subStr,&pos);
    if(FAIL==opResult)
        printf("KMP模式:匹配模式串失败\n");
    else
        printf("KMP模式:匹配模式串成功,匹配位置为:%d\n",pos);



    printf("\n---------------2-------------------\n");


    opResult= append_StringDynamic(stringDynamic,subStr);
    if(FAIL==opResult){
        printf("定长字符串追加失败\n");
    }
    opResult= show_StringDynamic(stringDynamic);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    opResult= append_StringDynamic(stringDynamic,stringDynamic);
    if(FAIL==opResult){
        printf("定长字符串追加失败\n");
    }
    opResult= show_StringDynamic(stringDynamic);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    opResult= append_StringDynamic(stringDynamic,stringDynamic);
    if(FAIL==opResult){
        printf("定长字符串追加失败\n");
    }
    opResult= show_StringDynamic(stringDynamic);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    printf("\n---------------3-------------------\n");

    int resultCompare=0;
    opResult=compare_StringDynamic(stringDynamic,stringDynamic,&resultCompare);
    if(SUCCESS==opResult)
        printf("stringFixedLength与stringFixedLength比较，结果为:%d\n",resultCompare);
    else
        printf("stringFixedLength与stringFixedLength比较失败\n");

    opResult= compare_StringDynamic(stringDynamic,subStr,&resultCompare);
    if(SUCCESS==opResult)
        printf("stringFixedLength与subStr比较，结果为:%d\n",resultCompare);
    else
        printf("stringFixedLength与subStr比较失败\n");

    opResult= compare_StringDynamic(stringDynamic,stringDynamic01,&resultCompare);
    if(SUCCESS==opResult)
        printf("stringFixedLength与stringFixedLength01比较，结果为:%d\n",resultCompare);
    else
        printf("stringFixedLength与stringFixedLength01比较失败\n");

    printf("\n---------------4-------------------\n");

    opResult=destroy_StringDynamic(&stringDynamic);
    if(SUCCESS==opResult)
        printf("销毁字符串%s成功\n","stringDynamic");
    opResult=destroy_StringDynamic(&stringDynamic01);
    if(SUCCESS==opResult)
        printf("销毁字符串%s成功\n","stringDynamic01");
    opResult=destroy_StringDynamic(&subStr);
    if(SUCCESS==opResult)
        printf("销毁字符串%s成功\n","subStr");

}
//
//void main(){
//    usingStringDynamic();
//}
