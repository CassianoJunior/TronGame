#include <iostream>
#include <string>
#include <cstdlib>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Collisions identifiers defines
#define NO_COLLISION 0
#define COLLISION_PLAYER_1 1
#define COLLISION_PLAYER_2 2

void renderScenario(int width, int height);
int hadSomeCollision(Player* player1, Player* player2);

void renderScenario(int width, int height){
  //Top edge
  glPushMatrix();
    glTranslatef(-200, 73, 0);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(width, 0);
      glVertex2f(width, 2.5);
      glVertex2f(0, 2.5);
    glEnd();
  glPopMatrix();

  //Bottom edge
  glPushMatrix();
    glTranslatef(-200, -73, 0);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(width, 0);
      glVertex2f(width, -2.5);
      glVertex2f(0, -2.5);
    glEnd();
  glPopMatrix();

  //Left edge
  glPushMatrix();
    glTranslatef(-100, -200, 0);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(2.5, 0);
      glVertex2f(2.5, height);
      glVertex2f(0, height);
    glEnd();
  glPopMatrix();

  //Right edge
  glPushMatrix();
    glTranslatef(100, -200, 0);
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(-2.5, 0);
      glVertex2f(-2.5, height);
      glVertex2f(0, height);
    glEnd();
  glPopMatrix();
}

int hadSomeCollision(Player* player1, Player* player2){
  if(player1->getXCoordenate() == player2->getXCoordenate() && player1->getYCoordenate() == player2->getYCoordenate()){
    int winner = rand() % 2;
    return winner == 0 ? COLLISION_PLAYER_1 : COLLISION_PLAYER_2;
  }

  return NO_COLLISION;
}