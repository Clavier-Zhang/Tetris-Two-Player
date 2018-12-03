#include "heavyDecorator.h"
#include "abstractBlock.h"
using namespace std;

HeavyDecorator::HeavyDecorator(shared_ptr<AbstractPlayer> absPlayer, Game *g, Xwindow * w) :
AbstractDecorator{absPlayer, g, w} {
}

void HeavyDecorator::drop(bool shouldClearBlind) {
 player->drop(shouldClearBlind);
}

shared_ptr<AbstractPlayer> HeavyDecorator::getUnderlyingPlayer() {
 return player;
}

void HeavyDecorator::setLevel(int level) {
 player->setLevel(level);
 }

int HeavyDecorator::getHighScore(){
    return player->getHighScore();
}

void HeavyDecorator::setHighScore(int hi){
    player->setHighScore(hi);
}

int HeavyDecorator::getLevel() {return player->getLevel();}
int HeavyDecorator::getNumDrop(){
    return player->getNumDrop();
}
void HeavyDecorator::setRandom(bool rand, string file) {
    player->setRandom(rand, file);
}

void HeavyDecorator::setNumDrop(int n){
    player->setNumDrop(n);
}
void HeavyDecorator::nullifyUnderlyingPlayer() {
 player = nullptr;
}

void HeavyDecorator::setUnderlyingPlayer(shared_ptr<AbstractPlayer> play) {
 player = play;
 // UNLESS YOU MADE A COPY SOMETHERE THIS WILL DESTROY IT BEWARE
}

void HeavyDecorator::drawGridPoint(int x, int y, int col) {
 player->drawGridPoint(x, y, col);
 }

int HeavyDecorator::rotate(bool counter, int step, bool isBlind) {
int newStep = player->rotate(counter, step, isBlind);
int test =1;
int result = getBasePlayer()->move("down", newStep, isBlind);
if (result == newStep)
    test = getBasePlayer()->canMoveDown(1);
if ((newStep == -1)||(result < newStep )||test==0){ 
    return -1;
    }
return newStep;// return this r the retval of the preceding line?
}

string HeavyDecorator::getGridPoint(int row, int col) {
return player->getGridPoint(row, col);
}

string HeavyDecorator::getGridRow(int row) {
return player->getGridRow(row);
}

void HeavyDecorator::setCurrentBlock(char c) {
 player->setCurrentBlock(c);
 }

int HeavyDecorator::move(string type, int step, bool isBlind) {
int newStep = player->move(type, step, isBlind);
int test=1;
int result = getBasePlayer()->move("down", newStep, isBlind);
if (result == newStep)
    test = getBasePlayer()->canMoveDown(1);
if ((newStep == -1)||(result < newStep )||test==0){ 
    return -1;
    }
return newStep;// return this r the retval of the preceding line?
}

shared_ptr<AbstractPlayer> HeavyDecorator::getBasePlayer() {
 shared_ptr<AbstractPlayer> tmp = getUnderlyingPlayer();
 while (tmp->getUnderlyingPlayer() != nullptr) {
  tmp = tmp->getUnderlyingPlayer();
  }
  return tmp;
}
