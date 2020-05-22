#include "player.h"

player::player()
{
    this->download_textures ();
    this->set_standing_sprites ();
    this->set_hero ();
    this->init_variables ();
}
player::~player()
{

}

void player::init_variables()
{
    this->hero_step_int_=0;
    this->hero_animation_change_=false;
}

void player::download_textures()
{
    this->textures_.emplace_back(this->get_textures ("textures/standing.png"));     //standing texture
}

void player::set_standing_sprites()
{
    //Czy w bohaterze bede zmienial teksture i wybieral dane klatki czy jak?

    this->standing_sprite_.setTexture (this->textures_[0]);
    for(int i=60; i<170*16; i+=170)                       //co 170pikseli wycinamy, 40 pikseli
    {
        standing_animations.emplace_back(sf::IntRect(i,40,40,45));
    }

}

void player::set_hero()
{
    this->hero_=standing_sprite_;
    this->hero_.setTextureRect (standing_animations[0]);
    this->hero_.setScale (2.5,2.5);
    this->hero_.setPosition (100,300);
}

void player::update_hero_step_int()
{
    hero_frame_time_+=time_.asSeconds ();
    if(hero_step_int_==standing_animations.size ()-1)
    {
        hero_step_int_=0;
    }
    if(hero_frame_time_>=1.0f/13.0f)
    {
        hero_step_int_++;
        hero_frame_time_=0;
    }

}
void player::choose_hero_animation()
{
    if(this->hero_frame_time_==0)
    {
        this->hero_.setTextureRect (this->standing_animations[this->hero_step_int_]);
    }

}

void player::update_hero()
{
    this->time_ = clock.restart();
    this->update_hero_step_int ();
    this->choose_hero_animation ();

}

void player::render(sf::RenderWindow &window)
{
    window.draw(hero_);
}






