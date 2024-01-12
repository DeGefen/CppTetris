#include "Tetromino.h"


void Tetromino::rotate(Board& board, short direction) { // Rotate clockwise (direction = -1), counter-clockwise (direction = 1)
    short checkList[6][2] = { -1,0,2,0,-1,-1,-1,0,2,0,-1,-1 };
    if (numOfPositions == 1)
        return;
    erase();
    position += direction;
    if (position < 0)
        position = numOfPositions - 1;
    if (position >= numOfPositions)
        position = 0;
    if (checkTetroMove(board))
        draw();
        return;
    for (auto& i : checkList) {
        headX += i[0];
        headY += i[1];
        if (checkTetroMove(board))
            draw();
            return;
    }
    //if can't rotate
    position += (-1) * direction;
    if (position < 0)
        position = numOfPositions - 1;
    if (position >= numOfPositions)
        position = 0;
    draw();
}

bool Tetromino::checkTetroMove(Board& board) {
    bool flag = true;
    int y = headY;
    if (headX < 0 || headX >= GAME_WIDTH || headY >= GAME_HEIGHT)
        return false;
    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        if (headX + cordX[3 * position + i] < 0 || headX + cordX[3 * position + i] >= GAME_WIDTH || headY + cordY[3 * position + i] >= GAME_HEIGHT)
            return false;
    }

    if (board.nodesCount > 0) {
        if (headY >= GAME_HEIGHT - board.nodesCount)
            flag = checkTetroMoveAUX(board, headY);
        for (int i = 0; i < NUM_OF_CORDS; ++i) {
            if (flag && headY + cordY[3 * position + i] != y && headY + cordY[3 * position + i] >= GAME_HEIGHT - board.nodesCount) {
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
            tetroLine->arr[headX + cordX[3 * position + i]] = '*';
            ++(tetroLine->countFilled);
        }
    }
    return tetroLine;
}

void Tetromino::jumpTo(int x, int y) {
    headX = x;
    headY = y;
}

void Tetromino::sideMove(Board& board, short direction) {
    erase();
    headX += direction;
    if (!checkTetroMove(board))
        headX += direction * (-1);
    draw();
}

bool Tetromino::move(Board& board) {
    erase();
    ++headY;
    if (!checkTetroMove(board)) {
        --headY;
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
        draw();
        return false;
    }
}

void Tetromino::placeTetroAux(Board& board, Line* tetroLine, int y) {
    if (y >= GAME_HEIGHT - board.nodesCount) {
        auto* tetroNode = new ListNode;
        tetroNode->line = tetroLine;
        board.addToHead(tetroNode);
    }
    else {
        auto* listNode = board.getNodeFromIndex(y);
        listNode->line->canIntersectLines(tetroLine);
    }
}

void Tetromino::dropDown(Board& board) {
    if (headY < GAME_HEIGHT - board.nodesCount)
        headY = GAME_HEIGHT - board.nodesCount;
    while (!move(board));
}


void Tetromino::draw() {
    Point p;
    if (headY >= 0) {
        p.init(headX, headY);
        p.draw('*', color);
    }
    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        if (headY + cordY[3 * position + i] >= 0) {
            p.init(headX + cordX[3 * position + i], headY + cordY[3 * position + i]);
            p.draw('*', color);
        }

    }
};

void Tetromino::erase() {
    Point p;
    if (headY >= 0) {
        p.init(headX, headY);
        p.draw(' ', 0x00);
    }
    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        if (headY + cordY[3 * position + i] >= 0) {
            p.init(headX + cordX[3 * position + i], headY + cordY[3 * position + i]);
            p.draw(' ', 0x00);
        }

    }
};

void Tetromino::setTetro(int num) {
    switch (num)
    {
    case 0: // tetro I
        cordX = { 0,0,0,-1,1,2 };
        cordY = { -1,1,2,0,0,0 };
        numOfPositions = 2;
        color = 0xBB;
        break;
    case 1: // tetro O
        cordX = { 1,0,1 };
        cordY = { 0,1,1 };
        numOfPositions = 1;
        color = 0xEE;
        break;
    case 2: // tetro T
        cordX = { 0, -1, 1, 0, -1, 0, -1, 1, 0, 0, 0, 1 };
        cordY = { -1, 0, 0, -1, 0, 1, 0, 0, 1, -1, 1, 0 };
        numOfPositions = 4;
        color = 0x55;
        break;
    case 3: // tetro J
        cordX = { 0, 0, -1, -1, 1, 1, 0, 0, 1, 1, -1, -1 };
        cordY = { -1, 1, 1, 0, 0, 1, 1, -1, -1, 0, 0, -1 };
        numOfPositions = 4;
        color = 0x11;
        break;
    case 4: // tetro L
        cordX = { 0, 0, 1, -1, 1, 1, 0, 0, -1, 1, -1, -1 };
        cordY = { -1, 1, 1, 0, 0, -1, 1, -1, -1, 0, 0, 1 };
        numOfPositions = 4;
        color = 0x66;
        break;
    case 5: // tetro S
        cordX = { 1, 0, -1, 0, 1, 1 };
        cordY = { 0, 1, 1, -1, 0, 1 };
        numOfPositions = 2;
        color = 0xAA;
        break;
    case 6: // tetro Z
        cordX = { -1, 0, 1, 0, -1, -1 };
        cordY = { 0, 1, 1, -1, 0, 1 };
        numOfPositions = 2;
        color = 0x44;
        break;
    }
}