#include "Line.h"

void Line::setNewLine() {
    countFilled = 0;
    for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
        arr[i] = GameConfig::SPACE;
}
void Line::printLine() {
    std::cout << arr << '\n';
}
bool Line::canIntersectLines(Line* line2, bool makeChange) {
    char str[13] = "            ";
    int add=0;

    for (int i = 0; i < GameConfig::GAME_WIDTH; ++i) {
        if (arr[i] != GameConfig::SPACE && line2->arr[i] == GameConfig::BAM)
            str[i] = line2->arr[i];
        else if (arr[i] != GameConfig::BOOM && line2->arr[i] != GameConfig::BAM &&  arr[i] != GameConfig::SPACE && line2->arr[i] != GameConfig::SPACE)
            return false;
        else if (makeChange && arr[i] != GameConfig::SPACE && line2->arr[i] == GameConfig::SPACE)
            str[i] = arr[i];
        else if (makeChange && line2->arr[i] != GameConfig::SPACE) {
            str[i] = line2->arr[i];
            ++add;
        }
    }

    if (makeChange) {
        for (int i = 0; i < 13; i++) arr[i] = str[i];
        countFilled += add;
    }
    return true;
}
