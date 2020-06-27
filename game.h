#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "background.h"
#include "player.h"
#include "collision.h"
#include "new_enemies.h"
#include "new_platforms.h"

class Game
{
private:
    //Window stuff
    sf::RenderWindow * window;
    sf::View widok;
    sf::Clock clock_;
    sf::Time time_;

    //Backgrounds
    background *background_;

    //Player
    player * player_;

    //Collision
    collision * collision_;

    //enemies
    std::vector <new_enemies*>  enemies_vector_;

    //platfroms
    std::vector <new_platform*>  platforms_vector_;

    //poczatek gry
    sf::Texture texture_start_;
    sf::Sprite sprite_start_;
    bool game_start_=false;
    bool first_loop_=true;              //by przy 1 petli nie robic updatu obiektow

    //koniec gry
    bool game_end_=false;
    sf::Text text_;
    sf::Font font_;

    //music
    sf::Music music_;
    bool second_music_;
    void set_music();

    //Private void functions
    void initWindow();
    void initVariables();
    void check_all_collisions();
    void add_enemies();
    void add_platforms();
    void check_enemy_hp_();
    void init_game_start_end();

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
