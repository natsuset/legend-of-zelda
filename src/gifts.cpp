#include "gifts.h"
#include "main.h"

Gifts::Gifts(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotation_axis = 0;
    this->speed_x = 0.2;
    this->speed_y = 0;
    this->speed_z = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.5f,-0.0f,-0.5f, // triangle 1 : begin
        -0.5f,-0.0f, 0.5f,
        -0.5f, 1.0f, 0.5f, // triangle 1 : end

        0.5f, 1.0f,-0.5f, // triangle 2 : begin
        -0.5f,-0.0f,-0.5f,
        -0.5f, 1.0f,-0.5f, // triangle 2 : end

        0.5f,-0.0f, 0.5f,
        -0.5f,-0.0f,-0.5f,
        0.5f,-0.0f,-0.5f,

        0.5f, 1.0f,-0.5f,
        0.5f,-0.0f,-0.5f,
        -0.5f,-0.0f,-0.5f,

        -0.5f,-0.0f,-0.5f,
        -0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f,-0.5f,

        0.5f,-0.0f, 0.5f,
        -0.5f,-0.0f, 0.5f,
        -0.5f,-0.0f,-0.5f,

        -0.5f, 1.0f, 0.5f,
        -0.5f,-0.0f, 0.5f,
        0.5f,-0.0f, 0.5f,

        0.5f, 1.0f, 0.5f,
        0.5f,-0.0f,-0.5f,
        0.5f, 1.0f,-0.5f,

        0.5f,-0.0f,-0.5f,
        0.5f, 1.0f, 0.5f,
        0.5f,-0.0f, 0.5f,

        0.5f, 1.0f, 0.5f,
        0.5f, 1.0f,-0.5f,
        -0.5f, 1.0f,-0.5f,

        0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f,-0.5f,
        -0.5f, 1.0f, 0.5f,

        0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f, 0.5f,
        0.5f,-0.0f, 0.5f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Gifts::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_1    = glm::rotate((float) (this->rotation_axis * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate_1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gifts::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Gifts::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
