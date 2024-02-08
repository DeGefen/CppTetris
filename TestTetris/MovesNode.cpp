#include "MovesNode.h"

void MovesNode::setNewNode() {
    next = nullptr; prev = nullptr;
    move = movesEnums::DOWN;
}
void MovesNode::deleteNode() {
    delete this;
}