#include "camera.h"
#include "useful_macros.h"

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include <cmath>
#include <tuple>
#include <algorithm>

camera::camera(int w, int h) {
    width = w;
    height = h;
    prv_cursor_pos = {0, 0};
    cur_cursor_pos = {0, 0};
    camera::reset();
}

void camera::apply() const {
    std::pair<double, double> p;

    p.first = (cur_cursor_pos.first - prv_cursor_pos.first) / width * M_PI;
    p.second = (cur_cursor_pos.second - prv_cursor_pos.second) / height * M_PI;
    if(std::hypot(p.first, p.second) < 1e-7) {
        p = {0, 0};
    }

    double theta = angle_h - p.first, phi = angle_v - p.second;
    phi = std::clamp(phi, 1e-7, M_PI / 2);

    double eyeX = x + eye_radius * std::sin(phi) * std::sin(theta);
    double eyeZ = z + eye_radius * std::sin(phi) * std::cos(theta);
    double eyeY = y + eye_radius * std::cos(phi);

    gluLookAt(eyeX, eyeY, eyeZ, x, y, z,0.0, 1.0, 0.0);
}

void camera::reset() {
    x = y = z = 0;
    key_pressed = false;
    eye_radius = 5;
    angle_h = M_PI / 4;
    angle_v = M_PI / 4;
}

void camera::reset_position(int x, int y) {
    prv_cursor_pos = cur_cursor_pos = {x, y};
}

void camera::on_mouse_pressed(int x, int y) {
    key_pressed = true;
    camera::reset_position(x, y);
}

void camera::on_mouse_released(int x, int y) {
    camera::angle_h -= (cur_cursor_pos.first - prv_cursor_pos.first) / width * M_PI;
    camera::angle_v -= (cur_cursor_pos.second - prv_cursor_pos.second) / height * M_PI;
    camera::angle_h = fmod(camera::angle_h, 2 * M_PI);
    camera::angle_v = std::clamp(camera::angle_v, 0.0, M_PI / 2);
    camera::reset_position(x, y);
    key_pressed = false;
}

void camera::mouse(int button, int state, int x, int y) {
    if(button == GLUT_MIDDLE_BUTTON) {
        camera::reset();
        return;
    }
    else if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_UP) {
            on_mouse_released(x, y);
        } else if(state == GLUT_DOWN) {
            on_mouse_pressed(x, y);
        }
    }
}

void camera::motion(int x, int y) {
    if(not key_pressed) return;
    cur_cursor_pos = {x, y};
}

void camera::keyboard(unsigned char key, int x, int y) {
    if(key == '\033') {
        exit(0); // if you pressed the esc key, close the window
    }

    double d = -1;

    if(key == 'w' || key == 'W') d = 0;
    else if(key == 's' || key == 'S') d = M_PI;
    else if(key == 'd' || key == 'D') d = - M_PI / 2;
    else if(key == 'a' || key == 'A') d = M_PI / 2;

    if(d != -1) {
        camera::z -= 0.1 * std::cos(camera::angle_h + d);
        camera::x -= 0.1 * std::sin(camera::angle_h + d);
    }
}

void camera::mouse_wheel(int button, int dir, int x, int y) {
    double dr = 0;
    if (dir > 0) {
        dr = 0.5;
    } else {
        dr = -0.5;
    }
    eye_radius = std::clamp(eye_radius + dr, 0.5, 30.0);
}