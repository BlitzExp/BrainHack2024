#ifndef structure
#define structure

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <tuple>
#include <list>

extern int camera_x;
extern int camera_y;
extern float camera_zoom;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

class object{
public:
    explicit object(double x, double y, std::string texture,
     int spritesheet_grid_lenght, int spritesheet_grid_height);

    virtual sf::Sprite draw(float parallax = 1);
    void xy_plus_spd(int vertical_or_horizontal);
    void resize(double res_x = 1, double res_y = 1);
    virtual void receive_input(sf::Event event);
    double get_x();
    double get_y();
    double get_spdx();
    double get_spdy();
    int get_length();
    int get_height();
    int get_direction();
    int get_x_plus_diff_x();
    sf::Sprite get_sprite();
    void set_spritesheet_coords();
    void set_direction(int direction);
    void set_x(int x);
    void set_y(int y);
    void set_spdx(double spdx);
    void set_spdy(double spdy);
    void set_diff_x(int diff_x);
    void set_diff_y(int diff_y);
    double get_frame_x();
    void set_frame_x(double frame_x);
    void set_rotation(float rotation);
    bool _alive = 1;

protected:
    double _length = 0;
    double _height = 0;
    double _spdx = 0;
    double _spdy = 0;
    double _extra_spdx = 0;
    double _extra_spdy = 0;
    double _conserved_spdy = 0;
    double _conserved_spdx = 0;
    double _slipperiness = 0.82;
    double _SPD_CONSTANT = 1;
    double _frame_x = 0;
    double _squish = 1;
    double _x = 0;
    double _y = 0;
    int _last_frame_x = 0;
    int _last_frame_y = 0;
    int _frame_count;
    int _spritesheet_grid_lenght;
    int _spritesheet_grid_height;
    sf::Sprite _player_sprite;
    sf::Texture _player_spritesheet;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::IntRect _spritesheet_coords;
    int _direction = 1;
    std::string _state = "";
    int _SCREEN_WIDTH = SCREEN_WIDTH;
    int _SCREEN_HEIGHT = SCREEN_HEIGHT;
    float _rotation = 0;
    int _diff_x = 0;
    int _diff_y = 0;
    sf::Keyboard::Key _jump_key = sf::Keyboard::Z;
    sf::Keyboard::Key _shooting_key = sf::Keyboard::LShift;

};

class has_collisions: public object{
public:
    explicit has_collisions(double x, double y, std::string texture, int player_length, int plater_height,
     int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions*>& vector_of_colliders);
    has_collisions* collision_check(std::vector<has_collisions*>& vector_of_colliders);
    void collisions(std::vector<has_collisions*>& vector_of_colliders, bool vertical_or_horizontal);
    

protected:
    int _direction_last_collision = 1;
};

class pendulum: public has_collisions{
public:
    explicit pendulum(double x, double y, std::string texture, int player_length, int plater_height,
     int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions*>& vector_of_colliders);
    void pendulum_physics(bool vertical_or_horiizontal, std::vector<has_collisions*>& vector_of_colliders);
    int get_center_x();
    int get_center_y();
    virtual void sum_x_y_pendulum(bool vertical_or_horizontal, std::vector<has_collisions*>& vector_of_colliders);
    void set_angular_speed(double vel);
    double get_angular_speed();
    void isdead(double max);
protected:
    int _added_x_linear = 0;
    int _added_x = 0;
    int _added_y = 0;
    int _frames = 0;
    int _time_retreat = 0;
    double _punch_x = 0;
    double _punch_y = 0;
    double _punch_spd = 0;
    double _angle = 1 + M_PI/4;
    double _acceleration = 0;
    double _angular_velocity = 0;
    double _rope_length = 70;
    double _center_x = 0;
    double _center_y = 0;
    double _follow_speed = 0.7;
    int _extra_x;
    int _extra_y;
    int _go_to_center_x = 0;
    int _go_to_center_y = 0;
    int _last_center_x = 0;
    int _last_center_y = 0;

};

class hammer: public pendulum{
public:
    explicit hammer(double x, double y, int player_length, int plater_height,
     int spritesheet_grid_lenght, int spritesheet_grid_height, std::vector<has_collisions*>& vector_of_colliders);
    void set_differences();
    void sum_x_y_pendulum(bool vertical_or_horizontal, std::vector<has_collisions *> &vector_of_colliders) override;

protected:

};

#endif