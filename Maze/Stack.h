//
//  Statck.h
//  Maze
//
//  Created by 舒佳瑞 on 2023/12/4.
//

#ifndef Statck_h
#define Statck_h

#endif /* Statck_h */
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
