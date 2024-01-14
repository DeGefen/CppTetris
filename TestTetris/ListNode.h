#pragma once
//
// Created by Eylon Serok on 07/01/2024.
//

#ifndef TETRIS_LISTNODE_H
#define TETRIS_LISTNODE_H

#include "Line.h"

class ListNode {
public:
    Line* line;
    ListNode* next = nullptr;
    ListNode* prev = nullptr;
    ListNode* setNewNode();
    void deleteNode();
};

#endif //TETRIS_LISTNODE_H
