#include "../include/structure.hpp"
#include "../src/functions.cpp"
#include <iostream>
#include <cmath>

pendulum::pendulum(double x, double y, std::string texture, int l, int h,
    int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions*>& vector_of_colliders)
:has_collisions(x, y, texture, l, h, spritesheet_grid_lenght, spritesheet_grid_height, vector_of_colliders){
    _player_sprite.setOrigin(_length/2,0);
    _diff_x = 24;
}

void pendulum::pendulum_physics(bool vertical_or_horizontal, std::vector<has_collisions*>& vector_of_colliders){
        //angular acc and vel calculations

    if (vertical_or_horizontal){
        double lesser_angle = _angle + M_PI / 2;
        _added_x = cos(lesser_angle) * _rope_length;

        int to_sum;

        _last_center_x = _go_to_center_x;

        _center_x += (_go_to_center_x - _center_x) * _follow_speed;
    } else{
        double gravity = (_rope_length/20);
        _acceleration = (- gravity / ceil(_rope_length)) * sin(_angle);
        _angular_velocity += _acceleration;
        _angular_velocity *= 0.95;
        _angle += _angular_velocity;
        double lesser_angle = _angle + M_PI / 2;
        _added_y = sin(lesser_angle) * _rope_length;

        _last_center_y = _go_to_center_y;

        _center_y += (_go_to_center_y - _center_y) * _follow_speed;

        _rotation = _angle * 180/M_PI;
    }

}

int pendulum::get_center_x(){
    return _center_x;
}

int pendulum::get_center_y(){
    return _center_y;
}

void pendulum::sum_x_y_pendulum( bool vertical_or_horizontal, std::vector<has_collisions*>& vector_of_colliders){
    
    if (vertical_or_horizontal){
        _y = _center_y + _added_y;
        if(collision_check(vector_of_colliders)){
            _go_to_center_y = _last_center_y;

            if(_last_frame_y < _y){

                _y = _last_frame_y;
            }
            _angular_velocity = 0;
        }
    } else{
        _x = _center_x + _added_x;
        if(collision_check(vector_of_colliders)){
            _go_to_center_x = _last_center_x;
            _angular_velocity = 0;
        }

    }

}