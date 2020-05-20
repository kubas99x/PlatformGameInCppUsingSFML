#include "game.h"

Game::Game()
{
    this->initWindow ();
    this->background_ = new background;
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
    this->updatePollEvents();
}

void Game::gamerender()
{
    this->window->clear ();

    this->background_->render (*this->window);

    this->window->display();
}


bool Game::game_is_running() const
{
    return this->window->isOpen ();
}
