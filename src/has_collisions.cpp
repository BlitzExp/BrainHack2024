#include "../include/structure.hpp"
#include <iostream>

has_collisions::has_collisions(double x, double y, std::string texture, int l, int h,
     int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions*>& vector_of_colliders)
:object(x, y, texture, spritesheet_grid_lenght, spritesheet_grid_height){
    vector_of_colliders.push_back(this);
}

has_collisions* has_collisions::collision_check(std::vector<has_collisions*>& vector_of_colliders){
    int right_collision = _x + _length;
    int down_collision = _y + _height;
    bool any_collisions = 0;
    has_collisions* object_collision = NULL;
 
    std::vector<has_collisions*>::iterator iter;
    iter = std::find(vector_of_colliders.begin(), vector_of_colliders.end(), this);
    std::vector<has_collisions*>::iterator pos = vector_of_colliders.begin() + int(iter - vector_of_colliders.begin());
    vector_of_colliders.erase(pos);
    for (auto i:vector_of_colliders){
        int left_collision2 = i -> get_x();
        int right_collision2 = left_collision2 + i -> get_length();
        int up_collision2 = i -> get_y();
        int down_collision2 = up_collision2 + i -> get_height();

        any_collisions = (right_collision > left_collision2 && //right side collision
                            _x < right_collision2 && //left side collision
                            _y < down_collision2 && //up collision
                            down_collision > up_collision2);//down collision
        if (any_collisions) {
            vector_of_colliders.push_back(this);
            return i;
        }
    }

    vector_of_colliders.push_back(this);
    
    return NULL;
}

void has_collisions::collisions(std::vector<has_collisions*>& vector_of_colliders, bool vertical_or_horizontal){
    has_collisions* whom_collided = collision_check(vector_of_colliders);
    if(collision_check(vector_of_colliders)){
        if (vertical_or_horizontal){
            int left_collision2 = whom_collided -> get_x();
            int right_collision2 = left_collision2 + whom_collided -> get_length();
        
            if(_last_frame_x - _x < 0){
                _x -= (_x + _length) - left_collision2;
            } else{
                _x += (right_collision2) - _x;
            }
            _spdx = 0;
            _extra_spdx = 0;

        }else{
            int up_collision2 = whom_collided -> get_y();
            int down_collision2 = up_collision2 + whom_collided -> get_height();

            if(_spdy > 0){
                _y -= _y + _height - up_collision2;
            } else{
                _y += (down_collision2) - _y;
            }
            _spdy = 0;
        }
    }

    if(vertical_or_horizontal){
        _last_frame_x = _x;
    }
    else{
        _last_frame_y = _y;
    }

}