
#include "ListNode.h"
#include "Board.h"

void Board::addToHead(ListNode* node) {
    if (head == nullptr) {
        head = tail = node;
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
ListNode* Board::getNodeFromIndex(int i) {
    ListNode* curr = head;
    int nodeIdx = nodesCount - 1;
    while (nodeIdx > i) {
        curr = curr->next;
        nodeIdx--;
    }
    return curr;
}
void Board::removeFromIndexes(int i, int j = -1) { // Need to test
    j = j == -1 ? i : j;
    ListNode* curr = getNodeFromIndex(i);
    ListNode* saver = curr->prev;
    while (i >= j) {
        if (i == 0) {
            removeFromHead();
        }
        else {
            curr = curr->next;
            curr->prev->deleteNode();
            nodesCount--;
            i--;
        }
    }
    curr->prev = saver;
    if (curr->prev == nullptr)
        head = curr;
    else
        curr->prev->next = curr;
}

int Board::count() const {
    return nodesCount;
}

void Board::draw() {
    ListNode* node = tail;
    while (node->prev != nullptr) {

    }
}