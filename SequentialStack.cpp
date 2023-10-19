#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10

typedef struct _Stack{
    int arr[MaxSize];
    int top;
}Stack,*SqStack;


void initSqList(SqStack &s)
{
    s=(Stack*)malloc(sizeof(Stack));
    s->top=-1;
}

void DestorySqList(SqStack &s)
{
    free(s);
}

bool EmptyStack(Stack s)
{
    if (s.top==-1)
    {
        /* code */
        return false;
    }
    return true;
    
}


void Push(SqStack &s,int target)
{
    if (s->top==MaxSize-1)
    {
        /* code */
        return;
    }
    s->top++;
    s->arr[s->top]=target;
}

void Pop(SqStack &s,int &e)
{
    if (s->top==-1)
    {
        return;
    }
    e=s->arr[s->top];
    s->top--;
}


void GetTop(SqStack s,int &e)
{
    if (s->top==-1)
    {
        /* code */
        return;
    }
    e=s->arr[s->top];
    
}
int main()
{
    SqStack S;
    initSqList(S);
    Push(S,33);
    Push(S,44);
    Push(S,55);
    Push(S,66);
    int i=0;
    int tmp=0,e=0;
    for(;i<4;i++)
    {
        GetTop(S,tmp);
        printf("%d  ",tmp);
        Pop(S,e);
        printf("出栈元素为：%d\n",e);
    }
    return 0;
}