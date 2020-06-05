#include "game.h"
#include <iostream>
Game::Game()
{
    this->initWindow ();
    this->background_ = new background;
    this->collision_ = new collision;
    this->platform_ = new platform(this->collision_);
    this->player_ = new player(this->collision_);
    this->add_enemies ();
    this->initVariables();

}

Game::~Game()
{
    delete background_;
    delete collision_;
    delete platform_;
    delete player_;
}

void Game::add_enemies()
{
    //typ , pos_x , pos_y, dystans_chodzenia, czas ktory czeka w miejscu
    enemies_vector_.emplace_back(new new_enemies(enemy_type::skeleton, 650, 700 , 250, 3 ));
}

void Game::check_enemy_hp_()
{
    //for(auto itr = enemies_vector_.begin(); itr<enemies_vector_.end() ; itr++)
     for(size_t i=0; i<enemies_vector_.size (); i++)
    {
      if(enemies_vector_[i]->hp_<=0)
      {
          enemies_vector_.erase (enemies_vector_.begin ()+i);
      }
    }
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1440, 900), "Sword and hammer", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initVariables()
{
    this->collision_->copy_platforms (this->platform_->return_sprites ());
    this->hero_x_position_=0;
}

void Game::check_all_collisions()
{
    if(player_->hero_action_==hero_action::attack1)
    {
        for(auto &el : enemies_vector_)
        {
            if(!el->was_attacked_ && collision_->check_fighting_collision (player_->return_hero (), el->return_enemy_sprite ()))
            {
                std::cout<<el->hp_<<std::endl;
                el->hp_-=50;
                std::cout<<el->hp_<<std::endl;
                el->was_attacked_ = true;
            }
        }
    }
    else
    {
        for(auto &el : enemies_vector_)
        {
            el->was_attacked_=false;
        }

    }
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

    this->hero_x_position_=this->player_->return_hero_x_position ();

    this->background_->update_background (hero_x_position_);

    this->platform_->update_platforms (hero_x_position_);

    for(const auto &el : enemies_vector_)
    {
        el->update_enemy (hero_x_position_);
    }

    this->check_all_collisions ();

    this->collision_->copy_platforms (this->platform_->return_sprites ());

    this->player_->update_hero();

    this->check_enemy_hp_();

}

void Game::gamerender()
{
    this->window->clear ();

    this->background_->render (*this->window);

    this->platform_->render (*this->window);

    this->player_->render (*this->window);

    for(const auto &el : enemies_vector_)
    {
        el->render (*this->window);
    }

    this->window->display();
}

bool Game::game_is_running() const
{
    return this->window->isOpen ();
}

