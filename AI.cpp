#include "AI.h"
void AI::init(Chess* chess) {
    this->chess = chess;
    this->score.resize(8, 0);
} 
void AI::go(chess_kind_t kind) {
    this->kind = kind;
    chess_kind_t k;
    if (kind == CHESS_WHITE)k = CHESS_BLACK;
    else k = CHESS_WHITE;
    ChessPos pos1, pos2;
    int attack_score, defend_score;
    attack_score = Score(pos1, kind, true); //获取进攻最高分
    defend_score = Score(pos2, k, false);    //获取防守最高分
    int Score = 0;
    int threshold = -50000;
    if (attack_score - defend_score > threshold) Score = attack_score;
    else if (defend_score - attack_score > threshold) Score = defend_score;
    else {
        if (rand() % 2) Score = attack_score;
        else Score = defend_score;
    }
    if (Score == attack_score) chess->ChessDown(&pos1, kind);
    else chess->ChessDown(&pos2, kind);
}

int AI::getScore(ChessPos pos, chess_kind_t Kind, bool iskind) {
    countInARow(pos, Kind); //判断活子
    countSleep(pos, Kind);//判断眠子
    int Score = 0;
    if (iskind) {
        Score = 1000000 * score[0] + 50000 * score[1]
            + 400 * score[2] + 400 * score[3] + 400 * score[4]
            + 20 * score[5] + 20 * score[6] + 20 * score[7]
            + 1 + controlCenter(pos);
    }
    else {
        Score = 10000000 * score[0] + 100000 * score[1]
            + 100000 * score[2] + 100000 * score[3] + 8000 * score[4]
            + 50 * score[5] + 50 * score[6] + 50 * score[7]
            + 3 + controlCenter(pos);
    }
    for (int i = 0; i < 8; ++i) {
        score[i] = 0;
    }
    return Score;
}
int AI::Score(ChessPos& pos, chess_kind_t Kind, bool iskind) {  //打分
    int score_ = -10000, S;
    int max_x = 7, max_y = 7;
    int count = 1;
    vector<vector<int> >chessMap;
    chess->copyChessMap(chessMap);
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (chessMap[i][j] == 0 && check_valid_move(j, i, 1, chessMap)) {
                pos.col = i;
                pos.row = j;
                S = getScore(pos, Kind, iskind);
                if (score_ > S)continue;
                else if (score_ < S) {
                    count = 1;
                    score_ = S;
                    max_x = j;
                    max_y = i;
                }
                else {
                    count++;
                    score_ = S;
                    if (rand() % 10 < (10 / count)) {
                        max_x = j;
                        max_y = i;
                    }
                }
            }
        }
    }
    pos.col = max_y;
    pos.row = max_x;
    return score_;
}
//检查水平方向
void AI::checkHorizontal(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind) {
    vector<vector<int> >chessMap;
    chess->copyChessMap(chessMap);
    int count = 1;  // 连在一起的棋子数量
    int edge_empty = 0;      //计算边缘类型是否为空
    int col = pos.col;
    int row = pos.row;
    // 向左检查
    for (int i = row - 1; i >= 0; i--) {
        if (chessMap[col][i] != Kind) {
            if (chessMap[col][i] == 0) edge_empty++;
            break;
        }
        count++;
    }
    // 向右检查
    for (int i = row + 1; i < 15; i++) {
        if (chessMap[col][i] != Kind) {
            if (chessMap[col][i] == 0) edge_empty++;
            break;
        }
        count++;
    }
    if (Life_or_Sleep == false) {
        score[2] += (count >= 4);
        score[5] += (count == 3);
    }
    else {
        if (edge_empty == 1) {   //冲子
            score[3] += (count >= 4);
            score[6] += (count == 3);
        }
        else {
            score[0] += (count >= 5);
            score[1] += (count == 4);
            score[4] += (count == 3);
            score[7] += (count == 2);
        }

    }
}
// 检查垂直方向
void AI::checkVertical(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind) {
    int count = 1;  // 连在一起的棋子数量
    int edge_empty = 0;      //计算边缘类型是否为空
    vector<vector<int> >chessMap;
    chess->copyChessMap(chessMap);
    // 向上检查
    for (int i = pos.col - 1; i >= 0; i--) {
        if (chessMap[i][pos.row] != Kind) {
            if (chessMap[i][pos.row] == 0) edge_empty++;
            break;
        }
        count++;
    }
    // 向下检查
    for (int i = pos.col + 1; i < 15; i++) {
        if (chessMap[i][pos.row] != Kind) {
            if (chessMap[i][pos.row] == 0) edge_empty++;
            break;
        }
        count++;
    }
    if (Life_or_Sleep == false) {
        score[2] += (count >= 4);
        score[5] += (count == 3);
    }
    else {
        if (edge_empty == 1) {   //冲子
            score[3] += (count >= 4);
            score[6] += (count == 3);
        }
        else {
            score[0] += (count >= 5);
            score[1] += (count == 4);
            score[4] += (count == 3);
            score[7] += (count == 2);
        }

    }
}
//检查斜线
void AI::checkDiagonal(ChessPos pos, bool Life_or_Sleep, chess_kind_t Kind) {
    int count = 1;  // 连在一起的棋子数量
    vector<vector<int> >chessMap;
    chess->copyChessMap(chessMap);
    int row = pos.row;
    int col = pos.col;
    int edge_empty = 0;      //计算边缘类型是否为空
    // 向左上检查
    for (int i = col - 1, j = row - 1; i >= 0 && j >= 0; i--, j--) {
        if (chessMap[i][j] != Kind) {
            if (chessMap[i][j] == 0) edge_empty++;
            break;
        }
        count++;
    }
    // 向右下检查
    for (int i = col + 1, j = row + 1; i < 15 && j < 15; i++, j++) {
        if (chessMap[i][j] != Kind) {
            if (chessMap[i][j] == 0) edge_empty++;
            break;
        }
        count++;
    }
    if (Life_or_Sleep == false) {
        score[2] += (count >= 4);
        score[5] += (count == 3);
    }
    else {
        if (edge_empty == 1) {   //冲子
            score[3] += (count >= 4);
            score[6] += (count == 3);
        }
        else {
            score[0] += (count >= 5);
            score[1] += (count == 4);
            score[4] += (count == 3);
            score[7] += (count == 2);
        }

    }
    edge_empty = 0;
    count = 1;  // 重置计数器
    // 向左下检查
    for (int i = col + 1, j = row - 1; i < 15 && j >= 0; i++, j--) {
        if (chessMap[i][j] != Kind) {
            if (chessMap[i][j] == 0) edge_empty++;
            break;
        }
        count++;
    }
    // 向右上检查
    for (int i = col - 1, j = row + 1; i >= 0 && j < 15; i--, j++) {
        if (chessMap[i][j] != Kind) {
            if (chessMap[i][j] == 0) edge_empty++;
            break;
        }
        count++;
    }
    if (Life_or_Sleep == false) {
        score[2] += (count >= 4);
        score[5] += (count == 3);
    }
    else {
        if (edge_empty == 1) {   //冲子
            score[3] += (count >= 4);
            score[6] += (count == 3);
        }
        else {
            score[0] += (count >= 5);
            score[1] += (count == 4);
            score[4] += (count == 3);
            score[7] += (count == 2);
        }

    }
}
//判断落子位置距中间的距离
int AI::controlCenter(ChessPos pos) {
    int score = 0;
    int center_x = 7, center_y = 7;
    int distance = abs(center_x - pos.row) + abs(center_y - pos.col);
    score -= distance * 2;
    return score;
}
//搜索连子
void AI::countInARow(ChessPos pos, chess_kind_t Kind) {
    checkHorizontal(pos, true, Kind);
    checkVertical(pos, true, Kind);
    checkDiagonal(pos, true, Kind);
}
//搜索眠子
void AI::countSleep(ChessPos pos, chess_kind_t Kind) {
    int row = pos.row;
    int col = pos.col;
    vector<vector<int> >chessMap;
    chess->copyChessMap(chessMap);
    ChessPos pos1;
    for (int i = 0; i < 15; ++i) {
        pos1.col = i;
        pos1.row = row;
        if (chessMap[i][row] != 0)continue;
        checkHorizontal(pos1, false, Kind);
        checkVertical(pos1, false, Kind);
        checkDiagonal(pos1, false, Kind);
    }
    for (int i = 0; i < 15; ++i) {
        pos1.col = col;
        pos1.row = i;
        if (chessMap[col][i] != 0)continue;
        checkHorizontal(pos1, false, Kind);
        checkVertical(pos1, false, Kind);
        checkDiagonal(pos1, false, Kind);
    }
    //左上到右下
    int left_x, left_y;
    if (col >= row) {
        left_x = 0;
        left_y = col - row;
    }
    else {
        left_x = row - col;
        left_y = 0;
    }
    for (int i = left_x, j = left_y; i <= 14 && j <= 14; ++i, ++j) {
        pos1.row = i;
        pos1.col = j;
        if (chessMap[j][i] != 0)continue;
        checkHorizontal(pos1, false, Kind);
        checkVertical(pos1, false, Kind);
        checkDiagonal(pos1, false, Kind);
    }
    //左下到右上
    if (col >= row) {
        left_x = col + row > 14 ? col + row - 14 : 0;
        left_y = col + row > 14 ? 14 : col + row;
    }
    else {
        left_x = row + col > 14 ? 14 : row + col;
        left_y = row + col > 14 ? row + col - 14 : 0;
    }
    for (int i = left_x, j = left_y; i <= 14 && j >= 0; ++i, --j) {
        pos1.row = i;
        pos1.col = j;
        if (chessMap[j][i] != 0)continue;
        checkHorizontal(pos1, false, Kind);
        checkVertical(pos1, false, Kind);
        checkDiagonal(pos1, false, Kind);
    }
}
bool AI::check_valid_move(int row, int col, int distance, vector<vector<int> >chessMap) {
    for (int i = col - distance; i <= col + distance; i++) {
        for (int j = row - distance; j <= row + distance; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                if (chessMap[i][j] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}
