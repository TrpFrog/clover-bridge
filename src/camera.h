#ifndef CLOVER_BRIDGE_CAMERA_H
#define CLOVER_BRIDGE_CAMERA_H

#include <tuple>

class camera {
private:
    std::pair<double, double> prv_cursor_pos;
    std::pair<double, double> cur_cursor_pos;
    double width, height, eye_radius;
    double angle_h, angle_v;
    double x, y, z;
    bool key_pressed;
    void on_mouse_pressed(int x, int y);
    void on_mouse_released(int x, int y);
    void reset_position(int x, int y);
    void reset();
public:
    camera(int w, int h);
    void apply();
    void mouse(int button, int state, int x, int y);
    void keyboard(unsigned char key, int x, int y);
    void motion(int x, int y);
    void mouse_wheel(int button, int dir, int x, int y);
};


#endif //CLOVER_BRIDGE_CAMERA_H
