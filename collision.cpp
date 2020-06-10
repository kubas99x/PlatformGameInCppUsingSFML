#include "collision.h"
#include <iostream>
collision::collision()
{

}

collision::~collision()
{

}

void collision::copy_platforms(const sf::Sprite &platform)
{
    vector_collision_platforms_.emplace_back(platform);
}

bool collision::check_standing_collision(const sf::Sprite &hero ,  const float &next_move, const sf::IntRect &animation)
{
    sf::Sprite guy = hero;
    guy.setTextureRect (animation);
    float guy_width = guy.getGlobalBounds ().width/2.0f - 15 ;              //-15 by zwezyc to brane pole bohatera, by nie lapalo miecza
    float guy_height = guy.getGlobalBounds ().height/2.0f;
    float guy_position_x = guy.getPosition ().x + guy_width;
    float guy_position_y = guy.getPosition ().y + guy_height + next_move;


    for(auto &el : this->vector_collision_platforms_)
    {
            float el_width = el.getGlobalBounds ().width/2.0f - 20;
            float el_height = el.getGlobalBounds ().height/2.0f ;
            float el_position_x = el.getPosition ().x + el_width;
            float el_position_y = el.getPosition ().y + el_height + 5;          //+5 by ladnie stal na platformie

            float delta_x = el_position_x - guy_position_x;
            float delta_y = el_position_y - guy_position_y;

            float intersect_x = std::abs(delta_x) - (guy_width + el_width) ;
            float intersect_y = std::abs(delta_y) - (guy_height + el_height);

            if(intersect_x < 0.0f && intersect_y < 0.0f )
            {
                return true;

            }
    }
                return false;

}

bool collision::check_walking_collision(const sf::Sprite &hero , const float &next_move , const sf::IntRect &animation)
{
    sf::Sprite guy = hero;
    guy.setTextureRect (animation);
    float guy_width = guy.getGlobalBounds ().width/2.0f;
    float guy_height = guy.getGlobalBounds ().height/2.0f  ;
    float guy_position_x = guy.getPosition ().x + guy_width  + next_move;
    float guy_position_y = guy.getPosition ().y + guy_height -1 ;      // -1 bo czasami wartosc intersect_y jest na poziomie ujemnych czesci tysiecznych
    guy_height-=10;                                     //by bohater sie ladnie miescil pod platforma
    guy_width-=30;
    if(guy.getPosition ().x + next_move <0)             //warunek by bohater nie mogl wypasc za mape
    {
        return true;
    }
    for(auto &el : this->vector_collision_platforms_)
    {
            float el_width = el.getGlobalBounds ().width/2.0f;
            float el_height = el.getGlobalBounds ().height/2.0f ;
            float el_position_x = el.getPosition ().x + el_width;
            float el_position_y = el.getPosition ().y + el_height + 5;      //+5 by ladnie stal na platformie

            float delta_x = el_position_x - guy_position_x;
            float delta_y = el_position_y - guy_position_y;

            float intersect_x = std::abs(delta_x) - (guy_width + el_width);
            float intersect_y = std::abs(delta_y) - (guy_height + el_height);

            if(intersect_x < 0.0f && intersect_y < 0.0f)
            {
                return true;

            }
    }
                return false;

}

bool collision::check_fighting_collision(const sf::Sprite &hero, const sf::Sprite &enemy)
{
    sf::Sprite guy = hero;
    float guy_width = guy.getGlobalBounds ().width/2.0f;
    float guy_height = guy.getGlobalBounds ().height/2.0f  ;
    float guy_position_x = guy.getPosition ().x + guy_width;
    float guy_position_y = guy.getPosition ().y + guy_height -1 ;      // -1 bo czasami wartosc intersect_y jest na poziomie ujemnych czesci tysiecznych

    guy_width-=40;                                                     //by zmienic hitpointy


            float el_width = enemy.getGlobalBounds ().width/2.0f;
            float el_height = enemy.getGlobalBounds ().height/2.0f ;
            float el_position_x = enemy.getPosition ().x + el_width;
            float el_position_y = enemy.getPosition ().y + el_height;      //+5 by ladnie stal na platformie

            float delta_x = el_position_x - guy_position_x;
            float delta_y = el_position_y - guy_position_y;

            float intersect_x = std::abs(delta_x) - (guy_width + el_width);
            float intersect_y = std::abs(delta_y) - (guy_height + el_height);

            if(intersect_x < 0.0f && intersect_y < 0.0f)
            {
                return true;

            }

    return false;
}

