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
	float x; // ����λ�õĺ�����
	float y; // ����λ�õ�������
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
	void init();  //��ʼ��
	void ChessDown(ChessPos* Pos, chess_kind_t kind);  //����
	bool CheckDown(float msg_x, float msg_y, ChessPos* Pos); //�ж�����λ��
	void update(ChessPos* Pos, chess_kind_t kind);
	bool Judge(ChessPos* Pos, int color);    //�ж���Ӯ
	void putimagePNG(int x, int y, IMAGE* picture); //�������ӱ�Ե
	float distance(float x1, float y1, int x2, int y2); //�������
	void copyChessMap(vector<vector<int> >& map);		//��������
};

