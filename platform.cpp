#include "platform.h"
#include <iostream>
platform::platform()
{
    this->download_textures ();
    this->download_sprites ();
    this->set_sprites ();
    this->collision_ = nullptr;

}

platform::platform(collision *wsk)
{
    this->collision_ = wsk;
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

std::vector<sf::Sprite> platform::return_sprites()
{
     return sprites_;
}

void platform::set_wsk_collision(collision *wsk)
{
    this->collision_ = wsk;
}

void platform::download_textures()
{
    this->textures_.emplace_back(this->get_textures ("textures/platforms.png"));
    this->textures_[0].setRepeated (true);

    sf::Texture tmp;
    tmp.loadFromFile ("textures/platforms.png", sf::IntRect(320 , 15, 175, 65));        //tekstura samej  trawy z ziemia by mozna powielac
    this->textures_.emplace_back(tmp);
    this->textures_[1].setRepeated (true);

}

void platform::download_sprites()
{
    this->sprites_.emplace_back(get_sprites(this->textures_[0]));
    this->sprites_.emplace_back(get_sprites(this->textures_[0]));
    this->sprites_.emplace_back(get_sprites(this->textures_[0]));
    this->sprites_.emplace_back(get_sprites(this->textures_[1]));       //ziemia

}

void platform::set_sprites()
{
    sf::Sprite test;
    sprites_[0].setTextureRect (sf::IntRect(20, 27 , 250 , 35));
    sprites_[0].setPosition (740,700);
    sprites_[0].setScale (0.5, 1);
    sprites_[1].setTextureRect (sf::IntRect(20, 27 , 250 , 35));
    sprites_[1].setPosition (930,620);
    sprites_[1].setScale (0.5, 1);
    sprites_[2].setTextureRect (sf::IntRect(20, 27 , 250 , 35));
    sprites_[2].setPosition (1140,540);
    sprites_[2].setScale (0.5, 1);

    //ziemia
    sprites_[3].setTextureRect (sf::IntRect(320, 15 , 710 , 50));
    sprites_[3].setPosition (0,817);
    sprites_[3].setScale (1, 1);



}


