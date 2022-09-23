#include <iostream>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <Windows.h>
#include <MMSystem.h>

#include "./classes/Player.h"
#include "./classes/Computer.h"
#include "./libraries/OBJLoader.h"
#include "./libraries/gameFunctions.h"

using namespace std;

// Main defines
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 30

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
#define GAME_OVER_SCREEN 3

// Language identifiers defines
#define ENGLISH 0
#define PORTUGUESE 1

// Global variables
int optionSelected = FIRST_OPTION; // Option selected in welcome screen
bool isInWelcomeScreen = true; // Flag to check if the game is in welcome screen
bool isInInstructionsScreen = false; // Flag to check if the game is in instructions screen
bool isInGame = false; // Flag to check if the game is in game screen
bool isInGameOverScreen = false; // Flag to check if the game is in game over screen
int language = ENGLISH; // Language selected in welcome screen
int windowWidth = WINDOW_WIDTH; // Window width
int windowHeight = WINDOW_HEIGHT; // Window height
GLuint ducati; // Ducati object model
Player* player1 = new Player(); // Player 1
Player* player2 = new Player(); // Player 2
Computer* pc = new Computer(); // Computer 
int player1Direction; // Player 1 direction
int player2Direction; // Player 2 direction
bool gameover = false; // Flag to check if the game is over
bool playerIsWinner = false; // Flag to check who is the winner | true = player 1 | false = player 2
bool hasPlayer2 = false; // Flag to check if the game is single player or versus computer
int score1 = 0; // Player 1 score
int score2 = 0; // Player 2 score

void init(void);
void reset();
void resetPlayers(void);
void reshape(int w, int h);

// Display functions
void welcomeDisplay_EN(void);
void welcomeDisplay_PTBR(void);
  void writeText(string text, int x, int y);
  void switchColor(float r, float g, float b);
void displayInstructions_EN(void);
void displayInstructions_PTBR(void);
  void writeInstructions(void);
void displayGameOver_EN(void);
void displayGame2Players(void);

void keyboard(unsigned char key, int x, int y);
  void changeScreen(int identifier);
void processSpecialKeys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void timer(int value);
void idle(int value);

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
  glutSpecialFunc(processSpecialKeys);\

  glutMouseFunc(mouse);

  glutTimerFunc(0, idle, 0);

  ducati = loadObj("./models/38-ducati/Ducati/x-bikerduc.obj");
  // sndPlaySound(TEXT("./sounds/theme.wav"), SND_ASYNC | SND_LOOP);

  glutMainLoop();

  return 0;
}


void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0); 
  resetPlayers();
}

void reset() {
  resetPlayers();
  gameover = false;
  score1 = 0;
  score2 = 0;
}

void resetPlayers(){
  player1->setCoordenate(-INITIAL_COORDENATE_X, INITIAL_COORDENATE_Y);
  player2->setCoordenate(INITIAL_COORDENATE_X, INITIAL_COORDENATE_Y);
  pc->setCoordenate(INITIAL_COORDENATE_X, INITIAL_COORDENATE_Y);
  player1->resetTrail();
  player2->resetTrail();
  pc->resetTrail();
  player1Direction = 5;
  player2Direction = LEFT;
  pc->setActualDirection(LEFT);
  gameover = false;
}

void reshape(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  windowWidth = w;
  windowHeight = h;
  glViewport(0, 0, w, h); 

  glOrtho(0, w, 0, h, -1 ,1);

	glMatrixMode(GL_MODELVIEW);
}

void reshapeInGame(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  windowWidth = w;
  windowHeight = h;

  glViewport(0, 0, w, h); 

  gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.0, 170.0);
  gluLookAt(30.0, -150.0, 150.0,
            0.0, 0.0, 0.0, 
            0.0, 2.0, 3.0);

	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case ESCAPE:
      if(isInInstructionsScreen || isInGameOverScreen) {
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
            hasPlayer2 = true;
            changeScreen(IN_GAME_SCREEN);
            break;
          case SECOND_OPTION:
            cout << "Second option selected" << endl;
            hasPlayer2 = false;
            changeScreen(IN_GAME_SCREEN);
            break;
          case THIRD_OPTION:
            cout << "Third option selected" << endl;
            hasPlayer2 = false;
            changeScreen(IN_GAME_SCREEN);
            break;
          case FOURTH_OPTION:
            changeScreen(INSTRUCTIONS_SCREEN);
            break;
        }
      } else if (isInGameOverScreen) {
        changeScreen(IN_GAME_SCREEN);
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
        if(player1Direction != DOWN) {
          player1Direction = UP;
          // player1->move(UP);
        }
        glutPostRedisplay();
      }
      break;
    case A_KEY:
      if(isInGame){
        cout << "Player 1 LEFT" << endl;
        if(player1Direction != RIGHT) {
          player1Direction = LEFT;
          // player1->move(LEFT);
        }
        glutPostRedisplay();
      }
      break;
    case S_KEY:
      if(isInGame){
        cout << "Player 1 DOWN" << endl;
        if(player1Direction != UP) {
          player1Direction = DOWN;
          // player1->move(DOWN);
        }
        glutPostRedisplay();
      }
      break;
    case D_KEY:
      if(isInGame){
        cout << "Player 1 RIGHT" << endl;
        if(player1Direction != LEFT) {
          player1Direction = RIGHT;
          // player1->move(RIGHT);
        }
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
        if(player2Direction != DOWN){
          player2Direction = UP;
        }
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
        if(player2Direction != UP){
          player2Direction = DOWN;
        }
      }
      glutPostRedisplay();
      break;
    case GLUT_KEY_LEFT:
      if(isInGame){
        cout << "Player 2 LEFT" << endl;
        if(player2Direction != RIGHT){
          player2Direction = LEFT;
        }
      }
      glutPostRedisplay();
      break;
    case GLUT_KEY_RIGHT:
      if(isInGame){
        cout << "Player 2 RIGHT" << endl;
        if(player2Direction != LEFT){
          player2Direction = RIGHT;
        }
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
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // reshape(windowWidth, windowHeight);
  // renderScenarioOrtho(windowWidth, windowHeight);
  // reshapeInGame(windowWidth, windowHeight);

  renderScenarioPerspective(windowWidth, windowHeight);

  // player1->render(ducati, 0.01, 0.24, 0.85, 0.15, 0.15, 0.15);
  // player2->render(ducati, 1.0, 0.17, 0.05, 0.15, 0.15, 0.15);
  // player1->render(ducati, 0.01, 0.24, 0.85, 0.4, 0.4, 0.4);
  // player2->render(ducati, 1.0, 0.17, 0.05, 0.4, 0.4, 0.4);

  player1->renderSphere(0.01, 0.24, 0.85, 1.2, 1.2, 1.2);
  hasPlayer2 
    ? player2->renderSphere(1.0, 0.17, 0.05, 1.2, 1.2, 1.2) 
    : pc->renderSphere(1.0, 0.17, 0.05, 1.2, 1.2, 1.2);

  // cout << "Player1 xy(" << player1->getXCoordenate() << "," << player1->getYCoordenate() << ")" << endl;
  // player1->showTrail();
  // cout << "Player2 xy(" << player2->getXCoordenate() << "," << player2->getYCoordenate() << ")" << endl;
  // player2->showTrail();

  if(!hasPlayer2) {
    // computerAction(pc, player1);
    // pc->showTrail();
  }

  int code = hasPlayer2 
              ? hadSomeCollision(player1, player2)
              : hadSomeCollision(player1, pc);

  switch(code){
    case NO_COLLISION:
      break;
    case COLLISION_PLAYER_1:
      cout << "Player 1 colidiu" << endl;
      gameover = true;
      score2 += 1;
      playerIsWinner = false;
      changeScreen(GAME_OVER_SCREEN);
      break;
    case COLLISION_PLAYER_2:
      cout << "Player 2 colidiu" << endl;
      gameover = true;
      playerIsWinner = true;
      score1 += 1;
      changeScreen(GAME_OVER_SCREEN);
      break;
    default:
      break;
  }

  glutSwapBuffers();
}

void welcomeDisplay_EN(){
  if(isInWelcomeScreen) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0);
    string welcome = "Welcome to Tron Game";
    string instructions1 = "[ 1 ] - Start Two Players Game";
    string instructions2 = "[ 2 ] - Start Game versus PC";
    string instructions3 = "[ 3 ] - Start Game versus PC (Hard)";
    string instructions4 = "[ 4 ] - Tutorial / Instructions";
    string exit = "[ ESC ] - Exit";

    writeText(welcome, windowWidth/2 - 100, windowHeight-225);

    switch(optionSelected){
      case FIRST_OPTION:
        switchColor(1.0, 1.0, 0.0);
        writeText(instructions1 + " (Press enter)", windowWidth/2 - 150, windowHeight-275);
        switchColor(1.0, 1.0, 1.0);
        writeText(instructions2, windowWidth/2 - 150, windowHeight-300);
        writeText(instructions3, windowWidth/2 - 150, windowHeight-325);
        writeText(instructions4, windowWidth/2 - 150, windowHeight-350);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      case SECOND_OPTION:
        writeText(instructions1, windowWidth/2 - 150, windowHeight-275);
        switchColor(1.0, 1.0, 0.0);
        writeText(instructions2 + " (Press enter)", windowWidth/2 - 150, windowHeight-300);
        switchColor(1.0, 1.0, 1.0);
        writeText(instructions3, windowWidth/2 - 150, windowHeight-325);
        writeText(instructions4, windowWidth/2 - 150, windowHeight-350);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      case THIRD_OPTION:
        writeText(instructions1, windowWidth/2 - 150, windowHeight-275);
        writeText(instructions2, windowWidth/2 - 150, windowHeight-300);
        switchColor(1.0, 1.0, 0.0);
        writeText(instructions3 + " (Press enter)", windowWidth/2 - 150, windowHeight-325);
        switchColor(1.0, 1.0, 1.0);
        writeText(instructions4, windowWidth/2 - 150, windowHeight-350);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      case FOURTH_OPTION:
        writeText(instructions1, windowWidth/2- 150, windowHeight-275);
        writeText(instructions2, windowWidth/2 - 150, windowHeight-300);
        writeText(instructions3, windowWidth/2 - 150, windowHeight-325);
        switchColor(1.0, 1.0, 0.0);
        writeText(instructions4 + " (Press enter)", windowWidth/2 - 150, windowHeight-350);
        switchColor(1.0, 1.0, 1.0);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      default:
        writeText(instructions1, windowWidth/2 - 150, windowHeight-275);
        writeText(instructions2, windowWidth/2 - 150, windowHeight-300);
        writeText(instructions3, windowWidth/2 - 150, windowHeight-325);
        writeText(instructions4, windowWidth/2 - 150, windowHeight-350);
        switchColor(1.0, 1.0, 0.0);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      }

    glutSwapBuffers();
  }
}

void welcomeDisplay_PTBR(){
  if(isInWelcomeScreen) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0);
    string welcome = "Bem-vindo ao Tron Game";
    string instructions1 = "[ 1 ] - Jogar com 2 jogadores";
    string instructions2 = "[ 2 ] - Jogar contra o computador";
    string instructions3 = "[ 3 ] - Jogar contra o computador (Dificil)";
    string instructions4 = "[ 4 ] - Tutorial / Instrucoes";
    string exit = "[ ESC ] - Sair";

    writeText(welcome, windowWidth/2 - 100, windowHeight-225);

    switch(optionSelected){
      case FIRST_OPTION:
        switchColor(1.0, 1.0, 0.0);
        writeText(instructions1 + " (Pressione enter)", windowWidth/2 - 150, windowHeight-275);
        switchColor(1.0, 1.0, 1.0);
        writeText(instructions2, windowWidth/2 - 150, windowHeight-300);
        writeText(instructions3, windowWidth/2 - 150, windowHeight-325);
        writeText(instructions4, windowWidth/2 - 150, windowHeight-350);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      case SECOND_OPTION:
        writeText(instructions1, windowWidth/2 - 150, windowHeight-275);
        switchColor(1.0, 1.0, 0.0);
        writeText(instructions2 + " (Pressione enter)", windowWidth/2 - 150, windowHeight-300);
        switchColor(1.0, 1.0, 1.0);
        writeText(instructions3, windowWidth/2 - 150, windowHeight-325);
        writeText(instructions4, windowWidth/2 - 150, windowHeight-350);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      case THIRD_OPTION:
        writeText(instructions1, windowWidth/2 - 150, windowHeight-275);
        writeText(instructions2, windowWidth/2 - 150, windowHeight-300);
        switchColor(1.0, 1.0, 0.0);
        writeText(instructions3 + " (Pressione enter)", windowWidth/2 - 150, windowHeight-325);
        switchColor(1.0, 1.0, 1.0);
        writeText(instructions4, windowWidth/2 - 150, windowHeight-350);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      case FOURTH_OPTION:
        writeText(instructions1, windowWidth/2- 150, windowHeight-275);
        writeText(instructions2, windowWidth/2 - 150, windowHeight-300);
        writeText(instructions3, windowWidth/2 - 150, windowHeight-325);
        switchColor(1.0, 1.0, 0.0);
        writeText(instructions4 + " (Pressione enter)", windowWidth/2 - 150, windowHeight-350);
        switchColor(1.0, 1.0, 1.0);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      default:
        writeText(instructions1, windowWidth/2 - 150, windowHeight-275);
        writeText(instructions2, windowWidth/2 - 150, windowHeight-300);
        writeText(instructions3, windowWidth/2 - 150, windowHeight-325);
        writeText(instructions4, windowWidth/2 - 150, windowHeight-350);
        switchColor(1.0, 1.0, 0.0);
        writeText(exit, windowWidth/2 - 80, windowHeight-395);
        break;
      }

    glutSwapBuffers();
  }
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
  writeText(firstTitle, windowWidth/2 - 350, windowHeight-125);
  writeText(secondTitle, windowWidth/2 - 80, windowHeight-125);

  switchColor(0.01, 0.24, 0.85);
  writeText(keymapsInstructions[0], windowWidth/2 - 340, windowHeight-150 - (0*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(keymapsInstructions[1], windowWidth/2 - 340, windowHeight-150 - (1*20));
  writeText(keymapsInstructions[2], windowWidth/2 - 340, windowHeight-150 - (2*20));
  writeText(keymapsInstructions[3], windowWidth/2 - 340, windowHeight-150 - (3*20));
  writeText(keymapsInstructions[4], windowWidth/2 - 340, windowHeight-150 - (4*20));
  writeText(keymapsInstructions[5], windowWidth/2 - 340, windowHeight-150 - (5*20));
  switchColor(1.0, 0.17, 0.05);
  writeText(keymapsInstructions[6], windowWidth/2 - 340, windowHeight-150 - (6*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(keymapsInstructions[7], windowWidth/2 - 340, windowHeight-150 - (7*20));
  writeText(keymapsInstructions[8], windowWidth/2 - 340, windowHeight-150 - (8*20));
  writeText(keymapsInstructions[9], windowWidth/2 - 340, windowHeight-150 - (9*20));
  writeText(keymapsInstructions[10], windowWidth/2 - 340, windowHeight-150 - (10*20));


  writeText(tutorial[0], windowWidth/2 -70, windowHeight-150 - (0*20));
  writeText(tutorial[1], windowWidth/2 -70, windowHeight-150 - (1*20));
  writeText(tutorial[2], windowWidth/2 -70, windowHeight-150 - (2*20));
  writeText(tutorial[3], windowWidth/2 -70, windowHeight-150 - (3*20));
  switchColor(1.0, 0.0, 0.0);
  writeText(tutorial[4], windowWidth/2 + 190, windowHeight-150 - (3*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(tutorial[5], windowWidth/2 + 290, windowHeight-150 - (3*20));
  writeText(tutorial[6], windowWidth/2 -70, windowHeight-150 - (4*20));
  writeText(tutorial[7], windowWidth/2 -70, windowHeight-150 - (5*20));
  writeText(tutorial[8], windowWidth/2 -70, windowHeight-150 - (6*20));
  writeText(tutorial[9], windowWidth/2 -70, windowHeight-150 - (7*20));
  writeText(tutorial[10], windowWidth/2 -70, windowHeight-150 - (8*20));

  writeText("Press esc to back", windowWidth/2 - 80, windowHeight-450);

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
  writeText(firstTitle, windowWidth/2 - 370, windowHeight-125);
  writeText(secondTitle, windowWidth/2 - 40, windowHeight-125);

  switchColor(0.01, 0.24, 0.85);
  writeText(keymapsInstructions[0], windowWidth/2 - 360, windowHeight-150 - (0*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(keymapsInstructions[1], windowWidth/2 - 360, windowHeight-150 - (1*20));
  writeText(keymapsInstructions[2], windowWidth/2 - 360, windowHeight-150 - (2*20));
  writeText(keymapsInstructions[3], windowWidth/2 - 360, windowHeight-150 - (3*20));
  writeText(keymapsInstructions[4], windowWidth/2 - 360, windowHeight-150 - (4*20));
  writeText(keymapsInstructions[5], windowWidth/2 - 360, windowHeight-150 - (5*20));
  switchColor(1.0, 0.17, 0.05);
  writeText(keymapsInstructions[6], windowWidth/2 - 360, windowHeight-150 - (6*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(keymapsInstructions[7], windowWidth/2 - 360, windowHeight-150 - (7*20));
  writeText(keymapsInstructions[8], windowWidth/2 - 360, windowHeight-150 - (8*20));
  writeText(keymapsInstructions[9], windowWidth/2 - 360, windowHeight-150 - (9*20));
  writeText(keymapsInstructions[10], windowWidth/2 - 360, windowHeight-150 - (10*20));


  writeText(tutorial[0], windowWidth/2 - 30, windowHeight-150 - (0*20));
  writeText(tutorial[1], windowWidth/2 - 30, windowHeight-150 - (1*20));
  writeText(tutorial[2], windowWidth/2 - 30, windowHeight-150 - (2*20));
  writeText(tutorial[3], windowWidth/2 - 30, windowHeight-150 - (3*20));
  writeText(tutorial[4], windowWidth/2 - 30, windowHeight-150 - (4*20));
  switchColor(1.0, 0.0, 0.0);
  writeText(tutorial[5], windowWidth/2 + 110, windowHeight-150 - (4*20));
  switchColor(1.0, 1.0, 1.0);
  writeText(tutorial[6], windowWidth/2 + 180, windowHeight-150 - (4*20));
  writeText(tutorial[7], windowWidth/2 - 30, windowHeight-150 - (5*20));
  writeText(tutorial[8], windowWidth/2 - 30, windowHeight-150 - (6*20));
  writeText(tutorial[9], windowWidth/2 - 30, windowHeight-150 - (7*20));
  writeText(tutorial[10], windowWidth/2 - 30, windowHeight-150 - (8*20));
  writeText(tutorial[11], windowWidth/2 - 30, windowHeight-150 - (9*20));

  writeText("Pressione esc para voltar", windowWidth/2 - 80, windowHeight-450);

  glutSwapBuffers();
}

void displayGameOver_EN(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  string gameOver = "Game Over";
  string winner;
  if(playerIsWinner){
    winner = "Winner: Player 1";
  } else {
    if(hasPlayer2){
      winner = "Winner: Player 2";
    } else {
      winner = "Winner: Computer";
    }
  }

  char player1Score[30];
  char player2Score[30];
  hasPlayer2 ? sprintf(player1Score, "Player 1: %d", score1) : sprintf(player1Score, "Player: %d", score1);
  hasPlayer2 ? sprintf(player2Score, "Player 2: %d", score2) : sprintf(player2Score, "Computer: %d", score2);; 

  string scores[3] = {
    "Scores:",
    player1Score,
    player2Score
  };
  string instructions = "Press esc to back to menu or press enter to play again";

  switchColor(1.0, 0.0, 0.0);
  writeText(gameOver, windowWidth/2 - 40, windowHeight-230);
  switchColor(0, 1.0, 0);
  writeText(winner, windowWidth/2 - 60, windowHeight-255);
  switchColor(1.0, 1.0, 0);
  writeText(scores[0], windowWidth/2 - 60, windowHeight-305);
  switchColor(1.0, 1.0, 1.0);
  writeText(scores[1], windowWidth/2 - 55, windowHeight-330);
  writeText(scores[2], windowWidth/2 - 55, windowHeight-355);
  writeText(instructions, windowWidth/2 - 220, windowHeight-450);

  glutSwapBuffers();
}

void displayGameOver_PTBR(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  string gameOver = "Fim de jogo";
  string winner;
  if(playerIsWinner){
    winner = "Vencedor: Jogador 1";
  } else {
    if(hasPlayer2){
      winner = "Vencedor: Jogador 2";
    } else {
      winner = "Vencedor: Computador";
    }
  }

  char player1Score[30];
  char player2Score[30];
  hasPlayer2 ? sprintf(player1Score, "Jogador 1: %d", score1) : sprintf(player1Score, "Jogador: %d", score1);
  hasPlayer2 ? sprintf(player2Score, "Jogador 2: %d", score2) : sprintf(player2Score, "Computador: %d", score2);
  string scores[3] = {
    "Placar:",
    player1Score,
    player2Score
  };
  string instructions = "Pressione esc para voltar para o menu ou pressione enter para jogar de novo";

  switchColor(1.0, 0.0, 0.0);
  writeText(gameOver, windowWidth/2 - 40, windowHeight-230);
  switchColor(0, 1.0, 0);
  writeText(winner, windowWidth/2 - 60, windowHeight-255);
  switchColor(1.0, 1.0, 0);
  writeText(scores[0], windowWidth/2 - 60, windowHeight-305);
  switchColor(1.0, 1.0, 1.0);
  writeText(scores[1], windowWidth/2 - 55, windowHeight-330);
  writeText(scores[2], windowWidth/2 - 55, windowHeight-355);
  writeText(instructions, windowWidth/2 - 320, windowHeight-450);

  glutSwapBuffers();
}

void timer(int value){
  if(isInGame && !gameover){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0);

    switch(player1Direction){
      case UP:
        player1->move(UP);
        break;
      case DOWN:
        player1->move(DOWN);
        break;
      case LEFT:
        player1->move(LEFT);
        break;
      case RIGHT:
        player1->move(RIGHT);
        break;
      default:
        break;
    }

    if(hasPlayer2){
      switch(player2Direction){
        case UP:
          player2->move(UP);
          break;
        case DOWN:
          player2->move(DOWN);
          break;
        case LEFT:
          player2->move(LEFT);
          break;
        case RIGHT:
          player2->move(RIGHT);
          break;
        default:
          break;
      }
    } else {
      pc->move(pc->getActualDirection());
    }
    
  }
}

void idle(int value){
  glutTimerFunc(1000/FPS, idle, 0);
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
      isInGameOverScreen = false;
      language == ENGLISH 
        ? glutDisplayFunc(welcomeDisplay_EN) 
        : glutDisplayFunc(welcomeDisplay_PTBR);
      glutTimerFunc(0, idle, 0);
      glutReshapeFunc(reshape);
      reshape(windowWidth, windowHeight);
      reset();
      glutPostRedisplay();
      break;
    case INSTRUCTIONS_SCREEN:
      isInWelcomeScreen = false;
      isInInstructionsScreen = true;
      isInGame = false;
      isInGameOverScreen = false;
      language == ENGLISH 
        ? glutDisplayFunc(displayInstructions_EN) 
        : glutDisplayFunc(displayInstructions_PTBR);
      glutTimerFunc(0, idle, 0);
      glutReshapeFunc(reshape);
      reshape(windowWidth, windowHeight);
      glutPostRedisplay();
      break;
    case IN_GAME_SCREEN:
      isInWelcomeScreen = false;
      isInInstructionsScreen = false;
      isInGame = true;
      isInGameOverScreen = false;
      glutReshapeFunc(reshapeInGame);
      glutDisplayFunc(displayGame2Players);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glutSwapBuffers();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glutTimerFunc(2000, timer, 0);
      reshapeInGame(windowWidth, windowHeight);
      glutPostRedisplay();
      break;
    case GAME_OVER_SCREEN:
      isInWelcomeScreen = false;
      isInInstructionsScreen = false;
      isInGame = false;
      isInGameOverScreen = true;
      language == ENGLISH 
        ? glutDisplayFunc(displayGameOver_EN) 
        : glutDisplayFunc(displayGameOver_PTBR);
      resetPlayers();
      glutTimerFunc(0, idle, 0);
      glutReshapeFunc(reshape);
      reshape(windowWidth, windowHeight);
      glutPostRedisplay();
      break;
    default:
      break;
  }
}