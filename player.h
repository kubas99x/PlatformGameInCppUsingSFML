#ifndef PLAYER_H
#define PLAYER_H

#include <texture_functions.h>
#include <SFML/Graphics.hpp>

#include <collision.h>

enum class hero_action
    {
        standing,
        standing_left,
        walking,
        walking_left,
        jumping,
        falling,
        attack1,
        attack1_left,
    };

class player : public texture_functions
{
private:
    //Time
    sf::Clock clock;
    sf::Time time_;

    //wsk
    collision * collision_;

    //Texture vector
    std::vector <sf::Texture> textures_;

    //elements of sprites
    std::vector <sf::IntRect> standing_animations;
    std::vector <sf::IntRect> standing_animations_left;
    std::vector <sf::IntRect> walking_animations;
    std::vector <sf::IntRect> jumping_animations;
    std::vector <sf::IntRect> attack1_animations;
    std::vector <sf::IntRect> attack1_animations_left;

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
    void hero_jumping();
    void hero_check_fight();


    //hero variables
    float hero_frame_time_;
    int hero_step_int_standing_;
    int hero_step_int_walking_;
    int hero_step_int_jumping_;
    int hero_step_int_attack1_;



    //Variables
    float gravity_;
    float velocity_x_;
    float velocity_y_;                  //to jest do zmiany, bo bohater bedzie skakal
    float velocity_jumping_;
    float jumping_time_;

    //bools
    bool hero_animation_change_;
    bool walking_;
    bool hero_in_air_;
    bool can_jump_;
    bool hero_jumping_;
    bool attack1_;
    bool attack1_still_;
    bool was_walking_left_;

protected:
    //Hero sprite
    sf::Sprite hero_;                       //bohater
public:
    player();
    player (collision *wsk);
    ~player();

    //Enum
    hero_action hero_action_;

    //public functions
    void render(sf::RenderWindow &window);
    void update_hero();
    float return_hero_x_position();
    sf::Sprite return_hero();

    void set_wsk_collision(collision *wsk);
};

#endif // PLAYER_H
