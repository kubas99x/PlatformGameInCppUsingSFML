#include "texture_functions.h"
#include "iostream"
texture_functions::texture_functions()
{


}

sf::Texture texture_functions::get_textures(const std::string &adres)
{
    /*
     pobieranie tekstur
     */
    sf:: Texture texture;
    if (!texture.loadFromFile(adres))
    {
        std::cerr << "Could not load texture" << std::endl;
    }
    return texture;

}

sf::Sprite  texture_functions::get_sprites(const sf::Texture &texture)
{
    /*
     funkcja zwracajaca sprite
     */
    sf::Sprite sprite_tmp;
    sprite_tmp.setTexture (texture);
    return sprite_tmp;
}

sf::SoundBuffer texture_functions::load_sound_effect(std::string file_name)
{
    /*
     funkcja zwracajace SoundBuffer z zaladowanym dzwiekiem
     */
    sf::SoundBuffer buffer_tmp;
        if (!buffer_tmp.loadFromFile(file_name))
        {
            std::cerr<<"sound not loaded"<<std::endl;
        }
       return buffer_tmp;
}
