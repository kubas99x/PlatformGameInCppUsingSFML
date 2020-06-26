#ifndef TEXTURE_FUNCTIONS_H
#define TEXTURE_FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

class texture_functions
{

public:
    texture_functions();
    sf::Texture get_textures(const std::string &adres);
    sf::Sprite  get_sprites(const sf::Texture &texture);
    sf::SoundBuffer load_sound_effect(std::string file_name);

};

#endif // TEXTURE_FUNCTIONS_H
