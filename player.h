#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "texture_functions.h"
#include "collision.h"
#include "enum_classes.h"

class player : public texture_functions
{
private:
    //Time
    sf::Clock clock;
    sf::Time time_;

    sf::Vector2u window_size_;

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
    std::vector <sf::IntRect> dying_animations;
    std::vector <sf::IntRect> spin_attack_animations;
    std::vector <sf::IntRect> spin_attack_animations_left;

    //health
    sf::Sprite health_bar_;
    std::vector <sf::IntRect> hp_steps_animations;
    void check_hero_hp();


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



    //hero variables
    float hero_frame_time_;
    int hero_step_int_standing_;
    int hero_step_int_walking_;
    int hero_step_int_jumping_;
    int hero_step_int_attack1_;
    int hero_step_int_dying_;

    //sound effects
    std::vector <sf::SoundBuffer> buffer;
    sf::Sound sound;
    void set_sound_effects();

    //Variables
    float gravity_;
    float velocity_x_;
    float velocity_y_;                  //to jest do zmiany, bo bohater bedzie skakal
    float velocity_jumping_;
    float velocity_jumping_start_;


    //bools
    bool hero_animation_change_;
    bool walking_;
    bool can_jump_;
    bool hero_jumping_;
    bool attack1_;
    bool attack1_still_;
    bool was_walking_left_;
    bool spin_attack_;
    bool spin_attack_still_;
protected:
    //Hero sprite
    sf::Sprite hero_;                       //bohater
public:
    player();
    player (collision *wsk);
    ~player();

    //Enum
    hero_action hero_action_;

    float hp_;

    //public functions
    void render(sf::RenderWindow &window);
    void update_hero();
    void get_window_size(const sf::Vector2u &window_s);
    float return_hero_x_position();
    float return_hp();
    sf::Sprite return_hero();
    sf::IntRect return_standing_animation();

    void set_wsk_collision(collision *wsk);
};

#endif // PLAYER_H
