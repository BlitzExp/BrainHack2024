#include "../include/structure.hpp"

has_collisions::has_collisions(double x, double y, std::string texture, int l, int h,
     int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions>& vector_of_colliders)
:object(x, y, texture, spritesheet_grid_lenght, spritesheet_grid_height){
}

bool has_collisions::collision_check(){
    int right_collision = _x + _length;
    return 0;
}