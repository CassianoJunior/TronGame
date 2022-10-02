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

void renderScenarioPerspective(int width, int height);
int hadSomeCollision(Player* player1, Player* player2);
void computerAction(Computer* computer, Player* player);
int changeDirectionUp(Computer* computer, Player* player);
int changeDirectionDown(Computer* computer, Player* player);
int changeDirectionLeft(Computer* computer, Player* player);
int changeDirectionRight(Computer* computer, Player* player);

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

  for (int i = 0; i < (int) player1->getTrail().size() - 1; i++) {
    int x1 = player1->getTrail()[i].getXCoordenate();
    int y1 = player1->getTrail()[i].getYCoordenate();

    int x2 = player2->getTrail()[i].getXCoordenate();
    int y2 = player2->getTrail()[i].getYCoordenate();

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
  switch(computer->getActualDirection()){
    case UP:
      {
        int choice = changeDirectionUp(computer, player);
        if(choice == UP){
          computer->setActualDirection(UP);
        } else if(choice == LEFT){
          computer->setActualDirection(LEFT);
        } else if(choice == RIGHT){
          computer->setActualDirection(RIGHT);
        }
        break;
      }
    case DOWN:
      {
        int choice = changeDirectionDown(computer, player);
        if(choice == DOWN){
          computer->setActualDirection(DOWN);
        } else if(choice == LEFT){
          computer->setActualDirection(LEFT);
        } else if(choice == RIGHT){
          computer->setActualDirection(RIGHT);
        }
        break;
      }
    case LEFT:
      {
        int choice = changeDirectionLeft(computer, player);
        if(choice == LEFT){
          computer->setActualDirection(LEFT);
        } else if(choice == UP){
          computer->setActualDirection(UP);
        } else if(choice == DOWN){
          computer->setActualDirection(DOWN);
        }
        break;
      }
    case RIGHT:
      {
        int choice = changeDirectionRight(computer, player);
        if(choice == RIGHT){
          computer->setActualDirection(RIGHT);
        } else if(choice == UP){
          computer->setActualDirection(UP);
        } else if(choice == DOWN){
          computer->setActualDirection(DOWN);
        }
        break;
      }
    default:
      break;
  }
}

int changeDirectionUp(Computer* computer, Player* player){
  int topEdgeDistance = abs(TOP_EDGE_Y - computer->getYCoordenate());
  int leftEdgeDistance = abs(LEFT_EDGE_X - computer->getXCoordenate());
  int rightEdgeDistance = abs(RIGHT_EDGE_X - computer->getXCoordenate());
  
  // Maior distancia possivel = de uma borda a outra
  int ownNearestTrailNodeUp = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no acima mais proximo da propria trilha 
  int playerNearestTrailNodeUp = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no acima mais proximo da trilha do player
  int ownNearestTrailNodeLeft = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à esquerda mais proximo da propria trilha
  int playerNearestTrailNodeLeft = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à esquerda mais proximo da trilha do player
  int ownNearestTrailNodeRight = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à direita mais proximo da propria trilha
  int playerNearestTrailNodeRight = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à direita mais proximo da trilha do player

  for(int i = 0; i < (int)player->getTrail().size(); i++){
    TrailNode actualOwnTrailNode = computer->getTrail()[i];
    TrailNode actualPlayerTrailNode = player->getTrail()[i];
    
    bool hasOwnTrailNodeAbove = actualOwnTrailNode.getYCoordenate() > computer->getYCoordenate() && actualOwnTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasPlayerTrailNodeAbove = actualPlayerTrailNode.getYCoordenate() > computer->getYCoordenate() && actualPlayerTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasOwnTrailNodeLeft = actualOwnTrailNode.getXCoordenate() < computer->getXCoordenate() && actualOwnTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasPlayerTrailNodeLeft = actualPlayerTrailNode.getXCoordenate() < computer->getXCoordenate() && actualPlayerTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasOwnTrailNodeRight = actualOwnTrailNode.getXCoordenate() > computer->getXCoordenate() && actualOwnTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasPlayerTrailNodeRight = actualPlayerTrailNode.getXCoordenate() > computer->getXCoordenate() && actualPlayerTrailNode.getYCoordenate() == computer->getYCoordenate();
    
    if(hasOwnTrailNodeAbove || hasPlayerTrailNodeAbove){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getYCoordenate() - computer->getYCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getYCoordenate() - computer->getYCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeUp) ownNearestTrailNodeUp = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeUp) playerNearestTrailNodeUp = playerTrailNodeDistance;
    }

    if(hasOwnTrailNodeLeft || hasPlayerTrailNodeLeft){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getXCoordenate() - computer->getXCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getXCoordenate() - computer->getXCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeLeft) ownNearestTrailNodeLeft = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeLeft) playerNearestTrailNodeLeft = playerTrailNodeDistance;
    }

    if(hasOwnTrailNodeRight || hasPlayerTrailNodeRight){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getXCoordenate() - computer->getXCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getXCoordenate() - computer->getXCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeRight) ownNearestTrailNodeRight = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeRight) playerNearestTrailNodeRight = playerTrailNodeDistance;
    }
  }

  int firstImpactUp = topEdgeDistance;
  if(ownNearestTrailNodeUp < firstImpactUp) firstImpactUp = ownNearestTrailNodeUp;
  if(playerNearestTrailNodeUp < firstImpactUp) firstImpactUp = playerNearestTrailNodeUp;

  int firstImpactLeft = leftEdgeDistance;
  if(ownNearestTrailNodeLeft < firstImpactLeft) firstImpactLeft = ownNearestTrailNodeLeft;
  if(playerNearestTrailNodeLeft < firstImpactLeft) firstImpactLeft = playerNearestTrailNodeLeft;

  int firstImpactRight = rightEdgeDistance;
  if(ownNearestTrailNodeRight < firstImpactRight) firstImpactRight = ownNearestTrailNodeRight;
  if(playerNearestTrailNodeRight < firstImpactRight) firstImpactRight = playerNearestTrailNodeRight;

  if(firstImpactUp >= firstImpactLeft && firstImpactUp >= firstImpactRight){
    return UP;
  }else if(firstImpactLeft >= firstImpactUp && firstImpactLeft >= firstImpactRight){
    return LEFT;
  }else if(firstImpactRight >= firstImpactUp && firstImpactRight >= firstImpactLeft){
    return RIGHT;
  }

  return UP;
}

int changeDirectionDown(Computer* computer, Player* player){
  int bottomEdgeDistance = abs(BOTTOM_EDGE_Y - computer->getYCoordenate());
  int leftEdgeDistance = abs(LEFT_EDGE_X - computer->getXCoordenate());
  int rightEdgeDistance = abs(RIGHT_EDGE_X - computer->getXCoordenate());
  
  // Maior distancia possivel = de uma borda a outra
  int ownNearestTrailNodeDown = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no abaixo mais proximo da propria trilha 
  int playerNearestTrailNodeDown = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no abaixo mais proximo da trilha do player
  int ownNearestTrailNodeLeft = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à esquerda mais proximo da propria trilha
  int playerNearestTrailNodeLeft = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à esquerda mais proximo da trilha do player
  int ownNearestTrailNodeRight = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à direita mais proximo da propria trilha
  int playerNearestTrailNodeRight = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à direita mais proximo da trilha do player

  for(int i = 0; i < (int)player->getTrail().size(); i++){
    TrailNode actualOwnTrailNode = computer->getTrail()[i];
    TrailNode actualPlayerTrailNode = player->getTrail()[i];
    
    bool hasOwnTrailNodeBelow = actualOwnTrailNode.getYCoordenate() < computer->getYCoordenate() && actualOwnTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasPlayerTrailNodeBelow = actualPlayerTrailNode.getYCoordenate() < computer->getYCoordenate() && actualPlayerTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasOwnTrailNodeLeft = actualOwnTrailNode.getXCoordenate() < computer->getXCoordenate() && actualOwnTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasPlayerTrailNodeLeft = actualPlayerTrailNode.getXCoordenate() < computer->getXCoordenate() && actualPlayerTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasOwnTrailNodeRight = actualOwnTrailNode.getXCoordenate() > computer->getXCoordenate() && actualOwnTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasPlayerTrailNodeRight = actualPlayerTrailNode.getXCoordenate() > computer->getXCoordenate() && actualPlayerTrailNode.getYCoordenate() == computer->getYCoordenate();

    if(hasOwnTrailNodeBelow || hasPlayerTrailNodeBelow){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getYCoordenate() - computer->getYCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getYCoordenate() - computer->getYCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeDown) ownNearestTrailNodeDown = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeDown) playerNearestTrailNodeDown = playerTrailNodeDistance;
    }

    if(hasOwnTrailNodeLeft || hasPlayerTrailNodeLeft){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getXCoordenate() - computer->getXCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getXCoordenate() - computer->getXCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeLeft) ownNearestTrailNodeLeft = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeLeft) playerNearestTrailNodeLeft = playerTrailNodeDistance;
    }

    if(hasOwnTrailNodeRight || hasPlayerTrailNodeRight){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getXCoordenate() - computer->getXCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getXCoordenate() - computer->getXCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeRight) ownNearestTrailNodeRight = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeRight) playerNearestTrailNodeRight = playerTrailNodeDistance;
    }
  }

  int firstImpactDown = bottomEdgeDistance;
  if(ownNearestTrailNodeDown < firstImpactDown) firstImpactDown = ownNearestTrailNodeDown;
  if(playerNearestTrailNodeDown < firstImpactDown) firstImpactDown = playerNearestTrailNodeDown;

  int firstImpactLeft = leftEdgeDistance;
  if(ownNearestTrailNodeLeft < firstImpactLeft) firstImpactLeft = ownNearestTrailNodeLeft;
  if(playerNearestTrailNodeLeft < firstImpactLeft) firstImpactLeft = playerNearestTrailNodeLeft;

  int firstImpactRight = rightEdgeDistance;
  if(ownNearestTrailNodeRight < firstImpactRight) firstImpactRight = ownNearestTrailNodeRight;
  if(playerNearestTrailNodeRight < firstImpactRight) firstImpactRight = playerNearestTrailNodeRight;

  if(firstImpactDown >= firstImpactLeft && firstImpactDown >= firstImpactRight){
    return DOWN;
  } else if(firstImpactLeft >= firstImpactDown && firstImpactLeft >= firstImpactRight){
    return LEFT;
  } else if(firstImpactRight >= firstImpactDown && firstImpactRight >= firstImpactLeft){
    return RIGHT;
  }

  return DOWN;
}

int changeDirectionLeft(Computer* computer, Player* player){
  int leftEdgeDistance = abs(LEFT_EDGE_X - computer->getXCoordenate());
  int bottomEdgeDistance = abs(BOTTOM_EDGE_Y - computer->getYCoordenate());
  int topEdgeDistance = abs(TOP_EDGE_Y - computer->getYCoordenate());
  
  // Maior distancia possivel = de uma borda a outra
  int ownNearestTrailNodeLeft = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à esquerda mais proximo da propria trilha
  int playerNearestTrailNodeLeft = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à esquerda mais proximo da trilha do player
  int ownNearestTrailNodeUp = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no acima mais proximo da propria trilha
  int playerNearestTrailNodeUp = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no acima mais proximo da trilha do player
  int ownNearestTrailNodeDown = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no abaixo mais proximo da propria trilha 
  int playerNearestTrailNodeDown = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no abaixo mais proximo da trilha do player

  for(int i = 0; i < (int)player->getTrail().size(); i++){
    TrailNode actualOwnTrailNode = computer->getTrail()[i];
    TrailNode actualPlayerTrailNode = player->getTrail()[i];
    
    bool hasOwnTrailNodeLeft = actualOwnTrailNode.getXCoordenate() < computer->getXCoordenate() && actualOwnTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasPlayerTrailNodeLeft = actualPlayerTrailNode.getXCoordenate() < computer->getXCoordenate() && actualPlayerTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasOwnTrailNodeUp = actualOwnTrailNode.getYCoordenate() > computer->getYCoordenate() && actualOwnTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasPlayerTrailNodeUp = actualPlayerTrailNode.getYCoordenate() > computer->getYCoordenate() && actualPlayerTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasOwnTrailNodeDown = actualOwnTrailNode.getYCoordenate() < computer->getYCoordenate() && actualOwnTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasPlayerTrailNodeDown = actualPlayerTrailNode.getYCoordenate() < computer->getYCoordenate() && actualPlayerTrailNode.getXCoordenate() == computer->getXCoordenate();

    if(hasOwnTrailNodeLeft || hasPlayerTrailNodeLeft){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getXCoordenate() - computer->getXCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getXCoordenate() - computer->getXCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeLeft) ownNearestTrailNodeLeft = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeLeft) playerNearestTrailNodeLeft = playerTrailNodeDistance;
    }

    if(hasOwnTrailNodeUp || hasPlayerTrailNodeUp){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getYCoordenate() - computer->getYCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getYCoordenate() - computer->getYCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeUp) ownNearestTrailNodeUp = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeUp) playerNearestTrailNodeUp = playerTrailNodeDistance;
    }

    if(hasOwnTrailNodeDown || hasPlayerTrailNodeDown){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getYCoordenate() - computer->getYCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getYCoordenate() - computer->getYCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeDown) ownNearestTrailNodeDown = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeDown) playerNearestTrailNodeDown = playerTrailNodeDistance;
    }
  }

  int firstImpactLeft = leftEdgeDistance;
  if(ownNearestTrailNodeLeft < firstImpactLeft) firstImpactLeft = ownNearestTrailNodeLeft;
  if(playerNearestTrailNodeLeft < firstImpactLeft) firstImpactLeft = playerNearestTrailNodeLeft;

  int firstImpactUp = topEdgeDistance;
  if(ownNearestTrailNodeUp < firstImpactUp) firstImpactUp = ownNearestTrailNodeUp;
  if(playerNearestTrailNodeUp < firstImpactUp) firstImpactUp = playerNearestTrailNodeUp;

  int firstImpactDown = bottomEdgeDistance;
  if(ownNearestTrailNodeDown < firstImpactDown) firstImpactDown = ownNearestTrailNodeDown;
  if(playerNearestTrailNodeDown < firstImpactDown) firstImpactDown = playerNearestTrailNodeDown;

  if(firstImpactLeft >= firstImpactUp && firstImpactLeft >= firstImpactDown){
    return LEFT;
  } else if(firstImpactUp >= firstImpactLeft && firstImpactUp >= firstImpactDown){
    return UP;
  } else if(firstImpactDown >= firstImpactUp && firstImpactDown >= firstImpactLeft){
    return DOWN;
  }

  return LEFT;
}

int changeDirectionRight(Computer* computer, Player* player){
  int rightEdgeDistance = abs(RIGHT_EDGE_X - computer->getXCoordenate());
  int bottomEdgeDistance = abs(BOTTOM_EDGE_Y - computer->getYCoordenate());
  int topEdgeDistance = abs(TOP_EDGE_Y - computer->getYCoordenate());
  
  // Maior distancia possivel = de uma borda a outra
  int ownNearestTrailNodeRight = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à direita mais proximo da propria trilha
  int playerNearestTrailNodeRight = abs(LEFT_EDGE_X - RIGHT_EDGE_X); // Distancia para um no à direita mais proximo da trilha do player
  int ownNearestTrailNodeUp = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no acima mais proximo da propria trilha
  int playerNearestTrailNodeUp = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no acima mais proximo da trilha do player
  int ownNearestTrailNodeDown = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no abaixo mais proximo da propria trilha 
  int playerNearestTrailNodeDown = abs(TOP_EDGE_Y - BOTTOM_EDGE_Y); // Distancia para um no abaixo mais proximo da trilha do player

  for(int i = 0; i < (int)player->getTrail().size(); i++){
    TrailNode actualOwnTrailNode = computer->getTrail()[i];
    TrailNode actualPlayerTrailNode = player->getTrail()[i];
    
    bool hasOwnTrailNodeRight = actualOwnTrailNode.getXCoordenate() > computer->getXCoordenate() && actualOwnTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasPlayerTrailNodeRight = actualPlayerTrailNode.getXCoordenate() > computer->getXCoordenate() && actualPlayerTrailNode.getYCoordenate() == computer->getYCoordenate();
    bool hasOwnTrailNodeUp = actualOwnTrailNode.getYCoordenate() > computer->getYCoordenate() && actualOwnTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasPlayerTrailNodeUp = actualPlayerTrailNode.getYCoordenate() > computer->getYCoordenate() && actualPlayerTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasOwnTrailNodeDown = actualOwnTrailNode.getYCoordenate() < computer->getYCoordenate() && actualOwnTrailNode.getXCoordenate() == computer->getXCoordenate();
    bool hasPlayerTrailNodeDown = actualPlayerTrailNode.getYCoordenate() < computer->getYCoordenate() && actualPlayerTrailNode.getXCoordenate() == computer->getXCoordenate();

    if(hasOwnTrailNodeRight || hasPlayerTrailNodeRight){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getXCoordenate() - computer->getXCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getXCoordenate() - computer->getXCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeRight) ownNearestTrailNodeRight = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeRight) playerNearestTrailNodeRight = playerTrailNodeDistance;
    }

    if(hasOwnTrailNodeUp || hasPlayerTrailNodeUp){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getYCoordenate() - computer->getYCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getYCoordenate() - computer->getYCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeUp) ownNearestTrailNodeUp = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeUp) playerNearestTrailNodeUp = playerTrailNodeDistance;
    }

    if(hasOwnTrailNodeDown || hasPlayerTrailNodeDown){
      int ownTrailNodeDistance = abs(actualOwnTrailNode.getYCoordenate() - computer->getYCoordenate());
      int playerTrailNodeDistance = abs(actualPlayerTrailNode.getYCoordenate() - computer->getYCoordenate());
      if(ownTrailNodeDistance < ownNearestTrailNodeDown) ownNearestTrailNodeDown = ownTrailNodeDistance;
      if(playerTrailNodeDistance < playerNearestTrailNodeDown) playerNearestTrailNodeDown = playerTrailNodeDistance;
    }
  }

  int firstImpactRight = rightEdgeDistance;
  if(ownNearestTrailNodeRight < firstImpactRight) firstImpactRight = ownNearestTrailNodeRight;
  if(playerNearestTrailNodeRight < firstImpactRight) firstImpactRight = playerNearestTrailNodeRight;

  int firstImpactUp = topEdgeDistance;
  if(ownNearestTrailNodeUp < firstImpactUp) firstImpactUp = ownNearestTrailNodeUp;
  if(playerNearestTrailNodeUp < firstImpactUp) firstImpactUp = playerNearestTrailNodeUp;

  int firstImpactDown = bottomEdgeDistance;
  if(ownNearestTrailNodeDown < firstImpactDown) firstImpactDown = ownNearestTrailNodeDown;
  if(playerNearestTrailNodeDown < firstImpactDown) firstImpactDown = playerNearestTrailNodeDown;

  if(firstImpactRight >= firstImpactUp && firstImpactRight >= firstImpactDown){
    return RIGHT;
  } else if(firstImpactUp >= firstImpactRight && firstImpactUp >= firstImpactDown){
    return UP;
  } else if(firstImpactDown >= firstImpactUp && firstImpactDown >= firstImpactRight){
    return DOWN;
  }

  return RIGHT;
}

#endif