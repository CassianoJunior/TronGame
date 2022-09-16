#include <iostream>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "./classes/Player.cpp"
#include "./libraries/OBJLoader.h"

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
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define L 108

// Direction identifiers defines
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Screen identifiers defines
#define WELCOME_SCREEN 0
#define INSTRUCTIONS_SCREEN 1
#define IN_GAME_SCREEN 2

// Language identifiers defines
#define ENGLISH 0
#define PORTUGUESE 1

// Global variables
int optionSelected = FIRST_OPTION;
bool isInWelcomeScreen = true;
bool isInInstructionsScreen = false;
bool isInGame = false;
int language = ENGLISH;


void init(void);
void reshape(int w, int h);
// Display functions
void welcomeDisplay_EN(void);
void welcomeDisplay_PTBR(void);
  void writeText(string text, int x, int y);
  void switchColor(float r, float g, float b);
void displayInstructions_EN(void);
void displayInstructions_PTBR(void);
  void writeInstructions(void);
void displayGame2Players(void);

void keyboard(unsigned char key, int x, int y);
  void changeScreen(int identifier);
void processSpecialKeys(int key, int x, int y);
void mouse(int button, int state, int x, int y);

GLuint ducati;

Player player1;
Player player2;

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Tron Game");

  init();

  glutReshapeFunc(reshape);
  glutDisplayFunc(welcomeDisplay_EN);

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(processSpecialKeys);

  glutMouseFunc(mouse);

  ducati = loadObj("./models/38-ducati/Ducati/x-bikerduc.obj");

  glutMainLoop();

  return 0;
}


void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0); 
  player1.setCoordenate(-40, 0);
  player2.setCoordenate(40, 0);
}

void reshape(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, w, h); 

  glOrtho(0, w, 0, h, -1 ,1);

	glMatrixMode(GL_MODELVIEW);
}

void reshapeInGame(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, w, h); 

  gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.0, 120.0);
  gluLookAt(0.0, 0.0, 100.0,
            0.0, 0.0, 0.0, 
            0.0, 2.0, 3.0);

	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case ESCAPE:
      if(isInInstructionsScreen) {
        changeScreen(WELCOME_SCREEN);
      } else {
        exit(0);
      }
      break;
    case ENTER:
      if (isInWelcomeScreen) {
        switch (optionSelected) {
          case FIRST_OPTION:
            cout << "First option selected" << endl;
            changeScreen(IN_GAME_SCREEN);
            break;
          case SECOND_OPTION:
            cout << "Second option selected" << endl;
            break;
          case THIRD_OPTION:
            cout << "Third option selected" << endl;
            break;
          case FOURTH_OPTION:
            changeScreen(INSTRUCTIONS_SCREEN);
            break;
        }
      }
      break;
    case L:
      if(isInWelcomeScreen){
        language == ENGLISH
        ? language = PORTUGUESE
        : language = ENGLISH;
        changeScreen(WELCOME_SCREEN);
      }
      break;
    case W_KEY:
      if(isInGame){
        cout << "Player 1 UP" << endl;
        player1.move(UP);
        glutPostRedisplay();
      }
      break;
    case A_KEY:
      if(isInGame){
        cout << "Player 1 LEFT" << endl;
        player1.move(LEFT);
        glutPostRedisplay();
      }
      break;
    case S_KEY:
      if(isInGame){
        cout << "Player 1 DOWN" << endl;
        player1.move(DOWN);
        glutPostRedisplay();
      }
      break;
    case D_KEY:
      if(isInGame){
        cout << "Player 1 RIGHT" << endl;
        player1.move(RIGHT);
        glutPostRedisplay();
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
      } else if(isInGame){
        cout << "Player 2 UP" << endl;
        player2.move(UP);
      }
      glutPostRedisplay();
      break;
    case GLUT_KEY_DOWN:
      if(isInWelcomeScreen){
        if(optionSelected == FOURTH_OPTION){
          optionSelected = FIRST_OPTION;
        }else{
          optionSelected++;
        }
      } else if(isInGame){
        cout << "Player 2 DOWN" << endl;
        player2.move(DOWN);
      }
      glutPostRedisplay();
      break;
    case GLUT_KEY_LEFT:
      if(isInGame){
        cout << "Player 2 LEFT" << endl;
        player2.move(LEFT);
      }
      glutPostRedisplay();
      break;
    case GLUT_KEY_RIGHT:
      if(isInGame){
        cout << "Player 2 RIGHT" << endl;
        player2.move(RIGHT);
      }
      glutPostRedisplay();
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


  // player1.render(ducati, 0.01, 0.24, 0.85, -2, -2, -20);
  // player2.render(ducati, 1.0, 0.17, 0.05, 2, 2, -20);

  player1.renderSphere(0.01, 0.24, 0.85, 1, 1, 1);
  player2.renderSphere(1.0, 0.17, 0.05, 1, 1, 1);

  cout << "Player1 xy(" << player1.getXCoordenate() << "," << player1.getYCoordenate() << ")" << endl;
  cout << "Player2 xy(" << player2.getXCoordenate() << "," << player2.getYCoordenate() << ")" << endl;

  glutSwapBuffers();
}

void welcomeDisplay_EN(){
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
      writeText(instructions1, WINDOW_WIDTH/2- 150, WINDOW_HEIGHT-275);
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

void welcomeDisplay_PTBR(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(1.0, 1.0, 1.0);
  string welcome = "Bem-vindo ao Tron Game";
  string instructions1 = "[ 1 ] - Jogar com 2 jogadores";
  string instructions2 = "[ 2 ] - Jogar contra o computador";
  string instructions3 = "[ 3 ] - Jogar contra o computador (Dificil)";
  string instructions4 = "[ 4 ] - Tutorial / Instrucoes";
  string exit = "[ ESC ] - Sair";

  writeText(welcome, WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT-225);

  switch(optionSelected){
    case FIRST_OPTION:
      switchColor(1.0, 1.0, 0.0);
      writeText(instructions1 + " (Pressione enter)", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
      switchColor(1.0, 1.0, 1.0);
      writeText(instructions2, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      writeText(instructions3, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      writeText(instructions4, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
      writeText(exit, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-395);
      break;
    case SECOND_OPTION:
      writeText(instructions1, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
      switchColor(1.0, 1.0, 0.0);
      writeText(instructions2 + " (Pressione enter)", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      switchColor(1.0, 1.0, 1.0);
      writeText(instructions3, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      writeText(instructions4, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
      writeText(exit, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-395);
      break;
    case THIRD_OPTION:
      writeText(instructions1, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-275);
      writeText(instructions2, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      switchColor(1.0, 1.0, 0.0);
      writeText(instructions3 + " (Pressione enter)", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      switchColor(1.0, 1.0, 1.0);
      writeText(instructions4, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
      writeText(exit, WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-395);
      break;
    case FOURTH_OPTION:
      writeText(instructions1, WINDOW_WIDTH/2- 150, WINDOW_HEIGHT-275);
      writeText(instructions2, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-300);
      writeText(instructions3, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-325);
      switchColor(1.0, 1.0, 0.0);
      writeText(instructions4 + " (Pressione enter)", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT-350);
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

void displayInstructions_EN(){
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

  string tutorial[11] = {
    "Each player starts at a point on the screen",
    "and starts moving to collide. Move your bike",
    "smartly, it leaves a trail that your opponent",
    "can crash into (and you too,",
    "BE CAREFUL!", ").",
    "The game consists of moving around the",
    "scenario with the objective of forcing your",
    "opponent to collide with your trail and",
    "thus win the game.",
    "Oh, watch out for the edges..."
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
  writeText(tutorial[4], WINDOW_WIDTH/2 + 190, WINDOW_HEIGHT-150 - (3*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(tutorial[5], WINDOW_WIDTH/2 + 290, WINDOW_HEIGHT-150 - (3*20));
  writeText(tutorial[6], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (4*20));
  writeText(tutorial[7], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (5*20));
  writeText(tutorial[8], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (6*20));
  writeText(tutorial[9], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (7*20));
  writeText(tutorial[10], WINDOW_WIDTH/2 -70, WINDOW_HEIGHT-150 - (8*20));

  writeText("Press esc to back", WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-450);

  glutSwapBuffers();
}

void displayInstructions_PTBR(){
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  string firstTitle = "Teclas do jogo";
  string keymapsInstructions[11] = {
    "Jogador 1:",
    " [ W ] - Cima",
    " [ S ] - Baixo",
    " [ A ] - Esquerda",
    " [ D ] - Direita",
    "",
    "Jogador 2:",
    " [ Seta para cima ] - Cima",
    " [ Seta para baixo ] - Baixo",
    " [ Seta para esquerda ] - Esquerda",
    " [ Seta para direita ] - Direita"
  };
  string secondTitle = "Tutorial";

  string tutorial[12] = {
      "Cada jogador surge em um ponto na tela",
      "e inicia a se mover para colidir. Mova",
      "sua moto de forma inteligente, ela deixa",
      "um rastro no qual seu oponente pode colidir",
      "(e voce tambem,", "CUIDADO!", ").",
      "O jogo consiste em movimentar-se pelo",
      "cenario com o objetivo de fazer seu",
      "oponente se colidir com o seu rastro e",
      "assim vencer o jogo.",
      "Ah, e cuidado com as bordas..."
    };

  switchColor(1.0, 1.0, 0.0);
  writeText(firstTitle, WINDOW_WIDTH/2 - 370, WINDOW_HEIGHT-125);
  writeText(secondTitle, WINDOW_WIDTH/2 - 40, WINDOW_HEIGHT-125);

  switchColor(0.01, 0.24, 0.85);
  writeText(keymapsInstructions[0], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (0*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(keymapsInstructions[1], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (1*20));
  writeText(keymapsInstructions[2], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (2*20));
  writeText(keymapsInstructions[3], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (3*20));
  writeText(keymapsInstructions[4], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (4*20));
  writeText(keymapsInstructions[5], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (5*20));
  switchColor(1.0, 0.17, 0.05);
  writeText(keymapsInstructions[6], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (6*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(keymapsInstructions[7], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (7*20));
  writeText(keymapsInstructions[8], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (8*20));
  writeText(keymapsInstructions[9], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (9*20));
  writeText(keymapsInstructions[10], WINDOW_WIDTH/2 - 360, WINDOW_HEIGHT-150 - (10*20));


  writeText(tutorial[0], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (0*20));
  writeText(tutorial[1], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (1*20));
  writeText(tutorial[2], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (2*20));
  writeText(tutorial[3], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (3*20));
  writeText(tutorial[4], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (4*20));
  switchColor(1.0, 0.0, 0.0);
  writeText(tutorial[5], WINDOW_WIDTH/2 + 110, WINDOW_HEIGHT-150 - (4*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(tutorial[6], WINDOW_WIDTH/2 + 180, WINDOW_HEIGHT-150 - (4*20));
  writeText(tutorial[7], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (5*20));
  writeText(tutorial[8], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (6*20));
  writeText(tutorial[9], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (7*20));
  writeText(tutorial[10], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (8*20));
  writeText(tutorial[11], WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT-150 - (9*20));

  writeText("Pressione esc para voltar", WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT-450);

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

void changeScreen(int identifier){
  switch(identifier){
    case WELCOME_SCREEN:
      isInWelcomeScreen = true;
      isInInstructionsScreen = false;
      isInGame = false;
      language == ENGLISH 
        ? glutDisplayFunc(welcomeDisplay_EN) 
        : glutDisplayFunc(welcomeDisplay_PTBR);
      glutPostRedisplay();
      break;
    case INSTRUCTIONS_SCREEN:
      isInWelcomeScreen = false;
      isInInstructionsScreen = true;
      isInGame = false;
      language == ENGLISH 
        ? glutDisplayFunc(displayInstructions_EN) 
        : glutDisplayFunc(displayInstructions_PTBR);
      glutPostRedisplay();
      break;
    case IN_GAME_SCREEN:
      isInWelcomeScreen = false;
      isInInstructionsScreen = false;
      isInGame = true;
      glutReshapeFunc(reshapeInGame);
      glutDisplayFunc(displayGame2Players);
      glutPostRedisplay();
      reshapeInGame(WINDOW_WIDTH, WINDOW_HEIGHT);
      break;
    default:
      break;
  }
}