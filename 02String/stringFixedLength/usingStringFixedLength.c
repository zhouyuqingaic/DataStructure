//
// Created by zhouyuqing on 2023/3/12.
//

#include "stringFixedLength.h"

void usingStringFixedLength(){
    /*
     * StringFixedLength测试&使用案例
     */
    StringFixedLength *stringFixedLength=NULL;
    Status opResult=init_StringFixedLength(&stringFixedLength);
    if(FAIL==opResult){
        printf("初始化定长字符串失败!\n");
        return;
    }
    opResult=assign_StringFixedLength(stringFixedLength,"fajifdosajofisaojzhouyuqingdfajiofjdoisafj");
    if(FAIL==opResult){
        printf("为定长字符串赋值失败\n");
        return;
    }
    opResult= show_StringFixedLength(stringFixedLength);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    StringFixedLength *stringFixedLength01=NULL;
    opResult=init_StringFixedLength(&stringFixedLength01);
    if(FAIL==opResult){
        printf("初始化定长字符串失败!\n");
        return;
    }
    opResult=assign_StringFixedLength(stringFixedLength01,"fajifdosajofisaojzhouyuqinijipoueoiwpqjfl;dsjaklvopdsajb[sajefwq;fe/zjklvjc[xz]vqe]wkl;dsajfdsoapfdjiasf;dsagaicf"
                                                        "jfdsafjdsaoifdsijaodioajfiodoaafdsajfpoidsajifpodsajifpodsaiifdusiaofjdsal;fjdiospajfidsajf;ldsajfposapfjio"
                                                        "dsajoifjaiosojoifjeiwqfjkld;sajofjidosajoifpueoiwqjlbjsa;jiodspuoidavlmfewqoipfsajfds;lafjdslaoifpaifaejfdsajfi"
                                                        "fdsafdsajfiodsaijfjdisafjsdalkfafjdsaiofjdoisafjdsalfkdsafjdkslafdjskalfdjsalkfjklsafljaodsafsjafewfewqfdsajfklsa");
    if(FAIL==opResult){
        printf("为定长字符串赋值失败\n");
    }
    opResult= show_StringFixedLength(stringFixedLength01);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    printf("\n---------------1-------------------\n");

    StringFixedLength *subStr;
    opResult=init_StringFixedLength(&subStr);
    if(FAIL==opResult){
        printf("初始化定长字符串失败!\n");
        return;
    }
    opResult= sub_StringFixedLength(stringFixedLength,7,10,subStr);
    if(FAIL==opResult){
        printf("获取定长字符串子串失败!\n");
        return;
    }
    opResult= show_StringFixedLength(subStr);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    int pos=0;
    opResult= index_StringFixedLength(stringFixedLength,subStr,&pos);
    if(FAIL==opResult)
        printf("普通模式:匹配模式串失败\n");
    else
        printf("普通模式:匹配模式串成功,匹配位置为:%d\n",pos);

    opResult= indexKMP_StringFixedLength(stringFixedLength,subStr,&pos);
    if(FAIL==opResult)
        printf("KMP模式:匹配模式串失败\n");
    else
        printf("KMP模式:匹配模式串成功,匹配位置为:%d\n",pos);



    printf("\n---------------2-------------------\n");

    opResult= append_StringFixedLength(stringFixedLength,subStr);
    if(FAIL==opResult){
        printf("定长字符串追加失败\n");
    }
    opResult= show_StringFixedLength(stringFixedLength);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    opResult= append_StringFixedLength(stringFixedLength,stringFixedLength);
    if(FAIL==opResult){
        printf("定长字符串追加失败\n");
    }
    opResult= show_StringFixedLength(stringFixedLength);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    opResult= append_StringFixedLength(stringFixedLength,stringFixedLength);
    if(FAIL==opResult){
        printf("定长字符串追加失败\n");
    }
    opResult= show_StringFixedLength(stringFixedLength);
    if(FAIL==opResult){
        printf("展示定长字符串失败\n");
    }

    printf("\n---------------3-------------------\n");

    int resultCompare=0;
    opResult=compare_StringFixedLength(stringFixedLength,stringFixedLength,&resultCompare);
    if(SUCCESS==opResult)
        printf("stringFixedLength与stringFixedLength比较，结果为:%d\n",resultCompare);
    else
        printf("stringFixedLength与stringFixedLength比较失败\n");

    opResult= compare_StringFixedLength(stringFixedLength,subStr,&resultCompare);
    if(SUCCESS==opResult)
        printf("stringFixedLength与subStr比较，结果为:%d\n",resultCompare);
    else
        printf("stringFixedLength与subStr比较失败\n");

    opResult= compare_StringFixedLength(stringFixedLength,stringFixedLength01,&resultCompare);
    if(SUCCESS==opResult)
        printf("stringFixedLength与stringFixedLength01比较，结果为:%d\n",resultCompare);
    else
        printf("stringFixedLength与stringFixedLength01比较失败\n");

    printf("\n---------------4-------------------\n");

    opResult=destroy_StringFixedLength(&stringFixedLength);
    if(SUCCESS==opResult)
        printf("销毁字符串%s成功\n","stringFixedLength");
    opResult=destroy_StringFixedLength(&stringFixedLength01);
    if(SUCCESS==opResult)
        printf("销毁字符串%s成功\n","stringFixedLength01");
    opResult=destroy_StringFixedLength(&subStr);
    if(SUCCESS==opResult)
        printf("销毁字符串%s成功\n","subStr");

}


//void main(){
//    usingStringFixedLength();
//}
