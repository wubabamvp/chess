#include "Player.h"
void Player::init(Chess* chess) {
	this->chess = chess;
}
void Player::go(chess_kind_t kind) {
	ExMessage msg = { 0 };
	ChessPos pos;
	while (1) {
		if (peekmessage(&msg, EM_MOUSE)) {
			pos.col = msg.x;
			pos.row = msg.y;
			if (msg.message == WM_LBUTTONDOWN && chess->CheckDown(msg.x, msg.y, &pos)) {
				break;
			}
		}
	} 
	chess->ChessDown(&pos, kind);
}

