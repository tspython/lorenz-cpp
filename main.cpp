#include <GL/glut.h>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 800;

const float h = 0.01;
const float a = 10.0;
const float b = 28.0;
const float c = 8.0 / 3.0;

float x = 1.0;
float y = 1.0;
float z = 1.0;

float angle_x = 0.0;
float angle_y = 0.0;
float angle_z = 0.0;

int mouse_x = 0;
int mouse_y = 0;
bool mouse_left_down = false;

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      mouse_left_down = true;
      mouse_x = x;
      mouse_y = y;
    } else {
      mouse_left_down = false;
    }
  }
}

void motion(int x, int y) {
  if (mouse_left_down) {
    angle_x += (y - mouse_y) / 2.0;
    angle_y += (x - mouse_x) / 2.0;
    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(angle_x, 1.0, 0.0, 0.0);
  glRotatef(angle_y, 0.0, 1.0, 0.0);
  glRotatef(angle_z, 0.0, 0.0, 1.0);

  glBegin(GL_POINTS);
  for (int i = 0; i < 10000; i++) {
    float dx = a * (y - x);
    float dy = x * (b - z) - y;
    float dz = x * y - c * z;
    x += dx * h;
    y += dy * h;
    z += dz * h;
    glVertex3f(x, y, z);
  }
  glEnd();

  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Lorenz Attractor");
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-30.0, 30.0, -30, 30.0, -30.0, 30.0);
glEnable(GL_DEPTH_TEST);
glutDisplayFunc(display);
glutMouseFunc(mouse);
glutMotionFunc(motion);
glutMainLoop();
return 0;
}
