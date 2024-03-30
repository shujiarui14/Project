//
//  mineClearance.h
//  mineClearance
//
//  Created by 舒佳瑞 on 2024/3/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2

#define sizeOfMine 32

#define EASY 10
#define MIDDLE 20
#define DIFFICULT 30

void menu();

void initTableAndDisplay(char table [ROWS][COLS],int row,int col,char set);
//如果要显示表的内容set应为字符'd'
int modeSelection();
void setMine(char table[ROWS][COLS],int row,int col,int mode,int noticeX[sizeOfMine],int noticeY[sizeOfMine]);

int demining(char mine[ROWS][COLS],char table[ROWS][COLS],int row,int col,int count,int &realCount,char mineTable[ROWS][COLS]);

int surrounds(char mine[ROWS][COLS],int row,int col,int x,int y);
char casting(int count);

