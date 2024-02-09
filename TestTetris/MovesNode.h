#pragma once

enum class moves {LEFT, RIGHT, DOWN, ROTATE_CLOCKWISE, ROTATE_COUNTERCLOCKWISE};

class MovesNode {
	void setNewNode();
public:
    MovesNode() { setNewNode(); }
    MovesNode(const MovesNode& node) = delete;
    MovesNode operator=(const MovesNode& node) = delete;

    void deleteNode();


    moves move;
    MovesNode* next = nullptr;
    MovesNode* prev = nullptr;
};