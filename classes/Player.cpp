#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <vector>

#include "TrailNode.cpp"

// Direction indentifiers defines
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define DEFAULT_DISPLACEMENT 1
class Player{
  private:
    int xCoordenate;
    int yCoordenate;
    vector<TrailNode> trail;
    float color[3];
    float scale[3];
  
  public:
    int getXCoordenate();
    int getYCoordenate();
    vector<TrailNode> getTrail();
    void setCoordenate(float x, float y);
    void move(int direction);
    void render(GLuint object, float r, float g, float b, float scaleX, float scaleY, float scaleZ);
    void renderSphere(float r, float g, float b, float scaleX, float scaleY, float scaleZ);
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
    glTranslatef(this->xCoordenate, this->yCoordenate, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glColor3f(r, g, b);
    glutSolidSphere(1, 50, 50);
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

void Player::move(int direction){
  switch(direction){
    case UP:
      setCoordenate(this->xCoordenate, this->yCoordenate + DEFAULT_DISPLACEMENT);
      trail.push_back(TrailNode(this->xCoordenate, this->yCoordenate));
      break;
    case DOWN:
      setCoordenate(this->xCoordenate, this->yCoordenate - DEFAULT_DISPLACEMENT);
      trail.push_back(TrailNode(this->xCoordenate, this->yCoordenate));
      break;
    case LEFT:
      setCoordenate(this->xCoordenate - DEFAULT_DISPLACEMENT, this->yCoordenate);
      trail.push_back(TrailNode(this->xCoordenate, this->yCoordenate));
      break;
    case RIGHT:
      setCoordenate(this->xCoordenate + DEFAULT_DISPLACEMENT, this->yCoordenate);
      trail.push_back(TrailNode(this->xCoordenate, this->yCoordenate));
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

// void drawPorshe() {
//     glPushMatrix();
//     glTranslatef(0, -20.0,-105);
//     glColor3f(0,1,1);
//     // glScalef(0.5,0.5,0.5);
//     glScalef(0.5,0.5,0.5);
//     glRotatef(porsheRot,0,1,0);
//     glCallList(porshe);
//     glPopMatrix();
//     porsheRot=porsheRot+0.6;
//     if(porsheRot>360)porsheRot=porsheRot-360;
// }