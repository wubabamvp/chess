#include "AI.h"

void AI::init(Chess* chess) {
	this->chess = chess;
    this->score[6] = { 0 };
}

void AI::go(chess_kind_t kind) {
    this->kind = kind;
}

//void AI::Five() {  //��5
//    score[0] = countFourInARow(5,pos,kind);
//}
//
//void AI::liveFour() {  //��4
//    score[1] = countFourInARow(4, pos, kind);
//}
//
//void AI::sleepFour(){  //��4
//
//}
//
//void AI::liveThree() {  //��3
//    score[3] = countFourInARow(3, pos, kind);
//}
//
//void AI::sleepThree() {  //��3
//
//}
//
//void AI::liveTwo() { //��2
//    score[5] = countFourInARow(2, pos, kind);
//}
//
//void AI::attackScore() {  //�������
//
//}
//
//void AI::defendScore() {  //���ش��
//
//}

// //���ˮƽ�����Ƿ���x������һ�������
//int AI::checkHorizontal(int number,ChessPos pos) {
//    vector<vector<int> >chessMap;
//    copyChessMap(chessMap);
//    int count = 0;  // ����һ�����������
//    int col = pos.col;
//    int row = pos.row;
//    // ������
//    for (int i = 15; i >= 0; i--) {
//        if (chessMap[col][i] != kind) break;
//        count++;
//    }
//
//    // ���Ҽ��
//    for (int i = col + 1; i < 15; i++) {
//        if (chessMap[15][i] != kind) break;
//        count++;
//    }
//
//    return (count >= number) ? 1 : 0;
//}
//
//// ��鴹ֱ�����Ƿ���x������һ�������
//int AI::checkVertical(int number, ChessPos pos) {
//    int count = 0;  // ����һ�����������
//    vector<vector<int> >chessMap;
//    copyChessMap(chessMap);
//    int side = 0;  //ͳ�Ʊ�Ե�����������Ƿ�Ϊ�Է����ӣ���Ϊ���壬�������õ�
//    // ���ϼ��
//    for (int i = pos.row - 1; i >= 0; i--) {
//        if (chessMap[i][pos.col] != kind) break;
//        count++;
//    }
//
//    // ���¼��
//    for (int i = pos.row + 1; i < 15; i++) {
//        if (chessMap[i][pos.col] != kind) break;
//        count++;
//    }
//
//    return (count >= number) ? 1 : 0;
//}
//
//int AI::checkDiagonal(int number, ChessPos pos) {
//    int count = 0;  // ����һ�����������
//    vector<vector<int> >chessMap;
//    copyChessMap(chessMap);
//    int row = pos.row;
//    int col = pos.col;
//
//    // �����ϼ��
//    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
//        if (chessMap[i][j] != kind) break;
//        count++;
//    }
//
//    // �����¼��
//    for (int i = row + 1, j = col + 1; i < 15 && j < 15; i++, j++) {
//        if (chessMap[i][j] != kind) break;
//        count++;
//    }
//
//    if (count >= 4) return true;
//
//    count = 0;  // ���ü�����
//
//    // �����¼��
//    for (int i = row, j = col; i < 15 && j >= 0; i++, j--) {
//        if (chessMap[i][j] != kind) break;
//        count++;
//    }
//    // �����ϼ��
//    for (int i = row - 1, j = col + 1; i >= 0 && j < 15; i--, j++) {
//        if (chessMap[i][j] != kind) break;
//        count++;
//    }
//
//    return (count >= number) ? 1 : 0;
//}
//
//int AI::countFourInARow(int number , ChessPos pos , chess_kind_t kind) {
//    vector<vector<int> >chessMap;
//    copyChessMap(chessMap);
//    int count = 0;
//    int row = pos.row;
//    int col = pos.col;
//    // ö��ÿһ��λ��
//    for (int row = 0; row < 15; row++) {
//        for (int col = 0; col < 15; col++) {
//            // ������λ���ϵ��������಻������Ҫ����ģ�������
//            if (chessMap[row][col] != kind) continue;
//            // ���򣬼�����λ�����Ƿ���number������һ�������
//            //if (checkHorizontal(number,pos) || checkVertical(number,pos) || checkDiagonal(number,pos)) {
//            //    count++;
//            //}
//            count = checkHorizontal(number, pos) + checkVertical(number, pos) + checkDiagonal(number, pos);
//        }
//    }
//    return count;
//}

