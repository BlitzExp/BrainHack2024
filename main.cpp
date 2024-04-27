#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "src/object.cpp"

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

    object chill(0, 0, "textures/chill.png", 50, 50);

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
                if (event.key.code == sf::Keyboard::C){
                    
                }

            }
        }

        window.draw(chill.draw());

        window.display(); //end of drawing events
    }
}