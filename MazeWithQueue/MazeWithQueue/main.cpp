//
//  main.cpp
//  MazeWithQueue
//
//  Created by 舒佳瑞 on 2023/12/7.
//

#include <stdio.h>
#include <stdlib.h>
#include "../Queue.h"
#include "../Maze.h"


//  The last modified on 2023/12/7.
//  Modified by 舒佳瑞

//  Compilation platform   Xcode Version 15.0 (15A240d)
//  Chip Apple M2 on arm64


//explanatory note
/*
 利用队列求最短路径
 
 先区分用栈的方式来解决
 
 1、栈（深搜）的思想是一条独木桥走到黑，不撞南墙不后退
 
 2、队列（广搜）的思考如下：
 最开始拿到这个问题的时候我在想我直接把每条路径求出来，然后再把最短的输出来就是好了
 然后也确实这么做了，但是这样干有个问题就是，为了找到最短的那一条我把所有路径都找了是否太得不偿失？
 
 然后看书上这个算法
 他把某点所有可走的位置都入队列，我觉得也有点蠢
 然后我就想插队：把靠近出口的路径先入队
 但在某些情况下又会找不到最短的路径
 比如如下这个迷宫：
 
  37
  35 #  #  #  #  #  #  #
  33 31 29 27 25 23 21 #
  1  4  7  10 13 16 19 #
  s  3  6  9  12 15 18 #  54 f
  2  5  8  11 14 17 20 #  52 53     ---->如果这样的话就有28步 3 6 9 12 15 18 20 22 24 26 28 30 32 34 36 38 39 ...54
  34 32 30 28 26 24 22 #  50 51
  36 #  #  #  #  #  #  #  48 49     但是如果用栈来解决从s->f最近的只有17步就可以
  38 39 40 41 42 43 44 45 46 47
 
 
 对于迷宫这儿是固定的，你也可以像栈那个迷宫算法一样通过随机数来自动生成一个迷宫
 然后由用户输入入口和出口的坐标
 
 */

int main()
{
    int Map[][COL]={{0,0,0,0,0,0,0,0},
                    {0,1,1,1,1,0,1,0},
                    {0,1,1,0,1,0,1,0},
                    {0,0,1,1,1,0,0,0},
                    {0,1,1,0,0,1,1,0},
                    {0,1,0,0,0,1,1,0},
                    {0,1,1,1,1,1,1,0},
                    {0,0,0,0,0,0,0,0}
    };
    MazePathWithQueue(1, 1, 6, 6, Map);
    return 0;
}

void initSqQueue(SqQueueList &q)
{
    q=(SqQueueList)malloc(sizeof(SqQueue));
    q->front=q->rear=-1;
}

void destroySqQueue(SqQueueList &q)
{
    free(q);
}

bool emptySqQueue(SqQueueList q)
{
    return(q->rear==q->front);
}


void enQueue(SqQueueList &q,Box in)
{
    if (q==NULL||q->rear==MaxSize-1)
    {
        return;
    }
    q->date[++q->rear]=in;
}


void deSqQueue(SqQueueList &q,Box &nowWhere)
{
    if (q==NULL||q->front==q->rear)
    {
        return;
    }
    nowWhere=q->date[++q->front];
}



bool MazePathWithQueue(int xs,int ys,int xf,int yf,int (*Map)[COL])
{
    SqQueueList Queue;
    initSqQueue(Queue);
    Box frist,nowWhere,in;
    frist.x=xs,frist.y=ys,frist.preStep=-1;
    enQueue(Queue,frist);
    (*(Map+frist.x)[frist.y])=-1;
    int status=-1;
    while (!emptySqQueue(Queue))
    {
        /* code */
        deSqQueue(Queue,nowWhere);//这个问题也非常巧妙，即使是出队了，这个元素任然在来的位置，靠的是pre，直到出口一直找pre
        //所以这里不能用环形队列，因为会复写
        //当然如果你的这个环足够大也是可以用的
        status=-1;
        if(nowWhere.x==xf&&nowWhere.y==yf)
        {
            dishplayPath(Queue, Queue->front);
            destroySqQueue(Queue);
            return true;
        }
        
        for (status+=1; status<4;status++)
        {
            switch (status)
            {
                case 0:
                    in.x=nowWhere.x-1;
                    in.y=nowWhere.y;
                    break;
                    
                case 1:
                    in.x=nowWhere.x+1;
                    in.y=nowWhere.y;
                    break;
                    
                case 2:
                    in.x=nowWhere.x;
                    in.y=nowWhere.y+1;
                    break;
                    
                case 3:
                    in.x=nowWhere.x;
                    in.y=nowWhere.y-1;
                    break;
                    
                default:
                    break;
            }
            if((*(Map+in.x))[in.y]==1)
            {
               
                in.preStep=Queue->front;
                enQueue(Queue, in);
                (*(Map+in.x))[in.y]=-1;
            }
        }
        
    }
    destroySqQueue(Queue);
    return true;
}


void dishplayPath(SqQueueList q,int end)
{
    Box path[MaxSize];
    //要说用数组来装，还是浪费空间
    //但是如果用顺序队列也是浪费空间
    //你可以用链式队列装
    //如果要用栈的话要用两次，因为他本来是正确的序列，无需逆置
    int last=end,i=0,j;
    while (last!=-1)
    {
        path[i]=q->date[last];
        last=q->date[last].preStep;
        i++;
    }
    printf("迷宫的路径如下：\n");
    for (j=i-1; j>=0; j-=1)
    {
        printf("\t(%d,%d)",path[j].x,path[j].y);
        if (j%5==0)
        {
            printf("\n");
        }
    }
}
