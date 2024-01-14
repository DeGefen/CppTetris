
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
void Board::removeFromTail() { // Necessary?
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
    node->deleteNode();
}

ListNode* Board::getNodeFromIndex(int i) {
    if (i >= GAME_HEIGHT - 1 || nodesCount == 1)
        return tail;
    ListNode* curr = head;
    for (int j = GAME_HEIGHT - nodesCount; j > i; --j, curr = curr->next);
    return curr;
}
//void Board::removeFromIndexes(int i, int j = -1) { // Need to test
//    j = j == -1 ? i : j;
//    updateScore(i - j+1);
//    ListNode* curr = getNodeFromIndex(i);
//    ListNode* saver = curr->prev;
//    while (i >= j) {
//        if (i == 0) {
//            removeFromHead();
//        }
//        else {
//            curr = curr->next;
//            curr->prev->deleteNode();
//            nodesCount--;
//            i--;
//        }
//    }
//    curr->prev = saver;
//    if (curr->prev == nullptr)
//        head = curr;
//    else
//        curr->prev->next = curr;
//}

int Board::count() const {
    return nodesCount;
}

void Board::draw(int from) { //draws board from the bottom, begin with "GAME_HEIGHT - from - 1"
    ListNode* node = tail;
    Point p;
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

void Board::remove(vector<ListNode*> arr) {
    updateScore(arr.size());
    for (ListNode* temp : arr) {
        if (temp == head) removeFromHead();
        else if (temp == tail) removeFromTail();
        else removeFromMiddle(temp);
    }
}

void Board::eraseLine(int y) {
    Point p;
    p.init(0, y);
    p.draw(' ');
    cout << "           ";
}
