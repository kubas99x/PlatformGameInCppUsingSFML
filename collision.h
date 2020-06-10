#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>


class collision
{
private:

public:
    collision();
    ~collision();

    //wektor platform
    std::vector <sf::Sprite> vector_collision_platforms_;
    
    //functions
    void copy_platforms(const sf::Sprite &platform );

    //check collision functions
    bool check_standing_collision(const sf::Sprite &hero,  const float &next_move, const sf::IntRect &animation);
    bool check_walking_collision(const sf::Sprite &hero, const float &next_move, const sf::IntRect &animation);
    bool check_fighting_collision (const sf::Sprite &hero , const sf::Sprite &enemy );

};


#endif // COLLISION_H
