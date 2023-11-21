//
//  Header_String.h
//  String
//
//  Created by 舒佳瑞 on 2023/11/7.
//

//几个简单的概念：
//1、字串：串中任意个连续字符组成的子序列
//2、主串：包含字串的串
//3、字符在字串中的位置：字符在串中的序列
//4、字串在主串中的位置：字串的 第一个字符在主串中的位置
//5、空格也是字符
//6、序位是从1开始的
//7、一个字符占一个B，八个比特位


//串是线性表的一种特殊表，数据成线性关系
//串的增删改查基本上是对字串进行操作的

#include <stdio.h>
#define maxSzie 255

typedef struct _StringNode
{
    char ch;
    struct _StringNode* next;
}StringNode;
//这样存储有一个缺点就是存储密度低
//在C语言中一个字符的大小是1个字节，而指针却要4个字节（32个比特位）
//这样来说这种存储方式的存储密度太低了
//可以参考下面这种存储方式

typedef struct _StringNode1
{
    char ch[4];
    struct _StringNode1* next;
}StringNode1;

typedef struct _SStringNode
{
    char ch[maxSzie];
    int length=1;
}SStringNode;



bool AddStr(SStringNode &SS,char in[30])
{
    int size=0,k=0;
    for (; in[k]!='\0'; k++) {
        size++;
    }
    if (maxSzie-SS.length<size) {
        return false;
    }
    int i=1;//因为串的起始位置是从1开始，我直接舍去一个空间吧
    int j=0;
    for(;i<SS.length;i++)
    {
        if(SS.ch[i]=='\0')
        {
            break;
        }
    }
    for (; in[j]!='\0'; j++,i++) {
        SS.ch[i]=in[j];
    }
    SS.ch[i]='\0';
    SS.length+=j-1;//因为数组从0开始，而串从1开始，所以要减掉1
    return true;
}


void display(SStringNode SS)
{
    int i=1;
    printf("串的元素如下：");
    for (; SS.ch[i]!='\0'; i++) {
        printf("%c  ",SS.ch[i]);
    }
    printf("\n");
}


bool SubString(SStringNode &Sub,SStringNode S,int pos,int len)
{
    if (pos+len>S.length) {
        return false;
    }
    
    for (int i=pos; i<pos+len; i++) 
    {
        Sub.ch[i-pos+1]=S.ch[i];//[i-pos+1]，其实这个就是让数组下标从1开始
    }
    Sub.length=len;
    return true;
}


int StrCompare(SStringNode str1,SStringNode str2)//如果>0就是str1大，如果==0的话就证明这两个串相等，如果<0这就是str2大
{
    int i=1;//一定得明确的是不是谁长就谁大
    for (; i<str1.length&&i<str2.length; i+=1) {
        if (str1.ch[i]!=str2.ch[i]) {
            return str1.ch[i]-str2.ch[i];
        }
    }
    return str1.ch[i]-str2.ch[i];
}

int Index(SStringNode str1,SStringNode str2)
{
    int i=1;
    SStringNode Sub;
    while (i<str1.length-str2.length+1)
    {
        SubString(Sub, str1, i, str2.length);
        if (StrCompare(Sub,str2))
        {
            i++;
        }
        else
        {
            return i;
        }
    }
    return 0;
}


int BF(SStringNode targetString,SStringNode patternString)
{
    int i=1,j=1;
    for (;i<=targetString.length&&j<=patternString.length;)
    {
        if (targetString.ch[i]==patternString.ch[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i=i-j+2;
            j=1;
        }
    }
    if (j>patternString.length) {
        return i-patternString.length;
    }
    else
        return 0;
   
}


void getNext(SStringNode T,int next[])
{
    int i=1,j=0;
    next[1]=0;
    while (i<T.length) 
    {
        if (j==0||T.ch[i]==T.ch[j]) 
        {
            ++i;
            ++j;
            next[i]=j;
        }
        else
            j=next[j];
    }
}

int IndexKMP(SStringNode S,SStringNode T)
{
    int i=1,j=1;
    int next[T.length];
    getNext(T, next);
    while (i<=S.length&&j<=T.length)
    {
        if (j==0||S.ch[i]==T.ch[j])
        {
            ++i;
            ++j;
        }
        else
            j=next[j];
    }
    if (j>T.length) {
        return i-T.length;
    }
    else
        return 0;
}
