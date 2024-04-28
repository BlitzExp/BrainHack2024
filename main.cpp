#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "src/object.cpp"
#include "src/has_collisions.cpp"
#include "src/pendulum.cpp"
#include "src/hammer.cpp"
#include "src/functions.cpp"

int camera_x = -480;
int camera_y = -100;
float camera_zoom = 1;
int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;
long frames = 0;
int LEVEL = 1;

int main()
{   
    //create window object
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Application");
    window.setFramerateLimit(60);
    
    std::vector<has_collisions*> vector_of_colliders;

    object background (-200, -100 , "textures/bck.png", 500, 500);
    hammer chill (50, 0, 35, 20, 43, 52, vector_of_colliders);
    pendulum chill2(300, 0, "textures/botellin.png", 37, 44, 37, 44, vector_of_colliders);

    int go_to_camera_x = 0;
    int go_to_camera_y = 0;
    int camera_x_no_zoom = 0;
    int camera_y_no_zoom = 0;
    std::string camera_mode = "player";
    double CAMERA_SPEED = 0.1; //must be a value between lim -> 0 and 1

    float target_zoom = 1;

    sf::SoundBuffer buffer;

////////////////////////////////////////////////////////////game_on///////////////////////

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                
                if (event.key.code == sf::Keyboard::W){
                    target_zoom += 1;
                } else if (event.key.code == sf::Keyboard::S){
                    target_zoom -= 1;

                    if(target_zoom == 0){
                        target_zoom += 1;
                    }
                }

            }
        }
        frames ++;

        target_zoom = 3;
        go_to_camera_x = -480 + chill.get_x() / 5;
        go_to_camera_y = -100 + chill.get_y() / 5;
        camera_x_no_zoom += (int) (go_to_camera_x - camera_x_no_zoom) * CAMERA_SPEED;
        camera_y_no_zoom += (int) (go_to_camera_y - camera_y_no_zoom) * CAMERA_SPEED * 0.5;
        camera_zoom += (target_zoom - camera_zoom) * 0.1;
        camera_x = camera_x_no_zoom + (camera_zoom - 1);
        camera_y = camera_y_no_zoom + (camera_zoom - 1);

        for (int i = 0; i < 2; i++){
            chill.pendulum_physics(i, vector_of_colliders);
            if (chill.collision_check(vector_of_colliders)) {
                has_collisions* colliding_with = chill.collision_check(vector_of_colliders);
                pendulum* p_ref = reinterpret_cast<pendulum*>(colliding_with);
                p_ref -> set_angular_speed((p_ref->get_angular_speed()/abs(p_ref->get_angular_speed()))*calcularVelocidadDespuesColision(chill, *p_ref ,100, 0.1));
                if (p_ref -> get_angular_speed() > 0.25) p_ref -> _alive = 0, p_ref -> set_x(3000);
            }

            chill.collisions(vector_of_colliders, i);

            chill2.pendulum_physics(i, vector_of_colliders);
            chill2.collisions(vector_of_colliders, i);
        }
        ////////
        std::cout<< chill2.get_angular_speed() <<std::endl;
        chill.set_differences();

        window.clear();
        
        window.draw(background.draw(2));
        window.draw(chill2.draw());
        window.draw(chill.draw());

        window.display(); //end of drawing events
    }
}