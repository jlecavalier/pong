#include "pong.h"

// window size
int width = 500;
int height = 200;

// 60 frames every 1000 miliseconds gives 60 fps
int interval = 1000 / 60;

// Scoring
int score_left = 0;
int score_right = 0;

// Racket globals
int racket_width = 10;
int racket_height = 80;
int racket_speed = 3;
// left player
float racket_left_x = 10.0f;
float racket_left_y = 50.0f;
// right racket position
float racket_right_x = 480;
float racket_right_y = 50;

// keys
int keys[256];

// Draw a rectangle
void drawRect(float x, float y, float width, float height) {
  glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+width,y);
    glVertex2f(x+width,y+height);
    glVertex2f(x,y+height);
  glEnd();
}

// Allows us to draw text on the screen easily.
void drawText(float x, float y, const char* format , ...) {
  glWindowPos2f(x, y);
  char buf[LEN];
  char* ch=buf;
  va_list args;
  // Turn the params into a string
  va_start(args,format);
  vsnprintf(buf,LEN,format,args);
  va_end(args);
  // Display the characters one at a time
  // at the current raster position
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,*ch++);
}

// Enables drawing in 2d mode instead of 3d
void enable2D(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// Tells glut what to draw on the screen
void draw() {
  // clear everything
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // Here's where we draw the stuff
  // First, draw the scores for each player
  char scorestr[3];
  sprintf(scorestr,"%d:%d",score_left,score_right);
  drawText(width / 2 - 10, height - 15, scorestr);
  // Next, draw the position of each racket
  drawRect(racket_left_x,racket_left_y,racket_width,racket_height);
  drawRect(racket_right_x,racket_right_y,racket_width,racket_height);

  // swap the buffers to increase performance
  glutSwapBuffers();
}

// Get asynchronous keyboard state so we can update according
// To the user's input.
void keyboard() {
  Uint8 *state = SDL_GetKeyState(NULL);
  if (state[SDLK_UP]) {
  	printf("HELLO?");
  	racket_right_y += racket_speed;
  }
  if (state[SDLK_DOWN]) {
  	racket_right_y -= racket_speed;
  }
  if (state[SDLK_w]) {
  	racket_left_y += racket_speed;
  	printf("HELLO?");
  }
  if (state[SDLK_s]) {
  	racket_left_y -= racket_speed;
  }
}

// Tells glut how to update what the player sees based on what they do
void update(int value) {
  // update positions of rackets
  keyboard();

  // call update every 'interval' milliseconds.
  glutTimerFunc(interval, update, 0);

  // Redisplay the current frame when you get a chance
  glutPostRedisplay();
}

// Tells glut what to do when normal keys are pressed
void g_key(unsigned char ch,int x,int y) {
  // Exit when the user presses ESC
  if (ch == 27) {
  	exit(0);
  }
}

// Code starts running here.
int main(int argc, char** argv) {
  // Initialize opengl using glut
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("PONG");	

  glutSetKeyRepeat(0);
  glutIgnoreKeyRepeat(0);

  // glut callbacks
  glutDisplayFunc(draw);
  glutTimerFunc(interval, update, 0);
  glutKeyboardFunc(g_key);

  // setup scene with 2d mode
  enable2D(width, height);
  // color in white only
  glColor3f(1.0f, 1.0f, 1.0f);
  
  // start glut
  glutMainLoop();
  return 0;
}