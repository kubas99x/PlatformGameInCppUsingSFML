#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "texture_functions.h"

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

    //public functions
    void render(sf::RenderWindow &window);


};

#endif // BACKGROUND_H
