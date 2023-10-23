#include <stdio.h>
#include <stdlib.h>


typedef struct _StackList
{
    /* data */
    int date;
    struct _StackList* next;
}Stack,*StackList;

bool initList(StackList &S)
{
    if (S==NULL)
    {
        /* code */
        return false;
    }
    else
    S=(Stack*)malloc(sizeof(Stack));
    S->next=NULL;
    return true;
}


bool DestroyStack(StackList &S)
{
    Stack *q=S,*p=S->next;

    while (q!=NULL)
    {
        /* code */
        free(q);
        q=p;
        p=p->next;
    }
    free(q);
    return true;
}
bool StakEmpty(StackList S)
{
    if (S->next==NULL)
    {
        /* code */
        return false;
    }
    else
    return true;
}
void Push(StackList &S,int target)
{
    if (S==NULL)
    {
        /* code */
        return;
    }
    Stack* in=(Stack*)malloc(sizeof(Stack));
    if (in==NULL)
    {
        /* code */
        return;
    }
    
    in->date=target;
    in->next=S->next;//这里一定会是头插法，因为栈的特点时先进后出，先进来的元素应该是在栈底，后进来的元素在栈顶
    S->next=in;
    
}
void Pop(StackList &S,int &out)
{
    if (S==NULL)
    {
        /* code */
        return;
    }
    out=S->next->date;
    S=S->next->next;
}
void GetTop(StackList S,int &e)
{
    if (S->next==NULL)
    {
        /* code */
        return;
    }
    e=S->next->date;
}



void printStack(StackList S)
{
    S=S->next;
    int count=0;
    printf("该栈的元素为：");
    while (S!=NULL)
    {
        /* code */
        printf("%d  ",S->date);
        S=S->next;
        count+=1;
    }
    printf("共计%d的个元素\n",count);
    
}

//测试上面的函数
int main()
{
    StackList S;
    initList(S);
    //DestroyStack(S);
    int i=0;
    for(;i<10;i++)
    {
        Push(S,i);
    }
    printStack(S);
    int top=0;
    GetTop(S,top);
    printf("栈顶的元素为：%d\n",top);
    return 0;
}
