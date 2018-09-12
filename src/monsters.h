#include "main.h"

#ifndef MONSTERS_H
#define MONSTERS_H


class Monsters {
public:
    Monsters() {}
    Monsters(float x, float y, float z, color_t color);
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
