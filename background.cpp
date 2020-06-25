#include "background.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



background::background()
{

    this->download_textures ();
    this->download_sprites ();
    this->set_sprites ();
}

background::~background()
{

}

void background::render(sf::RenderWindow &window)
{
    for(const auto  &el : sprites_)
    {
        window.draw (el);
    }
}

void background::download_textures()
{
    this->textures_.emplace_back(this->get_textures ("textures/scene1.png"));
    this->textures_.emplace_back(this->get_textures ("textures/scene2.png"));

}

void background::download_sprites()
{
    this->sprites_.emplace_back(get_sprites(this->textures_[0]));
    this->sprites_.emplace_back(get_sprites(this->textures_[1]));

}

void background::set_sprites()
{
    sprites_[0].setPosition (0,0);
    sprites_[1].setPosition (1440,0);

}



