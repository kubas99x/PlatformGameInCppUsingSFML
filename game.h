#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "background.h"
#include "platform.h"
#include "player.h"
#include "collision.h"
#include "enemies.h"

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

    //enemies
    enemies * enemies_;


    //Private void functions
    void initWindow();
    void initVariables();
    void check_all_collisions();

public:
    Game();
    ~Game();

    //Public variables
    float hero_x_position_;

    //Public functions
    void updatePollEvents();
    void update();
    void gamerender();

    //Bool functions
    bool game_is_running  () const ;
};

#endif // GAME_H
