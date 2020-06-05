#include "enemies.h"

enemies::enemies()
{

}

enemies::enemies(collision *wsk)
{
    this->init_variables ();
    this->collision_=wsk;
    this->download_textures ();
    this->set_enemies_sprites ();
    this->set_enemies ();
    this->save_start_position ();

}

enemies::~enemies()
{

}

void enemies::init_variables()
{
    this->enemy_frame_time_=0;
    this->enemy_step_standing_=0;
    this->enemy_animation_change_=false;
    this->waiting_time_=3;
    this->distance_=250;
    this->move_left=true;
}

void enemies::download_textures()
{
    this->textures_.emplace_back(get_textures("textures/skeleton_standing.png"));
}

void enemies::set_enemies_sprites()
{
    //standing animations
    for(int i=0; i<24*11; i+=24)
    {
        type_first_.emplace_back(sf::IntRect(i,0,24,32));
    }
}

void enemies::set_enemies()
{
    enemies_struct enemy;
    enemy.enemy_sprite_.setTexture (textures_[0]);
    enemy.enemy_sprite_.setTextureRect (type_first_[0]);
    enemy.enemy_sprite_.setScale (3.5, 3.5);
    enemy.enemy_sprite_.setPosition (650, 700);
    enemy.hp_=100;
    enemy.was_attacked_=false;
    enemies_.emplace_back(enemy);

}

void enemies::update_enemy_frame()
{
    enemy_frame_time_+=time_.asSeconds ();
    if(enemy_frame_time_>=1.0f/13.0f )
    {
        enemy_step_standing_++;
        enemy_frame_time_=0;
        enemy_animation_change_=true;
    }
}

void enemies::choose_enemy_animation()
{
    if(this->enemy_animation_change_)               //standing
    {
        if(this->enemy_step_standing_>=type_first_.size ()-1)
        {
            enemy_step_standing_=0;
        }
        this->enemies_[0].enemy_sprite_.setTexture (this->textures_[0]);
        this->enemies_[0].enemy_sprite_.setTextureRect (this->type_first_[this->enemy_step_standing_]);
    }
}

void enemies::enemy_move()
{
    if(waiting_time_<=0)
    {
        if(move_left)
        {
        enemies_[0].enemy_sprite_.move (-1,0);
        distance_-=1;
        start_position_[0].x-=1;                //potrzebne by przeciwnicy sie przesuwali wraz z mapa
        if(distance_<=0)
        {
            distance_=250;
            waiting_time_=3;
            move_left=false;
        }
        }
        else
        {
        enemies_[0].enemy_sprite_.move (1,0);
        distance_-=1;
        start_position_[0].x+=1;
        if(distance_<=0)
        {
            distance_=250;
            waiting_time_=3;
            move_left=true;
        }
        }
    }
}

void enemies::save_start_position()
{
    for(auto const &el : enemies_)
    {
        start_position_.emplace_back(el.enemy_sprite_.getPosition ());
    }
}

void enemies::update_enemy_position(const float pos_x)
{
    for(size_t i = 0; i<enemies_.size() ; i++)
    {
        enemies_[i].enemy_sprite_.setPosition (start_position_[i].x - pos_x, enemies_[i].enemy_sprite_.getPosition ().y);
    }
}

void enemies::check_enemy_hp()
{
    //for(size_t i=0; i<enemies_.size() ; i++)
    for(auto itr = enemies_.begin (); itr<enemies_.end (); itr++)
    {
        if(itr->hp_<=0)
        {
            enemies_.erase (itr);
        }
    }
}


void enemies::update_enemy(const float &pos_x)
{
    this->time_=clock.restart ();
    waiting_time_-=time_.asSeconds ();
    this->update_enemy_position(pos_x);
    this->enemy_move();
    this->update_enemy_frame ();
    this->choose_enemy_animation ();
    this->check_enemy_hp ();
}

std::vector <enemies_struct > enemies::return_enemies()
{
    return enemies_;
}

void enemies::render(sf::RenderWindow &window)
{
    for(const auto &el: enemies_)
    {
        window.draw(el.enemy_sprite_);
    }
}

