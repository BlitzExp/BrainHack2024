#include "../include/structure.hpp"


elements::elements(double x, double y, std::string texture, int l, int h,
    int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions*>& vector_of_colliders, int changetemperature, bool water)
:has_collisions(x, y, texture, l, h, spritesheet_grid_lenght, spritesheet_grid_height, vector_of_colliders){_changetemperature=changetemperature, _water=water;};

void elements::setchangetemperature(int changetemperature){_changetemperature=changetemperature;};

void elements::setwater(bool water){_water=water;};

int elements::getchangetemperature(){return _changetemperature;};

int elements::getwater(){return _water;};

void elements::movewater(){
    if (_water==true){
        //if(get_y()>-100){
            set_y(get_y()+3);
        //};
    };
};