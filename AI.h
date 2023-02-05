#pragma once
#include"Chess.h"
#include<vector>
class AI
{
private:
	Chess* chess;
	chess_kind_t kind;
	vector<int>score;
	//score 0:连5 | 1:活4 | 2:眠4 | 3:冲4 | 4:活3 | 5:眠3 | 6:冲3 | 7:活2
public:
	void init(Chess* chess);  //初始化
	void go(chess_kind_t kind);  //行动
	//int alpha_beta_search(int depth, int alpha, int beta); //alpha_beta剪枝
	void checkHorizontal(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind); //水平搜索
	void checkVertical(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind);   //竖直搜索
	void checkDiagonal(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind);   //斜向搜索
	void countInARow(ChessPos pos, chess_kind_t kind);      //搜索活子（连子）
	void countSleep(ChessPos pos, chess_kind_t kind);		//搜索眠子
	int getScore(ChessPos pos, chess_kind_t kind, bool iskind);			//获取分数
	int Score(ChessPos& pos, chess_kind_t Kind, bool iskind);			//计算分数
	int controlCenter(ChessPos pos);						//判断落子位置距中间的距离
	bool check_valid_move(int row, int col, int distance, vector<vector<int> >chessMap); //若落子周围distance个单位内没有其他棋子，则跳过
};





