#include "texture_functions.h"
#include "iostream"
texture_functions::texture_functions()
{


}

sf::Texture texture_functions::get_textures(const std::string &adres)
{
    sf:: Texture texture;
    if (!texture.loadFromFile(adres))
    {
        std::cerr << "Could not load texture" << std::endl;
    }
    return texture;

}

sf::Sprite  texture_functions::get_sprites(const sf::Texture &texture)
{
    sf::Sprite sprite_tmp;
    sprite_tmp.setTexture (texture);
    return sprite_tmp;
}
