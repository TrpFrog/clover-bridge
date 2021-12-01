#include "useful_macros.h"
#include "draw.h"
#include "camera.h"

camera cam(0, 0);

using namespace std;

GLfloat light0pos[] = {  0.0, 20.0,  0.0, 1.0 };

void display() {
    cam.apply();

    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

    draw::all();

    glutSwapBuffers();
}

GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat gray[] = { 0.5, 0.5, 0.5, 1.0 };

void init() {
    glClearColor(0.58, 0.75, 0.92, 0);
    glEnable(GL_DEPTH_TEST);

    glCullFace(GL_FRONT);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, gray);
    glLightfv(GL_LIGHT2, GL_SPECULAR, gray);
}

void resize(int w, int h) {
    // Set the entire window a viewport
    glViewport(0, 0, w, h);
    // Init transformation matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspect = (double)w / (double)h;
    gluPerspective(30.0, aspect, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    cam.keyboard(key, x, y);
}

void mouse(int button, int state, int x, int y) {
    cam.mouse(button, state, x, y);
}

void mouse_wheel(int button, int dir, int x, int y) {
    cam.mouse_wheel(button, dir, x, y);
}

void motion(int x, int y) {
    cam.motion(x, y);
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInitWindowPosition(100, 100);

    int w = 800, h = 600;
    glutInitWindowSize(w, h);
    cam = camera(w, h);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);

    // animation
    glutIdleFunc(idle);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutReshapeFunc(resize);
    init();
    glutMainLoop();
}