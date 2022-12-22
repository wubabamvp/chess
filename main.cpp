#include"Game.h"
int main() {
	Chess chess;
	Player player;
	AI ai;
	Game game;
	game.init(&chess, &player, &ai);
	game.play();
	return 0;
}



