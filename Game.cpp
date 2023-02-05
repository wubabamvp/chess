#include"Game.h"
#include <thread>
#include <chrono>
void Game::init(Chess* chess, Player* player, AI* ai) {
	this->chess = chess;
	this->player = player;
	this->ai = ai;
	ai->init(chess);
	player->init(chess);
}
 
void Game::play() {
	chess->init();
	while (1) {
		ai->go(CHESS_WHITE);
		player->go(CHESS_BLACK);
		//player->go(CHESS_WHITE);
	}
}
void Game::delay(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}