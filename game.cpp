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

    //platforma z interakcja
    //float pos_x, float pos_y, float scale_x, float scale_y, float arm_x, float arm_y, const platform_type &type, bool interaction
    platforms_vector_.emplace_back(new new_platform(1800,360,1,1,2100,195,platform_type::wood,true));


    platforms_vector_.emplace_back(new new_platform(0,817,1,1,700,50,platform_type::grass));
    platforms_vector_.emplace_back(new new_platform(1350,360,1,0.7,platform_type::grass_pocz));
    platforms_vector_.emplace_back(new new_platform(1480,360,1,0.7,platform_type::rock_with_gras));
    platforms_vector_.emplace_back(new new_platform(1700,360,1,0.7,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1950,230,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1420,400,0.7,1,65,1000,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(1465,650,1,0.5,250,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1465,870,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1960,550,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(2220,0,0.7,1,65,620,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(1950,260,0.5,1,65,100,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(1900,870,1,0.5,130,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(2170,870,1,0.5,130,65,platform_type::rock));


    //spikes    //wyskosc 12 maja
    platforms_vector_.emplace_back(new new_platform(1770,850,4,4,30,12,platform_type::spikes));
    platforms_vector_.emplace_back(new new_platform(2035,850,4,4,30,12,platform_type::spikes));

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
    for(const auto &el : platforms_vector_)
    {
        collision_->copy_platforms (el->return_sprite ());
    }
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
    for(auto &el : platforms_vector_)
    {
        if(el->damage_platform && collision_->check_platform_damage_collision (player_->return_hero (), el->return_sprite (), player_->return_standing_animation ()))
        {
                player_->hp_-=50;
                std::cout<<player_->hp_<<std::endl;
        }
    }

    //atakowanie przeciwnika

    for(auto &el : enemies_vector_)
    {
        if(el->can_attack_ && collision_->is_player_near (player_->return_hero (), el->return_enemy_sprite ()))
        {
            el->attacking_=true;
            el->can_attack_=false;
        }
        if(el->attacking_ && !el->hited_hero_ && collision_->check_fighting_collision (player_->return_hero (), el->return_enemy_sprite ())
                && el->can_deal_dmg_)
        {
            el->hited_hero_ = true;
            player_->hp_-=50;
            std::cout<<player_->hp_<<std::endl;
        }
    }



}

void Game::check_enemy_hp_()
{
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
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::F )
        {
            for(size_t i = 0; i<platforms_vector_.size ();i++)
            {
                if(platforms_vector_[i]->interaction_ &&
                        collision_->check_fighting_collision (player_->return_hero (), platforms_vector_[i]->return_sprite_interaction ())
                        && !platforms_vector_[i]->interaction_switched_)
                {

                        platforms_vector_[i]->interaction_switched_=true;

                }
            }
        }

    }
}

void Game::update()
{    
    this->time_ = clock_.restart();              //restartuje zegar

    this->updatePollEvents();

    this->hero_x_position_=player_->return_hero_x_position ();

    if(hero_x_position_>= window->getSize ().x/2.0f)
    {
    this->widok.setCenter (hero_x_position_, window->getSize ().y/2);

    this->window->setView (widok);
    }

    //kopiowanie platform, na razie tak bo nie mam innego pomyslu
    this->collision_->vector_collision_platforms_.clear ();

    for(const auto &el : platforms_vector_)
    {
        if(!el->damage_platform)
        {
        collision_->copy_platforms (el->return_sprite ());
        }
    }

    //dalej
    for(const auto &el : enemies_vector_)
    {
        el->update_enemy ();
    }

    for(const auto &el : platforms_vector_)
    {
        el->update_platform (time_.asSeconds ());
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

//zmien funkcje kopiowania platform! bo jezeli robisz to co petle to tworzysz ich nieskonczonosc
