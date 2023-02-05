#pragma once 
#include <graphics.h>
#include <vector>
#include<iostream>
#include <algorithm>
#include<cmath>
#include <vector>
using namespace std;
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
	Chess();
	void init();  //初始化
	void ChessDown(ChessPos* Pos, chess_kind_t kind);  //落子
	bool CheckDown(float msg_x, float msg_y, ChessPos* Pos); //判断落子位置
	void update(ChessPos* Pos, chess_kind_t kind);
	bool Judge(ChessPos* Pos, int color);    //判断输赢
	void putimagePNG(int x, int y, IMAGE* picture); //修饰棋子边缘
	float distance(float x1, float y1, int x2, int y2); //计算距离
	void copyChessMap(vector<vector<int> >& map);		//拷贝棋盘
};

