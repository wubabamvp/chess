#pragma once 
#include <graphics.h>
#include <vector>
#include<iostream>
#include <algorithm>
#include<cmath>
#include <vector>
using namespace std;

extern const int CHESSBOARD_WIDTH; // 棋盘图片的宽度
extern const int CHESSBOARD_HEIGHT; // 棋盘图片的高度
extern const float GRID_SIZE; // 棋盘格子的大小
extern const int MARGIN; //棋盘边缘宽度
extern const int CHESS_SIZE; //棋子大小
extern const int ROW_COUNT; // 棋盘的行数
extern const int COL_COUNT; // 棋盘的列数

typedef enum {
	CHESS_WHITE = -1,  
	CHESS_BLACK = 1    
} chess_kind_t;

struct ChessPos {
	int row;
	int col;
};

struct Grid {
	float x; // 落子位置的横坐标
	float y; // 落子位置的纵坐标
};

//extern Grid grids[14][14];

class Chess
{
private:
	float chessSize;
	float margin;
	int boardSize;

	IMAGE BlackImg;
	IMAGE WhiteImg;
	vector<vector<int> > chessMap;

	bool playerFlag;

public:
	Grid grids[14][14];

	Chess();

	void init();  //初始化

	void ChessDown(ChessPos* Pos,chess_kind_t kind);  //落子

	bool CheckDown(float msg_x, float msg_y,ChessPos* Pos); //判断落子位置

	void update(ChessPos* Pos, chess_kind_t kind);

	bool Judge(ChessPos* Pos,int color);    //判断输赢

	void putimagePNG(float, float,IMAGE*);  //修饰棋子边缘

	float distance(float x1, float y1, int x2, int y2);

	void copyChessMap(vector<vector<int> >& map);

	
};

