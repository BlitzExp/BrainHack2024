#include "../include/structure.hpp"

object::object(double x, double y, std::string texture, 
 int spritesheet_grid_lenght, int spritesheet_grid_height):_spritesheet_grid_lenght(spritesheet_grid_lenght), 
 _spritesheet_grid_height(spritesheet_grid_height), _x(x), _y(y){
    _player_spritesheet.loadFromFile(texture);
    sound.setBuffer(buffer);
    _player_sprite.setTexture(_player_spritesheet);
    _player_sprite.setScale(1, 1);
    _length = spritesheet_grid_lenght;
    _height = spritesheet_grid_height;

}

void object::receive_input(sf::Event event){
    
}

void object::xy_plus_spd(int vertical_or_horizontal){
    if (vertical_or_horizontal){
        _x += (int)(_spdx + _extra_spdx * _direction);
    } else{
        _y += (int)(_spdy);
    }
}

double object::get_x(){
    return _x;
}

double object::get_y(){
    return _y;
}

double object::get_spdx(){
    return _spdx;
}

double object::get_spdy(){
    return _spdy;
}

int object::get_length(){
    return _length;
}

int object::get_height(){
    return _height;
}

sf::Sprite object::get_sprite(){
    return _player_sprite;
}

double object::get_frame_x(){
    return _frame_x;
}

int object::get_direction(){
    return _direction;
}

int object::get_x_plus_diff_x(){
    return _x + _diff_x;
}

void object::set_frame_x(double frame_x){
    _frame_x = frame_x;
}

void object::set_direction(int direction){
    _direction = direction;
}

void object::set_x(int x){
    _x = x;
}

void object::set_y(int y){
    _y = y;
}

void object::set_spdx(double spdx){
    _spdx = spdx;
}

void object::set_spdy(double spdy){
    _spdy = spdy;
}

void object::set_diff_x(int diff_x){
    _diff_x = diff_x;
}

void object::set_diff_y(int diff_y){
    _diff_y = diff_y;
}

void object::set_spritesheet_coords(){
    _spritesheet_coords.left = _frame_x * _spritesheet_grid_lenght + _spritesheet_grid_lenght * ((_direction - 1)/-2);
    _spritesheet_coords.width = _spritesheet_grid_lenght * _direction;
    _spritesheet_coords.height = _spritesheet_grid_height;
}

void object::set_rotation(float rotation){
    _rotation = rotation;
}

sf::Sprite object::draw(float parallax){

    int x_with_diff = _x + _diff_x;
    int y_with_diff = _y + _diff_y;
    int sum_due_to_squish = ((_direction - 1)/-2) * (abs(_squish - 1) * (_spritesheet_grid_lenght) + (_squish < 1));
    int sum_due_to_zoom_x = ((camera_zoom - 1))* ((x_with_diff + sum_due_to_squish));
    int sum_due_to_zoom_y = (camera_zoom - 1)* (y_with_diff);
    int sum_due_to_parallax_x = ((-2 + _SCREEN_WIDTH * (-1 + parallax)) / (2 * parallax) + 1);
    int sum_due_to_parallax_y = ((-2 + _SCREEN_HEIGHT * (-1 + parallax)) / (2 * parallax) + 1);
    _player_sprite.setPosition(x_with_diff + sum_due_to_squish - (camera_x/parallax) + sum_due_to_zoom_x + sum_due_to_parallax_x, y_with_diff - (camera_y / parallax) + sum_due_to_zoom_y + sum_due_to_parallax_y);
    _player_sprite.setScale(camera_zoom * _squish, camera_zoom);

    set_spritesheet_coords();
    _player_sprite.setRotation(_rotation);
    _player_sprite.setTextureRect(_spritesheet_coords);
    return _player_sprite;
}

void object::gravity(double strength){
    _spdy += strength;
    _y += _spdy;

    if (_y > 1000){
        _alive = 0;
    }
}