#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "src/object.cpp"
#include "src/has_collisions.cpp"
#include "src/pendulum.cpp"

int camera_x = 0;
int camera_y = 0;
float camera_zoom = 1;
int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

int main()
{   

    //create window object
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Application");
    window.setFramerateLimit(60);
    
    std::vector<has_collisions*> vector_of_colliders;

    pendulum chill(0, 0, "textures/chill.png", 50, 50, 50, 50, vector_of_colliders);
    has_collisions chill2(100, 100, "textures/chill.png", 50, 50, 50, 50, vector_of_colliders);
    has_collisions chill3(200, 200, "textures/chill.png", 50, 50, 50, 50, vector_of_colliders);

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

        go_to_camera_x = chill.get_x() / 5 - SCREEN_WIDTH / 2;
        go_to_camera_y = chill.get_y() / 5 - SCREEN_HEIGHT / 2;
        camera_x_no_zoom += (int) (go_to_camera_x - camera_x_no_zoom) * CAMERA_SPEED;
        camera_y_no_zoom += (int) (go_to_camera_y - camera_y_no_zoom) * CAMERA_SPEED * 0.5;
        camera_zoom += (target_zoom - camera_zoom) * 0.1;
        camera_x = camera_x_no_zoom + (camera_zoom - 1) * chill.get_x();
        camera_y = camera_y_no_zoom + (camera_zoom - 1) * chill.get_y();

        // //temporary_code
        // chill.set_spdx(chill.get_spdx()*0.9);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        //     chill.set_spdx(-5);
        // } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //     chill.set_spdx(5);
        // }

        // chill.set_spdy(chill.get_spdy()*0.9);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        //     chill.set_spdy(-5);
        // } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        //     chill.set_spdy(5);
        // }

        for (int i = 0; i < 2; i++){
            //chill.xy_plus_spd(i);
            chill.pendulum_physics(i, vector_of_colliders);
            chill.collisions(vector_of_colliders, i);
        }
        ////////

        window.clear();
        int x1 = chill.get_x() + chill.get_length()/2;
        int x2 = chill.get_center_x() + chill.get_length()/2;
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x1 + ((camera_zoom - 1))* x1 - camera_x, chill.get_y() + ((camera_zoom - 1))* chill.get_x() - camera_y)),
            sf::Vertex(sf::Vector2f(x2 + ((camera_zoom - 1))* x2 - camera_x, chill.get_center_y() + ((camera_zoom - 1))* chill.get_center_y() - camera_y))
        };
        window.draw(line, 2, sf::Lines);
        
        window.draw(chill.draw());
        window.draw(chill2.draw());
        window.draw(chill3.draw());

        window.display(); //end of drawing events
    }
}