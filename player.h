#ifndef PLAYER_H
#define PLAYER_H

#include <texture_functions.h>
#include <SFML/Graphics.hpp>

class player : public texture_functions
{
private:
    //Time
    sf::Clock clock;
    sf::Time time_;

    //Texture vector
    std::vector <sf::Texture> textures_;

    //Sprites
    sf::Sprite standing_sprite_;            //Sprite z zaladowana tesktura chodzenia

    //Hero sprite
    sf::Sprite hero_;                       //bohater

    //elements of sprites
    std::vector <sf::IntRect> standing_animations;

    //functions
    void download_textures();
    void set_standing_sprites();
    void init_variables();

    //hero functions
    void set_hero();
    void update_hero_step_int();
    void choose_hero_animation();

    //hero variables
    float hero_frame_time_;
    int hero_step_int_;
    bool hero_animation_change_;

public:
    player();
    ~player();

    //public functions
    void render(sf::RenderWindow &window);
    void update_hero();
};

#endif // PLAYER_H
