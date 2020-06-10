#include "new_platforms.h"
#include <iostream>
new_platform::new_platform()
{

}

new_platform::new_platform(float pos_x, float pos_y, float scale_x, float scale_y, float width, float height, const platform_type &type)
{
    this->type_=type;
    download_textures ();
    set_sprites (pos_x, pos_y, scale_x, scale_y, width, height);
}

new_platform::new_platform(float pos_x, float pos_y, float scale_x, float scale_y, const platform_type &type )
{
    this->type_=type;
    download_textures ();
    set_sprites (pos_x, pos_y, scale_x, scale_y);
}

new_platform::~new_platform()
{

}

void new_platform::download_textures ()
{
    sf::Texture tmp;
    switch(type_)
    {
    case platform_type::grass:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(320 , 15, 175, 65));        //tekstura samej  trawy z ziemia by mozna powielac
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    case platform_type::wood:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(20, 27 , 250 , 35));
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    case platform_type::rock_with_gras:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(683 , 15, 220, 65));
        texture_=tmp;
        texture_.setRepeated (false);
        break;
    }
    case platform_type::rock_pion:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(21 , 80, 120, 65));
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    case platform_type::rock:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(780 , 15, 120, 65));
        texture_=tmp;
        texture_.setRepeated (true);
        break;
    }
    case platform_type::grass_pocz:
    {
        tmp.loadFromFile ("textures/platforms.png", sf::IntRect(535 , 15, 130, 65));
        texture_=tmp;
        texture_.setRepeated (false);
        break;
    }
    default:
    {
        std::cout<<"Cos poszlo nie tak"<<std::endl;
        break;
    }
    }
}

void new_platform::set_sprites(float pos_x, float pos_y, float scale_x, float scale_y)
{
    sprite_.setTexture (texture_);
    sprite_.setPosition (pos_x,pos_y);
    sprite_.setScale (scale_x,scale_y);
}

void new_platform::set_sprites(float pos_x, float pos_y, float scale_x, float scale_y, float width, float height)
{
    sprite_.setTexture (texture_);
    sprite_.setPosition (pos_x,pos_y);
    sprite_.setScale (scale_x,scale_y);
    sprite_.setTextureRect (sf::IntRect(0,0,width, height));

}

void new_platform::render(sf::RenderWindow &window)
{

    window.draw (sprite_);

}

sf::Sprite new_platform::return_sprite()
{
    return sprite_;
}

