//
//  init.cpp
//  mineClearance
//
//  Created by 舒佳瑞 on 2024/3/25.
//



#include "./mineClearance.h"




void toStart(int mark)
{
    char mine[ROWS][COLS]={0};
    char table[ROWS][COLS]={0};
    char mineTable[ROWS][COLS]={0};
    
    int noticeX[sizeOfMine]={0};
    int noticeY[sizeOfMine]={0};
    int count,realCount;
    int mode;
    int i=0;
    
    printf("开始之前：你需要了解\n");
    printf(" '*'  表示未知区域\n");
    printf(" '/'  表示已标为雷\n");
    printf("数值表示周围雷的个数\n\n");
    initTableAndDisplay(mine,ROWS,COLS,'0');
    initTableAndDisplay(table,ROWS,COLS,'*');
    initTableAndDisplay(mineTable,ROWS,COLS,'*');
    mode=modeSelection();
    setMine(mine, ROW, COL,mode,noticeX,noticeY);
    while (i<mode)
    {
        mineTable[noticeX[i]][noticeY[i]]='/';
        i++;
    }
    i=0;
    while (i<mode&&mark==2)
    {
        if (i%3==0)
        {
            table[noticeX[i]][noticeY[i]]='/';
        }
        i++;
    }
    
    
    initTableAndDisplay(table,ROW,COL,'d');
    count=realCount=mode;
    //initTableAndDisplay(mine, ROW, COL, 'd');
    //initTableAndDisplay(mineTable, ROW, COL, 'd');
    while (count+1)
    {
        count=demining(mine, table, ROW, COL,count,realCount,mineTable);
    }
}

int main()
{
    int optionMenu=0;
    do
    {
        menu();
        printf("请选择对应的选项以开始!：");
        scanf("%d",&optionMenu);
        switch (optionMenu)
        {
        case /* constant-expression */ 1:
            /* code */
            printf("扫雷\n");
                toStart(1);
                //system("clear");
            break;
        case 0:
            printf("退出游戏\n");
            break;
        case 2:
                printf("进入加外挂模式，将会提示部分雷的位置\n\n");
                toStart(2);
                break;
        default:
        printf("错误参数，请重新输入\n");
            break;
        }
    } while (optionMenu);
    return 0;
}
