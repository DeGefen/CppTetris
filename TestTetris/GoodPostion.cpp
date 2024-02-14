#include "GoodPosition.h"


GoodPositionNode* GoodPosition::getGoodPosition(bool miss) {
    GoodPositionNode* node = head;
    if (!miss) {
        return node;
    }
    int index = (rand() % nodesCount-1) + 1;
    for (int i = 0; i < index; ++i) node = node->prev;
    return node;
}

void GoodPosition::findGoodPositions(GameMech& game) {
    if (level == 'a' && game.curr.getType() == GameConfig::BOMB) {
        bombPosition(game);
        return;
    }
    ListNode* curr = game.board.getTail();
    int currY = GameConfig::GAME_HEIGHT-1;
    int headY = 0;
    int coverage;
    int maxCoverage = 0;
    int blockedSpaces;
    int neighbors;
    int linesAdded;

    for (int i = 0; i != game.curr.numOfPositions; ++i) {
        coverage = game.curr.getCoverage(headY);
        if (maxCoverage < coverage) maxCoverage = coverage;
        game.curr.rotate(game.board, Tetromino::_ROTATE_COUNTERCLOCKWISE, false);
    }

    while (curr != nullptr) {
        coverage = game.curr.getCoverage(headY);
        for (int x = 0; x < GameConfig::GAME_WIDTH; ++x) {
            game.curr.jumpTo(x, currY + headY);
            neighbors = game.curr.getNeighbors(game.board, x, currY + headY);
            blockedSpaces = game.curr.getBlockedSpaces(game.board, x, currY + headY);
            linesAdded = (GameConfig::GAME_HEIGHT - game.board.count()) - (headY + currY + game.curr.getHight());
            if (game.curr.checkTetroMove(game.board) && game.curr.getHeadY() + game.curr.getHight() >= 0) {
                addNode(coverage, x, currY + headY, game.curr.position, blockedSpaces, currY, (linesAdded > 0) ? linesAdded : 0, game.curr.getPotential(curr), neighbors);
            }
        }
        if (game.curr.numOfPositions - 1 == game.curr.position) {
            currY--;
            curr = curr->prev;
        }
        game.curr.rotate(game.board, Tetromino::_ROTATE_COUNTERCLOCKWISE, false);
    }

    while (game.curr.getCoverage(headY) != maxCoverage) {
        game.curr.rotate(game.board, 1, false);
    }
    int x = (-1) * game.curr.getMinX();
    linesAdded = (headY + currY + game.curr.getHight()) - (GameConfig::GAME_HEIGHT - game.board.count());
    addNode(maxCoverage, x, currY + headY, game.curr.position, game.curr.getBlockedSpaces(game.board,x, currY + headY), currY, (linesAdded > 0) ? linesAdded : 0, 0, 0);
    
    game.curr.jumpTo(GameConfig::STARTING_X, GameConfig::STARTING_Y);
    game.curr.position = 0;
}




void GoodPosition::addToHead(GoodPositionNode* node) {
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

void GoodPosition::addToTail(GoodPositionNode* node) {
    tail->next = node;
    node->prev = tail;
    tail = node;
}

void GoodPosition::addToPrev(GoodPositionNode* node, GoodPositionNode* newNode) {
    node->prev->next = newNode;
    newNode->prev = node->prev;
    node->prev = newNode;
    newNode->next = node;
}


void GoodPosition::addNode(int coverage, int headX, int headY, int position, int blockedSpaces, int bottomY, int linesAdded, int linesFilled, int emptyNeighbors) {
    GoodPositionNode* node = new GoodPositionNode(headX, headY, position, coverage, blockedSpaces, bottomY, linesAdded, linesFilled, emptyNeighbors);
    //prev = better, next = worst
    if (head==nullptr)
        addToHead(node);
    else if (node->betterThen(head)) addToHead(node);
    else {
        GoodPositionNode* curr = head;
        while (curr != tail && !(node->betterThen(head))) curr = curr->next;
        if (curr == tail)addToTail(node);
        else (addToPrev(curr, node));
    }
    ++nodesCount;
}

void GoodPosition::removeFromHead(){
    if (head == tail) {
        delete[] head;
        head = tail = nullptr;
        return;
    }
    head = head->next;
    delete[] head->prev;
    head->prev = nullptr;
}

void GoodPosition::deleteNodes() {
    GoodPositionNode* curr = tail;
    GoodPositionNode* next;
    while (curr != nullptr) {
        next = curr->next;
        delete[] curr;
        curr = next;
    }
}

void GoodPosition::bombPosition(GameMech& game) {
    ListNode* curr = game.board.getTail();
    int y = GameConfig::GAME_HEIGHT - 1;
    int coverage;

    while (curr != nullptr) {
        for (int x = 0; x < GameConfig::GAME_WIDTH; ++x) {
            if (curr->line->arr[x] != GameConfig::SPACE && curr->line->arr[x] != GameConfig::BOOM) {
                coverage = game.board.getBoom(x, y);
                addNode(y, x, y, 0, 0, coverage, 0, 0, 0);
            }
        }
        y--;
        curr = curr->prev;
    }

    for (int x = 0; x < GameConfig::GAME_WIDTH; ++x) {
        coverage = game.board.getBoom(x, y);
        addNode(y, x, y, 0, 0, coverage, 0, 0, 0);
    }
}
