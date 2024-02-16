#include "Board.h"

void Board::addToHead(ListNode* node) {
    if (head == nullptr) {
        head = node;
        tail = node;
    }
    else
    {
        head->prev = node;
        node->next = head;
        head = node;
    }
    nodesCount++;
}
void Board::addToTail(ListNode* node) {
    tail->next = node;
    node->prev = tail;
    tail = node;
    nodesCount++;
}
void Board::removeFromTail() {
    tail = tail->prev;
    tail->next = nullptr;
    nodesCount--;
}

void Board::removeFromHead() {
    if (head == tail) {
        head = tail = nullptr;
        nodesCount = 0;
        return;
    }
    head = head->next;
    head->prev = nullptr;
    nodesCount--;
}

void Board::removeFromMiddle(ListNode* node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    nodesCount--;
}

ListNode* Board::getNodeFromIndex(int i) const  {

    int y = GameConfig::GAME_HEIGHT - nodesCount;
    ListNode* node = head;
    while (y != i && node!=nullptr && node->next != nullptr) {
        ++y;
        node = node->next;;
    }
    return node;
}

int Board::count() const {
    return nodesCount;
}

void Board::erase() {
    for (int i = GameConfig::GAME_HEIGHT - 1; i >= 0; i--) eraseLine(i);
}

void Board::draw(int from) { //draws board from the bottom, begin with "GAME_HEIGHT - from - 1"
    ListNode* node = tail;
    for (int i = GameConfig::GAME_HEIGHT - from - 1; i >= 0 && node != nullptr; --i, node = node->prev) {
        p.init(0, i);
        for (int j = 0; j < GameConfig::GAME_WIDTH;++j) {
                p.init(j, i);
                if (node->line->arr[j]!= GameConfig::SPACE)
                    p.draw(node->line->arr[j]);
            }
        }
}

void Board::updateScore(add_score i) {
    switch (i) {
    case add_score::one_row:
        score += 40;
        break;
    case add_score::two_rows:
        score += 100;
        break;
    case add_score::three_rows:
        score += 300;
        break;
    case add_score::four_rows:
        score += 1200;
        break;
    default: break;
    }
    if (isGame1) drawScore(Point::MIN_X1 + (5 + GameConfig::GAME_WIDTH), 13);
    else  drawScore(Point::MIN_X2 + (5 + GameConfig::GAME_WIDTH), 13);
}

void Board::drawScore(int minx, int miny) const {
    int backcolor = Point::getColor(GameConfig::COLOR_INFO);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
    gotoxy(minx, miny);

    std::cout << "Score: " << score << std::endl;
}

bool Board::checkFilled() {
    int count = 0;
    bool foundBomb = false;
    int y = GameConfig::GAME_HEIGHT - nodesCount;
    ListNode* node = head;
    ListNode* next;
    while (node != nullptr) {
        next = node->next;
        if (node->line->countFilled < GameConfig::GAME_WIDTH) {
            foundBomb = blowBomb(node) || foundBomb;
            eraseLine(y);
        }
        if (node->line->countFilled >= GameConfig::GAME_WIDTH || node->line->countFilled == 0) {
            if (node->line->countFilled >= GameConfig::GAME_WIDTH) ++count;
            remove(node);
        }
        y++;
        node = next;
    }
    if (count > 0) {
        updateScore(add_score(count));
    }
    erase();
    draw();
    return foundBomb;
}

void Board::remove(ListNode* node) {
    if (node == head) {
        removeFromHead();
        return;
    }
    if (node == tail) {
        removeFromTail();
        return;
    }
    removeFromMiddle(node);
}

void Board::eraseLine(int y) {
    p.init(0, y);
    p.draw(' ');
    std::cout << "           ";
}

ListNode* Board::getTail() const {
    return tail;
}

ListNode* Board::getHead() const {
    return head;
}

int Board::matchCords(std::vector<int>& cords, bool empty_mode) const {
    int count = 0;
    ListNode* node;
    while (cords.size()>0) {
        int cordY = cords.back();
        cords.pop_back();
        int cordX = cords.back();
        cords.pop_back();
        node = (cordY < GameConfig::GAME_HEIGHT - nodesCount) ? nullptr : getNodeFromIndex(cordY);
        if (empty_mode) {
            if (cordY < GameConfig::GAME_HEIGHT && cordX >= 0 && cordX < GameConfig::GAME_WIDTH) {
                if (node == nullptr) count++;
                if (node != nullptr && (node->line->arr[cordX] == GameConfig::SPACE || node->line->arr[cordX] == GameConfig::BOOM)) count++;
            }
        }
        else {
            if (cordX < 0 || cordX >= GameConfig::GAME_WIDTH) count++;
            else if (node != nullptr && (node->line->arr[cordX] != GameConfig::SPACE && node->line->arr[cordX] != GameConfig::BOOM)) count++;
        }
    }
    return count;
}

bool Board::blowBomb(ListNode* node) {
    bool foundBomb = false;
    for (int i = 0; i < GameConfig::GAME_WIDTH; i++) {
        if (node->line->arr[i] == GameConfig::BOOM) {
            node->line->arr[i] = GameConfig::SPACE;
            node->line->countFilled--;
        }
        if (node->line->arr[i] == GameConfig::BAM) {
            foundBomb = true;
            node->line->arr[i] = GameConfig::BOOM;
        }

    }
    return foundBomb;
}

int Board::getBoom(int x, int y) const {
    bool first_time = true;
    int count = 0;
    int j = 0;
    int direcation = 1;
    ListNode* node = nullptr;
    for (int currY = y - GameConfig::BOMB_RADIUS; currY <= y + GameConfig::BOMB_RADIUS; currY++, j += direcation) {
        if (currY==y) direcation = -1;
        if (currY >= 0 && currY < GameConfig::GAME_HEIGHT) {
            if (first_time && node==nullptr) node = getNodeFromIndex(currY);
            for (int currX = (x - j) >= 0 ? (x - j) : 0; currX <= x + j && currX < GameConfig::GAME_WIDTH; currX++) {
                if (node != nullptr && node->line->arr[currX] != GameConfig::SPACE && node->line->arr[currX] != GameConfig::BOOM) count++;
            }
            if (first_time && node == nullptr) return count;
            node = node->next;
        }
    }
    return count;
}
