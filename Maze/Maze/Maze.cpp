//
//  Maze.h
//  Maze
//
//  Created by 舒佳瑞 on 2023/12/4.
//


//
//  Statck.h
//  Maze
//
//  Created by 舒佳瑞 on 2023/12/4.
//


//
//  Maze.cpp
//  Maze
//
//  Created by 舒佳瑞 on 2023/12/4.
//


//  The last modified on 2023/12/7. 
//  Modified by 舒佳瑞

//  Compilation platform   Xcode Version 15.0 (15A240d)
//  Chip Apple M2 on arm64

//explanatory note
/*
这是使用栈的思想来解决迷宫问题
其原理是把从起点到终点可走的某条路径入栈——这个写法可能和书上的写法不太一样，但其算法的思想都是一样的
然后将栈里面的元素逆置输出就得到迷宫可走的路径
在逆置的时候用了链式栈，原因在于我也不确定这个迷宫会有几个位置会入栈（这个入栈的范围在（行-2）*（列-2），如果使用顺序栈的话浪费资源
这里的迷宫是随机生成的，当然因为用的是时间的种子，可能会出现障碍物0和可走路径1的比例会失衡，你可以选择一直随机生成，直到你满意为止
对于生成的迷宫我需要你告诉我迷宫的入口和出口
对于这个入口和出口它的范围因该落在（行-2）（列-2）这个范围，同时对于非计算机专业的人来理解第一个位置应该是从1开始而不是0，所以对于坐标来说（1-（行-2））-（1-（列-2））
只有落在这个范围之中才是合格的坐标
*/




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 8
#define COL 8
#define MaxSize 255

typedef struct _Box
{
    int x,y,status;
}Box;

typedef struct _SqStatk{
    Box date[MaxSize];
    int top=-1;
}SqStack,*SqStackList;
typedef struct _LinkStatck
{
    Box date;
    struct _LinkStatck* next;
}LinkStack,*LinkStackList;



bool initSqStack(SqStackList &s);
void DestroyStack(SqStackList &s);
bool emptyStack(SqStackList s);
void PushStack(SqStackList &s,Box in);
void PopStack(SqStackList &s,Box &out);
bool getTop(SqStackList s,Box& topdate);


bool initLinkStack(LinkStackList &s);
void PushLinkStack(LinkStackList &s,Box in);
void PopStack(LinkStackList &s,Box &out);
bool emptyLinkStack(LinkStackList s);
void DestroyLinkStack(LinkStackList &s);
bool MazePath(int xs,int ys,int xf,int yf,int (*MazeMap)[COL]);
void displayPath(LinkStackList s);
void randArr(int (*arr)[COL]);

int main()
{
    int i=0,j=0,k=0;
    int xs,ys,xf,yf;
    int judg=0;
    /*int Map[][COL]={{0,0,0,0,0,0,0,0},
                    {0,1,1,1,1,0,1,0},
                    {0,1,1,0,1,0,1,0},
                    {0,0,1,1,1,0,0,0},
                    {0,1,1,0,0,1,1,0},
                    {0,1,0,0,0,1,1,0},
                    {0,1,1,1,1,1,1,0},
                    {0,0,0,0,0,0,0,0}
    };*/
    //MazePath(1, 1,6 ,3, Map);
    int arr[][COL]={};
    randArr(arr);
    printf("这个迷宫不是你想要的？是否要从新生成一个迷宫？：（0->否，这就是我要的,1->是，我想从新生成一个迷宫）\n");
    scanf("%d",&judg);
    /*
     其实通过scanf来取判断值是有一点蠢的
     通过scanf还需要按下回车
     在<conio.h>下有个_getch()，可以直接读取输入的字符
     但是这个函数只在mingw64下有
     但是我的编译环境是在：Apple clang version 15.0.0 (clang-1500.0.40.1)
                       Target: arm64-apple-darwin23.1.0
     所以如果你用的是Windows的mingw的话不妨考虑使用_getch()这个函数，会好用很多
     */
    while (judg)
    {
        system("cls");
        randArr(arr);
        printf("这个迷宫不是你想要的？是否要从新生成一个迷宫？：（0->否，这就是我要的,1->是，我想从新生成一个迷宫）\n");
        scanf("%d",&judg);
    }
    
    
    printf("请输入起始位置（x,y）和迷宫出口（x,y）,每个坐标用空格隔开！\n");
    while(true)
    {
        scanf("%d %d %d %d",&xs,&ys,&xf,&yf);
        if (xs>0&&xs<(ROW-1)&&ys>0&&ys<(COL-1)&&xf>0&&xf<(ROW-1)&&yf>0&&yf<(COL-1))
        {
            break;
        }
        else
        printf("你输入坐标的范围不在地图的有效范围内->的坐标的有效范围在：（%d-%d），请从新输入！！！\n",ROW-2,COL-2);
        
    }
    MazePath(xs,ys,xf,yf,arr);
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
           return true;
            
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
    printf("对于这个迷宫没有可走的路径\n");
    DestroyStack(Stack);
    return false;
}


void randArr(int (*arr)[COL])
{
    srand((unsigned)time(NULL));
    int i=0,j=0;
    for(;i<8;i++)
    {
        for(j=0;j<8;j+=1)
        {
            if (i==0||i==(ROW-1)||j==0||j==(COL-1))
            {
                (*(arr+i))[j]=0;
            }
            else
            {
                (*(arr+i))[j]=rand()%2;
            }
            
        }
    }
    printf("随机生成一个迷宫图:\n");
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%d  ",(*(arr+i))[j]);
        }
        printf("\n");
    }
}
