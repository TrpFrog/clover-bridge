#ifndef CLOVER_BRIDGE_PARTS_H
#define CLOVER_BRIDGE_PARTS_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <vector>

using vertexv = std::tuple<GLdouble, GLdouble, GLdouble>;

namespace parts {
    void box(GLdouble w, GLdouble h, GLdouble d);
    void pillar(std::__1::vector<vertexv> &v, double nx, double ny, double nz);

    void set_normal_vector(vertexv a, vertexv b, vertexv c);
}

#endif //CLOVER_BRIDGE_PARTS_H
