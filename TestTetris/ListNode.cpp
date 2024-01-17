#include "ListNode.h"
#include "Line.h"


void ListNode::setNewNode() {
    next = nullptr; prev = nullptr;
    line = new Line;
    line->setNewLine();
}
void ListNode::deleteNode() {
    delete (line);
    delete this;
}