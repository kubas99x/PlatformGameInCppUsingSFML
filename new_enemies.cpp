#include "new_enemies.h"

new_enemies::new_enemies()
{
    download_textures ();
    set_animations ();

}

new_enemies::new_enemies(const enemy_type &type , const float &pos_x, const float &pos_y , const float &distance, const float &time)
{
    this->enemy_type_=type;
    this->start_position_x_=pos_x;
    this->start_position_y_=pos_y;
    this->download_textures ();
    this->set_animations ();
    this->set_enemy ();
    this->walk_distance_ = distance;
    this->waiting_time_start_ = time;
    this->was_attacked_ = false;
}

void new_enemies::download_textures()
{
    if(enemy_type_==enemy_type::skeleton)
    {
        texture_.emplace_back(get_textures("textures/skeleton_standing.png"));
    }
}

void new_enemies::set_enemy()
{
    if(enemy_type_==enemy_type::skeleton)
    {
    enemy_action_=enemy_action::standing;
    enemy_sprite_.setTexture (texture_[0]);
    enemy_sprite_.setTextureRect (animations_[enemy_action::standing][0]);
    enemy_sprite_.setPosition (start_position_x_, start_position_y_);
    enemy_sprite_.setScale (3.5,3.5);
    distance_=walk_distance_;
    move_left=false;
    waiting_time_=waiting_time_start_;
    hp_=100;
    }
}
void new_enemies::set_animations()
{
    if(enemy_type_==enemy_type::skeleton)
    {
        std::vector <sf::IntRect> tmp_vector;
        for(int i=0; i<24*11; i+=24)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,24,32));

        }
        animations_.emplace(enemy_action::standing,tmp_vector);
    }
}



void new_enemies::update_enemy_frame()
{
    enemy_frame_time_+=time_.asSeconds ();
    if(enemy_frame_time_>=1.0f/13.0f )
    {
        enemy_step_standing_++;
        enemy_frame_time_=0;
        enemy_animation_change_=true;
    }
}
void new_enemies::choose_enemy_animation()
{
    if(this->enemy_animation_change_)
    {
        if(enemy_action_==enemy_action::standing)
        {
        if(this->enemy_step_standing_>=animations_[enemy_action::standing].size ()-1)
        {
            enemy_step_standing_=0;
        }
        this->enemy_sprite_.setTexture (texture_[0]);
        this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::standing][this->enemy_step_standing_]);
        }
    }
    enemy_animation_change_=false;
}

void new_enemies::move_enemy()
{
    if(waiting_time_<=0)
    {
        if(move_left)
        {
            enemy_sprite_.move (-1,0);
            distance_-=1;
            start_position_x_-=1;                //potrzebne by przeciwnicy sie przesuwali wraz z mapa
            if(distance_<=0)
            {
                distance_=walk_distance_;
                waiting_time_=waiting_time_start_;
                move_left=false;
            }
        }
        else
        {
            enemy_sprite_.move (1,0);
            distance_-=1;
            start_position_x_+=1;
            if(distance_<=0)
            {
                distance_=walk_distance_;
                waiting_time_=waiting_time_start_;
                move_left=true;
            }
        }
    }
}


void new_enemies::update_enemy_position(const float &pos_x)
{
    enemy_sprite_.setPosition (start_position_x_-pos_x,start_position_y_);
}

void new_enemies::update_enemy(const float &pos_x)
{
    this->time_=clock.restart ();
    waiting_time_-=time_.asSeconds ();
    this->update_enemy_position(pos_x);
    this->update_enemy_frame ();
    this->choose_enemy_animation ();
    if(enemy_type_==enemy_type::skeleton)
    {
    this->move_enemy ();
    }
}

sf::Sprite new_enemies::return_enemy_sprite()
{
    return enemy_sprite_;
}
void new_enemies::render(sf::RenderWindow &window)
{
    window.draw (enemy_sprite_);
}


