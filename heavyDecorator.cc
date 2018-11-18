#include "heavyDecorator.h"
using namespace std;

HeavyDecorator::HeavyDecorator(AbstractDecorator *abstractDecorator) {}
// player's operation
// check if it is possible to level up/down
void HeavyDecorator::setLevel(int level) {}
// check if it's movable, then call block's method to move
void HeavyDecorator::moveLeft(int step = 1) {}
void HeavyDecorator::moveRight(int step = 1) {}
void HeavyDecorator::moveDown(int step = 1) {}
void HeavyDecorator::rotateClockwise() {}
void HeavyDecorator::rotateCounterClockwise() {}
// add the points of blocks to grid, update the block in drop(), 
void HeavyDecorator::drop() {}