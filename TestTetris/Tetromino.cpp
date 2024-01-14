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
    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        int n = NUM_OF_CORDS * position + i;
        if (headX + cordX[n] < 0 || headX + cordX[n] > GAME_WIDTH-1 || headY + cordY[n] >= GAME_HEIGHT )
            return false;
    }

    if (board.count() > 0) {
        int y = NULL_VALUE;
        for (int i = 0; i < NUM_OF_CORDS; ++i) {
            int n = NUM_OF_CORDS * position + i;
            if (flag && headY + cordY[n] != y && headY + cordY[n] >= GAME_HEIGHT - board.count() - 1) {
                y = headY + cordY[n];
                flag = checkTetroMoveAUX(board, headY + cordY[n]);
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
        int n = NUM_OF_CORDS * position + i;
        if (headY + cordY[n] == y) {
            tetroLine->arr[headX + cordX[n]] = type;
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

bool Tetromino::move(Board& board) { // returns true if moved tetro down, false if placed into line
    erase();
    ++headY;
    if (!checkTetroMove(board)) {
        --headY;
        vector<ListNode*> filledLines;
        int y = NULL_VALUE;
        for (int i = 0; i < NUM_OF_CORDS; ++i) {
            int n = NUM_OF_CORDS * position + i;
            if (headY + cordY[n] != y) {
                y = headY + cordY[n];
                Line* tetroLine = convertToLine(y);
                ListNode* temp = placeTetro(board, tetroLine, y);
                if(temp!=nullptr) {
                    filledLines.push_back(temp);
                    board.eraseLine(y);
                }
            }
            board.remove(filledLines);
        }
        return false;
    }
    else {
        draw();
        return true;
    }
}

ListNode* Tetromino::placeTetro(Board& board, Line* tetroLine, int y) {
    if (y <= GAME_HEIGHT - board.count() - 1) {
        auto* tetroNode = new ListNode;
        tetroNode->line = tetroLine;
        board.addToHead(tetroNode);
        return nullptr;
    }
    else {
        auto* listNode = board.getNodeFromIndex(y);
        listNode->line->canIntersectLines(tetroLine);
        if (listNode->line->countFilled >= 12)
            return listNode;
        return nullptr;
    }
}

void Tetromino::dropDown(Board& board) {
    if (headY < GAME_HEIGHT - board.count() - 1)
        headY = GAME_HEIGHT - board.count() - 1;
    while (!move(board));
}


void Tetromino::draw() {
    Point p;

    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        int n = NUM_OF_CORDS * position + i;
        if (headY + cordY[n] >= 0) {
            p.init(headX + cordX[n], headY + cordY[n]);
            p.draw(type);
        }
    }
};

void Tetromino::erase() {
    Point p;
    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        int n = NUM_OF_CORDS * position + i;
        if (headY + cordY[n] >= 0) {
            p.init(headX + cordX[n], headY + cordY[n]);
            p.draw(' ');
        }
    }
};

void Tetromino::setTetro(int num) {
    switch (num)
    {
    case 0: // tetro I
        cordX = {0,0,0,0,0,-1,1,2 };
        cordY = {2,1,0,-1,0,0,0,0 };
        numOfPositions = 2;
        type = 'I';
        break;
    case 1: // tetro O
        cordX = {1, 0,1,0 };
        cordY = {1, 1,0,0 };
        type = 'O';
        numOfPositions = 1;
        break;
    case 2: // tetro T
        cordX = {0, 1, -1, 0,   0, 0, -1, 0,   0, -1, 1, 0,   0, 0, 1, 0 };
        cordY = {0, 0, 0, -1,   1, 0, 0, -1,   0, 0, 0, 1,    1, 0, 0, -1 };
        numOfPositions = 4;
        type = 'T';
        break;
    case 3: // tetro J
        cordX = {0, -1, 0, 0,   1, -1, 1, 0,    0, 0, 0, 1,    0, 1, -1, -1 };
        cordY = {1, 1, 0, -1,   1, 0, 0, 0,    1, 0, -1, -1,    0, 0, 0, -1 };
        numOfPositions = 4;
        type = 'J';
        break;
    case 4: // tetro L
        cordX = {0, 1, 0, 0,   0, -1, 1, 1,   0, 0, 0, -1,    -1, 1, -1, 0 };
        cordY = {1, 1, 0, -1,   0, 0, 0, -1,   1, 0, -1, -1,   1, 0, 0, 0 };
        numOfPositions = 4;
        type = 'L';
        break;
    case 5: // tetro S
        cordX = {0, -1, 0, 1,    1, 0, 1, 0 };
        cordY = {1, 1, 0, 0,    1, 0, 0, -1 };
        numOfPositions = 2;
        type = 'S';
        break;
    case 6: // tetro Z
        cordX = {1, 0, -1, 0,    -1, 0, -1, 0 };
        cordY = {1, 1, 0, 0,    1, 0, 0, -1 };
        numOfPositions = 2;
        type = 'Z';
        break;
    }
}