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
    void initVariables();

    // collision;
    std::vector <sf::Sprite>  platforms_collisions_;
    void game_take_platforms(const std::vector <sf::Sprite> &platforms);



public:
    Game();
    ~Game();


    //Public functions
    void updatePollEvents();
    void update();
    void gamerender();

    std::vector <sf::Sprite> game_return_platforms();


    //Bool functions
    bool game_is_running  () const ;
};

#endif // GAME_H
