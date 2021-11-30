#include <iostream>

#include "useful_macros.h"
#include "draw.h"
#include "camera.h"

camera cam(0, 0);

using namespace std;

void display() {
    cam.apply();


    draw::all();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.58, 0.75, 0.92, 0);
    glEnable(GL_DEPTH_TEST);
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