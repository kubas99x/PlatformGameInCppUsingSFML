#ifndef NEW_PLATFORMS_H
#define NEW_PLATFORMS_H

#include <texture_functions.h>
#include <SFML/Graphics.hpp>

#include "enum_classes.h"

class new_platform : public texture_functions
{
private:
    //Texture
    sf::Texture texture_;

    //Sprite
    sf::Sprite sprite_;

    //platform type
    platform_type type_;

    //functions
    void download_textures();
    void set_sprites(float pos_x, float pos_y, float scale_x, float scale_y);
    void set_sprites(float pos_x, float pos_y, float scale_x, float scale_y, float width, float height);

public:
    new_platform();
    new_platform(float pos_x , float pos_y , float scale_x, float scale_y , float width, float height, const platform_type &type );
    new_platform(float pos_x , float pos_y , float scale_x, float scale_y , const platform_type &type );
    ~new_platform();

    //public functions
    void render(sf::RenderWindow &window);
    sf::Sprite return_sprite();


};
#endif // NEW_PLATFORMS_H
