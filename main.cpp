#include <iostream>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

// Window defines
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Welcome window options defines
#define FIRST_OPTION 0
#define SECOND_OPTION 1
#define THIRD_OPTION 2
#define FOURTH_OPTION 3

// Keyboard keys defines
#define ESCAPE 27
#define ENTER 13

// Global variables
int optionSelected = FIRST_OPTION;
bool isInWelcomeScreen = true;
bool isInInstructionsScreen = false;
bool isInGame = false;

void init(void);
void reshape(int w, int h);
// Display functions
void welcomeDisplay(void);
  void writeText(string text, int x, int y);
  void switchColor(float r, float g, float b);
void displayInstructions(void);
  void writeInstructions(void);
void displayGame2Players(void);

void keyboard(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
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
  glutSpecialFunc(processSpecialKeys);

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
    case ESCAPE:
      if(isInInstructionsScreen) {
        isInInstructionsScreen = false;
        isInWelcomeScreen = true;
        glutDisplayFunc(welcomeDisplay);
        glutPostRedisplay();
      } else {
        exit(0);
      }
      break;
    case ENTER:
      if (isInWelcomeScreen) {
        switch (optionSelected) {
          case FIRST_OPTION:
            cout << "First option selected" << endl;
            isInGame = true;
            glutDisplayFunc(displayGame2Players);
            glutPostRedisplay();
            break;
          case SECOND_OPTION:
            cout << "Second option selected" << endl;
            break;
          case THIRD_OPTION:
            cout << "Third option selected" << endl;
            break;
          case FOURTH_OPTION:
            isInWelcomeScreen = false;
            isInInstructionsScreen = true;
            glutDisplayFunc(displayInstructions);
            glutPostRedisplay();
            break;
        }
      }
      break;
    default:
      break;
  }
}

void processSpecialKeys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      if(isInWelcomeScreen){
        if(optionSelected == FIRST_OPTION){
          optionSelected = FOURTH_OPTION;
        }else{
          optionSelected--;
        }
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_DOWN:
      if(isInWelcomeScreen){
        if(optionSelected == FOURTH_OPTION){
          optionSelected = FIRST_OPTION;
        }else{
          optionSelected++;
        }
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_LEFT:
      break;
    case GLUT_KEY_RIGHT:
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

void displayGame2Players(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  switchColor(0.0, 1.0, 1.0);
  glPushMatrix();
    glutSolidCube(2);
  glPopMatrix();

  glutSwapBuffers();
}

void welcomeDisplay(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(1.0, 1.0, 1.0);
  string welcome = "Welcome to Tron Game";
  string instructions1 = "[ 1 ] - Start Two Players Game";
  string instructions2 = "[ 2 ] - Start Game versus PC";
  string instructions3 = "[ 3 ] - Start Game versus PC (Hard)";
  string instructions4 = "[ 4 ] - Tutorial / Instructions";
  string exit = "[ ESC ] - Exit";

  writeText(welcome, WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT-225);

  switch(optionSelected){
    case FIRST_OPTION:
      switchColor(1.0, 1.0, 0.0);
      writeText(instructions1 + " (Press enter)", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
      switchColor(1.0, 1.0, 1.0);
      writeText(instructions2, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      writeText(instructions3, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      writeText(instructions4, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
      writeText(exit, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-395);
      break;
    case SECOND_OPTION:
      writeText(instructions1, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
      switchColor(1.0, 1.0, 0.0);
      writeText(instructions2 + " (Press enter)", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      switchColor(1.0, 1.0, 1.0);
      writeText(instructions3, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      writeText(instructions4, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
      writeText(exit, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-395);
      break;
    case THIRD_OPTION:
      writeText(instructions1, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
      writeText(instructions2, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      switchColor(1.0, 1.0, 0.0);
      writeText(instructions3 + " (Press enter)", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      switchColor(1.0, 1.0, 1.0);
      writeText(instructions4, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
      writeText(exit, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-395);
      break;
    case FOURTH_OPTION:
      writeText(instructions1, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
      writeText(instructions2, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      writeText(instructions3, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      switchColor(1.0, 1.0, 0.0);
      writeText(instructions4 + " (Press enter)", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
      switchColor(1.0, 1.0, 1.0);
      writeText(exit, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-395);
      break;
    default:
      writeText(instructions1, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
      writeText(instructions2, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      writeText(instructions3, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      writeText(instructions4, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
      switchColor(1.0, 1.0, 0.0);
      writeText(exit, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-395);
      break;
    }

  glutSwapBuffers();
}

void displayInstructions(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  string firstTitle = "Game keymaps";
  string keymapsInstructions[11] = {
    "Player 1:",
    " [ W ] - Up",
    " [ S ] - Down",
    " [ A ] - Left",
    " [ D ] - Right",
    "",
    "Player 2:",
    " [ ArrowUp ] - Up",
    " [ ArrowDown ] - Down",
    " [ ArrowLeft ] - Left",
    " [ ArrowRight ] - Right"
  };
  string secondTitle = "Tutorial";
  string tutorial[8] = {
    "Each player starts at a point on the",
    "screen and starts moving. Move your bike",
    "smartly, your bike leaves a trail that your",
    "opponent can crash into (and you too, ",
    "BEWARE!).",
    "The game consists of moving around the scenario",
    "with the objective of forcing your opponent to",
    "collide with your trail and thus win the game."
  };

  switchColor(1.0, 1.0, 0.0);
  writeText(firstTitle, WINDOW_WIDTH/2 - 350, WINDOW_HEIGHT-125);
  writeText(secondTitle, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-125);

  switchColor(0.01, 0.24, 0.85);
  writeText(keymapsInstructions[0], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (0*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(keymapsInstructions[1], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (1*20));
  writeText(keymapsInstructions[2], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (2*20));
  writeText(keymapsInstructions[3], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (3*20));
  writeText(keymapsInstructions[4], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (4*20));
  writeText(keymapsInstructions[5], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (5*20));
  switchColor(1.0, 0.17, 0.05);
  writeText(keymapsInstructions[6], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (6*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(keymapsInstructions[7], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (7*20));
  writeText(keymapsInstructions[8], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (8*20));
  writeText(keymapsInstructions[9], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (9*20));
  writeText(keymapsInstructions[10], WINDOW_WIDTH/2 - 340, WINDOW_HEIGHT-150 - (10*20));


  writeText(tutorial[0], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (0*20));
  writeText(tutorial[1], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (1*20));
  writeText(tutorial[2], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (2*20));
  writeText(tutorial[3], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (3*20));
  switchColor(1.0, 0.0, 0.0);
  writeText(tutorial[4], WINDOW_WIDTH/2 + 268, WINDOW_HEIGHT-150 - (3*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(tutorial[5], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (4*20));
  writeText(tutorial[6], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (5*20));
  writeText(tutorial[7], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (6*20));

  writeText("Press esc to back", WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-450);

  glutSwapBuffers();
}

void writeText(string text, int x, int y){
  glRasterPos2f(x, y);
  for(int i = 0; i < (int)text.length(); i++){
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
  }
}

void switchColor(float r, float g, float b){
  glColor3f(r, g, b);
}