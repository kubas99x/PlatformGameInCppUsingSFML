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
    this->spin_attack_still_=false;
    this->was_walking_left_ = false;
    this->spin_attack_ = true;
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
    this->textures_.emplace_back(this->get_textures ("textures/death.png"));        //7
    this->textures_.emplace_back(this->get_textures ("textures/spin_attack.png"));        //8
    this->textures_.emplace_back(this->get_textures ("textures/spin_attack_left.png"));        //9
    this->textures_.emplace_back(this->get_textures ("textures/health_bar.png"));        //10


}

void player::set_hero()
{
    this->hero_.setTexture (this->textures_[0]);
    this->hero_.setTextureRect (standing_animations[0]);
    this->hero_.setScale (2.5,2.5);
    this->hero_.setPosition (0,200);        //2400
    this->health_bar_.setTexture (this->textures_[10]);
    this->health_bar_.setTextureRect (hp_steps_animations[0]);
    this->health_bar_.setPosition (0,0);
    this->health_bar_.setScale (4,4);

}

void player::set_hero_sprites()
{

    //standing animations
    for(int i=60; i<170*16; i+=170)
    {
        standing_animations.emplace_back(sf::IntRect(i,25,40,55));
    }
    for(int i=70; i<170*16; i+=170)
    {
        standing_animations_left.emplace_back(sf::IntRect(i,25,40,55));
    }
    //walking animations
    for(int i=60; i<170*8; i+=170)
    {
        walking_animations.emplace_back(sf::IntRect(i,25,45,55));
    }

    //jumping animations
    jumping_animations.emplace_back(sf::IntRect(2990,15,60,55));

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
        dying_animations.emplace_back(sf::IntRect(i,25,60,55));
    }
    for(int i=60; i<170*30; i+=170)
    {
        if(i==2440)
            i+=7;
        if(i==3297)
            i+=15;
        if(i==3822)
            i+=8;
        spin_attack_animations.emplace_back(sf::IntRect(i,25,60,55));
    }
    for(int i=37; i<170*30; i+=170)
    {
        if(i==2417)
            i+=7;
        if(i==3274)
            i+=15;
        spin_attack_animations_left.emplace_back(sf::IntRect(i,25,60,55));
        if(i==887)
        {
            i-=12;
        }
        if(i==1385)
        {
            i+=12;
        }
    }
    hp_steps_animations.emplace_back(sf::IntRect(9,21,112,11));
    hp_steps_animations.emplace_back(sf::IntRect(9,32,112,11));
    hp_steps_animations.emplace_back(sf::IntRect(10,70,112,11));
    hp_steps_animations.emplace_back(sf::IntRect(10,81,112,11));
    hp_steps_animations.emplace_back(sf::IntRect(10,92,112,11));


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
    if(hero_frame_time_>=1.0f/15.0f && (this->hero_action_==hero_action::attack1 || this->hero_action_==hero_action::attack1_left ||
                                        this->hero_action_==hero_action::spin_attack || this->hero_action_==hero_action::spin_attack_left))
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
    if(hero_action_==hero_action::jumping)
    {
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

    if(this->hero_animation_change_ && this->hero_action_==hero_action::jumping)
    {
        this->hero_.setTexture (this->textures_[2]);
        this->hero_.setTextureRect (this->jumping_animations[0]);
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
    //spin attack
    if(this->hero_animation_change_ && (this->hero_action_==hero_action::spin_attack || this->hero_action_==hero_action::spin_attack_left ))               //standing
    {
        if(this->hero_step_int_attack1_>=spin_attack_animations.size ()-1)
        {
            hero_step_int_attack1_=0;
        }
        if(this->hero_action_==hero_action::spin_attack)
        {
            this->hero_.setTexture (this->textures_[8]);
            this->hero_.setTextureRect (this->spin_attack_animations[this->hero_step_int_attack1_]);
        }
        else
        {
            this->hero_.setTexture (this->textures_[9]);
            this->hero_.setTextureRect (this->spin_attack_animations_left[attack1_animations.size ()-1-this->hero_step_int_attack1_]);
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
        if(!attack1_still_ && !spin_attack_still_)
        {
            this->hero_action_=hero_action::walking_left;

        }
        any=true;
        was_walking_left_ = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !collision_->check_walking_collision (hero_,velocity_x_*time_.asSeconds (),walking_animations[0]))
    {
        hero_.move (velocity_x_*time_.asSeconds (),0);
        if(!attack1_still_ && !spin_attack_still_)
        {
            this->hero_action_=hero_action::walking;
        }
        any=true;
        was_walking_left_=false;
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && attack1_ && !spin_attack_still_) || attack1_still_ )
    {
        if(this->hero_action_==hero_action::standing || this->hero_action_==hero_action::walking )
        {
            this->hero_action_=hero_action::attack1;                 //warunek okreslajacy w ktora strone jest skierowany bohater
        }
        else if (this->hero_action_!=hero_action::attack1)
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
            hero_step_int_attack1_++;
        }
    }

    //Spin attack
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::X) && spin_attack_ && !attack1_still_) || spin_attack_still_ )
    {

        if(this->hero_action_==hero_action::standing || this->hero_action_==hero_action::walking )
        {
            this->hero_action_=hero_action::spin_attack;                 //warunek okreslajacy w ktora strone jest skierowany bohater
        }
        else if (this->hero_action_!=hero_action::spin_attack)
        {
            this->hero_action_=hero_action::spin_attack_left;
        }
        any=true;
        spin_attack_=false;
        spin_attack_still_=true;
        if(hero_step_int_attack1_==spin_attack_animations.size()-1)
        {
            any=false;
            spin_attack_=true;
            spin_attack_still_=false;
            hero_step_int_attack1_++;
        }
    }
    if(hero_jumping_ && !attack1_still_ && !spin_attack_still_)
    {
        hero_action_ = hero_action::jumping;
    }
    if(!any && !hero_jumping_ && !attack1_still_  && !spin_attack_still_)
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

    if(!collision_-> check_standing_collision (hero_ , velocity_y_+=gravity_*time_.asSeconds (), standing_animations[0]) && !this->hero_jumping_ && !attack1_still_)                  //sprawdzamy czy bohater stoi na platformie
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
    if(hero_.getPosition ().x>720)
    {
    health_bar_.setPosition (hero_.getPosition ().x - 720 , 0);
    }
    if(hp_==100)
    {
        health_bar_.setTextureRect (hp_steps_animations[0]);
    }
    if(hp_==75)
    {
        health_bar_.setTextureRect (hp_steps_animations[1]);
    }
    if(hp_==50)
    {
        health_bar_.setTextureRect (hp_steps_animations[2]);
    }
    if(hp_==25)
    {
        health_bar_.setTextureRect (hp_steps_animations[3]);
    }
    if(hp_==0)
    {
        health_bar_.setTextureRect (hp_steps_animations[4]);
    }







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

void player::get_window_size(const sf::Vector2u &window_s)
{
    this->window_size_ = window_s;
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
    window.draw (health_bar_);
}




