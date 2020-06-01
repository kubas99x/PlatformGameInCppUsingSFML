#include "player.h"
#include <iostream>

player::player()
{
    this->download_textures ();
    this->set_hero_sprites ();
    this->set_hero ();
    this->init_variables ();
    this->collision_ = nullptr;
}

player::player(collision *wsk)
{
    this->collision_ = wsk;
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
    this->gravity_=5;
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

    //standing animations
    for(int i=60; i<170*16; i+=170)                       //co 170pikseli wycinamy, 40 pikseli
    {
        standing_animations.emplace_back(sf::IntRect(i,40,40,36));
    }
    //walking animations
    for(int i=60; i<170*8; i+=170)                       //co 170pikseli wycinamy, 40 pikseli
    {
        walking_animations.emplace_back(sf::IntRect(i,40,45,36));
    }

}

void player::set_hero()
{
    this->hero_.setTexture (this->textures_[0]);
    this->hero_.setTextureRect (standing_animations[0]);
    this->hero_.setScale (2.5,2.5);
    this->hero_.setPosition (750,500);
}

void player::update_hero_step_int()
{
    hero_frame_time_+=time_.asSeconds ();
    if(hero_frame_time_>=1.0f/13.0f && this->hero_action_==hero_action::standing)
    {
        hero_step_int_standing_++;
        hero_frame_time_=0;
        hero_animation_change_=true;
    }
    if(hero_frame_time_>=1.0f/13.0f && this->hero_action_==hero_action::walking)
    {
        hero_step_int_walking_++;
        hero_frame_time_=0;
        hero_animation_change_=true;
    }

}
void player::choose_hero_animation()
{
    if(this->hero_animation_change_ && this->hero_action_==hero_action::standing)               //standing
    {
        if(this->hero_step_int_standing_>=standing_animations.size ()-1)
        {
            hero_step_int_standing_=0;
        }
        this->hero_.setTexture (this->textures_[0]);
        this->hero_.setTextureRect (this->standing_animations[this->hero_step_int_standing_]);




    }
    if(this->hero_animation_change_ && this->hero_action_==hero_action::walking)               //walking
    {
        this->hero_.setTexture (this->textures_[1]);
        this->hero_.setTextureRect (this->walking_animations[this->hero_step_int_walking_]);
        if(this->hero_step_int_walking_>=walking_animations.size ()-1)
        {
            hero_step_int_walking_=0;
        }
    }
    this->hero_animation_change_ = false;




}

void player::hero_check_moves()
{
    bool any=false;     //bool zeby zmienic animacje na stanie jezeli bohater sie nie rusza

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
     {
         std::cout<<"Space realised (hold)"<<std::endl;
     }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !collision_->check_standing_collision (velocity_x_*time_.asSeconds ()))
    {
        hero_.move (0,velocity_x_*time_.asSeconds ());
        this->hero_action_=hero_action::walking;
        any=true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))                    //Chwilowe 2 petle by latwiej sprawdzac kolizje
    {
        hero_.move (0,-1*velocity_x_*time_.asSeconds ());
        this->hero_action_=hero_action::walking;
        any=true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& !collision_->check_standing_collision (-1*velocity_x_*time_.asSeconds ()))
    {
        hero_.move (-1*velocity_x_*time_.asSeconds (),0);
        this->hero_action_=hero_action::walking;
        any=true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !collision_->check_walking_collision (velocity_x_*time_.asSeconds ()))
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

void player::hero_gravity_move()
{

    if(!this->collision_-> check_standing_collision (velocity_y_+=gravity_*time_.asSeconds () ))                  //sprawdzamy czy bohater stoi na platformie
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

    this->hero_gravity_move ();                 //sprawdza czy bohater znajduje sie w powietrzu

    this->update_hero_step_int ();              //zwieksza numer wybieranej klatki

    this->hero_check_moves ();                  //sprawdza czy bohater sie rusza

    this->choose_hero_animation ();             //wybiera odpowiednia animacje bohatera


}

sf::Sprite player::return_hero()
{
    return hero_;
}

void player::set_wsk_collision(collision *wsk)
{
    collision_ = wsk;
    //std::cout<<collision_->wsk_hero_collision_->getPosition ().x<<std::endl;
}

void player::render(sf::RenderWindow &window)
{
    window.draw(hero_);
}






