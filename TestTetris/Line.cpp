#include "Line.h"

void Line::setNewLine() {
    countFilled = 0;
    for (int i = 0; i < GAME_WIDTH; i++)
        arr[i] = SPACE;
}
void Line::printLine() {
    std::cout << arr << '\n';
}
bool Line::canIntersectLines(Line* line2, bool makeChange) {
    if (countFilled + line2->countFilled > GAME_WIDTH)
        return false;
    
    string str = EMPTY_LINE;
    int add=0;

    for (int i = 0; i < GAME_WIDTH; ++i) {
        if (arr[i] != SPACE && line2->arr[i] != SPACE)
            return false;
        else if (makeChange && arr[i] != SPACE)
            str[i] = arr[i];
        else if (makeChange && line2->arr[i] != SPACE) {
            str[i] = line2->arr[i];
            ++add;
        }
    }

    if (makeChange) {
        arr = str;
        countFilled += add;
    }
    return true;
}

void Line::bombLine(int fromX, int toX) {

}