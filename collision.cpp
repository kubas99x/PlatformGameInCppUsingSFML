#include "collision.h"
#include <iostream>
collision::collision()
{

}

collision::~collision()
{

}

void collision::collision_take_platforms(const std::vector <sf::Sprite> &platforms)
{

    collision::platforms_collisions_=platforms;

    std::cout<<platforms_collisions_.size()<<std::endl;
    std::cout<<collision::platforms_collisions_.size()<<std::endl;
}

bool collision::check_standing_collision(const sf::Sprite &hero)
{
    std::cout<<collision::platforms_collisions_.size ()<<std::endl;

    sf::Sprite guy = hero;
    guy.setOrigin (guy.getGlobalBounds ().width/2, guy.getGlobalBounds ().height/2);
    sf::Vector2f guy_possition =  guy.getPosition ();
    sf::FloatRect guy_dimension = guy.getGlobalBounds ();

    for(auto &el : this->platforms_collisions_)
    {
        el.setOrigin (el.getGlobalBounds ().width/2, el.getGlobalBounds ().height/2);
        sf::Vector2f platform_possition =  el.getPosition ();
        sf::FloatRect platform_dimension = el.getGlobalBounds ();

        float delta_x = platform_possition.x - guy_possition.x;
        float delta_y = platform_possition.y - guy_possition.y;

        float intersect_x = delta_x - (guy_dimension.width + platform_dimension.width) ;
        float intersect_y = delta_y - (guy_dimension.height + platform_dimension.height);

        std::cout<<"Intersect x:  "<<intersect_x<<"  intersect y:  "<<intersect_y <<std::endl;

        if(intersect_x < 0.0f && intersect_y < 0.0f )
        {
            return true;
            break;
        }
    }
    return false;

}

std::vector<sf::Sprite> collision::return_platforms()
{
    return platforms_collisions_;
}




