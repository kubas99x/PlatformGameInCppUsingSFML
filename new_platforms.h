#ifndef NEW_PLATFORMS_H
#define NEW_PLATFORMS_H

#include <texture_functions.h>
#include <SFML/Graphics.hpp>

#include "enum_classes.h"

class new_platform : public texture_functions
{
private:

    //Texture
    sf::Texture texture_;

    //Sprite
    sf::Sprite sprite_;

    //platform type
    platform_type type_;

    //do platform z interakcja

    sf::Sprite sprite_interaction_;
    sf::Texture texture_interaction_;
    float distance_;
    float distance_tmp_;
    float velocity_=200;
    bool moving_left_right_=true;


    //platformy ruszajace sie
    bool moving_=false;
    bool moving_right=false;

    //functions
    void download_textures();
    void set_sprites(float pos_x, float pos_y, float scale_x, float scale_y);
    void set_sprites(float pos_x, float pos_y, float scale_x, float scale_y, float width, float height);

    //platformy z interakcja
    void set_arm_interaction_(float x, float y);
    void chagne_arm_interaction();
    void move_platform(float time);
    void moving_side_to_side(float time);

public:
    new_platform();
    new_platform(float pos_x , float pos_y , float scale_x, float scale_y , float width, float height, const platform_type &type );

    new_platform(float pos_x , float pos_y , float scale_x, float scale_y , const platform_type &type );
    new_platform(float pos_x , float pos_y , float scale_x, float scale_y , const platform_type &type , bool moving , float moving_distance , bool movig_right);

    //platformy z dzwigniami
    new_platform(float pos_x , float pos_y , float scale_x, float scale_y ,float arm_x, float arm_y, const platform_type &type, bool interaction , bool moving_left_right);
    new_platform(float pos_x, float pos_y, float scale_x, float scale_y, float width, float height, float arm_x, float arm_y, const platform_type &type, bool interaction );
    ~new_platform();

    //interaction
    bool interaction_=false;
    bool interaction_switched_=false;
    bool changed_arm_=false;
    bool damage_platform=false;             //dla platform ktore zadaja dmg

    //public functions
    void update_platform(float time);
    void render(sf::RenderWindow &window);
    sf::Sprite return_sprite();
    sf::Sprite return_sprite_interaction();

};
#endif // NEW_PLATFORMS_H
