#include "main.h"

#ifndef BARRELS_H
#define BARRELS_H


class Barrels {
public:
    Barrels() {}
    Barrels(float x, float y, float z, float height, float radius, color_t color);
    glm::vec3 position;
    float rotation,rotation_axis,h,rad;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,speed_x,speed_y,speed_z;
private:
    VAO *object;
};

#endif // BALL_H
