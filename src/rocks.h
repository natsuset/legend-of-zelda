#include "main.h"

#ifndef ROCKS_H
#define ROCKS_H


class Rocks {
public:
    Rocks() {}
    Rocks(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,speed_x,speed_y,speed_z;
private:
    VAO *object;
};

#endif // BALL_H
