#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Trail.cpp"

// Direction indentifiers defines
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define DEFAULT_DISPLACEMENT 0.1

struct Coordenate {
  int x;
  int y;
};

class Player{
  private:
    int xCoordenate;
    int yCoordenate;
    Trail trail;
  
  public:
    int getXCoordenate();
    int getYCoordenate();
    Trail* getTrail();
    void setCoordenate(float x, float y);
    void setTrail(Trail* trail);

    void move(int direction);

    void render(GLuint object, float r, float g, float b, float translateX, float translateY, float translateZ);
    void renderSphere(float r, float g, float b, float scaleX, float scaleY, float scaleZ);
};

void Player::render(GLuint object, float r, float g, float b, float translateX, float translateY, float translateZ) {
  setCoordenate(translateX, translateY);

  glPushMatrix();
    glTranslatef(translateX, translateY, translateZ);
    glColor3f(r, g, b);
    glCallList(object);
  glPopMatrix();
}

void Player::renderSphere(float r, float g, float b, float scaleX, float scaleY, float scaleZ) {
  glPushMatrix();
    glTranslatef(this->xCoordenate, this->yCoordenate, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glColor3f(r, g, b);
    glScalef(0.2,0.2,0.2);
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
      break;
    case DOWN:
      setCoordenate(this->xCoordenate, this->yCoordenate - DEFAULT_DISPLACEMENT);
      break;
    case LEFT:
      setCoordenate(this->xCoordenate - DEFAULT_DISPLACEMENT, this->yCoordenate);
      break;
    case RIGHT:
      setCoordenate(this->xCoordenate + DEFAULT_DISPLACEMENT, this->yCoordenate);
      break;
    default:
      break;
  }
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