#include "Chess.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern const int CHESSBOARD_WIDTH = 540; // 棋盘图片的宽度
extern const int CHESSBOARD_HEIGHT = 540; // 棋盘图片的高度
extern const float GRID_SIZE = (540 - 44) / 14; // 棋盘格子的大小
extern const int MARGIN = 540; //棋盘边缘宽度
extern const int CHESS_SIZE = 30; //棋子大小
extern const int ROW_COUNT = 14; // 棋盘的行数
extern const int COL_COUNT = 14; // 棋盘的列数

Chess::Chess() {
	this->chessSize = CHESS_SIZE;
	this->boardSize = CHESSBOARD_WIDTH;
	this->margin = MARGIN;
	this->playerFlag = CHESS_BLACK;
	for (int i = 0; i < 15; ++i) {
		vector<int>arr;
		for (int j = 0; j < 15; ++j) {
			arr.push_back(0);
		}
		chessMap.push_back(arr);
	}
	for (int i = 0; i < ROW_COUNT; i++) {
		for (int j = 0; j < COL_COUNT; j++) {
			grids[i][j].x = MARGIN + j * GRID_SIZE;
			grids[i][j].y = MARGIN + i * GRID_SIZE;
		}
	}
}

void Chess::init() {
	initgraph(540, 540, EW_SHOWCONSOLE);
	loadimage(0, "board.png");
	mciSendString("play res/start.wav", 0, 0, 0);
	loadimage(&BlackImg, "black.png", chessSize, chessSize, true);
	loadimage(&WhiteImg, "white.png", chessSize, chessSize, true);
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			chessMap[i][j] = 0;
		}
	}
	playerFlag = true;
}

void Chess::ChessDown(ChessPos* pos,chess_kind_t kind) {
	mciSendString("play res/down7.WAV", 0, 0, 0);
	float x = pos->col * 496 / 14 + margin - 0.5 * chessSize;
	float y = pos->row * 496 / 14 + margin - 0.5 * chessSize;
	if (kind == CHESS_BLACK) {
		putimagePNG(x, y, &BlackImg);
	}
	else {
		putimagePNG(x, y, &WhiteImg);
	}
	update(pos, kind);
	bool judge = Judge(pos, kind);
	if (judge == true) {
		if (kind == CHESS_BLACK) {
			cout << "黑棋胜利" << endl;
		}
		else {
			cout << "白棋胜利" << endl;
		}
	}
}

bool Chess::CheckDown(float msg_x, float msg_y,ChessPos* Pos) {
	int pos_x_low = floor((msg_x - margin) / 36) < 0 ? 0 : floor((msg_x - margin) / 36);
	int pos_y_low = floor((msg_y - margin) / 36) < 0 ? 0 : floor((msg_y - margin) / 36);
	int pos_x_high = pos_x_low + 1 > 14 ? 14 : pos_x_low + 1;
	int pos_y_high = pos_y_low + 1 > 14 ? 14 : pos_y_low + 1;
	float left_High = distance(msg_x, msg_y, pos_x_low, pos_y_high);
	float left_Low = distance(msg_x, msg_y, pos_x_low, pos_y_low);
	float right_High = distance(msg_x, msg_y, pos_x_high, pos_y_high);
	float right_Low = distance(msg_x, msg_y, pos_x_high, pos_y_low);
	float MIN = min(right_High,min(right_Low,min(left_High, left_Low)));
	int value;
	if (MIN == left_High)value = 0;
	else if (MIN == left_Low)value = 1;
	else if (MIN == right_High)value = 2;
	else value = 3;
	//if (MIN > 225)value = 4;
	switch (value) {
	case 0:
		if (chessMap[pos_x_low][pos_y_high] == 0) {
			Pos->col = pos_x_low;
			Pos->row = pos_y_high;
			return true;
		}
		else {
			return false;
		}
	case 1:
		if (chessMap[pos_x_low][pos_y_low] == 0) {
			Pos->col = pos_x_low;
			Pos->row = pos_y_low;
			return true;
		}
		else {
			return false;
		}
	case 2:
		if (chessMap[pos_x_high][pos_y_high] == 0) {
			Pos->col = pos_x_high;
			Pos->row = pos_y_high;
			return true;
		}
		else {
			return false;
		}
	case 3:
		if (chessMap[pos_x_high][pos_y_low] == 0) {
			Pos->col = pos_x_high;
			Pos->row = pos_y_low;
			return true;
		}
		else {
			return false;
		}
	case 4:
		return false;
	}
	return false;
}

void Chess::update(ChessPos* Pos, chess_kind_t kind) {
	if (kind == CHESS_BLACK) {
		chessMap[Pos->col][Pos->row] = 1;
	}
	else {
		chessMap[Pos->col][Pos->row] = -1;
	}
}

bool Chess::Judge(ChessPos* Pos, int color) {
	int sum_max = 0;

	// 判断列
	for (int i = 0; i < 15; ++i) {
		int sum = 0;
		for (int j = 0; j < 15; ++j) {
			if (chessMap[i][j] == color) {
				sum++;
			}
			else {
				sum_max = max(sum_max, sum);
				sum = 0;
			}
		}
		sum_max = max(sum_max, sum);
	}

	// 判断行
	for (int j = 0; j < 15; ++j) {
		int sum = 0;
		for (int i = 0; i < 15; ++i) {
			if (chessMap[i][j] == color) {
				sum++;
			}
			else {
				sum_max = max(sum_max, sum);
				sum = 0;
			}
		}
		sum_max = max(sum_max, sum);
	}

	// 判断斜线
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			// 判断左上 - 右下
			int sum = 0;
			for (int k = 0; k < 5; ++k) {
				if (i + k < 15 && j + k < 15 && chessMap[i + k][j + k] == color) {
					sum++;
				}
				else {
					sum_max = max(sum_max, sum);
					break;
				}
			}
			sum_max = max(sum_max, sum);

			// 判断左下 - 右上
			sum = 0;
			for (int k = 0; k < 5; ++k) {
				if (i + k < 15 && j - k >= 0 && chessMap[i + k][j - k] == color) {
					sum++;
				}
				else {
					sum_max = max(sum_max, sum);
					break;
				}
			}
			sum_max = max(sum_max, sum);
		}
	}
	return sum_max >= 5;
}

void Chess::putimagePNG(float x, float y, IMAGE* picture) 
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

float Chess::distance(float x1, float y1, int x2, int y2) {
	// 计算两点间距离
	float dx = x2 - x1;
	float dy = y2 - y1;
	return std::sqrt(dx * dx + dy * dy);
}

void Chess::copyChessMap(vector<vector<int> >&map) {
	map = chessMap;
}
