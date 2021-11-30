//
// Created by つまみ on 2021/11/24.
//

#include "draw.h"

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <tuple>
#include "useful_macros.h"

using vertexv = std::tuple<GLdouble, GLdouble, GLdouble>;
using edge = std::pair<int, int>;

std::vector<vertexv> box_vertex(GLdouble x, GLdouble y, GLdouble z) {
    std::vector<vertexv> vertex = {
        {0, 0, 0},
        {0, y, 0},
        {x, y, 0},
        {x, 0, 0},
        {0, 0, z},
        {0, y, z},
        {x, y, z},
        {x, 0, z},
    };
    return vertex;
}


const std::vector<edge> box_edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4},
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},
};


std::vector<std::vector<int>> box_faces = {
        {0, 1, 2, 3},
        {1, 5, 6, 2},
        {5, 4, 7, 6},
        {4, 0, 3, 7},
        {4, 5, 1, 0},
        {3, 2, 6, 7}
};


void draw::box(GLdouble w, GLdouble h, GLdouble d) {
    glPushMatrix();
    glTranslated(-w/2, -h/2, -d/2);

    auto v = box_vertex(w, h, d);
    glBegin(GL_QUADS);
    REP(j, 6) {
        REP(i, 4) {
            auto [x, y, z] = v[box_faces[j][i]];
            glVertex3d(x, y, z);
        }
    }
    glEnd();

    glPopMatrix();
}