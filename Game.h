#pragma once 
#include"Chess.h"
#include"Player.h"
#include"AI.h"
class Game
{
private:
	Chess* chess;
	Player* player;
	AI* ai;

public:
	void init(Chess*, Player*, AI*);
	void play();
	void delay(int milliseconds);
};

