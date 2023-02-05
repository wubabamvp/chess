#include "Chess.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
Chess::Chess() { 
	this->chessSize = 28;
	this->margin = 22;
	this->boardSize = 496 / 14;
	for (int i = 0; i < 15; ++i) {
		vector<int>arr;
		for (int j = 0; j < 15; ++j) {
			arr.push_back(0);
		}
		chessMap.push_back(arr);
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
}
void Chess::ChessDown(ChessPos* pos, chess_kind_t kind) {
	mciSendString("play res/down7.WAV", 0, 0, 0);
	int x = 22 - 13 + pos->col * 496 / 14;
	int y = 22 - 13 + pos->row * 496 / 14;
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
			cout << "����ʤ��" << endl;
		}
		else {
			cout << "����ʤ��" << endl;
		}
	}
}
bool Chess::CheckDown(float msg_x, float msg_y, ChessPos* Pos) {
	int pos_x_left = floor((msg_x - 22) / (496 / 14)) < 0 ? 0 : floor((msg_x - 22) / (496 / 14));
	int pos_y_high = floor((msg_y - 22) / (496 / 14)) < 0 ? 0 : floor((msg_y - 22) / (496 / 14));
	int pos_x_right = pos_x_left + 1 > 14 ? 14 : pos_x_left + 1;
	int pos_y_low = pos_y_high + 1 > 14 ? 14 : pos_y_high + 1;
	float left_High = distance(msg_x, msg_y, pos_x_left, pos_y_high);
	float left_Low = distance(msg_x, msg_y, pos_x_left, pos_y_low);
	float right_High = distance(msg_x, msg_y, pos_x_right, pos_y_high);
	float right_Low = distance(msg_x, msg_y, pos_x_right, pos_y_low);
	float MIN = min(right_High, min(right_Low, min(left_High, left_Low)));
	int value;
	if (MIN == left_High)value = 0;
	else if (MIN == left_Low)value = 1;
	else if (MIN == right_High)value = 2;
	else value = 3;
	if (MIN > 16)value = 4;
	switch (value) {
	case 0:
		if (chessMap[pos_x_left][pos_y_high] == 0) {
			Pos->col = pos_x_left;
			Pos->row = pos_y_high;
			return true;
		}
		else {
			return false;
		}
	case 1:
		if (chessMap[pos_x_left][pos_y_low] == 0) {
			Pos->col = pos_x_left;
			Pos->row = pos_y_low;
			return true;
		}
		else {
			return false;
		}
	case 2:
		if (chessMap[pos_x_right][pos_y_high] == 0) {
			Pos->col = pos_x_right;
			Pos->row = pos_y_high;
			return true;
		}
		else {
			return false;
		}
	case 3:
		if (chessMap[pos_x_right][pos_y_low] == 0) {
			Pos->col = pos_x_right;
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
	// �ж���
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
	// �ж���
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
	// �ж�б��
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			// �ж����� - ����
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

			// �ж����� - ����
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
void Chess::putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�
	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
float Chess::distance(float x1, float y1, int x2, int y2) {
	// ������������
	float dx = x2 * 496 / 14 + 22 - x1;
	float dy = y2 * 496 / 14 + 22 - y1;
	return std::sqrt(dx * dx + dy * dy);
}
void Chess::copyChessMap(vector<vector<int> >& map) {
	map = chessMap;
}
