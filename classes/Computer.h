#ifndef COMPUTER_H
#define COMPUTER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <vector>

#include "./Player.h"

// Direction identifiers defines
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Computer : public Player{
  private:
    int actualDirection;
  public:
    void setActualDirection(int direction);
    int getActualDirection();
    // void takeDecision(Player* player);
};

void Computer::setActualDirection(int direction){
  this->actualDirection = direction;
}

int Computer::getActualDirection(){
  return this->actualDirection;
}



#endif