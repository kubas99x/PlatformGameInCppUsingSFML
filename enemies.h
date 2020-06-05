#ifndef ENEMIES_H
#define ENEMIES_H

#include "collision.h"
#include "texture_functions.h"
#include "SFML/Graphics.hpp"
#include <vector>

struct enemies_struct
{
public:
    sf::Sprite enemy_sprite_;
    float hp_;
    bool was_attacked_;

};

class enemies : public texture_functions
{
private:
    //Time
    sf::Clock clock;
    sf::Time time_;

    //wskaznik na kolizje
    collision * collision_;

    //Texture vector
    std::vector <sf::Texture> textures_;

    //wektory  z roznymi typami wrogow
    std::vector <sf::IntRect> type_first_;
    std::vector <sf::IntRect> type_second_;
    std::vector <sf::IntRect> type_third_;



    //vector with start positions
    std::vector <sf::Vector2f> start_position_;

    //variables
    float enemy_frame_time_;
    int enemy_step_standing_;
    bool enemy_animation_change_;
    bool move_left;
    float waiting_time_;                 //czas przez ktory wrog stoi i czeka w miejscu
    float distance_;

    //functions
    void download_textures();
    void set_enemies_sprites();
    void init_variables();
    void set_enemies();
    void update_enemy_frame();
    void choose_enemy_animation();
    void enemy_move();
    void save_start_position();
    void update_enemy_position(const float pos_x);
    void check_enemy_hp();


public:
    enemies();
    ~enemies();
    enemies(collision *wsk);

    //wektor wrogow
    std::vector <enemies_struct> enemies_;

    //Public functions
    void render(sf::RenderWindow &window);
    void update_enemy(const float &pos_x);
    std::vector <enemies_struct > return_enemies();
};

#endif // ENEMIES_H
