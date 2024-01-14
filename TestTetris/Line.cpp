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


    //adds line2 to this line if there's enough space in this line and makeChange is true
    /*Line* temp;
    temp = new Line;*/
    //if (makeChange) {
    //    //temp = new Line;
    //    temp->setNewLine();
    //    temp->arr = this->arr;
    //    (temp->countFilled) = (this->countFilled);
    //}
    //for (int i = 0; i < GAME_WIDTH; i++) {
    //    if (line2->arr[i] != SPACE) {
    //        if (this->arr[i] == SPACE) {
    //            if (makeChange) {
    //                temp->arr[i] = line2->arr[i];
    //                (temp->countFilled)++;
    //            }
    //        }
    //        else {
    //            if (makeChange)
    //                delete(this);
    //            return false;
    //        }
    //    }
    //} if (makeChange) {
    //    this->arr = temp->arr;
    //    delete(this);
    //}
    return true;
}