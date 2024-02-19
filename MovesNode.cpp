#include "MovesNode.h"

void MovesNode::setNewNode() {
    next = nullptr; prev = nullptr;
    move = moves::DOWN;
}
