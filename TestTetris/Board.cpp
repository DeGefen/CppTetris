
#include "ListNode.h"
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
    tail->next->deleteNode();
    tail->next = nullptr;
    nodesCount--;
}
void Board::removeFromHead() {
    if (head == tail) {
        head->deleteNode();
        head = tail = nullptr;
        nodesCount = 0;
        return;
    }
    head = head->next;
    head->prev->deleteNode();
    head->prev = nullptr;
    nodesCount--;
}

void Board::removeFromMiddle(ListNode* node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    nodesCount--;
    node->deleteNode();
}

ListNode* Board::getNodeFromIndex(int i) {

    int y = GAME_HEIGHT - nodesCount;
    ListNode* node = head;
    while (y != i && node->next != nullptr) {
        ++y;
        node = node->next;;
    }
    return node;
}

int Board::count() const {
    return nodesCount;
}

void Board::erase() {
    for (int i = GAME_HEIGHT - 1; i >= 0; i--) eraseLine(i);
}

void Board::draw(int from) { //draws board from the bottom, begin with "GAME_HEIGHT - from - 1"
    ListNode* node = tail;
    for (int i = GAME_HEIGHT - from - 1; i >= 0 && node != nullptr; --i, node = node->prev) {
        p.init(0, i);
        for (int j = 0; j < GAME_WIDTH;++j) {
                p.init(j, i);
                if (node->line->arr[j]!=SPACE)
                    p.draw(node->line->arr[j]);
            }
        }
}

void Board::updateScore(int i) {
    switch (i) {
    case 1:
        score += 40;
    case 2:
        score += 100;
    case 3:
        score += 300;
    case 4:
        score += 1200;
    default: {}
    }
}

void Board::remove(ListNode** filledNodes) {
    int i = 0;
    while (filledNodes[i] != nullptr) {
        if (filledNodes[i] == head) removeFromHead();
        else if (filledNodes[i] == tail) removeFromTail();
        else removeFromMiddle(filledNodes[i]);
        i++;
    }
}

void Board::eraseLine(int y) {
    p.init(0, y);
    p.draw(' ');
    cout << "           ";
}

void Board::init()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->nodesCount = 0;
    score = 0;
}
