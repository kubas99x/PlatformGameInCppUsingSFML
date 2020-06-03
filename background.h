#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <texture_functions.h>
#include <SFML/Graphics.hpp>
#include <vector>

class background : public texture_functions
{
private:
    //Texture vector
    std::vector <sf::Texture> textures_;

    //Sprite vector
    std::vector <sf::Sprite> sprites_;


    //functions
    void download_textures();
    void download_sprites();
    void set_sprites();

public:
    background();
    ~background();

    //hero x position
    float hero_x_position_background_;

    //public functions
    void render(sf::RenderWindow &window);
    void update_background(const float &pos_x);

};

#endif // BACKGROUND_H
