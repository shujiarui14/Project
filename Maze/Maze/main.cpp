//
//  main.cpp
//  Maze
//
//  Created by 舒佳瑞 on 2023/12/4.
//

#include <stdio.h>
#include <stdlib.h>
#include "../Stack.h"
#include "../Maze.h"
#include <time.h>
 

int main()
{
    int i=0,j=0,k=0;
    int Map[][COL]={{0,0,0,0,0,0,0,0},
                    {0,1,1,1,1,0,1,0},
                    {0,1,1,0,1,0,1,0},
                    {0,0,1,1,1,0,0,0},
                    {0,1,1,0,0,1,1,0},
                    {0,1,0,0,0,1,1,0},
                    {0,1,1,1,1,1,1,0},
                    {0,0,0,0,0,0,0,0}
    };
    MazePath(1, 1,6 ,3, Map);
    return 0;
}


bool initSqStack(SqStackList &s)
{
    
    s=(SqStackList)malloc(sizeof(SqStack));
    if (s==NULL) {
        return false;
    }
    s->top=-1;
    return true;
}

void DestroyStack(SqStackList &s)
{
    free(s);
}

bool emptyStack(SqStackList s)
{
    return (s->top==-1);
}
void PushStack(SqStackList &s,Box in)
{
    if (s==NULL) {
        return;
    }
    if (s->top==MaxSize-1) {
        return;
    }
    s->top++;
    s->date[s->top]=in;
}

void PopStack(SqStackList &s,Box &out)
{
    if (s==NULL||s->top==-1) {
        return;
    }
    out=s->date[s->top];
    s->top--;
}

bool getTop(SqStackList s,Box &topDate)
{
    if (s==NULL||s->top==-1) {
        return false;
    }
    topDate=s->date[s->top];
    return true;
}





bool initLinkStack(LinkStackList &s)
{
    s=(LinkStackList)malloc(sizeof(LinkStack));
    if (s==NULL)
    {
        return false;
    }
    s->next=NULL;
    return true;
}


void PushLinkStack(LinkStackList &s,Box in)
{
    if(s==NULL)
    {
        return;
    }
    LinkStack* p=(LinkStack*)malloc(sizeof(LinkStack));
    p->date=in;
    p->next=s->next;
    s->next=p;
}


void PopStack(LinkStackList &s,Box &out)
{
    if(s==NULL)
    {
        return;
    }
    out=s->next->date;
    s->next=s->next->next;
}


bool emptyLinkStack(LinkStackList s)
{
    return (s->next==NULL);
}

void DestroyLinkStack(LinkStackList &s)
{
    LinkStack* pre=s->next;
    while (s!=NULL) {
        free(s);
        s=pre;
        pre=s->next;
    }
    free(pre);
}

void displayPath(LinkStackList s)
{
    Box out;
    int enter=1;
    printf("迷宫的路径为：\n");
    while (!emptyLinkStack(s))
    {
        PopStack(s, out);
        printf("%d %d   ",out.x,out.y);
        if (enter%4==0) {
            printf("\n");
        }
        enter++;
    }
}

bool MazePath(int xs,int ys,int xf,int yf,int (*MazeMap)[COL])
{

    SqStackList Stack;
    LinkStackList path;
    initLinkStack(path);
    initSqStack(Stack);
    Box nowWhere,Top,in,out;
    nowWhere.x=xs;
    nowWhere.y=ys;
    nowWhere.status=-1;
    PushStack(Stack, nowWhere);
    int status=0,xNext=0,yNext=0;
    bool isFind;
    
    
    while (!emptyStack(Stack))
    {
        //printf("test\n");
        getTop(Stack, Top);
        status=Top.status;
        if (Top.x==xf&&Top.y==yf)
        {
            while (!emptyStack(Stack)) 
            {
                PopStack(Stack, out);
                PushLinkStack(path, out);
            }
            displayPath(path);
            
        }
        isFind=false;
        for (status++; status<4&&!isFind;status+=1)
        {
            switch (status) {
                case 0:
                    xNext=Top.x-1;
                    yNext=Top.y;
                    //printf("one  ");
                    break;
                    
                case 1:
                    xNext=Top.x;
                    yNext=Top.y+1;
                    //printf("tow  ");
                    break;
                    
                case 2:
                    xNext=Top.x+1;
                    yNext=Top.y;
                    //printf("three  ");
                    break;
                    
                case 3:
                    xNext=Top.x;
                    yNext=Top.y-1;
                    //printf("fore  ");
                    break;
                    
                default:
                    status++;
                    break;
            }
            if ((*(MazeMap+xNext))[yNext]==1)
            {
                isFind=true;
            }
        }
        if (isFind)
        {
            Stack->date[Stack->top].status=-1;
            in.x=xNext,in.y=yNext,in.status=-1;
            PushStack(Stack,in);
            (*(MazeMap+xNext))[yNext]=-1;
        }
        else
        {
            PopStack(Stack, out);
            //他为什么要退栈？
            //既然能走到这个位置那就证明始终有一条路可以走到这个，既然走得通有为什么要退栈？
            //人生哲理：我们到底在追求些什么？为何一直往前冲？捏出血的双手忘了也可稍微退后
            //我们总是以为能自由，回过头来这世界却依旧
            MazeMap[Top.x][Top.y]=0;
        }
        
    }
    DestroyStack(Stack);
    return false;
}

