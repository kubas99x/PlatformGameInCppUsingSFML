#include "platform.h"

platform::platform()
{
    this->download_textures ();
    this->download_sprites ();
    this->set_sprites ();

}

platform::~platform()
{

}

void platform::render(sf::RenderWindow &window)
{
    for(const auto  &el : sprites_)
    {
        window.draw (el);
    }
}

void platform::download_textures()
{
    this->textures_.emplace_back(this->get_textures ("textures/platforms.png"));
}

void platform::download_sprites()
{
    this->sprites_.emplace_back(get_sprites(this->textures_[0]));
    this->sprites_.emplace_back(get_sprites(this->textures_[0]));
    this->sprites_.emplace_back(get_sprites(this->textures_[0]));

}

void platform::set_sprites()
{
    sprites_[0].setTextureRect (sf::IntRect(18, 27 , 253 , 35));
    sprites_[0].setPosition (720,700);
    sprites_[0].setScale (0.5, 1);
    sprites_[1].setTextureRect (sf::IntRect(18, 27 , 253 , 35));
    sprites_[1].setPosition (930,620);
    sprites_[1].setScale (0.5, 1);
    sprites_[2].setTextureRect (sf::IntRect(18, 27 , 253 , 35));
    sprites_[2].setPosition (1140,540);
    sprites_[2].setScale (0.5, 1);



}
