//
// Created by Eylon Serok on 07/01/2024.
//
#include "ListNode.h"
#include "Line.h"


ListNode* ListNode::setNewNode() {
    line = new Line;
    line->setNewLine();
    return this; //Necessary ?
}
void ListNode::deleteNode() {
    delete (line);
    delete this;
}