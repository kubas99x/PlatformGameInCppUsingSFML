#include "game.h"
#include <iostream>
Game::Game()
{
    this->initWindow ();
    this->background_ = new background;
    this->collision_ = new collision;
    this->player_ = new player(this->collision_);
    this->add_enemies ();
    this->add_platforms ();
    this->initVariables();

}

Game::~Game()
{
    delete background_;
    delete collision_;
    delete player_;
    for(size_t i=0; i<enemies_vector_.size (); i++)
    {
        delete enemies_vector_[i];
    }
    for(size_t i=0; i<platforms_vector_.size (); i++)
    {
        delete platforms_vector_[i];
    }
}

void Game::add_enemies()
{
    //typ , pos_x , pos_y, dystans_chodzenia, czas ktory czeka w miejscu
    enemies_vector_.emplace_back(new new_enemies(enemy_type::skeleton, 650, 700 , 250, 3 ));
    enemies_vector_.emplace_back(new new_enemies(enemy_type::skeleton, 500, 700 , 200, 1 ));

}

void Game::add_platforms()
{
    //pos_x , pos_y , scale_x, scale_y , width, height, platform_type type
    //podstawowa wysokosc tekstury - 65
    platforms_vector_.emplace_back(new new_platform(740,600,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(930,520,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(1140,440,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(530,680,0.5,1,platform_type::wood));

    platforms_vector_.emplace_back(new new_platform(0,817,1,1,700,50,platform_type::grass));
    platforms_vector_.emplace_back(new new_platform(1350,360,1,1,platform_type::grass_pocz));
    platforms_vector_.emplace_back(new new_platform(1480,360,1,1,platform_type::rock_with_gras));
    platforms_vector_.emplace_back(new new_platform(1700,360,1,1,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1950,230,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1420,420,1,1,65,1000,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(1480,650,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1480,850,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1960,550,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(2220,0,1,1,65,620,platform_type::rock_pion));


}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1440, 900), "Sword and hammer", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
    this->widok.setSize (1440,900);
}

void Game::initVariables()
{
    this->hero_x_position_=0;
}

void Game::check_all_collisions()
{
    if(player_->hero_action_==hero_action::attack1 || player_->hero_action_==hero_action::attack1_left )
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

void Game::check_enemy_hp_()
{
    //for(auto itr = enemies_vector_.begin(); itr<enemies_vector_.end() ; itr++)
     for(size_t i=0; i<enemies_vector_.size (); i++)
    {
      if(enemies_vector_[i]->dead_==true)
      {
          enemies_vector_.erase (enemies_vector_.begin ()+i);
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

    this->hero_x_position_=player_->return_hero_x_position ();

    if(hero_x_position_>= window->getSize ().x/2.0f)
    {
    this->widok.setCenter (hero_x_position_, window->getSize ().y/2);

    this->window->setView (widok);
    }

    for(const auto &el : enemies_vector_)
    {
        el->update_enemy ();
    }
    for(const auto &el : platforms_vector_)
    {
        collision_->copy_platforms (el->return_sprite ());
    }

    this->check_all_collisions ();

    this->player_->update_hero();

    this->check_enemy_hp_();

}

void Game::gamerender()
{
    this->window->clear ();

    this->background_->render (*this->window);

    for(const auto &el : platforms_vector_)
    {
        el->render (*this->window);
    }

    for(const auto &el : enemies_vector_)
    {
        el->render (*this->window);
    }

    this->player_->render (*this->window);




    this->window->display();
}

bool Game::game_is_running() const
{
    return this->window->isOpen ();
}

