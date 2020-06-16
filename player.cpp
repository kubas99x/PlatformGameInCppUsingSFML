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
    this->hero_step_int_jumping_=0;
    this->hero_step_int_attack1_=0;
    this->hero_step_int_dying_=0;
    this->velocity_x_=230;
    this->velocity_y_=0;
    this->gravity_=5;
    this->velocity_jumping_ = 150;
    this->velocity_jumping_start_=150;
    this->hero_animation_change_=false;
    this->walking_=false;
    this->hero_in_air_=true;
    this->can_jump_ = true;
    this->hero_jumping_ = false;
    this->hero_action_=hero_action::standing;
    this->attack1_ = true;
    this->attack1_still_ = false;
    this->was_walking_left_ = false;
    this->hp_=100;
}

void player::download_textures()
{
    this->textures_.emplace_back(this->get_textures ("textures/standing.png"));      //0      //standing texture
    this->textures_.emplace_back(this->get_textures ("textures/walking.png"));       //1
    this->textures_.emplace_back(this->get_textures ("textures/jumping.png"));       //2
    this->textures_.emplace_back(this->get_textures ("textures/walking_left.png"));  //3
    this->textures_.emplace_back(this->get_textures ("textures/attack1.png"));       //4     //attack 1
    this->textures_.emplace_back(this->get_textures ("textures/standing_left.png")); //5    //standing left
    this->textures_.emplace_back(this->get_textures ("textures/attack1_left.png"));  //6
    this->textures_.emplace_back(this->get_textures ("textures/death.png"));  //7
}

void player::set_hero()
{
    this->hero_.setTexture (this->textures_[0]);
    this->hero_.setTextureRect (standing_animations[0]);
    this->hero_.setScale (2.5,2.5);
    this->hero_.setPosition (0,200);
}

void player::set_hero_sprites()
{

    //standing animations
    for(int i=60; i<170*16; i+=170)
    {
        standing_animations.emplace_back(sf::IntRect(i,40,40,36));
    }
    for(int i=70; i<170*16; i+=170)
    {
        standing_animations_left.emplace_back(sf::IntRect(i,40,40,36));
    }
    //walking animations
    for(int i=60; i<170*8; i+=170)
    {
        walking_animations.emplace_back(sf::IntRect(i,40,45,36));
    }

    //jumping animations        (13 animacji) (od 7 zaczyna obrot)
    for(int i=60; i<220*8; i+=220)
    {
        jumping_animations.emplace_back(sf::IntRect(i,40,60,36));
    }
    for(int i=1835; i<230*5 + 1835; i+=230)
    {
        jumping_animations.emplace_back(sf::IntRect(i,5,60,50));
    }
    jumping_animations.emplace_back(sf::IntRect(2990,15,60,50));

    //fighting animations
    for(int i=58; i<170*30+60; i+=170)
    {
        attack1_animations.emplace_back(sf::IntRect(i,25,60,55));
    }
    for(int i=50; i<170*30+60; i+=170)
    {
        attack1_animations_left.emplace_back(sf::IntRect(i,25,60,55));
    }
    for(int i=60; i<170*41; i+=170)
    {
        dying_animations.emplace_back(sf::IntRect(i,40,60,36));      //wycinanie na 40 jak cos
    }
}



void player::update_hero_step_int()
{
    hero_frame_time_+=time_.asSeconds ();
    if(hero_frame_time_>=1.0f/13.0f && (this->hero_action_==hero_action::standing || this->hero_action_==hero_action::standing_left))
    {
        hero_step_int_standing_++;
        hero_frame_time_=0;
        hero_animation_change_=true;
    }
    if(hero_frame_time_>=1.0f/13.0f && (this->hero_action_==hero_action::walking || this->hero_action_==hero_action::walking_left))
    {
        hero_step_int_walking_++;
        hero_frame_time_=0;
        hero_animation_change_=true;
    }
    if(hero_frame_time_>=1.0f/15.0f && this->hero_action_==hero_action::jumping)
    {
        hero_step_int_jumping_++;
        hero_frame_time_=0;
        hero_animation_change_=true;
    }
    if(hero_frame_time_>=1.0f/15.0f && (this->hero_action_==hero_action::attack1 || this->hero_action_==hero_action::attack1_left))
    {
        hero_step_int_attack1_++;
        hero_frame_time_=0;
        hero_animation_change_=true;
    }
    if(hero_frame_time_>=1.0f/13.0f && this->hero_action_==hero_action::dying)
    {
        hero_step_int_dying_++;
        hero_frame_time_=0;
        hero_animation_change_=true;
    }


}

void player::choose_hero_animation()
{
    if(this->hero_animation_change_ && (this->hero_action_==hero_action::standing || this->hero_action_==hero_action::standing_left))               //standing
    {
        if(this->hero_step_int_standing_>=standing_animations.size ()-1)
        {
            hero_step_int_standing_=0;
        }
        if(this->hero_action_==hero_action::standing)
        {
            this->hero_.setTexture (this->textures_[0]);
            this->hero_.setTextureRect (this->standing_animations[this->hero_step_int_standing_]);
        }
        else
        {
            this->hero_.setTexture (this->textures_[5]);
            this->hero_.setTextureRect (this->standing_animations_left[this->hero_step_int_standing_]);
        }

    }

    if(this->hero_animation_change_ && (this->hero_action_==hero_action::walking || this->hero_action_==hero_action::walking_left) )               //walking
    {
        if(this->hero_action_==hero_action::walking)
        {
            this->hero_.setTexture (this->textures_[1]);
        }
        else
        {
            this->hero_.setTexture (this->textures_[3]);

        }
        this->hero_.setTextureRect (this->walking_animations[this->hero_step_int_walking_]);
        if(this->hero_step_int_walking_>=walking_animations.size ()-1)
        {
            hero_step_int_walking_=0;
        }
    }

    if(this->hero_animation_change_ && this->hero_action_==hero_action::jumping)               //walking
    {
        this->hero_.setTexture (this->textures_[2]);
        //this->hero_.setTextureRect (this->jumping_animations[this->hero_step_int_jumping_]);
        this->hero_.setTextureRect (this->jumping_animations[13]);
        if(this->hero_step_int_jumping_>=jumping_animations.size ()-1)
        {
            hero_step_int_jumping_=0;
        }
    }

    //fight animation
    if(this->hero_animation_change_ && (this->hero_action_==hero_action::attack1 || this->hero_action_==hero_action::attack1_left ))               //standing
    {
        if(this->hero_step_int_attack1_>=attack1_animations.size ()-1)
        {
            hero_step_int_attack1_=0;
        }
        if(this->hero_action_==hero_action::attack1)
        {
            this->hero_.setTexture (this->textures_[4]);
            this->hero_.setTextureRect (this->attack1_animations[this->hero_step_int_attack1_]);
        }
        else
        {
            this->hero_.setTexture (this->textures_[6]);
            this->hero_.setTextureRect (this->attack1_animations_left[attack1_animations.size ()-1-this->hero_step_int_attack1_]);
        }
    }


    if(this->hero_animation_change_ && this->hero_action_==hero_action::dying)
    {
        this->hero_.setTexture (this->textures_[7]);
        this->hero_.setTextureRect (this->dying_animations[this->hero_step_int_dying_]);
    }
    this->hero_animation_change_ = false;

}

void player::hero_check_moves()
{
    bool any=false;     //bool zeby zmienic animacje na stanie jezeli bohater sie nie rusza

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->can_jump_) || this->hero_jumping_)
    {
        this->can_jump_  = false;
        this->hero_jumping_ = true;

        if(velocity_jumping_start_>0 && !collision_->check_standing_collision (hero_,-3*velocity_jumping_*time_.asSeconds (),standing_animations[0]))
        {

            hero_.move (0, -3*velocity_jumping_*time_.asSeconds ());

            velocity_jumping_start_-=3*velocity_jumping_*time_.asSeconds ();
        }
        else
        {
            hero_jumping_ = false;
            hero_step_int_jumping_ = 0;
            velocity_jumping_start_=150;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&& !collision_->check_walking_collision (hero_,-1*velocity_x_*time_.asSeconds (),walking_animations[0]))
    {
        hero_.move (-1*velocity_x_*time_.asSeconds (),0);
        this->hero_action_=hero_action::walking_left;
        any=true;
        was_walking_left_ = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !collision_->check_walking_collision (hero_,velocity_x_*time_.asSeconds (),walking_animations[0]))
    {
        hero_.move (velocity_x_*time_.asSeconds (),0);
        this->hero_action_=hero_action::walking;
        any=true;
        was_walking_left_=false;
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && attack1_) || attack1_still_)
    {
        if(attack1_)
        {
            hero_.move (0, -40);
        }
        if(this->hero_action_==hero_action::standing || this->hero_action_==hero_action::walking || this->hero_action_==hero_action::attack1)
        {
           this->hero_action_=hero_action::attack1;                 //warunek okreslajacy w ktora strone jest skierowany bohater
        }
        else if (this->hero_action_!=hero_action::attack1_left)
        {
           this->hero_action_=hero_action::attack1_left;
        }
        any=true;
        attack1_=false;
        attack1_still_=true;
        if(hero_step_int_attack1_==attack1_animations.size()-1)
        {
            any=false;
            attack1_=true;
            attack1_still_=false;
            hero_.move(0,40);
            hero_step_int_attack1_++;
        }
    }
    if(hero_jumping_)
    {
        hero_action_ = hero_action::jumping;
    }
    if(!any && !hero_jumping_ && !attack1_still_ )
    {
        hero_animation_change_=true;
        if(!was_walking_left_)
        {
        this->hero_action_=hero_action::standing;
        }
        else
        {
        this->hero_action_=hero_action::standing_left;
        }
    }

}

void player::hero_gravity_move()
{

    //optymalizuj to by sie nie powtarzaly te same instrukcje
    if(!collision_-> check_standing_collision (hero_ , velocity_y_+=gravity_*time_.asSeconds (), standing_animations[0]) && !this->hero_jumping_ && !attack1_still_)                  //sprawdzamy czy bohater stoi na platformie
    {
        if(velocity_y_<10)
        {
            this->velocity_y_+=gravity_*time_.asSeconds ();
        }
        this->hero_.move (0,velocity_y_);

    }
    else if(attack1_still_ && !collision_-> check_standing_collision (hero_ , velocity_y_+=gravity_*time_.asSeconds (), attack1_animations[0] ))
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
        this->can_jump_ = true;
    }
}



float player::return_hero_x_position()
{
    return hero_.getPosition ().x;
}

float player::return_hp()
{
    return hp_;
}

void player::check_hero_hp()
{
    //dodaj napis przegranej itp.
    if(hp_<=0)
    {
        hero_action_=hero_action::dying;
    }
    if(this->hero_step_int_dying_>=dying_animations.size ()-1)
    {
        hp_=100;
        hero_step_int_dying_=0;
        hero_.setPosition (0,200);
        hero_action_=hero_action::standing;
        was_walking_left_= false;
    }

}

void player::update_hero()
{

    this->time_ = clock.restart();              //restartuje zegar

    this->hero_gravity_move ();                 //sprawdza czy bohater znajduje sie w powietrzu

    this->update_hero_step_int ();              //zwieksza numer wybieranej klatki

    if(hero_action_!=hero_action::dying)
    {
    this->hero_check_moves ();                  //sprawdza czy bohater sie rusza
    }

    this->choose_hero_animation ();             //wybiera odpowiednia animacje bohatera

    this->check_hero_hp ();

}

sf::Sprite player::return_hero()
{
    return hero_;
}

sf::IntRect player::return_standing_animation()
{
    return standing_animations[0];
}

void player::render(sf::RenderWindow &window)
{
    window.draw(hero_);
}




