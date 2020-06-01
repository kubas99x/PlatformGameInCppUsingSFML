#include "collision.h"
#include <iostream>
collision::collision()
{

}

collision::~collision()
{

}

void collision::copy_platforms(const std::vector<sf::Sprite> &platforms)
{
    vector_collision_platforms = platforms;
}

bool collision::check_standing_collision(const sf::Sprite &hero ,  const float &next_move)
{
    sf::Sprite guy = hero;
    float guy_width = guy.getGlobalBounds ().width/2.0f - 15 ;              //-15 by zwezyc to brane pole bohatera, by nie lapalo miecza
    float guy_height = guy.getGlobalBounds ().height/2.0f;
    float guy_position_x = guy.getPosition ().x + guy_width;
    float guy_position_y = guy.getPosition ().y + guy_height + next_move;

    //juz dla wszystkich platform
//    std::cout<<"#############################"<<std::endl;
//    std::cout<<guy_position_y<<"   "<<guy_height<<std::endl;

    for(auto &el : this->vector_collision_platforms)
    {
            float el_width = el.getGlobalBounds ().width/2.0f - 20;
            float el_height = el.getGlobalBounds ().height/2.0f ;
            float el_position_x = el.getPosition ().x + el_width;
            float el_position_y = el.getPosition ().y + el_height + 5;          //+5 by ladnie stal na platformie

            float delta_x = el_position_x - guy_position_x;
            float delta_y = el_position_y - guy_position_y;

            float intersect_x = std::abs(delta_x) - (guy_width + el_width) ;
            float intersect_y = std::abs(delta_y) - (guy_height + el_height);
//            std::cout<< el_position_y<<"    "<<el_height<<std::endl;
//            std::cout<<"Intersect x:  "<<intersect_x<<"  intersect y:  "<<intersect_y <<std::endl;

            if(intersect_x < 0.0f && intersect_y < 0.0f )
            {
                return true;

            }
    }
                return false;

}

bool collision::check_walking_collision(const sf::Sprite &hero , const float &next_move)
{
    sf::Sprite guy = hero;
    float guy_width = guy.getGlobalBounds ().width/2.0f - 15;
    float guy_height = guy.getGlobalBounds ().height/2.0f;
    float guy_position_x = guy.getPosition ().x + guy_width  + next_move;
    float guy_position_y = guy.getPosition ().y + guy_height - 1 ;      // -1 bo czasami wartosc intersect_y jest na poziomie ujemnych czesci tysiecznych

//    std::cout<<"##########################################"<<std::endl;
    for(auto &el : this->vector_collision_platforms)
    {
            float el_width = el.getGlobalBounds ().width/2.0f;
            float el_height = el.getGlobalBounds ().height/2.0f ;
            float el_position_x = el.getPosition ().x + el_width;
            float el_position_y = el.getPosition ().y + el_height + 5;      //+5 by ladnie stal na platformie

            float delta_x = el_position_x - guy_position_x;
            float delta_y = el_position_y - guy_position_y;

            float intersect_x = std::abs(delta_x) - (guy_width + el_width);
            float intersect_y = std::abs(delta_y) - (guy_height + el_height);
//            std::cout<<"El width:  "<<el_width<<"  position  "<<el_position_x <<std::endl;
//            std::cout<<"Intersect x:  "<<intersect_x<<"  intersect y:  "<<intersect_y <<std::endl;

            if(intersect_x < 0.0f && intersect_y < 0.0f )
            {
                return true;

            }
    }
                return false;

}

