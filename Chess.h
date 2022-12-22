#pragma once 
#include <graphics.h>
#include <vector>
#include<iostream>
#include <algorithm>
#include<cmath>
#include <vector>
using namespace std;

extern const int CHESSBOARD_WIDTH; // ����ͼƬ�Ŀ��
extern const int CHESSBOARD_HEIGHT; // ����ͼƬ�ĸ߶�
extern const float GRID_SIZE; // ���̸��ӵĴ�С
extern const int MARGIN; //���̱�Ե���
extern const int CHESS_SIZE; //���Ӵ�С
extern const int ROW_COUNT; // ���̵�����
extern const int COL_COUNT; // ���̵�����

typedef enum {
	CHESS_WHITE = -1,  
	CHESS_BLACK = 1    
} chess_kind_t;

struct ChessPos {
	int row;
	int col;
};

struct Grid {
	float x; // ����λ�õĺ�����
	float y; // ����λ�õ�������
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

	void init();  //��ʼ��

	void ChessDown(ChessPos* Pos,chess_kind_t kind);  //����

	bool CheckDown(float msg_x, float msg_y,ChessPos* Pos); //�ж�����λ��

	void update(ChessPos* Pos, chess_kind_t kind);

	bool Judge(ChessPos* Pos,int color);    //�ж���Ӯ

	void putimagePNG(float, float,IMAGE*);  //�������ӱ�Ե

	float distance(float x1, float y1, int x2, int y2);

	void copyChessMap(vector<vector<int> >& map);

	
};

