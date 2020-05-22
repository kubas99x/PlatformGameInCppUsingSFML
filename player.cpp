#include "player.h"
#include <iostream>
player::player()
{
    this->download_textures ();
    this->set_hero_sprites ();
    this->set_hero ();
    this->init_variables ();
}
player::~player()
{

}

void player::init_variables()
{
    this->hero_step_int_standing_=0;
    this->hero_step_int_walking_=0;
    this->velocity_x_=150;
    this->velocity_y_=0;
    this->gravity_=10;
    this->hero_animation_change_=false;
    this->walking_=false;
    this->hero_in_air_=true;
    this->hero_action_=hero_action::standing;

}

void player::download_textures()
{
    this->textures_.emplace_back(this->get_textures ("textures/standing.png"));     //standing texture
    this->textures_.emplace_back(this->get_textures ("textures/walking.png"));
}

void player::set_hero_sprites()
{
    //Czy w bohaterze bede zmienial teksture i wybieral dane klatki czy jak?



    //standing animations
    for(int i=60; i<170*16; i+=170)                       //co 170pikseli wycinamy, 40 pikseli
    {
        standing_animations.emplace_back(sf::IntRect(i,40,40,45));
    }
    //walking animations
    for(int i=60; i<170*8; i+=170)                       //co 170pikseli wycinamy, 40 pikseli
    {
        walking_animations.emplace_back(sf::IntRect(i,40,40,45));
    }

}

void player::set_hero()
{
    this->hero_.setTexture (this->textures_[0]);
    this->hero_.setTextureRect (standing_animations[0]);
    this->hero_.setScale (2.5,2.5);
    this->hero_.setPosition (100,300);
}

void player::update_hero_step_int()
{
    hero_frame_time_+=time_.asSeconds ();
    if(hero_frame_time_>=1.0f/13.0f && this->hero_action_==hero_action::standing)
    {
        hero_step_int_standing_++;
        hero_frame_time_=0;
    }
    if(hero_frame_time_>=1.0f/13.0f && this->hero_action_==hero_action::walking)
    {
        hero_step_int_walking_++;
        hero_frame_time_=0;
    }

}
void player::choose_hero_animation()
{
    if(this->hero_frame_time_==0 && this->hero_action_==hero_action::standing)               //standing
    {
        this->hero_.setTexture (this->textures_[0]);
        this->hero_.setTextureRect (this->standing_animations[this->hero_step_int_standing_]);
        if(this->hero_step_int_standing_==standing_animations.size ()-1)
        {
            hero_step_int_standing_=0;
        }

    }
    if(this->hero_frame_time_==0 && this->hero_action_==hero_action::walking)               //walking
    {
        this->hero_.setTexture (this->textures_[1]);
        this->hero_.setTextureRect (this->walking_animations[this->hero_step_int_walking_]);
        if(this->hero_step_int_walking_==walking_animations.size ()-1)
        {
            hero_step_int_walking_=0;
        }
    }



}

void player::hero_check_moves()
{


    bool any=false;     //bool zeby zmienic animacje na stanie jezeli bohater sie nie rusza

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        hero_.move (0,velocity_y_*time_.asSeconds ());
        this->hero_action_=hero_action::walking;
        any=true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))                    //Chwilowe 2 petle by latwiej sprawdzac kolizje
    {
        hero_.move (0,-1*velocity_x_*time_.asSeconds ());
        this->hero_action_=hero_action::walking;
        any=true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        hero_.move (-1*velocity_x_*time_.asSeconds (),0);
        this->hero_action_=hero_action::walking;
        any=true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        hero_.move (velocity_x_*time_.asSeconds (),0);
        this->hero_action_=hero_action::walking;
        any=true;
    }
    if(!any)
    {
        this->hero_action_=hero_action::standing;
    }

}

void player::hero_check_in_air()
{
    if(this->hero_in_air_)
    {
        if(velocity_y_<10)
        {
        this->velocity_y_+=gravity_*time_.asSeconds ();
        }
        this->hero_.move (0,velocity_y_);
    }
    else
    {
        this->velocity_y_=0;
    }
}

void player::update_hero()
{
    this->time_ = clock.restart();              //restartuje zegar

    //this->hero_check_in_air ();                 //sprawdza czy bohater znajduje sie w powietrzu

    this->update_hero_step_int ();              //zwieksza numer wybieranej klatki

    this->hero_check_moves ();                  //sprawdza czy bohater sie rusza

    this->choose_hero_animation ();             //wybiera odpowiednia animacje bohatera

}

void player::render(sf::RenderWindow &window)
{
    window.draw(hero_);
}






