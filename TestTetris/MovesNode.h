#pragma once

enum class movesEnums {DOWN, LEFT, RIGHT, ROTATE_CLOCKWISE, ROTATE_COUNTERCLOCKWISE};

class MovesNode {
	void setNewNode();
public:
    MovesNode() { setNewNode(); }
    MovesNode(const MovesNode& node) = delete;
    MovesNode operator=(const MovesNode& node) = delete;

    void deleteNode();


    movesEnums move;
    MovesNode* next = nullptr;
    MovesNode* prev = nullptr;
};