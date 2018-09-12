#include "main.h"

#ifndef CANNON_BALLS_H
#define CANNON_BALLS_H


class Cannon_balls {
public:
    Cannon_balls() {}
    Cannon_balls(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation,rotation_axis;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,speed_x,speed_y,speed_z;
private:
    VAO *object;
};

#endif // BALL_H
