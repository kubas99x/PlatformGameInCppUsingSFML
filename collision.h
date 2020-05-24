#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

class collision
{
private:

    std::vector <sf::Sprite>  platforms_collisions_;

public:
    collision();
    ~collision();


    //function to take platforms (placed in game.cpp)
    void collision_take_platforms(const std::vector <sf::Sprite> &platforms);
    bool check_standing_collision(const sf::Sprite &hero);

    std::vector <sf::Sprite> return_platforms();


};


#endif // COLLISION_H
