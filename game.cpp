#include "game.h"

Game::Game()
{
    this->initWindow ();
    this->background_ = new background;
    this->platform_ = new platform;
    this->player_ = new player;
    this->collision_ = new collision;

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


bool Game::game_is_running() const
{
    return this->window->isOpen ();
}
