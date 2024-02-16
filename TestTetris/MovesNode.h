#pragma once

class MovesNode {
	void setNewNode();
public:
    enum class moves { LEFT, RIGHT, DOWN, ROTATE_CLOCKWISE, ROTATE_COUNTERCLOCKWISE, DROP};

    MovesNode() { setNewNode(); }
    MovesNode(const MovesNode& node) = delete;
    MovesNode operator=(const MovesNode& node) = delete;
    MovesNode* operator=(const MovesNode* node) = delete;

    ~MovesNode() { delete[] this; }

    moves move;
    MovesNode* next = nullptr;
    MovesNode* prev = nullptr;
};