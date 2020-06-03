#ifndef PLATFORM_H
#define PLATFORM_H

#include <texture_functions.h>
#include <SFML/Graphics.hpp>

#include "collision.h"

class platform : public texture_functions
{
private:
    //Texture vector
    std::vector <sf::Texture> textures_;

    //wsk
    collision * collision_;

    //Sprite vector
    std::vector <sf::Sprite> sprites_;

    //vector with start positions
    std::vector <sf::Vector2f> start_position_;

    //functions
    void download_textures();
    void download_sprites();
    void set_sprites();
    void save_start_position();

public:
    platform();
    platform(collision *wsk);
    ~platform();

    //public functions
    void render(sf::RenderWindow &window);
    void update_platforms(const float &pos_x);
    std::vector <sf::Sprite> return_sprites();


};

#endif // PLATFORM_H
