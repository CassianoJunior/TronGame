#include <iostream>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void init(void);
void reshape(int w, int h);
void welcomeDisplay(void);
  void writeText(string text, int x, int y);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);


int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Tron Game");

  init();

  glutReshapeFunc(reshape);
  glutDisplayFunc(welcomeDisplay);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutMainLoop();

  return 0;
}


void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0); 
}

void reshape(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, w, h); 

  glOrtho (0, w, 0, h, -1 ,1);  

	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27: // Escape key
      exit(0);
      break;
    default:
      break;
  }
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) {
        cout << "Left mouse button pressed at (" << x << ", " << WINDOW_HEIGHT - y << ")" << endl;
      }
    break;
    default:
      break;
  }
}

void welcomeDisplay(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(1.0, 1.0, 1.0);
  string welcome = "Welcome to Tron Game";
  string instructions1 = "[ 1 ] - Start Two Players Game";
  string instructions2 = "[ 2 ] - Start Game versus PC";
  string instructions3 = "[ 3 ] - Start Game versus PC (Hard)";
  string instructions4 = "[ ESC ] - Exit";

  writeText(welcome, WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT-225);

  writeText(instructions1, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
  writeText(instructions2, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
  writeText(instructions3, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
  writeText(instructions4, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-370);

  glutSwapBuffers();
}

void writeText(string text, int x, int y){
  glRasterPos2f(x, y);
  for(int i = 0; i < (int)text.length(); i++){
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
  }
}