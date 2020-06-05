#ifndef NEW_ENEMIES_H
#define NEW_ENEMIES_H
#include "texture_functions.h"
#include "SFML/Graphics.hpp"
#include "enum_classes.h"
#include <vector>
#include <map>

class new_enemies : public texture_functions
{
private:
    //czas
    sf::Clock clock;
    sf::Time time_;

    //enemy sprite
    sf::Sprite enemy_sprite_;



    //enemy type
    enemy_type enemy_type_;

    //enemy action
    enemy_action enemy_action_;

    //texture
    std::vector<sf::Texture> texture_;

    //mapa z roznymi animacjami (ktora bedzie zawiera kwadraty ktore trzeba wziac z tekstury)
    std::map <enemy_action,std::vector<sf::IntRect>> animations_;

    //variables
    float enemy_frame_time_;//
    int enemy_step_standing_;//
    bool enemy_animation_change_;//
    bool move_left;
    float waiting_time_;    //             //czas przez ktory wrog stoi i czeka w miejscu
    float distance_;
    float start_position_x_;//
    float start_position_y_;//
    float walk_distance_;
    float waiting_time_start_;



    //functions
    void download_textures();
    void set_animations();
    void set_enemy();
    void update_enemy_position(const float &pos_x);
    void update_enemy_frame();
    void choose_enemy_animation();
    void move_enemy();

public:
    //enemy variables
    float hp_;

    bool was_attacked_;
    new_enemies();
    new_enemies(const enemy_type &type,const float &pos_x, const float &pos_y , const float &distance, const float &time);
    void render(sf::RenderWindow &window);
    void update_enemy(const float &pos_x);
    sf::Sprite return_enemy_sprite();
};

#endif // NEW_ENEMIES_H
