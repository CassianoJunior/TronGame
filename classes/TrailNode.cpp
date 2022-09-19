#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
using namespace std;

class TrailNode{
  private:
    int xCoordenate;
    int yCoordenate;
    bool drawn;

  public:
    TrailNode(int x, int y);
    int getXCoordenate();
    int getYCoordenate();
    void setCoordenate(int x, int y);
    bool isDrawn();
    void setDrawn(bool drawn);
    void render(float r, float g, float b, float scaleX, float scaleY, float scaleZ);
};

TrailNode::TrailNode(int x, int y){
  this->xCoordenate = x;
  this->yCoordenate = y;
  this->drawn = false;
}

int TrailNode::getXCoordenate(){
  return this->xCoordenate;
}

int TrailNode::getYCoordenate(){
  return this->yCoordenate;
}

void TrailNode::setCoordenate(int x, int y){
  this->xCoordenate = x;
  this->yCoordenate = y;
}

bool TrailNode::isDrawn(){
  return this->drawn;
}

void TrailNode::setDrawn(bool drawn){
  this->drawn = drawn;
}

void TrailNode::render(float r, float g, float b, float scaleX, float scaleY, float scaleZ){
  glPushMatrix();
    glTranslatef(this->xCoordenate, this->yCoordenate, 0);
    glColor3f(r, g, b);
    glScalef(scaleX*0.5, scaleY*0.5, scaleZ*0.5);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();
}