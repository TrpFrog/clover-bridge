#include "parts.h"

#include "useful_macros.h"
#include <vector>
#include <tuple>
#include <cmath>

using edge = std::pair<int, int>;

std::vector<vertexv> box_vertex(GLdouble x, GLdouble y, GLdouble z) {
    std::vector<vertexv> vertex = {
        {0, 0, 0},
        {x, 0, 0},
        {x, y, 0},
        {0, y, 0},
        {0, 0, z},
        {x, 0, z},
        {x, y, z},
        {0, y, z},
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

GLdouble normal[][3] = {
        { 0.0, 0.0,-1.0 },
        { 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0 },
        {-1.0, 0.0, 0.0 },
        { 0.0,-1.0, 0.0 },
        { 0.0, 1.0, 0.0 }
};


void parts::box(GLdouble w, GLdouble h, GLdouble d) {
    glPushMatrix();
    glTranslated(-w/2, -h/2, -d/2);

    auto v = box_vertex(w, h, d);
    glBegin(GL_QUADS);
    REP(j, 6) {
        glNormal3dv(normal[j]);
        REP(i, 4) {
            auto [x, y, z] = v[box_faces[j][i]];
            glVertex3d(x, y, z);
        }
    }
    glEnd();

    glPopMatrix();
}

void parts::set_normal_vector(vertexv a, vertexv b, vertexv c) {
    auto [ax, ay, az] = a;
    auto [bx, by, bz] = b;
    auto [cx, cy, cz] = c;
    ax -= cx; bx -= cx;
    ay -= cy; by -= cy;
    az -= cz; bz -= cz;
    double x = ay * bz - az * by;
    double y = az * bx - ax * bz;
    double z = ax * by - ay * bz;
    double d = std::hypot(x, y, z);
    glNormal3d(x / d, y / d, z / d);
}

void parts::pillar(std::vector<vertexv> &v, double nx, double ny, double nz) {
    int n = (int) v.size();
    glBegin(GL_POLYGON);
    glNormal3d(-nx, -ny, -nz);
    for(auto [x, y, z] : v) {
        glVertex3d(x, y, z);
    }
    glEnd();

    v.push_back(v.front());
    glBegin(GL_QUADS);
    REP(i, n) {
        auto [x1, y1, z1] = v[i];
        auto [x2, y2, z2] = v[i + 1];
        set_normal_vector(v[i], v[i + 1], {x1 + nx, y1 + ny, z1 + nz});
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
        glVertex3d(x2 + nx, y2 + ny, z2 + nz);
        glVertex3d(x1 + nx, y1 + ny, z1 + nz);
    }
    glEnd();
    v.pop_back();

    glBegin(GL_POLYGON);
    glNormal3d(nx, ny, nz);
    for(auto [x, y, z] : v) {
        glVertex3d(x + nx, y + ny, z + nz);
    }
    glEnd();
}