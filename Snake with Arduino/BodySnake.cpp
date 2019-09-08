/* Snake Class */
#include "BodySnake.h"
int _posX;
int _posY;

BodySnake::BodySnake() {

}

BodySnake::BodySnake(int posX, int posY) {
  _posX = posX;
  _posY = posY;
}

BodySnake::~BodySnake() {

}

int BodySnake::GetPosX() {
  return _posX;
}

int BodySnake::GetPosY() {
  return _posY;
}

void BodySnake::SetPosX(int posX) {
  _posX = posX;
}

void BodySnake::SetPosY(int posY) {
  _posY = posY;
}
