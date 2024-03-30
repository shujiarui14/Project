//
//  lib.cpp
//  mineClearance
//
//  Created by 舒佳瑞 on 2024/3/25.
//

#include "./mineClearance.h"
void menu()
{
    printf("* * * * * * * * * * * * *\n");
    printf("* * * * * 0.退出 * * * * *\n");
    printf("* * * * * 1.开始 * * * * *\n");
    printf("* * * * * 2.加外挂 * * * *\n");
    printf("* * * * * * * * * * * * *\n\n");
}


//需要说明的是，在打印时候我只会在雷区做更改，不对边界做更改，所有的都是从1开始
//但在初始化的时候会对整个区域初始化
void initTableAndDisplay(char table [ROWS][COLS],int row,int col,char set)
{
    int i=0,j=0;
    
    if (set=='d')
    {
        i=1;
        //printf("   ");
        for (j=0; j<=col; j++) {
            printf("%d  ",j);
        }
        printf("\n");
        for(;i<=row;i++)
        {
            printf("%d  ",i);
            for(j=1;j<=col;j++)
            {
                printf("%c  ",table[i][j]);
            }
            printf("\n");
        }
        if (i>=row)
        {
            printf("\n");
            return;
        }
    }
    
    for(;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            table[i][j]=set;
        }
    }
}

int modeSelection()
{
    printf("请选择模式（1简单->10个雷、2一般->20个雷、3困难->30个雷）:");
    int mode=1;
    do {
        scanf("%d",&mode);
        switch (mode) 
        {
            case 1:
                return EASY;
                
            case 2:
                return MIDDLE;
            case 3:
                return DIFFICULT;
                
            default:
                printf("\n参数错误，请重新输入！！：");
                mode=1;
                break;
        }
    } while (mode);
    return 0;
}
    
void setMine(char table[ROWS][COLS],int row,int col,int mode,int noticeX[sizeOfMine],int noticeY[sizeOfMine])
{
    int count=mode;
    srand((unsigned int)time(NULL));
    int i=0;
    while(count&&i<mode)
    {
        int x=rand()%row+1;
        int y=rand()%col+1;
        if (table[x][y]=='0')
        {
            table[x][y]='1';
            noticeX[i]=x;
            noticeY[i]=y;
            i++;
            count--;
        }
    }
}


int demining(char mine[ROWS][COLS],char table[ROWS][COLS],int row,int col,int count,int &realCount,char mineTable[ROWS][COLS])
{
    int x=1,y=1;
    int is=2;
    
    if (count==0&&realCount!=0)
    {
        printf("你未找到所有的雷，且你标记雷的个数达到最大值，所以你输了!\n\n");
        printf("所有雷在的位置如下\n");
        initTableAndDisplay(mineTable, row, col, 'd');
        printf("而你标记雷的位置如下所示\n");
        return  -1;
    }
    else if(count==realCount&&count==0)
    {
        printf("恭喜你成功的找到了所有的雷，你赢了!\n\n");
        return -1;
    }
    
    printf("请输入需要排查的坐标x y:");
    while (true)
    {
        scanf("%d %d",&x,&y);
        if (x>0&&x<=row&&y>0&&y<=col) 
        {
            break;
        }
        printf("坐标位置越界，请重新输入\n");
    }
    
    if(mine[x][y]=='1')
    {
        printf("踩到雷了，游戏结束!\n");
        printf("雷的位置如下所示\n");
        initTableAndDisplay(mineTable, row, col, 'd');
        return -1;
    }
    
    table[x][y]=casting(surrounds(mine, row, col, x, y));
    initTableAndDisplay(table, ROW, COL, 'd');
    //printf("test %c",casting(surrounds(mine, row, col, x, y)));
    
    
    while (1)
    {
        
        printf("（1）继续，（0）我知道那个是雷了：");
        scanf("%d",&is);
        if (is==1)
        {
            /*initTableAndDisplay(table, ROW, COL, 'd');*/
            return count;
        }
        
        if (is==0)
        {
            printf("请输入你认为是雷的坐标x y：");
            scanf("%d %d",&x,&y);
            table[x][y]='/';
            initTableAndDisplay(table, ROW, COL, 'd');
            count--;
            if (mine[x][y]=='1')
            {
                realCount--;
                return count;
            }
            break;
        }
        printf("参数错误，请重新输入！！\n");
    }
    
    return count;
}


int surrounds(char mine[ROWS][COLS],int row,int col,int x,int y)
{
    int surround=0;
    int xi=x-1,yi=y-1;
    for (int i=0; i<3; i++,xi+=1)
    {
        
        for (int j=0; j<3; j++,yi+=1)
        {
            if (xi<1&&xi>=row&&yi<1&&yi>=col)
            {
                continue;
            }
            if (mine[xi][yi]=='1')
            {
                surround+=1;
            }
        }
        yi-=3;
    }
    
    return  surround;
}



char casting(int count)
{
    char res;
    switch (count)
    {
        case 0:
            res='0';
            break;
        case 1:
            res='1';
            break;
        case 2:
            res='2';
            break;
        case 3:
            res='3';
            break;
        case 4:
            res='4';
            break;
        case 5:
            res='5';
            break;
        case 6:
            res='6';
            break;
        case 7:
            res='7';
            break;
        case 8:
            res='8';
            break;
        default:
            res=-1;
            break;
    }
    return res;
}

