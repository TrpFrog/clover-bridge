#include "draw.h"
#include "parts.h"
#include "useful_macros.h"
#include <tuple>
#include <vector>
#include <cmath>
#include <chrono>

long long millis() {
    using namespace std::chrono;
    auto now = system_clock::now().time_since_epoch();
    return duration_cast<milliseconds>(now).count();
}

void draw::all() {
//    draw::axis();
    draw::river();
    draw::bridge();
    draw::bank();
    draw::buildings();
    draw::boat_animation();
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
    GLfloat river_color[] = {.0f, .44f, .95f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat gray[] = {.1f, .1f, .1f, 1.0f};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, river_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    const float field_size = 202;
    glNormal3d(0, 1, 0);
    glBegin(GL_QUADS); {
        glVertex3d(field_size / 2, 0, field_size / 2);
        glVertex3d(field_size / 2, 0, -field_size / 2);
        glVertex3d(-field_size / 2, 0, -field_size / 2);
        glVertex3d(-field_size / 2, 0, field_size / 2);
    } glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
}

void draw::bridge() {
    glPushMatrix();
    GLfloat bridge_color[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat fence_color[] = {0.4f, 0.4f, 0.8f, 1.0f};

    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslated(0, 0.899, 0);
    glRotated(45, 0, 1, 0);

    std::vector<vertexv> circle_vertices;
    {
        const int n = 12;
        const double r = 0.05;
        double dtheta = 2 * M_PI / n;
        REP(i, n) {
            circle_vertices.emplace_back(r * std::sin(dtheta * i), 0, r * std::cos(dtheta * i));
        }
    }

    const int fence_cnt = 5;
    const double bridge_length = 8, bridge_width = 1.2, fence_height = 0.5;

    REP(i, 4) {

        parts::render(0.4f, 0.4f, 0.8f,
                      0.4f, 0.4f, 0.8f, 0.633, 0.727811, 0.633, 0.4);
        for(double x : {-0.5, 0.5}) {
        glPushMatrix();
            glTranslated(x, 0, bridge_width / 2 - 0.1);
            REP(j, fence_cnt) {
                parts::pillar(circle_vertices, 0, fence_height, 0);
                glTranslated(0, 0, (bridge_length / 2 - bridge_width / 2) / (fence_cnt - 1));
            }
            glPopMatrix();
        }

        glPushMatrix();
        glTranslated(0, 0, bridge_length / 4 + bridge_width / 2);
        for(double x : {-0.5, 0.5}) {
            glPushMatrix();
            glTranslated(x, fence_height, - 0.4);
            parts::box(0.1, 0.1, bridge_length / 2 - 0.5);
            glPopMatrix();
        }
        parts::default_render();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, bridge_color);
        parts::box(bridge_width, 0.2, bridge_length / 2);
        glPopMatrix();
        glRotated(90, 0, 1, 0);
    }
    parts::box(1.2, 0.2, 1.2);

    glPopMatrix();
}

void draw::bank() {
    glPushMatrix();

    GLfloat road_color[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat grass_color[] = {0.3f, 0.5f, 0.3f, 1.0f};


    const double sx = 100, sz = 100, h = 1;
    const double outer_r = 2.5, inner_r = 1;
    const int pts = 40;
    const double dtheta = M_PI / 2 / pts;
    const double river_width = 2;

    REP(_, 4) {
        glPushMatrix();
        glTranslated(river_width / 2, 0, river_width / 2);

        glBegin(GL_QUADS); {

            glMaterialfv(GL_FRONT, GL_DIFFUSE, grass_color);

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

            glMaterialfv(GL_FRONT, GL_DIFFUSE, road_color);
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
    GLfloat buildings_color[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, buildings_color);
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

void draw::boat_animation() {
    GLfloat blue[]   = {0.3f, 0.3f, 0.8f, 1.0f};
    GLfloat yellow[] = {0.6f, 0.6f, 0.3f, 1.0f};
    GLfloat red[]    = {0.8f, 0.3f, 0.3f, 1.0f};
    GLfloat green[]  = {0.3f, 0.8f, 0.3f, 1.0f};

    long long unixtime = millis();

    glPushMatrix();

    parts::render(0.19125, 0.0735, 0.0225,
                  0.3f, 0.3f, 0.8f, 0.256777, 0.137622, 0.086014, 0.1);
    draw::boat((unixtime % 160000 - 80000.0) / 800.0, 0, 0, 90);

    parts::render(0.19125, 0.0735, 0.0225,
                  0.6f, 0.6f, 0.3f, 0.256777, 0.137622, 0.086014, 0.1);
    draw::boat(0, 0, ((unixtime + 40000) % 160000 - 80000.0) / 800.0, 0);

    parts::render(0.19125, 0.0735, 0.0225,
                  0.8f, 0.3f, 0.3f, 0.256777, 0.137622, 0.086014, 0.1);
    draw::boat(((unixtime + 80000) % 160000 - 80000.0) / 800.0, 0, 0, 90);

    parts::render(0.19125, 0.0735, 0.0225,
                  0.3f, 0.8f, 0.3f, 0.256777, 0.137622, 0.086014, 0.1);
    draw::boat(0, 0, ((unixtime + 120000) % 160000 - 80000.0) / 800.0, 0);

    glPopMatrix();

    parts::default_render();
}

void draw::boat(double x, double y, double z, double angle) {
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(angle, 0, 1, 0);
    glScaled(.7, .7, .7);

    double vertices[][3] = {
            {-1, .5, 1},
            {1, .5, 1},
            {1, .5, -2},
            {-1, .5, -2},
            {0, -.5, .5},
            {0, -.5, -1},
            {0, .7, 2}
    };

    std::vector<std::vector<int>> quad_edges = {
            {0, 1, 2, 3},
            {0, 3, 5, 4},
            {1, 4, 5, 2}
    };

    std::vector<std::vector<int>> tri_edges = {
            {0, 6, 1},
            {2, 5, 3},
            {1, 6, 4},
            {0, 4, 6}
    };

    glBegin(GL_QUADS);
    for(auto &v : quad_edges) {
        parts::set_normal_vector(vertices[v[0]], vertices[v[1]], vertices[v[2]]);
        for(int i : v) {
            glVertex3dv(vertices[i]);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    for(auto &v : tri_edges) {
        parts::set_normal_vector(vertices[v[0]], vertices[v[1]], vertices[v[2]]);
        for(int i : v) {
            glVertex3dv(vertices[i]);
        }
    }
    glEnd();

    glTranslated(0, .5, -.5);
    parts::box(1, .5, 1.5);

    glPopMatrix();
}