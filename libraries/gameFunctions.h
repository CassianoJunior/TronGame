#include <iostream>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void renderScenario(int width, int height);

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