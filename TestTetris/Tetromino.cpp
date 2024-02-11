#include "Tetromino.h"


void Tetromino::rotate(Board& board, short direction, bool change) { // Rotate clockwise (direction = -1), counter-clockwise (direction = 1)
    short checkList[12] = { -1,0,2,0,-1,-1,-1,0,2,0,-1,-1 };
    if (numOfPositions == 1)
        return;
    if (change) erase();
    position += direction;
    if (position < 0)
        position = numOfPositions - 1;
    if (position >= numOfPositions)
        position = 0;
    if (!change || checkTetroMove(board)) {
        if (change) draw();
        return;
    }
    for (int i = 0; i < 12; i += 2) {
        headX += checkList[i];
        headY += checkList[i + 1];
        if (checkTetroMove(board)) {
            if (change) draw();
            return;
        }
    }
    //if can't rotate

    headY += 2;
    position += (-1) * direction;
    if (position < 0)
        position = numOfPositions - 1;
    if (position >= numOfPositions)
        position = 0;
    if (change) draw();
}

bool Tetromino::checkTetroMove(Board& board) { // return false if cant place
    bool flag = true;
    for (int i = 0; i < (type == 'B' ? 1 : NUM_OF_CORDS); ++i) {
        int n = NUM_OF_CORDS * position + i;
        if (headX + cordX[n] < 0 || headX + cordX[n] > GAME_WIDTH-1 || headY + cordY[n] >= GAME_HEIGHT )
            return false;
    }

    if (board.count() > 0) {
        int y = NULL_VALUE;
        for (int i = 0; i < (type == 'B' ? 1 : NUM_OF_CORDS); ++i) {
            int n = NUM_OF_CORDS * position + i;
            if (flag && headY + cordY[n] != y && headY + cordY[n] >= GAME_HEIGHT - board.count()) {
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
    for (int i = 0; i < (type == 'B' ? 1 : NUM_OF_CORDS); ++i) {
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

void Tetromino::sideMove(Board& board, short direction, bool change) {
    if (change) erase();
    headX += direction;
    if (!checkTetroMove(board))
        headX += direction * (-1);
    if (change) draw();
}

bool Tetromino::move(Board& board, bool change) { // returns true if moved tetro down, false if placed into line
    if (change) erase();
    ++headY;
    if (!checkTetroMove(board)) {
        --headY;
        ListNode* filledLines[4] = {nullptr,nullptr,nullptr,nullptr};
        int y = NULL_VALUE;
        int score = 0;
        for (int i = 0; i < (type == 'B' ? 1 : NUM_OF_CORDS); ++i) {
            int n = NUM_OF_CORDS * position + i;
            if (headY + cordY[n] != y) {
                y = headY + cordY[n];
                Line* tetroLine = convertToLine(y);
                ListNode* temp = placeTetro(board, tetroLine, y);
                if (type == 'B')
                    board.blowBomb(headX, headY);
                if(temp!=nullptr) filledLines[score++] = temp;
            }

        }
        if (change && score > 0) {
            board.updateScore(score);
            board.remove(filledLines);
            board.erase();
            board.draw();
        }
        if (change) erase();
        return false;
    }
    else {
        if (change) draw();
        return true;
    }
}

ListNode* Tetromino::placeTetro(Board& board, Line* tetroLine, int y) {
    if (y <= GAME_HEIGHT - board.count() - 1) {
        auto* tetroNode = new ListNode;
        delete tetroNode->line; //delete double memory alloction
        tetroNode->line = tetroLine;
        board.addToHead(tetroNode);
        return nullptr;
    }
    else {
        ListNode* listNode = board.getNodeFromIndex(y);
        listNode->line->canIntersectLines(tetroLine);
        if (listNode->line->countFilled >= 12)
            return listNode;
        return nullptr;
    }
}

void Tetromino::dropDown(Board& board) {
    while (move(board));
}


void Tetromino::draw() {

    for (int i = 0; i < (type == 'B' ? 1 : NUM_OF_CORDS); ++i) {
        int n = NUM_OF_CORDS * position + i; 
        if (headY + cordY[n] >= 0) {
            p.init(headX + cordX[n], headY + cordY[n]);
            p.draw(type);
        }
    }
};

void Tetromino::erase() {
    for (int i = 0; i < (type == 'B' ? 1 : NUM_OF_CORDS); ++i) {
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
        cordY = {0, 0, 0, -1,   1, 0, 0, -1,   1, 0, 0, 0,    1, 0, 0, -1 };
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
    case 7: // tetro B
        cordX = { 0 };
        cordY = { 0 };
        type = 'B';
        numOfPositions = 1;
        break;
    }
    p = Point(game);
}

int Tetromino::getCoverage(int& headY) {
    int maxY = 0;
    int count = 0;
    for (int i = 0; i < NUM_OF_CORDS; ++i) {
        int n = NUM_OF_CORDS * position + i;
        if (cordY[n] == maxY) {
            count++;
        }
        else if (cordY[n] > maxY) {
            maxY = cordY[n];
            count = 1;
        }
    }
    headY = maxY * (-1);
    return count;
}

int Tetromino::getBlockedSpaces(ListNode* node, Board& board) {
    int cordIndex = NUM_OF_CORDS * position;
    int currY = cordY[cordIndex];
    int count = 0;
    bool foundCord=false;
    int index = 0;

    if (node != nullptr){
        if (node == board.getTail()) {
            for (; index < NUM_OF_CORDS && cordY[cordIndex + index] == currY; ++index);
            currY = cordY[cordIndex + index];
        }
        else node = node->prev;

        for (; index < NUM_OF_CORDS && node!=nullptr; ++index, foundCord=false) {
            if (currY != cordY[cordIndex + index]) {
                node = node->prev;
                currY = cordY[cordIndex + index];
            }
            for (int j = index - 1; j >= 0; --j) {
                if (cordY[cordIndex + index] != cordY[cordIndex] && cordX[cordIndex + index] == cordX[cordIndex + j]) foundCord = true;
            }
            if (!foundCord && node->line->arr[headX + cordX[cordIndex + index]] == SPACE) ++count;
        }
    }

    if (index == 0) {
        if (board.count() != 0) {
            node = board.getHead();
            for (; index < NUM_OF_CORDS && cordY[cordIndex + index] == cordY[cordIndex]; ++index) {
                if (node->line->arr[headX + cordX[cordIndex + index]] == SPACE) ++count;
            }
        }
        else ++index;
    }
    for (; index < NUM_OF_CORDS; ++index, foundCord = false) {
        for (int j = index - 1; j >= 0; --j) {
            if (cordY[cordIndex + index] != cordY[cordIndex] && cordX[cordIndex + index] == cordX[cordIndex + j]) foundCord = true;
        }
        if (!foundCord) ++count;
    }
    return count;
}

int Tetromino::getMinX() {
    int minX = 0;
    int index = NUM_OF_CORDS * position;
    for (int i = 0; i < NUM_OF_CORDS; ++i) if (cordX[index + i] > minX) minX = cordX[index + i];
    return minX;
}

int Tetromino::getHeadX(){
    return headX;
}

int Tetromino::getHeadY(){
    return headY;
}


char Tetromino::getType() {
    return type;
}
