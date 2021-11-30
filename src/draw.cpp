#include "draw.h"
#include "parts.h"
#include "useful_macros.h"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>

void draw::all() {
    draw::axis();
    draw::river();
    draw::bridge();
    draw::bank();
    draw::buildings();
}

void draw::axis() {
    glPushMatrix();
    glBegin(GL_LINES); {
        glColor3f ( 1.0f, 0.0f, 0.0f );
        glVertex3f( 1.0f, 0.0f, 0.0f );
        glVertex3f( 0.0f, 0.0f, 0.0f );

        glColor3f ( 0.0f, 1.0f, 0.0f );
        glVertex3f( 0.0f, 1.0f, 0.0f );
        glVertex3f( 0.0f, 0.0f, 0.0f );

        glColor3f ( 0.0f, 0.0f, 1.0f );
        glVertex3f( 0.0f, 0.0f, 1.0f );
        glVertex3f( 0.0f, 0.0f, 0.0f );
    } glEnd();
    glPopMatrix();
}

void draw::river() {
    glColor3f(.5f, .5f, 1.0f);
    const float field_size = 22;
    glBegin(GL_QUADS); {
        glVertex3d(field_size / 2, 0, field_size / 2);
        glVertex3d(field_size / 2, 0, -field_size / 2);
        glVertex3d(-field_size / 2, 0, -field_size / 2);
        glVertex3d(-field_size / 2, 0, field_size / 2);
    } glEnd();
}

void draw::bridge() {
    glPushMatrix();

    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslated(0, 0.9, 0);
    glRotated(45, 0, 1, 0);
    REP(i, 2) {
        parts::box(1.2, 0.2, 10);
        glRotated(90, 0, 1, 0);
    }

    glPopMatrix();
}

void draw::bank() {
    glPushMatrix();
    const double sx = 10, sz = 10, h = 1;
    const double outer_r = 2.5, inner_r = 1;
    const int pts = 40;
    const double dtheta = M_PI / 2 / pts;
    const double river_width = 2;

    REP(_, 4) {
        glPushMatrix();
        glTranslated(river_width / 2, 0, river_width / 2);

        glBegin(GL_QUADS); {

            glColor3f(.5f, 1.0f, .5f);

            glVertex3d(outer_r - inner_r, h, sz);
            glVertex3d(outer_r - inner_r, h, outer_r);
            glVertex3d(0, 0, outer_r);
            glVertex3d(0, 0, sz);

            REP(i, pts) {
                double theta1 = dtheta * i;
                double theta2 = dtheta * (i + 1);
                glVertex3d(outer_r - inner_r * std::sin(theta1), h, outer_r - inner_r * std::cos(theta1));
                glVertex3d(outer_r - inner_r * std::sin(theta2), h, outer_r - inner_r * std::cos(theta2));
                glVertex3d(outer_r * (1 - std::sin(theta2)), 0, outer_r * (1 - std::cos(theta2)));
                glVertex3d(outer_r * (1 - std::sin(theta1)), 0, outer_r * (1 - std::cos(theta1)));
            }

            glVertex3d(sx, h, outer_r - inner_r);
            glVertex3d(outer_r, h, outer_r - inner_r);
            glVertex3d(outer_r, 0, 0);
            glVertex3d(sx, 0, 0);

            glColor3f(0.7f, 0.7f, 0.7f);
            glVertex3d(outer_r, h, outer_r);
            glVertex3d(outer_r, h, sz);
            glVertex3d(sx, h, sz);
            glVertex3d(sx, h, outer_r);

            glVertex3d(outer_r, h, outer_r);
            glVertex3d(outer_r, h, outer_r - inner_r);
            glVertex3d(sx, h, outer_r - inner_r);
            glVertex3d(sx, h, outer_r);

            glVertex3d(outer_r, h, outer_r);
            glVertex3d(outer_r, h, sz);
            glVertex3d(outer_r - inner_r, h, sz);
            glVertex3d(outer_r - inner_r, h, outer_r);

            glVertex3d(sx, 0, sz);
            glVertex3d(sx, h, sz);
            glVertex3d(outer_r - inner_r, h, sz);
            glVertex3d(0, 0, sz);

            glVertex3d(sx, 0, sz);
            glVertex3d(sx, h, sz);
            glVertex3d(sx, h, outer_r - inner_r);
            glVertex3d(sx, 0, 0);

        } glEnd();

        glBegin(GL_TRIANGLES); {
            REP(i, pts) {
                double theta1 = dtheta * i;
                double theta2 = dtheta * (i + 1);
                glVertex3d(outer_r - inner_r * std::sin(theta1), h, outer_r - inner_r * std::cos(theta1));
                glVertex3d(outer_r - inner_r * std::sin(theta2), h, outer_r - inner_r * std::cos(theta2));
                glVertex3d(outer_r, h, outer_r);
            }
        } glEnd();

        glPopMatrix();

        glRotated(90, 0, 1, 0);
    }
    glPopMatrix();
}

void draw::buildings() {
    glPushMatrix();
    glColor3f(.3f, .3f, .3f);
    REP(_, 4) {
        glPushMatrix();
        glTranslated(5, 0, 5);
        int len = 5;
        std::vector<vertexv> v {
                {0, 0, 0},
                {0, 0, len},
                {len, 0, len},
                {len, 0, 0},
        };
        parts::pillar(v, 0, 5, 0);
        glPopMatrix();
        glRotated(90, 0, 1, 0);
    }
    glPopMatrix();
}