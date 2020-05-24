#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "background.h"
#include "platform.h"
#include "player.h"
#include "collision.h"

class Game
{
private:
    //Window stuff
    sf::RenderWindow * window;
    sf::Clock clock_;
    sf::Time time_;

    //Backgrounds
    background *background_;

    //Platforms
    platform *platform_;

    //Player
    player * player_;

    //Collision
    collision * collision_;


    //Private void functions
    void initWindow();

    // collision;
    std::vector <sf::Sprite>  platforms_collisions_;



public:
    Game();
    ~Game();


    //Public functions
    void updatePollEvents();
    void update();
    void gamerender();


    //Bool functions
    bool game_is_running  () const ;
};

#endif // GAME_H
