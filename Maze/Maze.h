//
//  Maze.h
//  Maze
//
//  Created by 舒佳瑞 on 2023/12/4.
//

#ifndef Maze_h
#define Maze_h
#define ROW 8
#define COL 8

#endif /* Maze_h */

bool MazePath(int xs,int ys,int xf,int yf,int (*MazeMap)[COL]);
void displayPath(LinkStackList s);
