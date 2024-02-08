#include "GoodPosition.h"

GoodPositionNode* GoodPosition::getGoodPosition(bool randPosition) {
    if (!randPosition) return head;
    int index = (rand() % nodesCount-1) + 1;
    GoodPositionNode* node = head;
    for (int i = 0; i < index; ++i) node = node->prev;
    return node;
}

void GoodPosition::findGoodPositions(GameMech& game) {
    ListNode* curr = game.board.getTail();
    int currY = GAME_HEIGHT-1;
    int headY = 0;
    int coverage;
    int maxCoverage = 0;

    while (curr != nullptr) {
        coverage = game.curr.getCoverage(headY);
        if (maxCoverage < coverage) maxCoverage = coverage;
        if (curr->line->countFilled + coverage <= GAME_WIDTH) {
            for (int x = 0; x < GAME_WIDTH; ++x) {
                game.curr.jumpTo(x, currY + headY);
                if (game.curr.checkTetroMove(game.board))
                    addNode(coverage, x, currY+headY, game.curr.position, game.curr.getBlockedSpaces(curr,game.board), currY);
            }
        }
        game.curr.rotate(game.board,1,false);
        if (game.curr.numOfPositions - 1 <= game.curr.position) {
            game.curr.rotate(game.board, 1, false);
            currY--;
            curr = curr->next;
        }
    }

    while (game.curr.getCoverage(headY) < maxCoverage) {
        game.curr.rotate(game.board, 1, false);
    }
    addNode(maxCoverage, (-1)*game.curr.getMinX(), currY + headY, game.curr.position, game.curr.getBlockedSpaces(curr, game.board), currY);
    game.curr.jumpTo(GameMech::STARTING_X, GameMech::STARTING_Y);
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

void GoodPosition::addNode(int coverage, int headX, int headY, int position, int blockedSpaces, int bottomY) {
    GoodPositionNode* node = new GoodPositionNode(coverage, headX, headY, position, blockedSpaces, bottomY);
    if (node->betterThen(head)) addToHead(node);
    else addToTail(node);
    ++nodesCount;
}

