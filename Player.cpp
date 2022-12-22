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

//char mousePosStr[32];
//sprintf_s(mousePosStr, "Mouse Pos: (%d, %d)", msg.x, msg.y);
//outtextxy(5, 5, mousePosStr);

//IMAGE BOARD;
//// �������⻭��
//HDC hdc = CreateCompatibleDC(NULL);
//HBITMAP hbmp = CreateCompatibleBitmap(GetDC(NULL), 640, 480);
//SelectObject(hdc, hbmp);
//loadimage(&BOARD, "board.png");
//putimage(0, 0, &BOARD, SRCCOPY);

//// �ҳ��������λ�����������λ��
//int minRow = 0, minCol = 0;
//double minDist = 1e9;
//for (int i = 0; i < ROW_COUNT; i++) {
//	for (int j = 0; j < COL_COUNT; j++) {
//		double dist = chess->distance(msg.x, msg.y, chess->grids[i][j].x, chess->grids[i][j].y);
//		if (dist < minDist) {
//			minRow = i;
//			minCol = j;
//			minDist = dist;
//		}
//	}
//}
// //�����������λ����Χ��һ�����α�ʾ����
//int x1 = chess->grids[minRow][minCol].x ;
//int y1 = chess->grids[minRow][minCol].y ;
//int x2 = x1 + 10;
//int y2 = y1 + 10;
//setfillcolor(BLACK);
//solidrectangle(x1, y1, x2, y2);
//
//// �����⻭���������Ļ��
//HDC hdcScreen = GetDC(NULL);
//BitBlt(hdcScreen, x1, y1, 10, 10, hdc, 0, 0, SRCCOPY);
//ReleaseDC(NULL, hdcScreen);
//Sleep(1);