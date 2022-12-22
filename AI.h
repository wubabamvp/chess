#pragma once
#include"Chess.h"

class AI
{
private:
	Chess* chess;
	chess_kind_t kind;
	int score[6];

public:
	void init(Chess* chess);

	void go(chess_kind_t kind);


	//int checkHorizontal(int number,ChessPos pos);

	//int checkVertical(int number, ChessPos pos);

	//int checkDiagonal(int number, ChessPos pos);

	//int countFourInARow(int number, ChessPos pos , chess_kind_t kind);

	//void Five();

	//void liveFour();

	//void sleepFour();

	//void liveThree();

	//void sleepThree();

	//void liveTwo();

	//void attackScore();

	//void defendScore();

};





