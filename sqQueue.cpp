#include <stdio.h>
#include <stdlib.h>
#define maxSize 6

typedef struct _sqQueue
{
    int date[maxSize];
    int front,rear;
}sqQueue,*sqQueueList;

bool initQueue(sqQueueList &q)
{
    q=(sqQueue*)malloc(sizeof(sqQueue));
    if (q==NULL)
    {
        return false;
    }
    q->front=q->rear=0;
    return true;
}


void delSqQueue(sqQueueList &q)
{
    free(q);
}

bool QueueEmpty(sqQueue q)
{
    if (q.front==q.rear)
    {
        return true;
    }
    return false;
}

bool enQueue(sqQueueList &q,int in)
{
    if ((q->rear+1)%maxSize==q->front)
    {
        /* code */
        return false;
    }
    q->date[q->rear]=in;
    q->rear=(q->rear+1)%maxSize;
    return true;
}

bool deQueue(sqQueueList &q,int &out)
{
    if (q->front==q->rear)
    {
        return false;
    }
    out=q->date[q->front];
    q->front=(q->front+1)%maxSize;
    return true;
    
}

int count(sqQueueList q)
{
    return (q->rear-q->front+maxSize)%maxSize;
}


void display(sqQueueList q)
{
    int tmp=q->front;
    printf("当前栈里的元素有：");
    while (q->front!=q->rear)
    {
        printf("%d  ",q->date[q->front]);
        q->front=(q->front+1)%maxSize;
    }
    q->front=tmp;
    printf("\n");
}


int main()
{
    sqQueueList q;
    initQueue(q);
    for(int i=0;i<maxSize-2;i+=1)
    {
        enQueue(q,i+2);
    }
    display(q);
    int out;
    deQueue(q,out);
    printf("出栈元素为：%d\n",out);
     enQueue(q,99);
     display(q);
     deQueue(q,out);
     printf("出栈元素为：%d\n",out);
    display(q);
    return 0;
}
