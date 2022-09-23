#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <iostream>
#include <string>
#include <cstdlib>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../classes/Player.h"
#include "../classes/Computer.h"
#include "../classes/TrailNode.h"
// Initial coordinates of players defines
#define INITIAL_COORDENATE_X 60
#define INITIAL_COORDENATE_Y 0

// Collisions identifiers defines
#define NO_COLLISION 0
#define COLLISION_PLAYER_1 1
#define COLLISION_PLAYER_2 2

// Edges limits defines
#define LEFT_EDGE_X -97
#define RIGHT_EDGE_X 97
#define TOP_EDGE_Y 73
#define BOTTOM_EDGE_Y -73

void renderScenarioOrtho(int width, int height);
void renderScenarioPerspective(int width, int height);
int hadSomeCollision(Player* player1, Player* player2);
void computerAction(Computer* computer, Player* player);

void renderScenarioOrtho(int width, int height){
  //Top edge
  glColor3f(0.19, 0.23, 0.3);
  glPushMatrix();
    glBegin(GL_QUADS);
      glVertex2f(50, height-30);
      glVertex2f(width - 50, height-30);
      glVertex2f(width - 50, height - 8 - 30);
      glVertex2f(50, height - 8 - 30);
    glEnd();
  glPopMatrix();

  //Bottom edge
  glPushMatrix();
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(width, 0);
      glVertex2f(width, 8);
      glVertex2f(0, 8);
    glEnd();
  glPopMatrix();

  //Left edge
  glPushMatrix();
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(0, height);
      glVertex2f(8, height);
      glVertex2f(8, 0);
    glEnd();
  glPopMatrix();

  //Right edge
  glPushMatrix();
    glBegin(GL_QUADS);
      glVertex2f(width, 0);
      glVertex2f(width, height);
      glVertex2f(width - 8, height);
      glVertex2f(width - 8, 0);
    glEnd();
  glPopMatrix();
  glColor3f(1, 1, 1);
}

void renderScenarioPerspective(int width, int height){
  glColor3f(0.19, 0.23, 0.3);
  //Top edge
  glPushMatrix();
    glTranslatef(-100, 73, 0);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(200, 0);
      glVertex2f(200, 3);
      glVertex2f(0, 3);
    glEnd();
  glPopMatrix();

  //Bottom edge
  glPushMatrix();
    glTranslatef(-100, -73, 0);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(200, 0);
      glVertex2f(200, -3);
      glVertex2f(0, -3);
    glEnd();
  glPopMatrix();
  // glutWireCube(20);

  //Left edge
  glPushMatrix();
    glTranslatef(-100, -73, 0);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(3, 0);
      glVertex2f(3, 146);
      glVertex2f(0, 146);
    glEnd();
  glPopMatrix();

  //Right edge
  glPushMatrix();
    glTranslatef(100, -73, 0);
    glBegin(GL_QUADS);
      glVertex2f(0, 0);
      glVertex2f(-3, 0);
      glVertex2f(-3, 146);
      glVertex2f(0, 146);
    glEnd();
  glPopMatrix();
  glColor3f(1, 1, 1);
}

int hadSomeCollision(Player* player1, Player* player2){
  if(player1->getXCoordenate() == player2->getXCoordenate() && player1->getYCoordenate() == player2->getYCoordenate()){
    int randomNumber = rand() % 2;
    return randomNumber == 0 ? COLLISION_PLAYER_1 : COLLISION_PLAYER_2;
  } 

  bool player1CollideIntoTopEdge = player1->getYCoordenate() == TOP_EDGE_Y;
  bool player2CollideIntoTopEdge = player2->getYCoordenate() == TOP_EDGE_Y;
  bool player1CollideIntoBottomEdge = player1->getYCoordenate() == BOTTOM_EDGE_Y;
  bool player2CollideIntoBottomEdge = player2->getYCoordenate() == BOTTOM_EDGE_Y;
  bool player1CollideIntoLeftEdge = player1->getXCoordenate() == LEFT_EDGE_X;
  bool player2CollideIntoLeftEdge = player2->getXCoordenate() == LEFT_EDGE_X;
  bool player1CollideIntoRightEdge = player1->getXCoordenate() == RIGHT_EDGE_X;
  bool player2CollideIntoRightEdge = player2->getXCoordenate() == RIGHT_EDGE_X;

  bool player1CollideWithEdges =  player1CollideIntoTopEdge   || player1CollideIntoBottomEdge ||
                                  player1CollideIntoRightEdge || player1CollideIntoLeftEdge;

  bool player2CollideWithEdges =  player2CollideIntoTopEdge   || player2CollideIntoBottomEdge ||
                                  player2CollideIntoRightEdge || player2CollideIntoLeftEdge;

  if(player1CollideWithEdges) return COLLISION_PLAYER_1;

  if(player2CollideWithEdges) return COLLISION_PLAYER_2;

  for (int i = 0; i < (int) player2->getTrail().size() - 1; i++) {
    int x1 = player1->getTrail()[i].getXCoordenate();
    int y1 = player1->getTrail()[i].getYCoordenate();
    // cout << "xy("<< x1 << "," << y1 << ")" << endl;
    int x2 = player2->getTrail()[i].getXCoordenate();
    int y2 = player2->getTrail()[i].getYCoordenate();
    // cout << "xy("<< x2 << "," << y2 << ")" << endl;

    bool player1CollideWithPlayer2Trail = player1->getXCoordenate() == x2 && player1->getYCoordenate() == y2;
    bool player1CollideWithOwnTrail = player1->getXCoordenate() == x1 && player1->getYCoordenate() == y1;

    bool player2CollideWithPlayer1Trail = player2->getXCoordenate() == x1 && player2->getYCoordenate() == y1;
    bool player2CollideWithOwnTrail = player2->getXCoordenate() == x2 && player2->getYCoordenate() == y2;

    if(player1CollideWithPlayer2Trail || player1CollideWithOwnTrail) return COLLISION_PLAYER_1;

    if(player2CollideWithOwnTrail || player2CollideWithPlayer1Trail) return COLLISION_PLAYER_2;

  }
  
  return NO_COLLISION;
}

void computerAction(Computer* computer, Player* player){
  int topEdgeDistance = abs(TOP_EDGE_Y - computer->getYCoordenate());
  int bottomEdgeDistance = abs(BOTTOM_EDGE_Y - computer->getYCoordenate());
  int leftEdgeDistance = abs(LEFT_EDGE_X - computer->getXCoordenate());
  int rightEdgeDistance = abs(RIGHT_EDGE_X - computer->getXCoordenate());

  int lowerDistanceOwnTrailUp = 0;// Proprio rastro acima
  int lowerDistanceOwnTrailDown = 0;// Proprio rastro abaixo
  int lowerDistanceOwnTrailRight = 0;// Proprio rastro a direita
  int lowerDistanceOwnTrailLeft = 0;// Proprio rastro a esquerda

  int lowerDistanceOponentTrailUp = 0;// Rastro do oponente acima
  int lowerDistanceOponentTrailDown = 0;// Rastro do oponente abaixo
  int lowerDistanceOponentTrailRight = 0;// Rastro do oponente a direita
  int lowerDistanceOponentTrailLeft = 0;// Rastro do oponente a esquerda

  for (int i = 0; i < (int)computer->getTrail().size() - 1; i++){
    TrailNode actualOwnTrailNode = computer->getTrail()[i];
    TrailNode actualOponentTrailNode = player->getTrail()[i];

    int yDistanceOwnTrailNode = abs(actualOwnTrailNode.getYCoordenate() - computer->getYCoordenate());
    int xDistanceOwnTrailNode = abs(actualOwnTrailNode.getXCoordenate() - computer->getXCoordenate());
    int yDistanceOponentTrailNode = abs(actualOponentTrailNode.getYCoordenate() - computer->getYCoordenate());
    int xDistanceOponentTrailNode = abs(actualOponentTrailNode.getXCoordenate() - computer->getXCoordenate());

    if(i == 0){
      lowerDistanceOwnTrailUp = yDistanceOwnTrailNode;
      lowerDistanceOwnTrailDown = yDistanceOwnTrailNode;
      lowerDistanceOwnTrailRight = xDistanceOwnTrailNode;
      lowerDistanceOwnTrailLeft = xDistanceOwnTrailNode;
      lowerDistanceOponentTrailUp = yDistanceOponentTrailNode;
      lowerDistanceOponentTrailDown = yDistanceOponentTrailNode;
      lowerDistanceOponentTrailRight = xDistanceOponentTrailNode;
      lowerDistanceOponentTrailLeft = xDistanceOponentTrailNode;

      cout << "lowerDistanceOwnTrailUp: " << lowerDistanceOwnTrailUp << endl;
      cout << "lowerDistanceOwnTrailDown: " << lowerDistanceOwnTrailDown << endl;
      cout << "lowerDistanceOwnTrailRight: " << lowerDistanceOwnTrailRight << endl;
      cout << "lowerDistanceOwnTrailLeft: " << lowerDistanceOwnTrailLeft << endl;
      cout << "lowerDistanceOponentTrailUp: " << lowerDistanceOponentTrailUp << endl;
      cout << "lowerDistanceOponentTrailDown: " << lowerDistanceOponentTrailDown << endl;
      cout << "lowerDistanceOponentTrailRight: " << lowerDistanceOponentTrailRight << endl;
      cout << "lowerDistanceOponentTrailLeft: " << lowerDistanceOponentTrailLeft << endl;
    }

    if(actualOwnTrailNode.getYCoordenate() > computer->getYCoordenate()){
      if(actualOwnTrailNode.getXCoordenate() == computer->getXCoordenate() 
      && yDistanceOwnTrailNode < lowerDistanceOwnTrailUp) lowerDistanceOwnTrailUp = yDistanceOwnTrailNode;
    } else {
      if(actualOwnTrailNode.getXCoordenate() == computer->getXCoordenate()
      && yDistanceOwnTrailNode < lowerDistanceOwnTrailDown) lowerDistanceOwnTrailDown = yDistanceOwnTrailNode;
    }

    if(actualOwnTrailNode.getXCoordenate() < computer->getXCoordenate()){
      if(actualOwnTrailNode.getYCoordenate() == computer->getYCoordenate()
      && xDistanceOwnTrailNode < lowerDistanceOwnTrailRight) lowerDistanceOwnTrailRight = xDistanceOwnTrailNode;
    } else {
      if(actualOwnTrailNode.getYCoordenate() == computer->getYCoordenate()
      && xDistanceOwnTrailNode < lowerDistanceOwnTrailLeft) lowerDistanceOwnTrailLeft = xDistanceOwnTrailNode;
    }

    if(actualOponentTrailNode.getYCoordenate() > computer->getYCoordenate()){
      if(actualOponentTrailNode.getXCoordenate() == computer->getXCoordenate()
      && yDistanceOponentTrailNode < lowerDistanceOponentTrailUp) lowerDistanceOponentTrailUp = yDistanceOponentTrailNode;
    } else {
      if(actualOponentTrailNode.getXCoordenate() == computer->getXCoordenate()
      && yDistanceOponentTrailNode < lowerDistanceOponentTrailDown) lowerDistanceOponentTrailDown = yDistanceOponentTrailNode;
    }

    if(actualOponentTrailNode.getXCoordenate() > computer->getXCoordenate()) {
      if(actualOponentTrailNode.getYCoordenate() == computer->getYCoordenate()
      && xDistanceOponentTrailNode > lowerDistanceOponentTrailRight) lowerDistanceOponentTrailRight = xDistanceOponentTrailNode;
    } else {
      if(actualOponentTrailNode.getYCoordenate() == computer->getYCoordenate()
      && xDistanceOponentTrailNode > lowerDistanceOponentTrailLeft) lowerDistanceOponentTrailLeft = xDistanceOponentTrailNode;
    }
  }

  int firstImpactUp = topEdgeDistance;
  if(lowerDistanceOponentTrailUp < firstImpactUp) firstImpactUp = lowerDistanceOponentTrailUp;
  if(lowerDistanceOwnTrailUp < firstImpactUp) firstImpactUp = lowerDistanceOwnTrailUp;

  int firstImpactDown = bottomEdgeDistance;
  if(lowerDistanceOponentTrailDown < firstImpactDown) firstImpactDown = lowerDistanceOponentTrailDown;
  if(lowerDistanceOwnTrailDown > firstImpactDown) firstImpactDown = lowerDistanceOwnTrailDown;

  int firstImpactRight = rightEdgeDistance;
  if(lowerDistanceOponentTrailRight < firstImpactRight) firstImpactRight = lowerDistanceOponentTrailRight;
  if(lowerDistanceOwnTrailRight > firstImpactRight) firstImpactRight = lowerDistanceOwnTrailRight;

  int firstImpactLeft = leftEdgeDistance;
  if(lowerDistanceOponentTrailLeft < firstImpactLeft) firstImpactLeft = lowerDistanceOponentTrailLeft;
  if(lowerDistanceOwnTrailLeft > firstImpactLeft) firstImpactLeft = lowerDistanceOwnTrailLeft;

  cout << "firstImpactUp: " << firstImpactUp << endl;
  cout << "firstImpactDown: " << firstImpactDown << endl;
  cout << "firstImpactRight: " << firstImpactRight << endl;
  cout << "firstImpactLeft: " << firstImpactLeft << endl;

  switch(computer->getActualDirection()){
    case UP:
      {
        int lastImpact = firstImpactUp;
        if(firstImpactLeft > lastImpact) lastImpact = firstImpactLeft;
        if(firstImpactRight > lastImpact) lastImpact = firstImpactRight;

        if(lastImpact == firstImpactRight){
          computer->move(RIGHT);
          computer->setActualDirection(RIGHT);
        }
        if(lastImpact == firstImpactLeft){
          computer->move(LEFT);
          computer->setActualDirection(LEFT);
        }
      }
      break;
    case DOWN:
      {
        int lastImpact = firstImpactDown;
        if(firstImpactRight > lastImpact) lastImpact = firstImpactRight;
        if(firstImpactLeft > lastImpact) lastImpact = firstImpactLeft;

        if(lastImpact == firstImpactRight){
          computer->move(RIGHT);
          computer->setActualDirection(RIGHT);
        }
        if(lastImpact == firstImpactLeft){
          computer->move(LEFT);
          computer->setActualDirection(LEFT);
        }
      }
      break;
    case LEFT:
      {
        int lastImpact = firstImpactLeft;
        if(firstImpactUp > lastImpact) lastImpact = firstImpactUp;
        if(firstImpactDown > lastImpact) lastImpact = firstImpactDown;

        if(lastImpact == firstImpactUp){
          computer->move(UP);
          computer->setActualDirection(UP);
        }
        if(lastImpact == firstImpactDown){
          computer->move(DOWN);
          computer->setActualDirection(DOWN);
        }
      }
      break;
    case RIGHT:
      {
        int lastImpact = firstImpactRight;
        if(firstImpactUp > lastImpact) lastImpact = firstImpactUp;
        if(firstImpactDown > lastImpact) lastImpact = firstImpactDown;

        if(lastImpact == firstImpactUp){
          computer->move(UP);
          computer->setActualDirection(UP);
        }
        if(lastImpact == firstImpactDown){
          computer->move(DOWN);
          computer->setActualDirection(DOWN);
        }
      }
      break;
    default:
      break;
  }
}

#endif