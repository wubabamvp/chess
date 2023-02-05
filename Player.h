#pragma once
#include"Chess.h"
#include <easyx.h>
class Player
{
private:
	Chess* chess;

public:
	void init(Chess*);
	void go(chess_kind_t);
};

 