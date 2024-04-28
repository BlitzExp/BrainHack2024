#include "../include/structure.hpp"
#include <cmath>
#include <iostream>
#include "../include/structure.hpp"

hammer::hammer(double x, double y, int player_length, int plater_height,
     int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions*>& vector_of_colliders)
:pendulum(x,y,"textures/hammer.png", player_length, plater_height, spritesheet_grid_lenght, spritesheet_grid_height, vector_of_colliders){
        _rope_length = 30;
}

void hammer::set_differences(){
    _diff_x = _rope_length * sin(_angle) + 20;
    _diff_y = -(_rope_length * cos(_angle)) + 30;
}

void hammer::sum_x_y_pendulum(bool vertical_or_horizontal, std::vector<has_collisions *> &vector_of_colliders){
    if(vertical_or_horizontal){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _go_to_center_x += 5;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) _go_to_center_x -= 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) _angular_velocity += 0.03;

        _angular_velocity += _spdx/50;

    }else{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) _go_to_center_y += 5;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) _go_to_center_y -= 5;
    }
    pendulum::sum_x_y_pendulum(vertical_or_horizontal, vector_of_colliders);
}