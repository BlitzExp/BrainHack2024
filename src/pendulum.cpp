#include "../include/structure.hpp"

pendulum::pendulum(double x, double y, std::string texture, int l, int h,
    int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions*>& vector_of_colliders)
:has_collisions(x, y, texture, l, h, spritesheet_grid_lenght, spritesheet_grid_height, vector_of_colliders){}