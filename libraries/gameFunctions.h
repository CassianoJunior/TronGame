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
#define LEFT_EDGE_X -97
#define RIGHT_EDGE_X 97
#define TOP_EDGE_Y 73
#define BOTTOM_EDGE_Y -73


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
  
  if(((player1->getXCoordenate() >= LEFT_EDGE_X || player1->getXCoordenate() <= RIGHT_EDGE_X) && player1->getYCoordenate() == TOP_EDGE_Y) ||
     ((player1->getXCoordenate() >= LEFT_EDGE_X || player1->getXCoordenate() <= RIGHT_EDGE_X) && player1->getYCoordenate() == BOTTOM_EDGE_Y) ||
     ((player1->getYCoordenate() >= BOTTOM_EDGE_Y || player1->getYCoordenate() <= TOP_EDGE_Y) && player1->getXCoordenate() == LEFT_EDGE_X) ||
	 ((player1->getYCoordenate() >= BOTTOM_EDGE_Y || player1->getYCoordenate() <= TOP_EDGE_Y) && player1->getXCoordenate() == RIGHT_EDGE_X)){
	  return COLLISION_PLAYER_1;
  }
  
  
  if(((player2->getXCoordenate() >= LEFT_EDGE_X || player2->getXCoordenate() <= RIGHT_EDGE_X) && player2->getYCoordenate() == TOP_EDGE_Y) ||
     ((player2->getXCoordenate() >= LEFT_EDGE_X || player2->getXCoordenate() <= RIGHT_EDGE_X) && player2->getYCoordenate() == BOTTOM_EDGE_Y) ||
     ((player2->getYCoordenate() >= BOTTOM_EDGE_Y || player2->getYCoordenate() <= TOP_EDGE_Y) && player2->getXCoordenate() == LEFT_EDGE_X) ||
	 ((player2->getYCoordenate() >= BOTTOM_EDGE_Y || player2->getYCoordenate() <= TOP_EDGE_Y) && player2->getXCoordenate() == RIGHT_EDGE_X)){
	  return COLLISION_PLAYER_2;
  }
  
  return NO_COLLISION;
}