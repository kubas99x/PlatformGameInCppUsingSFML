#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>


class collision
{
private:

    std::vector <sf::Sprite>  platforms_collisions_;
    const std::vector <sf::Sprite>  *platforms_collisions_wsk_ ;

public:
    collision();
    ~collision();

    //now with GAME class
    void copy_platforms(const std::vector <sf::Sprite> &vector);

    //function to take platforms (placed in game.cpp)
    void collision_take_platforms(const std::vector <sf::Sprite> &platforms);
    bool check_standing_collision(const sf::Sprite &hero);

    void init_wsk(const std::vector <sf::Sprite> &platforms);

    std::vector <sf::Sprite> return_platforms();


};


#endif // COLLISION_H
