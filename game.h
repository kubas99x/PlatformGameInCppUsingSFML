#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "background.h"

class Game
{
private:
    //Window stuff
    sf::RenderWindow * window;

    //Backgrounds
    background *background_;


    //Private void functions
    void initWindow();



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
