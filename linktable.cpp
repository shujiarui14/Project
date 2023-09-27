//
//  linkTable.h
//  linkTable
//
//  Created by 舒佳瑞 on 2023/9/22.
//

#ifndef linkTable_h
#define linkTable_h


#endif /* linkTable_h */
#include <stdio.h>
#include <stdlib.h>

typedef struct _LNode//带头节点的
{
    int date;//其实我一直很疑惑这里为什么不是指针类型，因为之前顺序表这里定义的是个指针，但现在不再是使用date指针来管理malloc分配的空间，是用LNode类型来管理的，所以自然而然date就可以不定义为指针类型
    struct _LNode* next;
}LNode,*LinkList;


bool initList(LinkList &L)
{
    L=NULL;
    return true;
}

bool listInserct(LinkList &L,int elem ,int i)
{
    if (i<1) {
        return  false;
    }
    LNode* move=L;
    int j=0;
    while (move!=NULL&&j<i-1)
    {
        move=move->next;
        j+=1;
    }
    if (move==NULL) {
        return false;
    }
    LNode *in=(LinkList)malloc(sizeof(LNode));
    in->date=elem;
    in->next=move->next;
    move->next=in;
    return true;
}

bool listInserct1(LinkList &L,int elem,int i)
{
    if (i<1) {
        return  false;
    }
    if (i==1) {
        LNode* in=(LNode*)malloc(sizeof(LNode));
        in->date=elem;
        in->next=L;
        L=in;
        return true;//如果i==1的话，执行到这里就会直接返回去了，不会再运行下面的了
    }
    int j=1;
    LNode* move=L;
    if (move!=NULL&&j<i-1) {
        move=move->next;
        j++;
    }
    if (move==NULL) {
        return false;
    }
    LNode* in=(LNode*)malloc(sizeof(LNode));
    in->date=elem;
    in->next=move->next;//这里的顺序必须这么这么写
    move->next=in;
    return true;
}

bool InserctNextNode(LNode* p,int elem)//在p节点之后插入一个数e，传过来的这个节点该如何描述？
{
    if (p==NULL) {
        return false;
    }
    LNode* in=(LNode*)malloc(sizeof(LNode));
    if (in==NULL) {
        return false;
    }
    in->date=elem;
    in->next=p->next;
    p->next=in;
    return true;
}

bool InsertPriorNode(LNode* p,LNode* in)//在p节点之后插入一个数e，
{
    if (p==NULL) {
        return false;
        printf("inserct fail\n");
    }
    in->next=p->next;
    p->next=in;
    int tmp=p->date;
    p->date=in->date;
    in->date=tmp;
    return true;
}//其实简单来说只是把新节点插进来之后把p的数据域和插进来节点的数据域交换一下


void listDisplay(LinkList &L)
{
    LNode* tmp=L;
    tmp=tmp->next;
    while (tmp!=NULL) {
        printf("%d  ",tmp->date);
        tmp=tmp->next;
    }
    free(tmp);
}

void listDelete(LinkList &L,int &del,int i)
{
    if (i<1) {
        return;
    }
    LNode* move=L;
    int j=0;
    while (move!=NULL&&j<i-1) {
        move=move->next;
        j++;
    }
    if (move==NULL) {
        return;
    }
    LNode* reDel=move->next;
    del=reDel->date;
    move->next=move->next->next;
    //move=reDel->next;
    free(reDel);
}

int listLength(LinkList &L)
{
    int i=0;
    LNode *move=L;
    for (; move->next!=NULL; i++) {
        move=move->next;
    }
    return i;
}

void getElem(LinkList &L,int &elem,int i)
{
    if (i<1) {
        return;
    }
    int j=1;
    LNode *move=L->next;
    while (move!=NULL&&j<i) {
        move=move->next;
        j++;
    }
    elem=move->date;
}

int locateElem(LinkList &L,int elem)
{
    int i=1;
    LNode* move=L;
    while (move->next!=NULL) {
        move=move->next;
        i++;
        if (move->date==elem) {
            return i;
        }
    }
    return 0;
}

void listDestroy(LinkList &L)
{
    LNode* dst=L;
    LNode* predst=L->next;
    while (predst!=NULL) {
        free(dst);
        dst=predst;
        predst=predst->next;
    }
    free(dst); //这儿肯定会多出来一个dst，而predet已经指向NULL了，就没必要释放了，只有dst是多出来的
}


//#include "linkTable.h"

int main()
{
    LinkList L;
    L=(LNode*)malloc(sizeof(LNode));
    L->next=NULL;
    listInserct(L, 9, 1);
    listInserct(L, 8, 2);
    listInserct(L, 29, 3);
    listInserct(L, 5, 4);
    listInserct(L, 99, 5);
    listInserct(L, 65, 6);
    listDisplay(L);
    int del=0;
    listDelete(L,del, 2);
    printf("\n删除的值是：%d\n",del);
    listDisplay(L);
    printf("\n");
    printf("线性表的长度为：%d\n",listLength(L));
    int elem=0;
    getElem(L, elem, 1);
    printf("第%d位置的值是:%d\n",1,elem);
    printf("%d的位置在%d的位置上\n",99,locateElem(L, 99));
    listDestroy(L);//释放掉后
    //listDisplay(L);L就不能再使用了
    return 0;
}
