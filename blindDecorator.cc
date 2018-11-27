#include "blindDecorator.h"
#include "abstractDecorator.h"
using namespace std;

// Useful constants
const int MIN_ROW_BOUND = 3;
const int MAX_ROW_BOUND = 12;
const int MIN_COL_BOUND = 3;
const int MAX_COL_BOUND = 9;

BlindDecorator::BlindDecorator(shared_ptr<AbstractPlayer> absPlayer, Game *g) : AbstractDecorator{absPlayer, g} {}

BlindDecorator::~BlindDecorator() {}

// add the points of blocks to grid, update the block in drop(), 
void BlindDecorator::drop() {
    player->drop();
}

shared_ptr<AbstractPlayer> BlindDecorator::getUnderlyingPlayer() {
 return player;
}

void BlindDecorator::nullifyUnderlyingPlayer() {
 player = nullptr;
}

void BlindDecorator::rotate(bool counter, int step){
    player->rotate(counter, step);
}

string BlindDecorator::getGridPoint(int row, int col) {
 if ((( MIN_ROW_BOUND + reservedRowNum  <= row )&&(row <= MAX_ROW_BOUND + reservedRowNum))&&((MIN_COL_BOUND <=col)&&(col <= MAX_COL_BOUND))) return "?";
 return player->getGridPoint(row, col);
}

string BlindDecorator::getGridRow(int row){
    if (!(( MIN_ROW_BOUND + reservedRowNum <= row) && (row <= MAX_ROW_BOUND + reservedRowNum))) return player->getGridRow(row);
    string s;
    for (int i = 0; i < colNum; i++) {
        s += getGridPoint(row, i);
    }
    return s;


}

void BlindDecorator::setCurrentBlock(char type){
// probably should be remooved
}

bool BlindDecorator::move(string type, int step){
    return player->move(type, step);
}
