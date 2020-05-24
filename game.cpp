#include "game.h"
#include <iostream>
Game::Game()
{
    this->initWindow ();
    this->background_ = new background;
    this->platform_ = new platform;
    this->player_ = new player;
    this->collision_ = new collision;

    this->initVariables();

}

Game::~Game()
{

}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1440, 900), "Sword and hammer", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initVariables()
{
    this->game_take_platforms (this->platform_->return_sprites ());

    this->collision_->init_wsk (this->game_return_platforms ());

    //this->collision_->copy_platforms (this->game_return_platforms ());

    //this->collision_->copy_hero (this->player_->hero_return ());

}

void Game::updatePollEvents()
{
    sf::Event e;

    while (this->window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
        {
            this->window->close();
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
        {
            this->window->close();
        }
    }
}

void Game::update()
{
    this->clock_.restart ();

    this->updatePollEvents();

    //this->platform_->collision_take_platforms (platform_->return_sprites ());       //funkcja ktora wysyla do klasy collision platformy

    this->player_->update_hero();

}

void Game::gamerender()
{
    this->window->clear ();

    this->background_->render (*this->window);

    this->platform_->render (*this->window);

    this->player_->render (*this->window);

    this->window->display();
}

std::vector<sf::Sprite> Game::game_return_platforms()
{
    return platforms_collisions_;
}


bool Game::game_is_running() const
{
    return this->window->isOpen ();
}

void Game::game_take_platforms(const std::vector <sf::Sprite> &platforms)
{

    platforms_collisions_=platforms;
    std::cout<<"GAME platforms wektor size:  "<<platforms_collisions_.size()<<std::endl;

}
