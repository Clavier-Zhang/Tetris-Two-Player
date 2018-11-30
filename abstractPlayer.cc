#include "abstractPlayer.h"
#include "game.h"
#include "abstractLevel.h"
#include "levelZero.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"
#include "point.h"
#include <string.h>
#include <memory>
#include <map>
#include <iostream>
using namespace std;

// constructor
AbstractPlayer::AbstractPlayer(Game *game):level{shared_ptr<AbstractLevel>(new LevelZero())},currentBlock{level->generateBlock()},nextBlock{level->generateBlock()} {
    // initialize the grid
    for (int i = 0; i < rowNum; i++) {
        vector<Point> row;
        for (int j = 0; j < colNum; j++) {
            string empty = " ";
            row.emplace_back(Point(j,i,empty));
        }
        grid.emplace_back(row);
    }
    currentBlock->initialize(this);
    this->game = game;
}

AbstractPlayer::~AbstractPlayer(){}

// check if possible to level up or down
void AbstractPlayer::setLevel(int level){
    if (level == 0) {
        this->level.reset(new LevelZero());
    } else if (level == 1) {
        this->level.reset(new LevelOne());
    }else if (level == 2){
        this->level.reset(new LevelTwo());
    }else if (level == 3){
        this->level.reset(new LevelThree());
    }else if ( level == 4){
        this->level.reset(new LevelFour());
    }
}


bool AbstractPlayer::isValid(pair<int, int> &c) {
    if (c.first < 0 || c.second < 0) {
        return false;
    }
    if (c.first >= colNum || c.second >= rowNum) {
        return false;
    }
    Point *p = this->getPoint(c);
    if (p->getType() != " " && !currentBlock->contain(p)) {
        return false;
    }
    return true;
}

void AbstractPlayer::recalculateGrid() {
   bool shouldClear;
   int offset = 0;
   for (int row = rowNum - 1; row > reservedRowNum; row--) {
        shouldClear = false;
       for (int col = 0; col < colNum; col++) {
            if ((grid[row][col].getType() != " ") && (col == colNum - 1)) shouldClear = true;
            if (grid[row][col].getType() == " ") break; 
        }

        if(shouldClear) {
            clearRow(row);
            offset++;
        } else {
            shiftRowDown(row, offset);
        }
   }
    applyLevelEffects(offset);
    recalculateInactiveBlocks();
}

void AbstractPlayer::clearRow(int row) {
   for (int col = 0; col < colNum; col++){
        Point *p = &this->grid[row][col];
        p->setType(" ");
        for (auto cell : inactiveBlocks[p->getID()]->getPoints()){
            if (cell == p){
                inactiveBlocks[p->getID()].get()->removeOnePoint(p);
            }
        }
        p->setID(-1);// reset to default
   }
}

void AbstractPlayer::shiftRowDown(int row, int offset) {
    if (row < reservedRowNum || offset == 0) return; //checks if were within correct range
    for (int col =0; col < colNum; col++) { // iterates through the columns in the current row
      Point *p = &grid[row][col];// gets the point to be moved
      if (p->getType() != " ") {
        Point *newP = &grid[row+offset][col]; // finds the place the point needs to be moved
        newP->setID(p->getID());// changes id
        
        for (auto cell : inactiveBlocks[p->getID()]->getPoints()) {
             if (cell == p) {//once we find the point in the block...
                pair<int, int> coor = make_pair(newP->getX(), newP->getY());
                inactiveBlocks[p->getID()].get()->addPoint(coor, this); // creates the point that it should be moved to
                grid[row][col].setType(" ");
                inactiveBlocks[p->getID()].get()->removeOnePoint(p);// removes the current point from the block
            }

         }
        p->setID(-1);
        }
    }
}

void AbstractPlayer::recalculateInactiveBlocks(){
    for(auto & entry : inactiveBlocks){
        if (entry.second->getPoints().size() == 0){
            currentScore += entry.second->getScore();
            inactiveBlocks.erase(entry.first);
        }
    }

}

void AbstractPlayer::applyLevelEffects(int offset){
   if (level->getLevel() == 4){
        shared_ptr<LevelFour> lf = static_pointer_cast<LevelFour>(level);
        offset>0?lf->resetNumUncleared():lf->incNumUncleared();
        int uncleared= lf->getNumUncleared();

        if (uncleared>0 && uncleared%5 == 0){
            unique_ptr<AbstractBlock> divider {lf->createCustomBlock('X')};
            divider->initialize(this);
            divider->setID(AbstractBlock::getCurId());
            inactiveBlocks[AbstractBlock::getCurId()] = std::move(divider);
            AbstractBlock::incrementCurId();
        }
    }
}

void AbstractPlayer::setIsDecorated(bool isDec) {
 isDecorated = isDec;
}

bool AbstractPlayer::getIsDecorated() { return isDecorated;}


void AbstractPlayer::setRandom() {}

// observer pattern
void AbstractPlayer::notifyGameover() {
   game->setGameOver();
}

void AbstractPlayer::notifyTurnover() {
   game->turnOver();
}

void AbstractPlayer::notifySpecialAction() {
    game->specialAction();
}

// getter
int AbstractPlayer::getCurrentScore() {
    return currentScore;
}

int AbstractPlayer::getHighestScore() {
    return highestScore;
}

int AbstractPlayer::getLevel() {
    return level->getLevel();
}

string AbstractPlayer::getNextBlock() {
    return nextBlock->getType();
}

Point* AbstractPlayer::getPoint(pair<int, int> &c) {
  return &grid[c.second][c.first];
}

void AbstractPlayer::drawScore(){
    
}