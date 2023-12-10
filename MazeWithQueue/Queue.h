//
//  Queue.h
//  MazeWithQueue
//
//  Created by 舒佳瑞 on 2023/12/7.
//

#ifndef Queue_h
#define Queue_h
#define MaxSize 255

#endif /* Queue_h */




typedef struct _Box
{
    int x,y;
    int preStep;
}Box;

typedef struct _SqQueue{
    Box date[MaxSize];
    int front,rear;
    
}SqQueue,*SqQueueList;


void initSqQueue(SqQueueList &q);
void destroySqQueue(SqQueueList &q);
bool emptySqQueue(SqQueueList q);
void enQueue(SqQueueList &q,Box in);
void deSqQueue(SqQueueList &q,Box &out);
