#include "MovesList.h"

MovesNode::moves MovesList::popHead() {
    if (head == nullptr) return MovesNode::moves::DOWN;
    MovesNode::moves move = head->move;
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
    if (head == nullptr) {
        head = node;
        tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void MovesList::removeFromHead() {
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
        return;
    }
    head = head->next;
    head->prev = nullptr;
}

void MovesList::removeFromTail() {
    tail = tail->prev;
    tail->next = nullptr;
}

void MovesList::addMove(MovesNode::moves move) {
    MovesNode* node = new MovesNode;
    node->move = move;
    addToHead(node);
}

bool MovesList::isEmpty() const {
    if (head == nullptr) return true;
    return false;
}

void MovesList::empty() {
    MovesNode* curr = tail;
    MovesNode* next;
    while (curr != nullptr) {
        next = curr->next;
        curr = next;
    }
    tail = nullptr;
    head = nullptr;
}

