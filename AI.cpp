#include "AI.h"

void AI::init(Chess* chess) {
	this->chess = chess;
    this->score[6] = { 0 };
}

void AI::go(chess_kind_t kind) {
    this->kind = kind;
}

//void AI::Five() {  //连5
//    score[0] = countFourInARow(5,pos,kind);
//}
//
//void AI::liveFour() {  //活4
//    score[1] = countFourInARow(4, pos, kind);
//}
//
//void AI::sleepFour(){  //眠4
//
//}
//
//void AI::liveThree() {  //活3
//    score[3] = countFourInARow(3, pos, kind);
//}
//
//void AI::sleepThree() {  //眠3
//
//}
//
//void AI::liveTwo() { //活2
//    score[5] = countFourInARow(2, pos, kind);
//}
//
//void AI::attackScore() {  //进攻打分
//
//}
//
//void AI::defendScore() {  //防守打分
//
//}

// //检查水平方向是否有x个连在一起的棋子
//int AI::checkHorizontal(int number,ChessPos pos) {
//    vector<vector<int> >chessMap;
//    copyChessMap(chessMap);
//    int count = 0;  // 连在一起的棋子数量
//    int col = pos.col;
//    int row = pos.row;
//    // 向左检查
//    for (int i = 15; i >= 0; i--) {
//        if (chessMap[col][i] != kind) break;
//        count++;
//    }
//
//    // 向右检查
//    for (int i = col + 1; i < 15; i++) {
//        if (chessMap[15][i] != kind) break;
//        count++;
//    }
//
//    return (count >= number) ? 1 : 0;
//}
//
//// 检查垂直方向是否有x个连在一起的棋子
//int AI::checkVertical(int number, ChessPos pos) {
//    int count = 0;  // 连在一起的棋子数量
//    vector<vector<int> >chessMap;
//    copyChessMap(chessMap);
//    int side = 0;  //统计边缘的两颗棋子是否为对方棋子，若为死棋，则舍弃该点
//    // 向上检查
//    for (int i = pos.row - 1; i >= 0; i--) {
//        if (chessMap[i][pos.col] != kind) break;
//        count++;
//    }
//
//    // 向下检查
//    for (int i = pos.row + 1; i < 15; i++) {
//        if (chessMap[i][pos.col] != kind) break;
//        count++;
//    }
//
//    return (count >= number) ? 1 : 0;
//}
//
//int AI::checkDiagonal(int number, ChessPos pos) {
//    int count = 0;  // 连在一起的棋子数量
//    vector<vector<int> >chessMap;
//    copyChessMap(chessMap);
//    int row = pos.row;
//    int col = pos.col;
//
//    // 向左上检查
//    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
//        if (chessMap[i][j] != kind) break;
//        count++;
//    }
//
//    // 向右下检查
//    for (int i = row + 1, j = col + 1; i < 15 && j < 15; i++, j++) {
//        if (chessMap[i][j] != kind) break;
//        count++;
//    }
//
//    if (count >= 4) return true;
//
//    count = 0;  // 重置计数器
//
//    // 向左下检查
//    for (int i = row, j = col; i < 15 && j >= 0; i++, j--) {
//        if (chessMap[i][j] != kind) break;
//        count++;
//    }
//    // 向右上检查
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
//    // 枚举每一个位置
//    for (int row = 0; row < 15; row++) {
//        for (int col = 0; col < 15; col++) {
//            // 如果这个位置上的棋子种类不是我们要计算的，就跳过
//            if (chessMap[row][col] != kind) continue;
//            // 否则，检查这个位置上是否有number个连在一起的棋子
//            //if (checkHorizontal(number,pos) || checkVertical(number,pos) || checkDiagonal(number,pos)) {
//            //    count++;
//            //}
//            count = checkHorizontal(number, pos) + checkVertical(number, pos) + checkDiagonal(number, pos);
//        }
//    }
//    return count;
//}

