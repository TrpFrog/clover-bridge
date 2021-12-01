#ifndef CLOVER_BRIDGE_PARTS_H
#define CLOVER_BRIDGE_PARTS_H

#include "useful_macros.h"
#include <vector>

using vertexv = std::tuple<GLdouble, GLdouble, GLdouble>;

namespace parts {
    void box(GLdouble w, GLdouble h, GLdouble d);
    void pillar(std::vector<vertexv> &v, double nx, double ny, double nz);

    void set_normal_vector(vertexv a, vertexv b, vertexv c);

    void set_normal_vector(double *a, double *b, double *c);

    void
    render(GLfloat ambr, GLfloat ambg, GLfloat ambb, GLfloat difr, GLfloat difg, GLfloat difb,
           GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine);

    void default_render();
}

#endif //CLOVER_BRIDGE_PARTS_H
