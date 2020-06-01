#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>


class collision
{
private:

public:
    collision();
    ~collision();

    //OD NOWA
    std::vector <sf::Sprite> vector_collision_platforms;

    //functions
    void copy_platforms(const std::vector <sf::Sprite> &platforms);

    //check collision functions
    bool check_standing_collision(const sf::Sprite &hero,  const float &next_move);
    bool check_walking_collision(const sf::Sprite &hero, const float &next_move);




};


#endif // COLLISION_H
