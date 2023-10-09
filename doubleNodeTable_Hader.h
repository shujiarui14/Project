//
//  doubleNodeTable_Hader.h
//  doubleNodeTable
//
//  Created by 舒佳瑞 on 2023/10/9.
//

#ifndef doubleNodeTable_Hader_h
#define doubleNodeTable_Hader_h


#endif /* doubleNodeTable_Hader_h */
#include <stdio.h>
#include <stdlib.h>

typedef struct _DNode
{
    int date;
    struct _DNode* prior,*next;
}DNode,*DNodeList;



bool initDNodelist(DNodeList &L)
{
    L=(DNode*)malloc(sizeof(DNode));
    if (L==NULL) {
        return false;
    }
    L->prior=NULL;
    L->next=NULL;
    return true;
}


bool InsertNextDNode(DNode* p,DNode* in)//在p节点之后插入一个in节点
{
    if (p==NULL||in==NULL) {
        return false;
    }
    in->next=p->next;
    if (p->next!=NULL) {
        p->next->prior=in;
    }
    in->prior=p;
    p->next=in;
    return true;
}


bool DeletNextDNode(DNode* p)//删除p节点之后的一个节点
{
    if (p==NULL) {
        return false;
    }
    DNode* q=p->next;
    if (q==NULL) {
        return false;
    }
    p->next=q->next;
    if (q->next!=NULL) {
        q->next->prior=p;
    }
    return true;
    
}

void InsertList(DNodeList &L,int elem)//尾插法
{
    DNode* move=L;
    DNode* in=(DNode*)malloc(sizeof(DNode));
    in->date=elem;
    if (move==NULL) {
        return;
    }
    while (move->next!=NULL) {
        move=move->next;
    }
    in->next=move->next;
    if (move->next!=NULL) {
        move->next->prior=in;
    }
    move->next=in;
    in->prior=move;
    
}

void InsertListHead(DNodeList &L,int elem)//头插法
{
    DNode* in=(DNode*)malloc(sizeof(DNode));
    in->date=elem;
    in->next=L->next;
    if (L->next!=NULL) {
        L->next->prior=in;
    }
    in->prior=L;
    L->next=in;
}

void DeletDNList(DNodeList &L,int &elem,int i)//删除第i个节点
{
    DNode* move,*tmp;
    move=L->next;
    if (move==NULL) {
        return;
    }
    int j=1;
    for (; j<i-1; j+=1 && move!=NULL) //在这里要找到的是第i个节点的前一个节点，然后跳过他
    {
        move=move->next;
    }
    if (move==NULL) {
        return;
    }
    tmp=move->next;
    if (tmp==NULL) {
        return;
    }
    elem=tmp->date;
    move->next=tmp->next;
    if (tmp->next==NULL) {
        return;
    }
    tmp->next->prior=move;
    free(tmp);
    
}
void DestoryList(DNodeList &L)
{
    DNode* move;
    while (L->next!=NULL)
    {
        move=L;//1 2 3
        L=move->next;//2 3 4
        free(move);//1 2 3
    }
    free(L);
}
void DisplayList(DNodeList &L)//输出线性表
{
    DNode* move=L->next;
    if (move==NULL) {
        return;
    }
    while (move!=NULL) {
        printf("%d  ",move->date);
        move=move->next;
    }
    printf("\n");
}
