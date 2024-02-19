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
    int flag = true;
    for (int i = 0; i < (GameConfig::NUM_OF_CORDS); ++i) {
        int n = GameConfig::NUM_OF_CORDS * position + i;
        if (headX + cordX[n] < 0 || headX + cordX[n] > GameConfig::GAME_WIDTH-1 || headY + cordY[n] >= GameConfig::GAME_HEIGHT )
            return false;
    }

    if (board.count() > 0) {
        int y = GameConfig::NULL_VALUE;
        for (int i = 0; i < (GameConfig::NUM_OF_CORDS); ++i) {
            int n = GameConfig::NUM_OF_CORDS * position + i;
            if (flag && headY + cordY[n] != y && headY + cordY[n] >= GameConfig::GAME_HEIGHT - board.count()) {
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
    for (int i = 0; i < (type == 'B' ? 1 : GameConfig::NUM_OF_CORDS); ++i) {
        int n = GameConfig::NUM_OF_CORDS * position + i;
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

bool Tetromino::sideMove(Board& board, short direction, bool change) {
    if (change) erase();
    headX += direction;
    if (!checkTetroMove(board)) {
        headX += direction * (-1);
        if (change) draw();
        return false;
    }
    if (change) draw();
    return true;
}

bool Tetromino::move(Board& board, bool change) { // returns true if moved tetro down, false if placed into line
    if (change) erase();
    ++headY;
    if (!checkTetroMove(board)) {
        if (change) {
            --headY;
            if (type == GameConfig::BOMB) {
                plantBomb(board);
                erase();
                return false;
            }
            int y = GameConfig::NULL_VALUE;
            for (int i = 0; i < GameConfig::NUM_OF_CORDS; ++i) {
                int n = GameConfig::NUM_OF_CORDS * position + i;
                if (headY + cordY[n] != y) {
                    y = headY + cordY[n];
                    Line* tetroLine = convertToLine(y);
                    placeTetro(board, tetroLine, y);
                }
            }
            erase();
        }
        if (!change)--headY;
        return false;
    }
    else {
        if (change) draw();
        else --headY;
        return true;
    }
}

void Tetromino::placeTetro(Board& board, Line* tetroLine, int y) {
    if (y <= GameConfig::GAME_HEIGHT - board.count() - 1) {
        auto* tetroNode = new ListNode;
        delete tetroNode->line; //delete double memory alloction
        tetroNode->line = tetroLine;
        board.addToHead(tetroNode);
    }
    else {
        ListNode* listNode = board.getNodeFromIndex(y);
        listNode->line->canIntersectLines(tetroLine);
    }
}

void Tetromino::dropDown(Board& board) {
    while (move(board));
}


void Tetromino::draw() {

    for (int i = 0; i < (type == 'B' ? 1 : GameConfig::NUM_OF_CORDS); ++i) {
        int n = GameConfig::NUM_OF_CORDS * position + i; 
        if (headY + cordY[n] >= 0) {
            p.init(headX + cordX[n], headY + cordY[n]);
            p.draw(type);
        }
    }
};

void Tetromino::erase() {
    for (int i = 0; i < (type == 'B' ? 1 : GameConfig::NUM_OF_CORDS); ++i) {
        int n = GameConfig::NUM_OF_CORDS * position + i;
        if (headY + cordY[n] >= 0) {
            p.init(headX + cordX[n], headY + cordY[n]);
            p.draw(' ');
        }
    }
};

void Tetromino::setTetro(int num) {
    switch (num) {
    case 'I':
    case (int)tetromino_shape::I:// tetro I
    {
        int x[16] = { 0,0,0,0,0,-1,1,2 };
        int y[16] = { 2,1,0,-1,0,0,0,0 };
        copyCords(this->cordX, x);
        copyCords(this->cordY, y);
        numOfPositions = 2;
        type = 'I';
        break;
    }
    case 'O':
    case (int)tetromino_shape::O: // tetro O
    {
        int x[16] = { 1,0,1,0 };
        int y[16] = { 1,1,0,0 };
        copyCords(this->cordX, x);
        copyCords(this->cordY, y);
        type = 'O';
        numOfPositions = 1;
        break;
    }
    case 'T':
    case (int)tetromino_shape::T: // tetro T
    {
        int x[16] = { 0, 1, -1, 0,   0, 0, -1, 0,   0, -1, 1, 0,   0, 0, 1, 0 };
        int y[16] = { 0, 0, 0, -1,   1, 0, 0, -1,   1, 0, 0, 0,    1, 0, 0, -1 };
        copyCords(this->cordX, x);
        copyCords(this->cordY, y);
        numOfPositions = 4;
        type = 'T';
        break;
    }
    case 'J':
    case (int)tetromino_shape::J: // tetro J
    {
        int x[16] = { 0, -1, 0, 0,   1, -1, 1, 0,    0, 0, 0, 1,    0, 1, -1, -1 };
        int y[16] = { 1, 1, 0, -1,   1, 0, 0, 0,    1, 0, -1, -1,    0, 0, 0, -1 };
        copyCords(this->cordX, x);
        copyCords(this->cordY, y);
        numOfPositions = 4;
        type = 'J';
        break;
    }
    case 'L':
    case (int)tetromino_shape::L: // tetro L
    {
        int x[16] = { 0, 1, 0, 0,   0, -1, 1, 1,   0, 0, 0, -1,    -1, 1, -1, 0 };
        int y[16] = { 1, 1, 0, -1,   0, 0, 0, -1,   1, 0, -1, -1,   1, 0, 0, 0 };
        copyCords(this->cordX, x);
        copyCords(this->cordY, y);
        numOfPositions = 4;
        type = 'L';
        break;
    }
    case 'S':
    case (int)tetromino_shape::S: // tetro S
    {
        int x[16] = { 0, -1, 0, 1,    1, 0, 1, 0 };
        int y[16] = { 1, 1, 0, 0,    1, 0, 0, -1 };
        copyCords(this->cordX, x);
        copyCords(this->cordY, y);
        numOfPositions = 2;
        type = 'S';
        break;
    }
    case 'Z':
    case (int)tetromino_shape::Z: // tetro Z
    {
        int x[16] = { 1, 0, -1, 0,    -1, 0, -1, 0 };
        int y[16] = { 1, 1, 0, 0,    1, 0, 0, -1 };
        copyCords(this->cordX, x);
        copyCords(this->cordY, y);
        numOfPositions = 2;
        type = 'Z';
        break;
    }
    case GameConfig::BOMB:
    case (int)tetromino_shape::BOMB:
    {
        int x[16] = { 0,0,0,0 };
        int y[16] = { 0,0,0,0 };
        copyCords(this->cordX, x);
        copyCords(this->cordY, y);    
        numOfPositions = 1;
        type = GameConfig::BOMB;
        break; }
    }
}

int Tetromino::getCoverage(int& headY) const{
    int maxY = 0;
    int count = 0;
    for (int i = 0; i < GameConfig::NUM_OF_CORDS; ++i) {
        int n = GameConfig::NUM_OF_CORDS * position + i;
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

int Tetromino::getNeighbors(Board& board, int x, int y) const{
    int cordIndex = GameConfig::NUM_OF_CORDS * position;
    std::vector<int> cords_checkList;
    bool same_cord_right = false;
    bool same_cord_left = false;
    int arr[7][7] = {0};

    for (int i = 0; i < GameConfig::NUM_OF_CORDS; ++i) {
        ++arr[cordX[cordIndex + i] + 3][cordY[cordIndex + i] + 3];
    }

    for (int i = 0; i < GameConfig::NUM_OF_CORDS; ++i, same_cord_right = false, same_cord_left) {
        if (arr[cordX[cordIndex + i] + 3 + 1][cordY[cordIndex + i] + 3]++ == 0) {
            cords_checkList.push_back(x + cordX[i + cordIndex] + 1);
            cords_checkList.push_back(y + cordY[i + cordIndex]);
        }
        if (arr[cordX[cordIndex + i] + 3 - 1][cordY[cordIndex + i] + 3]++ == 0) {
            cords_checkList.push_back(x + cordX[i + cordIndex] - 1);
            cords_checkList.push_back(y + cordY[i + cordIndex]);
        }
    }
    return board.matchCords(cords_checkList, false);
}

int Tetromino::getBlockedSpaces(Board& board, int x, int y) {
    int cordIndex = GameConfig::NUM_OF_CORDS * position;
    std::vector<int> cords_checkList;
    bool same_cord = false;
    int arr[5] = { 0 };

    for (int i = 0; i < GameConfig::NUM_OF_CORDS; ++i) {
        if (++arr[cordX[cordIndex + i] + 2] == 1) {
            cords_checkList.push_back(x + cordX[i + cordIndex]);
            cords_checkList.push_back(y + cordY[i + cordIndex] + 1);
        }
    }
    return board.matchCords(cords_checkList);
}

int Tetromino::getHeadX () const{
    return headX;
}

int Tetromino::getHeadY() const {
    return headY;
}


char Tetromino::getType() const {
    return type;
}

int Tetromino::getHight() const {
    return cordY[position * GameConfig::NUM_OF_CORDS + 3];
}

void Tetromino::copyCords(int* arr1,const int* arr2) {
    for (int i = 0; i < 16; i++) {
        arr1[i] = arr2[i];
    }
}

void Tetromino::plantBomb(Board& board) {
    int j = 0; 
    int direcation = 1;
    for (int i = (GameConfig::BOMB_RADIUS); i >= -GameConfig::BOMB_RADIUS; --i, j += direcation) {
        if (i == 0) direcation = -1;
        if (headY + i >= 0 && headY + i < GameConfig::GAME_HEIGHT) {
            Line* bombLine = new Line;
            bombLine->setNewLine();
            for (int k = (headX - j) >= 0 ? (headX - j) : 0 ; k <= headX + j && k < GameConfig::GAME_WIDTH; k++) {
                bombLine->arr[k] = GameConfig::BAM;
                bombLine->countFilled++;
            }
            placeTetro(board, bombLine, headY + i);
        }
    } 
}

int Tetromino::getPotential(ListNode* node) const {
    int rowCount = 1;
    int fillCount = 0;
    int y = cordY[0];
    for (int i = 1; i < GameConfig::NUM_OF_CORDS; ++i) {
        int index = GameConfig::NUM_OF_CORDS * position + i;
        if (node == nullptr) return fillCount;
        if (cordY[i] != y) {
            if (node->line->countFilled + rowCount == GameConfig::GAME_WIDTH) fillCount++;
            node = node->prev;
            y = cordY[i];
            rowCount = 1;
        }
        else rowCount++;
    }
    if (node == nullptr) return fillCount;
    if (node->line->countFilled + rowCount == GameConfig::GAME_WIDTH) fillCount++;
    return fillCount;
}

