#include "barrels.h"
#include "main.h"

Barrels::Barrels(float x, float y, float z,float height,float radius,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotation_axis = 0;
    this->speed_x = 0.2;
    this->speed_y = 0;
    this->speed_z = 0;
    this->h = height;
    this->rad = radius;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
//    int r = 1;
//    int height = 2;


//    GLfloat g_vertex_buffer_data[4000];
//        float PI = 3.14159265;
//        int top = 0;
//        // float z = 0;
//        float degree = 0;
//        while(degree <= 360.0f)
//        {
//            g_vertex_buffer_data[top++] = r*cos(degree*PI/180.0);
//            g_vertex_buffer_data[top++] = r*sin(degree*PI/180.0);
//            g_vertex_buffer_data[top++] = height;

//            g_vertex_buffer_data[top++] = r*cos(degree*PI/180.0);
//            g_vertex_buffer_data[top++] = r*sin(degree*PI/180.0);
//            g_vertex_buffer_data[top++] = 0.0;

//            degree += 1;

//        }


//        this->object = create3DObject(GL_LINES, 720, g_vertex_buffer_data, color, GL_FILL);

    float angle = 0,PI = 3.14159265;
    int i=0;
    float r = -this->rad;
    GLfloat g_data[9000];
    while(angle <= 360){
        g_data[i++] = r * sin(angle * 180.0/PI);
        g_data[i++] = this->h;
        g_data[i++] = r * cos(angle * 180.0/PI);


        g_data[i++] = r * sin((angle + 1) * 180.0/PI);
        g_data[i++] = this->h;
        g_data[i++] = r * cos((angle + 1) * 180.0/PI);


        g_data[i++] = r * sin((angle + 1) * 180.0/PI);
        g_data[i++] = -this->h;
        g_data[i++] = r * cos((angle + 1) * 180.0/PI);


        g_data[i++] = r * sin(angle * 180.0/PI);
        g_data[i++] = this->h;
        g_data[i++] = r * cos(angle * 180.0/PI);


        g_data[i++] = r * sin(angle * 180.0/PI);
        g_data[i++] = -this->h;
        g_data[i++] = r * cos(angle * 180.0/PI);

        g_data[i++] = r * sin((angle + 1) * 180.0/PI);
        g_data[i++] = -this->h;
        g_data[i++] = r * cos((angle + 1) * 180.0/PI);

        angle += 1;
    }

//        static const GLfloat vertex_buffer_data[] = {


//        -2.0f,-0.0f,-2.0f, // triangle 1 : begin
//        -2.0f,-0.0f, 2.0f,
//        -2.0f, 1.0f, 2.0f, // triangle 1 : end
//        2.0f, 1.0f,-2.0f, // triangle 2 : begin
//        -2.0f,-0.0f,-2.0f,
//        -2.0f, 1.0f,-2.0f, // triangle 2 : end
//        2.0f,-0.0f, 2.0f,
//        -2.0f,-0.0f,-2.0f,
//        2.0f,-0.0f,-2.0f,
//        2.0f, 1.0f,-2.0f,
//        2.0f,-0.0f,-2.0f,
//        -2.0f,-0.0f,-2.0f,
//        -2.0f,-0.0f,-2.0f,
//        -2.0f, 1.0f, 2.0f,
//        -2.0f, 1.0f,-2.0f,
//        2.0f,-0.0f, 2.0f,
//        -2.0f,-0.0f, 2.0f,
//        -2.0f,-0.0f,-2.0f,
//        -2.0f, 1.0f, 2.0f,
//        -2.0f,-0.0f, 2.0f,
//        2.0f,-0.0f, 2.0f,
//        2.0f, 1.0f, 2.0f,
//        2.0f,-0.0f,-2.0f,
//        2.0f, 1.0f,-2.0f,
//        2.0f,-0.0f,-2.0f,
//        2.0f, 1.0f, 2.0f,
//        2.0f,-0.0f, 2.0f,
//        2.0f, 1.0f, 2.0f,
//        2.0f, 1.0f,-2.0f,
//        -2.0f, 1.0f,-2.0f,
//        2.0f, 1.0f, 2.0f,
//        -2.0f, 1.0f,-2.0f,
//        -2.0f, 1.0f, 2.0f,
//        2.0f, 1.0f, 2.0f,
//        -2.0f, 1.0f, 2.0f,
//        2.0f,-0.0f, 2.0f
//    };

    this->object = create3DObject(GL_TRIANGLES, 720*3, g_data, color, GL_FILL);
}

void Barrels::draw(glm::mat4 VP) {
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

void Barrels::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Barrels::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
