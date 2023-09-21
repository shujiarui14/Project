#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
typedef struct _sQlist
{
    int* date;
    int length;
    int maxSize;
}sQlsit;

void creatList(sQlsit &L)
{
    int maxSize=20;
    L.date=(int *)malloc(maxSize*sizeof(int));
    L.length=0;
    L.maxSize=maxSize;
}

void initList(sQlsit &L)
{
    int i=0;
    for(;i<L.maxSize;i+=1)
    {
        *(L.date+i)=0;
        //printf("%d ",*(L.date+i));
    }
}

bool listLength(sQlsit &L)
{
    if (L.length==0) {
        return true;
    }else
        return false;
}
void displayList(sQlsit &L)
{
    int i=0;
    if (L.length==0)
    {
        printf("这张表没有任何数据！！\n");
    }
    else
    {
        printf("表内的值如下：");
        for(;i<L.maxSize;i++)
        {
            printf("%d ",*(L.date+i));
        }
    }
}

void getElem(sQlsit &L,int elem)
{
    int i=0;
    if(L.length!=0)
    {
        while (i<L.maxSize)
        {
            if (*(L.date+i)==elem) {
                printf("查找到%d的位置在%d\n",elem,i+1);
                break;
            }
            else if(i==L.maxSize-1)
                printf("这张表没有这个值\n");
            i++;
        }
    }
    else
    {
        printf("这张表是空表！！\n");
    }
        
}


void locateElem(sQlsit &L,int i)
{
    if (L.length!=0) {
        if (i<=L.maxSize)
        {
            printf("%d号元素的值为：%d\n",i,*(L.date+i-1));
        }
        else
        {
            printf("非法输入！\n");
            return;
        }   
    }
    else
        printf("这是一张空表！！\n");
}

void listInsert(sQlsit &L,int elem,int i)
{
    i--;
    if (*(L.date+i)==0) {//我在想，如果插入的这个位置本身就有一个值，那么我插入一个值那么这个表的长度需要加一吗？
        L.length++;//其实我应该将这个表的长度用malloc函数让它增加一个，这样算是插入一个值
    }//我觉得这是替换，并非插入！！！
    int j=L.maxSize-1;
    if (L.maxSize-1>=i)
    {
        /* code */
        for (; i<=j;j-=1) {
        *(L.date+j)=*(L.date+j-1);
        }
    }
    else
    printf("非法输入！\n");
    *(L.date+i)=elem;
    
}
void listDelete(sQlsit &L,int i)
{
    i--;
    int j=L.maxSize-1;
    printf("你删除的是%d位置上的%d\n",i+1,*(L.date+i));
    for (; i<=j; i++) {
        *(L.date+i)=*(L.date+i+1);
    }
    *(L.date+L.maxSize-1)=0;
    L.length--;
}

void listDestroy(sQlsit &L)
{
    free(L.date);
    /*for(int i=0;i<L.maxSize;i++)
    {
        printf("%d ",*(L.date+L.maxSize-1));
    }*/
    L.date=NULL;
    L.length=0;
    //函数描述：1、Deallocates or frees a memory block.
    //         2、The free function deallocates a memory block (memblock) that was previously allocated by a call to calloc, malloc, or realloc（可见只能释放掉动态开辟的内存）
    //         3、If memblock is NULL, the pointer is ignored and free immediately returns
    //         4、
    //函数原型：void free( void *memblock );
    //其实使用free函数你会发现一个点，当用malloc函数创建的空间被free函数释放掉后，指针管理的那一块空间仍然有能力指向它原本管理的那一块某些空间空间
    //其实可以这样理解，我是使用free函数释放掉原本开辟的这块空间时，只是在把这块空间还给了系统，告诉系统说：这块空间你可以用了,但我还能找得到这块空间

}
void listinput(sQlsit &L)
{
    printf("你要输入几个值？\n");
    int size=0,i=0;;
    char choose='1';
    while (1) {
        scanf("%d",&size);
        if (size<=L.maxSize) {
            break;
        }
        else
            printf("你要输入的值超过线性表的最大长度，请重新输入！！\n");
    }
    printf("本次写入数据是从线性表的1号位置往后写%d个数，你确定要这么做吗y（是）/n（否）:",size);
    choose=_getch();
    if (choose=='y') {
        for (; i<size; i++) {
            printf("\n请输入第%d个值：",i+1);
            scanf("%d",L.date+i);
        }
    }
    else
        printf("操作已取消\n");
    L.length=i+1;
    
}

char menu()
{
    printf("*****请输入对应数字执行对应选项*****\n");
    printf("********1、查看线性表长度********\n");
    printf("********2、查看线性表内容********\n");
    printf("********3、以位置查找数值********\n");
    printf("********4、以数值查找位置********\n");
    printf("********5、向线性表插入值********\n");
    printf("********6、删除线性表的值********\n");
    printf("********7、向线性表输入值********\n");
    printf("********8、强制销毁线性表********\n");
    printf("********9、退出Terminal*********\n");
    char options='1';
    //scanf("%c",&options);
    //getchar();
    options=_getch();
    return options;
}
int main()
{
    
    sQlsit L;
    creatList(L);
    initList(L);
    int i,elem;
    while (1) {
        switch (menu()) {
            
            case '1':
                listLength(L);
                break;
            case '2':
                displayList(L);
                break;
            case '3':
                printf("请输入你要查找的位置：");
                scanf("%d",&i);
                locateElem(L,i);
                break;
            case '4':
                printf("请输入你要查找的值：");
                scanf("%d",&elem);
                getElem(L, elem);
                break;
            case '5':
                printf("请输入你要插入的值和位置：");
                scanf("%d %d",&elem,&i);
                listInsert(L,elem,i);
                break;
            case '6':
                printf("请输入你要删除的位置：");
                scanf("%d",&i);
                listDelete(L,i);
                break;
            case '7':
                listinput(L);
                break;
            case '8':
                listDestroy(L);
                break;    
            default:
                break;
        }
        system("pause");
        system("cls");
    }
    
    
    return 0;
}

//其实还应该加入两个功能才算完整：1、可以让顺序表边长
//                             2、可以写入文件、下次可以继续访问