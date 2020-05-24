#ifndef PLATFORM_H
#define PLATFORM_H

#include <texture_functions.h>
#include <SFML/Graphics.hpp>

#include <collision.h>

class platform : public texture_functions , public collision
{
private:
    //Texture vector
    std::vector <sf::Texture> textures_;

    //Sprite vector
    std::vector <sf::Sprite> sprites_;

    //functions
    void download_textures();
    void download_sprites();
    void set_sprites();

public:
    platform();
    ~platform();

    //public functions
    void render(sf::RenderWindow &window);
    std::vector <sf::Sprite> return_sprites();

};

#endif // PLATFORM_H
