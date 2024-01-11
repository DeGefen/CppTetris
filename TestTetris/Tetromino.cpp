#include "Tetromino.h"

void Tetromino::rotate(Board& board, short direction) { // Rotate clockwise (direction = -1), counter-clockwise (direction = 1)
    short checkList[6][2] = { -1,0,2,0,-1,1,-1,0,2,0,-1,1 };
    if (numOfPositions == 1)
        return;
    position += direction;
    if (position < 0)
        position = numOfPositions - 1;
    if (position >= numOfPositions)
        position = 0;
    if (checkTetroMove(board))
        return;
    for (auto& i : checkList) {
        headX += i[0];
        headY += i[1];
        if (checkTetroMove(board))
            return;
    }
    //if can't rotate
    position += (-1) * direction;
    if (position < 0)
        position = numOfPositions - 1;
    if (position >= numOfPositions)
        position = 0;
}

bool Tetromino::checkTetroMove(Board& board) {
    bool flag = true;
    int y = headY;
    if (headX < 0 || headX >= GAME_WIDTH || headY < 0)
        return false;
    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        if (headX + cordX[3 * position + i] < 0 || headX + cordX[3 * position + i] >= GAME_WIDTH || headY + cordY[3 * position + i] < 0)
            return false;
    }

    if (board.nodesCount > 0) {
        if (headY <= board.nodesCount - 1)
            flag = checkTetroMoveAUX(board, headY);
        for (int i = 0; i < NUM_OF_CORDS; ++i) {
            if (flag && headY + cordY[3 * position + i] != y && headY + cordY[3 * position + i] <= board.nodesCount - 1) {
                y = headY + cordY[3 * position + i];
                flag = checkTetroMoveAUX(board, headY + cordY[3 * position + i]);
            }
        }
    }
    return flag;
}

bool Tetromino::checkTetroMoveAUX(Board& board, int y) {
    bool flag;
    ListNode* checkLine = board.getNodeFromIndex(y);
    Line* tetroLine = convertToLine(y);
    flag = checkLine->line->canIntersectLines(tetroLine, false);
    delete tetroLine;
    return flag;
}

Line* Tetromino::convertToLine(int y) {
    Line* tetroLine = new Line;
    tetroLine->setNewLine();
    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        if (headY + cordY[3 * position + i] == y) {
            tetroLine->arr[headX + cordX[3 * position + i]] = type;
            ++(tetroLine->countFilled);
        }
    }
    return tetroLine;
}

void Tetromino::moveTetro(Board& board, short direction) {
    headX += direction;
    if (!checkTetroMove(board))
        headX += direction * (-1);
}

bool Tetromino::placeTetro(Board& board) {
    --headY;
    if (!checkTetroMove(board)) {
        ++headY;
        int y = headY;
        Line* tetroLine = convertToLine(y);
        placeTetroAux(board, tetroLine, y);
        for (int i = 0; i < NUM_OF_CORDS; ++i) {
            if (headY + cordY[3 * position + i] != y) {
                y = headY + cordY[3 * position + i];
                tetroLine = convertToLine(y);
                placeTetroAux(board, tetroLine, y);
            }
        }
        return true;
    }
    else {
        ++headY;
        return false;
    }
}

void Tetromino::placeTetroAux(Board& board, Line* tetroLine, int y) {
    if (y >= board.nodesCount - 1) {
        auto* tetroNode = new ListNode;
        tetroNode->line = tetroLine;
        board.addToHead(tetroNode);
    }
    else {
        auto* listNode = board.getNodeFromIndex(y);
        listNode->line->canIntersectLines(tetroLine);
    }
}

void Tetromino::dropTetro(Board& board) {
    if (headY > board.nodesCount)
        headY = board.nodesCount;
    while (checkTetroMove(board))
        --headY;
    placeTetro(board);
}

void Tetromino::moveDown(Board& board) {
    if (!placeTetro(board))
        --headY;
}

void Tetromino::init(int headX, int headY, char type)
{
    this->type = type;
    //this->position
};