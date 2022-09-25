#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <vector>

#include "TrailNode.h"

// Direction indentifiers defines
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define DEFAULT_DISPLACEMENT 1
class Player{
  protected:
    int xCoordenate;
    int yCoordenate;
    int direction;
    vector<TrailNode> trail;
    float color[3];
    float scale[3];
  
  public:
    int getXCoordenate();
    int getYCoordenate();
    int getDirection();
    void setDirection(int);
    vector<TrailNode> getTrail();
    void setCoordenate(float x, float y);
    void move(int direction);
    void render(GLuint object, float r, float g, float b, float scaleX, float scaleY, float scaleZ);
    void renderSphere(float r, float g, float b, float scaleX, float scaleY, float scaleZ);
    void renderCube(float r, float g, float b, float scaleX, float scaleY, float scaleZ);
    void resetTrail();
    void renderTrail();
    void showTrail();
};

void Player::render(GLuint object, float r, float g, float b, float scaleX, float scaleY, float scaleZ) {
  glPushMatrix();
    glTranslatef(this->xCoordenate, this->yCoordenate, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glColor3f(r, g, b);
    glCallList(object);
  glPopMatrix();
}

void Player::renderSphere(float r, float g, float b, float scaleX, float scaleY, float scaleZ) {
  color[0] = r;
  color[1] = g;
  color[2] = b;
  scale[0] = scaleX;
  scale[1] = scaleY;
  scale[2] = scaleZ;
  glPushMatrix();
    glTranslatef(this->xCoordenate, this->yCoordenate, 1);
    glScalef(scaleX, scaleY, scaleZ);
    glColor3f(r, g, b);
    glutWireSphere(1, 50, 50);
  glPopMatrix();
}

void Player::renderCube(float r, float g, float b, float scaleX, float scaleY, float scaleZ){
  color[0] = r;
  color[1] = g;
  color[2] = b;
  scale[0] = scaleX;
  scale[1] = scaleY;
  scale[2] = scaleZ;
  glPushMatrix();
    glTranslatef(this->xCoordenate, this->yCoordenate, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glColor3f(r, g, b);
    glutSolidCube(1);
  glPopMatrix();
}

int Player::getXCoordenate(){
  return this->xCoordenate;
}

int Player::getYCoordenate(){
  return this->yCoordenate;
}

void Player::setCoordenate(float x, float y) { 
  this->xCoordenate = (int)x;
  this->yCoordenate = (int)y;
}

int Player::getDirection(){
  return this->direction;
}

void Player::setDirection(int direction){
  if(direction == UP && this->direction != DOWN){
    this->direction = direction;
  } else if(direction == DOWN && this->direction != UP){
    this->direction = direction;
  } else if(direction == LEFT && this->direction != RIGHT){
    this->direction = direction;
  } else if(direction == RIGHT && this->direction != LEFT){
    this->direction = direction;
  }
}

void Player::move(int direction){
  switch(direction){
    case UP:
      if(this->direction != DOWN){
        this->direction = UP;
        setCoordenate(this->xCoordenate, this->yCoordenate + DEFAULT_DISPLACEMENT);
        trail.push_back(TrailNode(this->xCoordenate, this->yCoordenate));
      }
      break;
    case DOWN:
      if(this->direction != UP){
        this->direction = DOWN;
        setCoordenate(this->xCoordenate, this->yCoordenate - DEFAULT_DISPLACEMENT);
        trail.push_back(TrailNode(this->xCoordenate, this->yCoordenate));
      }
      break;
    case LEFT:
      if(this->direction != RIGHT){
        this->direction = LEFT;
        setCoordenate(this->xCoordenate - DEFAULT_DISPLACEMENT, this->yCoordenate);
        trail.push_back(TrailNode(this->xCoordenate, this->yCoordenate));
      }
      break;
    case RIGHT:
      if(this->direction != LEFT){
        this->direction = RIGHT;
        setCoordenate(this->xCoordenate + DEFAULT_DISPLACEMENT, this->yCoordenate);
        trail.push_back(TrailNode(this->xCoordenate, this->yCoordenate));
      }
      break;
    default:
      break;
  }
}

void Player::renderTrail(){
  for (int i = 0; i < (int)this->trail.size(); i++){
    trail[i].render(color[0], color[1], color[2], scale[0], scale[1], scale[2]);
  }
}

vector<TrailNode> Player::getTrail(){
  return this->trail;
}

void Player::showTrail(){
  cout << "Trail: " << endl;
  for (int i = 0; i < (int)this->trail.size(); i++){
    cout << "Trail node " << i << ": xy(" << trail[i].getXCoordenate() << ", " << trail[i].getYCoordenate() << ")" << endl;
  }
}

void Player::resetTrail(){
  this->trail.clear();
}

#endif