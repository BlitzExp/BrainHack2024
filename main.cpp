#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <format>
#include <sstream>
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
    hammer chill (150, -50, 35, 20, 43, 52, vector_of_colliders);
    pendulum chill2(0, 0, "textures/botellin.png", 37, 44, 37, 44, vector_of_colliders);
    //pendulum bigboy(0, 0, "textures/bigboy.png", 74, 88, 74, 88, vector_of_colliders);

    int go_to_camera_x = 0;
    int go_to_camera_y = 0;
    int camera_x_no_zoom = 0;
    int camera_y_no_zoom = 0;
    std::string camera_mode = "player";
    double CAMERA_SPEED = 0.1; //must be a value between lim -> 0 and 1

    float target_zoom = 1;

    sf::SoundBuffer buffer;

    std::vector<object*> shard_vector;
    std::vector<pendulum*> jars;

    sf::Font font;
    if (!font.loadFromFile("fonts/04B_30__.TTF"))
    {
        return -1;
    }

    // Create a text object
    sf::Text text;

    // Set the font of the text
    text.setFont(font);
    text.setString("???");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(50, 50);

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
                if (p_ref -> get_angular_speed() > 0.25){
                    p_ref -> _alive = 0;
                    p_ref -> set_x(3000);
                    p_ref -> _first_time_dead = 1;
                }

                if (!(p_ref -> _alive) && p_ref -> _first_time_dead == 1){
                    p_ref -> _first_time_dead = 0;

                    
                    for (int j = 0; j < 6; j++){
                        // int x_pos = p_ref -> get_x() + (rand()% (p_ref -> get_length())) - (p_ref -> get_length()/2);
                        // int y_pos = p_ref -> get_y() + (rand()% (p_ref -> get_height())) - (p_ref -> get_height()/2);
                        int x_pos = 0 + (rand()% (p_ref -> get_length())) - (p_ref -> get_length()/2);
                        int y_pos = 0 + (rand()% (p_ref -> get_height())) - (p_ref -> get_height()/2);
                        shard_vector.push_back( new object(x_pos, y_pos, "textures/shattered.png", 18, 20));
                        shard_vector[j] -> set_spdy(-(rand() % 5));
                        shard_vector[j] -> set_spdx(rand() % 5);
                        shard_vector[j] -> set_rotation(rand() % int(2*M_PI));

                    }
                }
            }

            chill.collisions(vector_of_colliders, i);

            chill2.pendulum_physics(i, vector_of_colliders);
            chill2.collisions(vector_of_colliders, i);
        }

        for (int i = 0; i < shard_vector.size(); i++){
            shard_vector[i] -> gravity(0.3);

            if (!(shard_vector[i] -> _alive)){
                delete shard_vector[i];
                std::vector<object*>::iterator pos;
                pos = shard_vector.begin() + i;
                shard_vector.erase(pos);

                if(shard_vector.size() == 0){
                    LEVEL++;
                }
            }
        }
        ////////
        chill.set_differences(); // DO NOT DELETE

        window.clear();
        
        window.draw(background.draw(2));
        window.draw(chill2.draw());
        window.draw(chill.draw());
        window.draw(text);

        for (auto i:shard_vector){
            window.draw(i -> draw());
        }

        std::stringstream ss;
        ss << "LEVEL: " << LEVEL;
        std::string str = ss.str();
        text.setString(str);

        window.display(); //end of drawing events
    }
}