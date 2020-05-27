#ifndef PLAYER_H
#define PLAYER_H

#include <texture_functions.h>
#include <SFML/Graphics.hpp>

#include <collision.h>

enum class hero_action
    {
        standing,
        walking,
        jumping
    };

class player : public texture_functions
{
private:
    //Time
    sf::Clock clock;
    sf::Time time_;

    //wsk
    const collision * collision_;

    //Texture vector
    std::vector <sf::Texture> textures_;

    //elements of sprites
    std::vector <sf::IntRect> standing_animations;
    std::vector <sf::IntRect> walking_animations;

    //functions
    void download_textures();
    void set_hero_sprites();
    void init_variables();

    //hero functions
    void set_hero();
    void update_hero_step_int();
    void choose_hero_animation();
    void hero_check_moves();
    void hero_gravity_move();

    //hero variables
    float hero_frame_time_;
    int hero_step_int_standing_;
    int hero_step_int_walking_;
    float velocity_x_;
    float velocity_y_;                  //to jest do zmiany, bo bohater bedzie skakal

    //Enum
    hero_action hero_action_;

    //Variables
    float gravity_;

    //bools
    bool hero_animation_change_;
    bool walking_;
    bool hero_in_air_;

protected:
    //Hero sprite
    sf::Sprite hero_;                       //bohater
public:
    player();
    player (collision *wsk);
    ~player();

    //public functions
    void render(sf::RenderWindow &window);
    void update_hero();
    sf::Sprite return_hero();

    void set_wsk_collision(collision *wsk);
};

#endif // PLAYER_H
