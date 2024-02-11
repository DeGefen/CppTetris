#include "MovesList.h"

moves MovesList::popHead() {
    moves move = head->move;
    removeFromHead();
    return move;
}

void MovesList::addToHead(MovesNode* node) {
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
}

void MovesList::addToTail(MovesNode* node) {
    tail->next = node;
    node->prev = tail;
    tail = node;
}

void MovesList::removeFromHead() {
    if (head == tail) {
        head->deleteNode();
        head = tail = nullptr;
        return;
    }
    head = head->next;
    head->prev->deleteNode();
    head->prev = nullptr;
}

void MovesList::removeFromTail() {
    tail = tail->prev;
    tail->next->deleteNode();
    tail->next = nullptr;
}

void MovesList::addMove(moves move) {
    MovesNode* node = new MovesNode;
    node->move = move;
    addToTail(node);
}