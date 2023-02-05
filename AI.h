#pragma once
#include"Chess.h"
#include<vector>
class AI
{
private:
	Chess* chess;
	chess_kind_t kind;
	vector<int>score;
	//score 0:��5 | 1:��4 | 2:��4 | 3:��4 | 4:��3 | 5:��3 | 6:��3 | 7:��2
public:
	void init(Chess* chess);  //��ʼ��
	void go(chess_kind_t kind);  //�ж�
	//int alpha_beta_search(int depth, int alpha, int beta); //alpha_beta��֦
	void checkHorizontal(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind); //ˮƽ����
	void checkVertical(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind);   //��ֱ����
	void checkDiagonal(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind);   //б������
	void countInARow(ChessPos pos, chess_kind_t kind);      //�������ӣ����ӣ�
	void countSleep(ChessPos pos, chess_kind_t kind);		//��������
	int getScore(ChessPos pos, chess_kind_t kind, bool iskind);			//��ȡ����
	int Score(ChessPos& pos, chess_kind_t Kind, bool iskind);			//�������
	int controlCenter(ChessPos pos);						//�ж�����λ�þ��м�ľ���
	bool check_valid_move(int row, int col, int distance, vector<vector<int> >chessMap); //��������Χdistance����λ��û���������ӣ�������
};





