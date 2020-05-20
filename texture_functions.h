#ifndef TEXTURE_FUNCTIONS_H
#define TEXTURE_FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <vector>

class texture_functions
{

public:
    texture_functions();
    sf::Texture get_textures(const std::string &adres);
    sf::Sprite  get_sprites(const sf::Texture &texture);

};

#endif // TEXTURE_FUNCTIONS_H
