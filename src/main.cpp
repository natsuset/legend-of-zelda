#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "boat.h"
#include "rocks.h"
#include "barrels.h"
#include "gifts.h"
#include "cannon_balls.h"
#include "monsters.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Water water;
Boat boat;
Rocks rocks[20];
Barrels barrels[20],cannon;
Gifts gifts[20];
vector<Cannon_balls> fire_balls;
vector<Monsters> monsters;
vector<Monsters> monster_boss;
vector<Gifts> boosters;
static int old = GLFW_RELEASE;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0,wind_speed_x = 0,wind_speed_z = 0,random_time = 1.0,jmp_flag = 0,normal_speed = 0.2;
float camera_rotation_angle = 0,normal_fi_speed = 0.4;
int count_fiballs=0,test_flag_rem = 0.2,global_x = 2,monster_count = 20,super_power = 0,global_health = 1000,global_lives = 3,booster_count = 0;
float target_x = 0, target_y = 0, target_z = 0, up_x = 0, up_y = 1, up_z = 0,eye_x = 5,eye_y = 5,eye_z = 0,angle = 2;
Timer t60(1.0 / 60);
Timer t180(random_time);
Timer t360(20.0);
Timer t120(2.0);
Timer t320(random_time);
Timer t720(5.0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);


    //Top view
//    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye ( ball1.position.x+2, 30, ball1.position.z );
//    // Target - Where is the camera looking at.  Don't change unless you are sure!!
//    glm::vec3 target (ball1.position.x-1*cos(ball1.rotation*M_PI/180.0f), ball1.position.y, ball1.position.z+1*sin(ball1.rotation*M_PI/180.0f));
//    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
//    glm::vec3 up (0, 1, 0);

    //Boat view
        // Eye - Location of camera. Don't change unless you are sure!!
//        glm::vec3 eye ( ball1.position.x-2, ball1.position.y+1,  ball1.position.z );
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
 //       glm::vec3 target (ball1.position.x-1*cos(ball1.rotation*M_PI/180.0f), ball1.position.y, ball1.position.z+1*sin(ball1.rotation*M_PI/180.0f));
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
   //     glm::vec3 up (0, 1, 0);



       glm::vec3 eye (eye_x, eye_y, eye_z);
       // Target - Where is the camera looking at.  Don't change unless you are sure!!
       glm::vec3 target (target_x, target_y, target_z);
       // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
       glm::vec3 up (up_x, up_y, up_z);





    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    water.draw(VP);
    cannon.draw(VP);
    for(int i=0;i<20;i++){
      //fire_balls.draw(VP);
        rocks[i].draw(VP);
        barrels[i].draw(VP);
        gifts[i].draw(VP);

    }
    for(int i=0;i<monster_count;i++){
        monsters[i].draw(VP);
    }
    for(int i=0;i<count_fiballs;i++){
        fire_balls[i].draw(VP);
    }
    for(int i =0;i<booster_count;i++){
        boosters[i].draw(VP);
    }
   // boat.draw(VP);
}

void cam_func0(int f){
    target_x = ball1.position.x - 100 * cos(ball1.rotation * M_PI / 180.0f);
    target_y = ball1.position.y+2;
    target_z = ball1.position.z + 100 * sin(ball1.rotation * M_PI / 180.0f);
    eye_x   = ball1.position.x - 1.4 * cos(ball1.rotation * M_PI / 180.0f);
    eye_y = ball1.position.y+3;
    eye_z   = ball1.position.z + 1.4 * sin(ball1.rotation * M_PI / 180.0f);
}
void cam_func2(int f){
    eye_x = ball1.position.x+2;
    eye_y = 30;
    eye_z = ball1.position.z;
    target_x = ball1.position.x-1*cos(ball1.rotation*M_PI/180.0f);
    target_y =  ball1.position.y;
    target_z = ball1.position.z+1*sin(ball1.rotation*M_PI/180.0f);
    angle = 2;
}

void cam_func3(){
    target_x = ball1.position.x - 100 * cos(ball1.rotation * M_PI / 180.0f);
    target_y = 6;
    target_z = ball1.position.z + 100 * sin(ball1.rotation * M_PI / 180.0f);
    eye_x   = ball1.position.x + 7 * cos(ball1.rotation * M_PI / 180.0f);
    eye_y = 6;
    eye_z   = ball1.position.z - 7 * sin(ball1.rotation * M_PI / 180.0f);
}


void cam_func1(int f){
    //if(f == 0){
//        target_x = ball1.position.x - 100 * cos(ball1.rotation * M_PI / 180.0f);
//        target_y = 4;
//        target_z = ball1.position.z + 100 * sin(ball1.rotation * M_PI / 180.0f);
//        eye_x   = ball1.position.x - 1.4 * cos(ball1.rotation * M_PI / 180.0f);
//        eye_y = ball1.position.y+3;
//        eye_z   = ball1.position.z + 1.4 * sin(ball1.rotation * M_PI / 180.0f);
        if(f == 0){
           target_x = boat.position.x - 100 * cos(boat.rotation * M_PI / 180.0f);
           target_y = 6;
           target_z = boat.position.z + 100 * sin(boat.rotation * M_PI / 180.0f);
           eye_x   = boat.position.x + 7 * cos(boat.rotation * M_PI / 180.0f);
           eye_y = 6;
           eye_z   = boat.position.z - 7 * sin(boat.rotation * M_PI / 180.0f);
        }
        if(f = 1){
            eye_x -= ball1.speed_x;
            eye_z += ball1.speed_z;
            target_x -= ball1.speed_x;
            target_z += ball1.speed_z;

        }


//    }
//    else if(f == 1){
//        eye_x -= ball1.speed_x;
//        eye_z += ball1.speed_z;
//        target_x -= ball1.speed_x;
//        target_z += ball1.speed_z;
//    }
//    else if( f == 2){
//        eye_x += ball1.speed_x;
//        eye_z -= ball1.speed_z;
//        target_x += ball1.speed_x;
//        target_z -= ball1.speed_z;
//    }
}


void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int f_key = glfwGetKey(window,GLFW_KEY_F);
    int w_key = glfwGetKey(window,GLFW_KEY_W);
    int one_key = glfwGetKey(window,GLFW_KEY_1);
    int two_key = glfwGetKey(window,GLFW_KEY_2);
    int three_key = glfwGetKey(window,GLFW_KEY_3);
    int four_key = glfwGetKey(window,GLFW_KEY_4);

    if(one_key){
        cam_func0(1);
        angle = 1;

    }
    if(two_key){
        //    // Eye - Location of camera. Don't change unless you are sure!!
        //    glm::vec3 eye ( ball1.position.x+2, 30, ball1.position.z );
        //    // Target - Where is the camera looking at.  Don't change unless you are sure!!
        //    glm::vec3 target (ball1.position.x-1*cos(ball1.rotation*M_PI/180.0f), ball1.position.y, ball1.position.z+1*sin(ball1.rotation*M_PI/180.0f));
        //    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        //    glm::vec3 up (0, 1, 0);
//        eye_x = ball1.position.x+2;
//        eye_y = 30;
//        eye_z = ball1.position.z;
//        target_x = ball1.position.x-1*cos(ball1.rotation*M_PI/180.0f);
//        target_y =  ball1.position.y;
//        target_z = ball1.position.z+1*sin(ball1.rotation*M_PI/180.0f);
        cam_func2(1);
        angle = 2;



    }
    if(three_key){
        cam_func3();
        angle = 3;
    }
    if(four_key){
//        angle = 0;
//        eye_y = 10;
//        eye_x = ball1.position.x - 5;
//        eye_z = ball1.position.z - 5;
//        target_x = ball1.position.x;
//        target_z = ball1.position.z;
        eye_y = 10;
        eye_x = 0;
        eye_z = 0;
        angle = 0;
//        eye_x = ball1.position.x - 5;
//        eye_z = ball1.position.z - 5;
        target_x = ball1.position.x * 100000 + 100000;
        target_z = ball1.position.z * 100000 + 100000;

    }
    if (left) {
        // Do something
        //ball1.position.z += 0.1;
        ball1.rotation += 0.5;
        cannon.rotation += 0.5;
        //ball1.rotation_axis = ball1.speed_x*10 ;
        ball1.speed_x = normal_speed * cos(ball1.rotation * M_PI/180.0f);
        ball1.speed_z = normal_speed * sin(ball1.rotation * M_PI/180.0f);
    }
    if (right) {
        // Do something
        ball1.rotation -= 0.5;
        cannon.rotation -= 0.5;
        ball1.rotation_axis = -ball1.speed_x*10 ;
        //ball1.speed_x += 0.1;
        ball1.speed_x = normal_speed * cos(ball1.rotation * M_PI/180.0f);
        ball1.speed_z = normal_speed * sin(ball1.rotation * M_PI/180.0f);
    }
    if(up){
        ball1.speed_x = normal_speed * cos(ball1.rotation * M_PI/180.0f) - wind_speed_x;
        ball1.speed_z = normal_speed * sin(ball1.rotation * M_PI/180.0f) - wind_speed_z;
        ball1.position.x -= ball1.speed_x;
        cannon.position.x -= ball1.speed_x;
        ball1.position.z += ball1.speed_z;
        cannon.position.z += ball1.speed_z;
        //cam_func0(1);
    }

    if(down){
        ball1.speed_x = -normal_speed * cos(ball1.rotation * M_PI/180.0f) + wind_speed_x;
        ball1.speed_z = -normal_speed * sin(ball1.rotation * M_PI/180.0f) + wind_speed_z;
        ball1.position.x -= ball1.speed_x;
        cannon.position.x -= ball1.speed_x;
        ball1.position.z += ball1.speed_z;
        cannon.position.z += ball1.speed_z;
        //cam_func0(1);
    }
    if(space && jmp_flag == 0){
        ball1.speed_y = 0.3;
        ball1.position.y += 0.1;
        cannon.position.y += 0.1;
        jmp_flag = 1;
        normal_speed = 0.4;
    }
    if(f_key == GLFW_RELEASE && old == GLFW_PRESS){
        //fire_balls[count_fiballs++] = Cannon_balls(ball1.position.x,ball1.position.y + 1.4,-1,COLOR_GREEN);
        //fire_balls[count_fiballs++] = Cannon_balls(0,1.4,-1,COLOR_GREEN);
        fire_balls.push_back(Cannon_balls(ball1.position.x,ball1.position.y + 1.4,ball1.position.z-1,COLOR_GREEN));
        fire_balls[count_fiballs].speed_x = 0.2;
        count_fiballs++;
        if(super_power == 1){
            fire_balls[0].rotation = 90 + ball1.rotation;
            fire_balls[0].speed_x = normal_fi_speed * cos(ball1.rotation * M_PI/180.0f);
            fire_balls[0].speed_z = normal_fi_speed * sin(ball1.rotation * M_PI/180.0f);
            fire_balls[0].speed_y = (normal_speed +2 )* sin((cannon.rotation_axis+90) * M_PI/180.0f);
        }
        else{
            fire_balls[count_fiballs -1].rotation = 90 + ball1.rotation;
            fire_balls[count_fiballs -1].speed_x = normal_fi_speed * cos(ball1.rotation * M_PI/180.0f);
            fire_balls[count_fiballs -1].speed_z = normal_fi_speed * sin(ball1.rotation * M_PI/180.0f);
            fire_balls[count_fiballs -1].speed_y = (normal_speed +1 )* sin((cannon.rotation_axis+90) * M_PI/180.0f);
        }
//        cout << "#########################" << endl;
//        cout << fire_balls[0].speed_y << endl;
//        cout << "#########################" << endl;
        //normal_fi_speed = normal_speed + 1;


        test_flag_rem = 1;
    }
    old = f_key;
    if(w_key){
        //cout << cannon.rotation_axis << endl;
        if(cannon.rotation_axis <= -28)
        cannon.rotation_axis += 0.5;
        normal_fi_speed = (normal_speed + 1)* cos((cannon.rotation_axis) * M_PI/180.0f);
        if(count_fiballs != 0){

        //fire_balls[0].speedy
        //if(cannon.rotation_axis == 0)
        //    cout << "HEYA";
        }
    }
}


bool detect_collision_fireballs(int fno,int eno){
    if(fire_balls[fno].position.x <= monsters[eno].position.x + 1 && fire_balls[fno].position.x >= monsters[eno].position.x - 1){
        if(fire_balls[fno].position.z <= monsters[eno].position.z + 1 && fire_balls[fno].position.z >= monsters[eno].position.z - 1){
            //cout << "SADBHFJKSDBKV" << endl;
            return true;
        }
        else
            return false;
    }
    else
        return false;

}

bool detect_collision_boat_rocks(int rno){
    if(ball1.rotation == 0){
        if(abs(rocks[rno].position.x -ball1.position.x) <= 3 && abs(rocks[rno].position.z - ball1.position.z) <= 3){
            //cout << "HERERERE" << endl;
            return true;
        }
        else
            return false;
    }
    else{
        if(abs(rocks[rno].position.x -ball1.position.x) <= 3.8 &&  abs(rocks[rno].position.z - ball1.position.z) <= 3.8){
            return true;
        }
        else
            return false;
    }
}

bool detect_collision_boat_barrels(int bno){
    if(ball1.rotation == 0){
        if(abs(barrels[bno].position.x -ball1.position.x) <= 3 && abs(barrels[bno].position.z - ball1.position.z) <= 3 && ball1.position.y == 0){
           // cout << "HERERERE" << endl;
            return true;
        }
        else
            return false;
    }
    else{
        if(abs(barrels[bno].position.x -ball1.position.x) <= 3.8 &&  abs(barrels[bno].position.z - ball1.position.z) <= 3.8 && ball1.position.y == 0){
            return true;
        }
        else
            return false;
    }
}

bool detect_collision_boat_enemies(int eno){
    if(ball1.rotation == 0){
        if(abs(monsters[eno].position.x -ball1.position.x) <= 3 && abs(monsters[eno].position.z - ball1.position.z) <= 3 && ball1.position.y == 0){
            cout << "HEREREREMON" << endl;
            return true;
        }
        else
            return false;
    }
    else{
        if(abs(monsters[eno].position.x -ball1.position.x) <= 4.2 &&  abs(monsters[eno].position.z - ball1.position.z) <= 4.2&& ball1.position.y == 0){
            cout << "HERERERE_MOS" << endl;
            return true;
        }
        else
            return false;
    }
}

bool detect_collision_boat_gifts(int gno){
    if(ball1.rotation == 0){
        if(abs(gifts[gno].position.x -ball1.position.x) <= 2.5 && abs(gifts[gno].position.z - ball1.position.z) <= 2.5){
            cout << "HEREREREMON" << endl;
            return true;
        }
        else
            return false;
    }
    else{
        if(abs(gifts[gno].position.x -ball1.position.x) <= 3.0 &&  abs(gifts[gno].position.z - ball1.position.z) <= 3.0){
            cout << "HERERERE_MOS" << endl;
            return true;
        }
        else
            return false;
    }
}

bool detect_collision_boat_boosters(int gno){
    if(ball1.rotation == 0){
        if(abs(boosters[gno].position.x -ball1.position.x) <= 2.5 && abs(boosters[gno].position.z - ball1.position.z) <= 2.5){
            cout << "HEREREREMON" << endl;
            return true;
        }
        else
            return false;
    }
    else{
        if(abs(boosters[gno].position.x -ball1.position.x) <= 3.0 &&  abs(boosters[gno].position.z - ball1.position.z) <= 3.0){
            cout << "HERERERE_MOS" << endl;
            return true;
        }
        else
            return false;
    }
}


void tick_elements() {
    ball1.tick();
    if(angle == 0){
        eye_y = 10;
        eye_x = 0;
        eye_z = 0;
//        eye_x = ball1.position.x - 5;
//        eye_z = ball1.position.z - 5;
        target_x = ball1.position.x * 100000 + 100000;
        target_z = ball1.position.z * 100000 + 100000;

    }
    if(angle ==  1)
        cam_func0(1);
    if(angle == 2)
        cam_func2(1);
    if(angle == 3){
        cam_func3();
    }
    ball1.rotation_axis = -ball1.speed_z*30;
    ball1.rotation_axis = 0;
    cannon.position.x = ball1.position.x;
    cannon.position.y = ball1.position.y+1.4;
    cannon.position.z = ball1.position.z-1;
    if(t180.processTick()){


        for(int i=0;i<20;i++){
            //if(t180.processTick())
            global_x = rand() % 4;
    //        monsters[i].position.z += (monsters[i].speed_z * ((-1)^x));
    //        monsters[i].position.x += (monsters[i].speed_x * ((-1)^x));
            if(global_x == 0){
                //(monsters[i].speed_z) = (monsters[i].speed_z);
                //monsters[i].position.x += (monsters[i].speed_x);
            }
            if(global_x == 1){
                //monsters[i].position.z += (monsters[i].speed_z);
                monsters[i].speed_x     = -(monsters[i].speed_x);
            }
            if(global_x == 2){
                monsters[i].speed_z = -(monsters[i].speed_z);
                //monsters[i].position.x += (monsters[i].speed_x);
            }
            if(global_x == 3){
                monsters[i].speed_z = -(monsters[i].speed_z);
                monsters[i].speed_x = -(monsters[i].speed_x);
            }


        }
    }

    for(int i = 0;i<20;i++){
        if(detect_collision_boat_rocks(i)){
            if(ball1.position.x >= rocks[i].position.x){
            ball1.position.x = rocks[i].position.x + 4;
            cannon.position.x = rocks[i].position.x+4;
            ball1.position.y = 0;
            cannon.position.y = 0;
        }
        else{
            ball1.position.x = rocks[i].position.x - 4;
            cannon.position.x = rocks[i].position.x-4;
            ball1.position.y = 0;
            cannon.position.y = 0;
        }
       }
    }
    for(int i = 0;i<20;i++){
        if(detect_collision_boat_barrels(i)){
            if(ball1.position.x >= barrels[i].position.x){
            ball1.position.x = barrels[i].position.x + 4;
            cannon.position.x = barrels[i].position.x+4;
            ball1.position.y = 0;
            cannon.position.y = 0;
        }
        else{
            ball1.position.x = barrels[i].position.x - 4;
            cannon.position.x = barrels[i].position.x-4;
            ball1.position.y = 0;
            cannon.position.y = 0;
        }
       }
    }

    for(int i = 0;i<20;i++){
        monsters[i].position.z += (monsters[i].speed_z);
        monsters[i].position.x += (monsters[i].speed_x);
    }

    for(int i=0;i<count_fiballs;i++){
        if(count_fiballs != 0){
            //cout << fire_balls[0].speed_y << endl;
            //fire_balls[0].position.x -= ;
            if(super_power == 1){
                if(t360.processTick()){
                    super_power = 0;
                }
                int r_x = rand() % 4;
                int r_y = rand() % 4;
                int r_z = rand() % 4;
                fire_balls[0].position.x -= r_x;
                fire_balls[0].position.z += r_z;
                fire_balls[0].position.y += r_y;

                if(fire_balls[0].position.y >= 0 && cannon.rotation_axis != -90){
                    fire_balls[0].speed_y -= 0.04;
                }
                if(fire_balls[0].position.y >= 0 && cannon.rotation_axis == -90){
                    fire_balls[0].speed_y -= 0.0004;
                }
                if(fire_balls[0].position.y < 0){
                    fire_balls.erase(fire_balls.begin() + 0);
                    count_fiballs--;
                }
            }
            else{
                fire_balls[i].position.x -= fire_balls[i].speed_x;
                fire_balls[i].position.z += fire_balls[i].speed_z;
                fire_balls[i].position.y += fire_balls[i].speed_y;

                if(fire_balls[i].position.y >= 0 && cannon.rotation_axis != -90){
                    fire_balls[i].speed_y -= 0.04;
                }
                if(fire_balls[i].position.y >= 0 && cannon.rotation_axis == -90){
                    fire_balls[i].speed_y -= 0.0004;
                }
                if(fire_balls[i].position.y < 0){
                    fire_balls.erase(fire_balls.begin() + i);
                    count_fiballs--;
                }
            }
        }
    }
    for(int j = 0;j<count_fiballs;j++){
        for(int i = 0;i<monster_count+1 && count_fiballs != 0;i++){
            if(detect_collision_fireballs(j,i)){
                boosters.push_back(Gifts(monsters[i].position.x,2,monsters[i].position.z,COLOR_YELLOW));
                booster_count++;
                fire_balls.erase(fire_balls.begin() + j);
                count_fiballs--;
                monsters.erase(monsters.begin() + i);
                monster_count--;
             //   cout << monster_count << endl;
            }
        }
    }
    if(global_lives <= 0){
        quit(window);
    }
    if(global_health <= 0){
        global_lives -= 1;
        global_health = 1000;
        cout << "LIVES LOST" << endl;
        ball1.position.x = 0;
        ball1.position.z = 0;

    }

    for(int i = 0;i<monster_count;i++){
        if(detect_collision_boat_enemies(i)){
            global_health -= 500;

//            monsters[i].speed_x = -monsters[i].speed_x;
//            monsters[i].speed_z = -monsters[i].speed_z;
//            monsters[i].position.x += 2*monsters[i] .speed_x;
//            monsters[i].position.z += 2*monsters[i] .speed_z;
            boosters.push_back(Gifts(monsters[i].position.x,2,monsters[i].position.z,COLOR_YELLOW));
            booster_count++;
            monsters.erase(monsters.begin() + i);
            monster_count--;

        }
    }

    for(int i = 0;i<20;i++){
        if(detect_collision_boat_gifts(i)){
            gifts[i].position.x = 80 + i;
            gifts[i].position.z = 80 + i;
            //cout << "GOT GIFT!!!!" << endl;

        }
    }
    for(int i = 0;i<booster_count;i++){
        if(detect_collision_boat_boosters(i)){
            cout << "KILLING IT" << endl;
            ball1.speed_x = 10 * ball1.speed_x;
            ball1.speed_z = 10 * ball1.speed_z;
            super_power = 1;
            if(t720.processTick()){
                ball1.speed_x = 0.2;
                ball1.speed_z = 0.2;
            }
            boosters.erase(boosters.begin() + i);
            booster_count--;
            //cout << "GOT GIFT!!!!" << endl;

        }
    }
    if(ball1.position.y <= 0){
        ball1.position.y = 0;
        cannon.position.y = 1.4;
        ball1.speed_y = 0;
        jmp_flag = 0;
        normal_speed = 0.2;
    }
    if(ball1.position.y > 0){
        ball1.speed_y -= 0.02;
        ball1.position.y += ball1.speed_y;
        cannon.position.y += ball1.speed_y;
        //ball1.position.y += ball1.speed_y;

    }
    //cout << ball1.rotation_axis << endl;
    if(t320.processTick()){
        //camera_rotation_angle += 45;

        //random_time /=  10;
        wind_speed_x = (rand() % 10) ;
        wind_speed_z = (rand() % 10) ;
        wind_speed_x /= 500;
        wind_speed_z /= 500;
//        wind_speed_x = 0;
//        wind_speed_z = 0;
        ball1.speed_x = wind_speed_x;
        //cout << wind_speed_x;
        //cout << wind_speed_z;
        //random_time = rand() % 10;
    }
    ball1.position.x -= wind_speed_x;
    cannon.position.x -= wind_speed_x;
    ball1.position.z -= wind_speed_z;
    cannon.position.z -= wind_speed_z;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, COLOR_RED);
    cannon      = Barrels(0,1.4,-1,1.5,0.4,COLOR_BROWN);
    cannon.rotation_axis =-90;
    cannon.rotation =90;
    //fire_balls = Cannon_balls(0,1.4,-1,COLOR_GREEN);
    water       = Water(0,0,COLOR_BLUE);
    for(int i=0;i<10;i++){

        int x = abs(rand() % 200);
        if(x < 2.0){
            rocks[i] = Rocks(-x-3.0,0,abs(rand() % 200),COLOR_BLACK);
        }
        else{
            rocks[i] = Rocks(-x,0,abs(rand() % 200),COLOR_BLACK);
        }
        //rocks[i] = Rocks(-abs(rand() % 100),0,rand() % 100,COLOR_BLACK);
    }
    for(int i=10;i<20;i++){
        int x = abs(rand() % 200);
        if(x < 2.0){
            rocks[i] = Rocks(-x-3.0,0,-abs(rand() % 200),COLOR_BLACK);
        }
        else{
            rocks[i] = Rocks(-x,0,-abs(rand() % 200),COLOR_BLACK);
        }
    }
    for(int i=0;i<10;i++){

        int x = abs(rand() % 200);
        if(x < 2.0){
            monsters.push_back(Monsters(-x-3.0,0,abs(rand() % 200),COLOR_GREEN));
        }
        else{
            monsters.push_back(Monsters(-x,0,abs(rand() % 200),COLOR_GREEN));
        }
        //rocks[i] = Rocks(-abs(rand() % 100),0,rand() % 100,COLOR_BLACK);
    }
    for(int i=10;i<20;i++){
        int x = abs(rand() % 200);
        if(x < 2.0){
            monsters.push_back(Monsters(-x-3.0,0,-abs(rand() % 200),COLOR_GREEN));
        }
        else{
             monsters.push_back(Monsters(-x,0,-abs(rand() % 200),COLOR_GREEN));
        }
    }
    for(int i=0;i<10;i++){

        int x = abs(rand() % 200);
        int z = abs(rand() % 200);
        if(x < 2.0){
            barrels[i] = Barrels(-x-3.0,0,z,1.0,1,COLOR_BROWN);
            gifts[i] = Gifts(-x-3.0,1,z,COLOR_YELLOW);
        }
        else{
            barrels[i] = Barrels(-x,0,z,1.0,1,COLOR_BROWN);
            gifts[i] = Gifts(-x,1,z,COLOR_YELLOW);
        }
        //rocks[i] = Rocks(-abs(rand() % 100),0,rand() % 100,COLOR_BLACK);
    }
    for(int i=10;i<20;i++){
        int x = abs(rand() % 200);
        int z = abs(rand() % 200);
        if(x < 2.0){
            barrels[i] = Barrels(-x-3.0,0,-z,1.0,1.0,COLOR_BROWN);
            gifts[i] = Gifts(-x-3.0,2,-z,COLOR_YELLOW);
        }
        else{
            barrels[i] = Barrels(-x,0,-z,1.0,1.0,COLOR_BROWN);
            gifts[i] = Gifts(-x,2,-z,COLOR_YELLOW);
        }
    }
   // boat = Boat(0,0.5,COLOR_RED);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    //cam_func0(0);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 8 / screen_zoom;
    float bottom = screen_center_y - 8 / screen_zoom;
    float left   = screen_center_x - 8 / screen_zoom;
    float right  = screen_center_x + 8 / screen_zoom;
    Matrices.projection = glm::infinitePerspective(90.0f, 2.0f, 0.2f);
}
