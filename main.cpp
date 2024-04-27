#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "src/object.cpp"
#include "src/has_collisions.cpp"

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
    
    std::vector<has_collisions> vector_of_colliders;

    has_collisions chill(0, 0, "textures/chill.png", 50, 50, 50, 50, vector_of_colliders);
    has_collisions chill2(100, 100, "textures/chill.png", 50, 50, 50, 50, vector_of_colliders);

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
                    target_zoom += 1; //toggle if collision grids are visible or not
                } else if (event.key.code == sf::Keyboard::S){
                    target_zoom -= 1;

                    if(target_zoom == 0){
                        target_zoom += 1;
                    }
                }

            }
        }
        camera_zoom += (target_zoom - camera_zoom) * CAMERA_SPEED * 2;
        //temporary_code
        chill.set_spdx(chill.get_spdx()*0.9);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            chill.set_spdx(-5);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            chill.set_spdx(5);
        }

        chill.set_spdy(chill.get_spdy()*0.9);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            chill.set_spdy(-5);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            chill.set_spdy(5);
        }
        ////////

        chill.xy_plus_spd(0);
        chill.xy_plus_spd(1);

        window.clear();
        window.draw(chill.draw());
        window.draw(chill2.draw());

        window.display(); //end of drawing events
    }
}