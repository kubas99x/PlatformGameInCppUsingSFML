#include "game.h"
#include <iostream>
Game::Game()
{
    this->initWindow ();
    this->background_ = new background;
    this->platform_ = new platform;
    this->player_ = new player;
    this->collision_ = new collision();

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
    //this->player_->init_wsk (this->platform_->return_sprites ());             //jak na razie na wskaznikach nie da rady

    this->player_->copy_platforms (this->platform_->return_sprites ());

    //this->collision_->take_obiekty_player(this->player_);

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

bool Game::game_is_running() const
{
    return this->window->isOpen ();
}

