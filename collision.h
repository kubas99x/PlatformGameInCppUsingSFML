#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>


class collision
{
private:
    //wektor wskaznikow na platformy
    std::vector <sf::Sprite*> vector_wsk_platforms;


    std::vector <sf::Sprite>  platforms_collisions_;
    const std::vector <sf::Sprite>  *platforms_collisions_wsk_ ;

public:
    collision();
    ~collision();

    //now with GAME class
    void copy_platforms(const std::vector <sf::Sprite> &vector);

    //check collision functions
    bool check_standing_collision(const sf::Sprite &hero,  const float &next_move);
    bool check_walking_collision(const sf::Sprite &hero, const float &next_move);
    void init_wsk(const std::vector <sf::Sprite> &platforms);


};


#endif // COLLISION_H
