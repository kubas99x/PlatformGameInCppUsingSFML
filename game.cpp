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
    this->init_game_start_end ();
    this->set_music ();

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



void Game::initWindow()
{
    /*
     tworzenie okna, ustawianie limitu klatek
     synchronizacji pionowej
    */
    this->window = new sf::RenderWindow(sf::VideoMode(1440, 900), "Sword and hammer", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
    this->widok.setSize (1440,900);
    this->window->setKeyRepeatEnabled(false);               //by wyrywalo klikniecie pojedyncze

}

void Game::initVariables()
{
    /*
     ustawianie zmiennych
    */
    this->hero_x_position_=0;
    this->second_music_=false;
    for(const auto &el : platforms_vector_)
    {
        collision_->copy_platforms (el->return_sprite ());
    }
    this->player_->get_window_size (window->getSize ());
}

void Game::init_game_start_end()
{
    /*
     ustawianie napisow na poczatku i na koncu gry
    */
    //start game
    this->texture_start_.loadFromFile ("textures/game_info.png");
    this->sprite_start_.setTexture (texture_start_);
    this->sprite_start_.setTextureRect (sf::IntRect(350,0,420,302));
    this->sprite_start_.setPosition (370,0);
    this->sprite_start_.setScale (2,2.5);

    //end game
    this->font_.loadFromFile ("textures/font2.ttf");
    this->text_.setFont(font_);
    this->text_.setString("WYGRANA");
    this->text_.setCharacterSize(175);
    this->text_.setFillColor(sf::Color::White);
    this->text_.setPosition (2880,350);
}
void Game::set_music()
{
    /*
     ustawianie dzwiekow ktore graja w tle, glosnosci itp.
     ze sa to dzwieki dlugie i ktore waza sporo uzylem "music"
     ktora nie "pobiera" muzyki a bardziej ja zaczyna odtwarzac wprost z danego folderu
    */
    if(!second_music_)
    {
        if (!music_.openFromFile("music/music5.ogg"))
            std::cerr<<"error with music"<<std::endl;
        music_.setLoop (true);
        music_.setVolume (20);
        music_.play();
    }
    else
    {
        if (!music_.openFromFile("music/music1.ogg"))
            std::cerr<<"error with music"<<std::endl;
        music_.setLoop (true);
        music_.setVolume (20);
        music_.play();
    }
}

void Game::add_enemies()
{
    /*
     Dodawanie przeciwnikow wedlug schematu ponizej
    */
    //typ , pos_x , pos_y, dystans_chodzenia, czas ktory czeka w miejscu (dla wilka czas po ktorym zaatakuje)

    //Skeletons
    enemies_vector_.emplace_back(new new_enemies(enemy_type::skeleton, 650, 700 , 200, 3 ));
    enemies_vector_.emplace_back(new new_enemies(enemy_type::skeleton, 400, 700 , 200, 1 ));
    enemies_vector_.emplace_back(new new_enemies(enemy_type::skeleton, 2120, 440 , 180, 2 ));

    //Wolfs
    enemies_vector_.emplace_back(new new_enemies(enemy_type::wolf, 1800, 270 , 450, 0.25 ));
    enemies_vector_.emplace_back(new new_enemies(enemy_type::wolf, 2700, 785 , 500, 0.25 ));
    enemies_vector_.emplace_back(new new_enemies(enemy_type::wolf, 2600, 785 , 400, 0.25 ));

    //Golems
    enemies_vector_.emplace_back(new new_enemies(enemy_type::golem, 1700, 230 , 350, 3 ));
    enemies_vector_.emplace_back(new new_enemies(enemy_type::golem, 2000, 100 , 0, 3 ));
    enemies_vector_.emplace_back(new new_enemies(enemy_type::golem, 1600, 520 , 100, 3 ));
    enemies_vector_.emplace_back(new new_enemies(enemy_type::golem, 1600, 740 , 150, 2 ));

    //BOSS DEMON
    enemies_vector_.emplace_back(new new_enemies(enemy_type::demon, 4000, 550 , 1000, 3 ));
}

void Game::add_platforms()
{
    /*
     dodawanie platform,
     ze jest kilka typow sa rozne konstruktory parametrowe zaleznie od tego co chcemy wstawic
     -platformy zwykle
     -platformy ruszajace sie na boki
     -platformy ktore reaguja na dzwignie
     -platformy zadajace obrazenia
    */

    //pos_x , pos_y , scale_x, scale_y , width, height, platform_type type
    //podstawowa wysokosc tekstury - 65
    platforms_vector_.emplace_back(new new_platform(740,600,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(930,520,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(1140,440,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(530,680,0.5,1,platform_type::wood));

    //platforma z interakcja
    //float pos_x, float pos_y, float scale_x, float scale_y, float arm_x, float arm_y, const platform_type &type, bool interaction, bool moving_left_right
    platforms_vector_.emplace_back(new new_platform(1800,360,1,1,2100,195,platform_type::wood,true,true));
    platforms_vector_.emplace_back(new new_platform(2215,600,0.5,1,65,300,1480,835,platform_type::rock_pion,true));
    platforms_vector_.emplace_back(new new_platform(1800,360,1,1,2100,195,platform_type::wood,true,true));
    platforms_vector_.emplace_back(new new_platform(2600,-100,0.5,1,2280,305,platform_type::wood,true,false));
    platforms_vector_.emplace_back(new new_platform(4380,870,1,0.5,350,65,4250,214,platform_type::rock,true));

    platforms_vector_.emplace_back(new new_platform(0,817,1,1,700,50,platform_type::grass));
    platforms_vector_.emplace_back(new new_platform(1350,360,1,0.7,platform_type::grass_pocz));
    platforms_vector_.emplace_back(new new_platform(1480,360,1,0.7,platform_type::rock_with_gras));
    platforms_vector_.emplace_back(new new_platform(1700,360,1,0.7,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1950,230,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1420,400,0.7,1,65,1000,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(1465,650,1,0.5,250,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1465,870,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(1960,550,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(2215,0,0.7,1,65,620,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(1950,260,0.5,1,65,100,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(1900,870,1,0.5,130,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(2170,870,1,0.5,835,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(2220,340,1,0.5,250,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(2880,300,0.5,1,65,570,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(2880,300,1,0.5,300,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(3130,870,1,0.5,150,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(3410,870,1,0.5,150,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(3690,870,1,0.5,150,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(3350,200,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(3700,150,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(4050,100,0.5,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(4170,250,1,0.5,150,65,platform_type::rock));
    platforms_vector_.emplace_back(new new_platform(4310,0,0.5,1,65,900,platform_type::rock_pion));
    platforms_vector_.emplace_back(new new_platform(3100,720,0.25,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(3350,620,0.25,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(3600,720,0.25,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(3850,620,0.25,1,platform_type::wood));
    platforms_vector_.emplace_back(new new_platform(3600,520,0.25,1,platform_type::wood));

    //ruszajce sie platformy
    platforms_vector_.emplace_back(new new_platform(2600,730,0.5,1,platform_type::wood, true , 300, false));
    platforms_vector_.emplace_back(new new_platform(2500,600,0.5,1,platform_type::wood, true , 200 , true));
    platforms_vector_.emplace_back(new new_platform(2600,470,0.5,1,platform_type::wood, true , 300, false));

    //spikes
    platforms_vector_.emplace_back(new new_platform(1770,850,4,4,30,12,platform_type::spikes));
    platforms_vector_.emplace_back(new new_platform(2035,850,4,4,30,12,platform_type::spikes));
    platforms_vector_.emplace_back(new new_platform(2035,850,4,4,30,12,platform_type::spikes));
    platforms_vector_.emplace_back(new new_platform(3010,850,4,4,30,12,platform_type::spikes));
    platforms_vector_.emplace_back(new new_platform(3285,850,4,4,30,12,platform_type::spikes));
    platforms_vector_.emplace_back(new new_platform(3565,850,4,4,30,12,platform_type::spikes));
    platforms_vector_.emplace_back(new new_platform(3845,850,4,4,30,12,platform_type::spikes));
}

void Game::check_all_collisions()
{
    /*
     funkcja do sprawdzania kolizji
     gracz-przeciwnicy
     przeciwnicy-gracz
     gracz-platformy zadajace obrazenia
    */

    //sprawdzanie czy bohater trafia przeciwnikow atakujac
    if(player_->hero_action_==hero_action::attack1 || player_->hero_action_==hero_action::attack1_left ||
            player_->hero_action_==hero_action::spin_attack || player_->hero_action_==hero_action::spin_attack_left)
    {
        for(auto &el : enemies_vector_)
        {
            if(!el->was_attacked_ && collision_->check_fighting_collision (player_->return_hero (), el->return_enemy_sprite (), el->return_enemy_type ()))
            {
                el->hp_-=50;
                //std::cout<<"enemy hp:  "<<el->hp_<<std::endl;
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

    //sprawdzanie czy bohater dotyka platform zadajcych obrazenia
    for(auto &el : platforms_vector_)
    {
        if(player_->hero_action_!=hero_action::dying && el->damage_platform && collision_->check_platform_damage_collision (player_->return_hero (), el->return_sprite (), player_->return_standing_animation ()))
        {
            player_->hp_-=50;
        }
    }

    //sprawdzanie czy bohater nie wypadl za mape
    if(player_->return_hero ().getGlobalBounds ().top > window->getSize ().y && player_->return_hp ()>0)
    {
        player_->hp_-=100;
    }

    /*
     Najpierw wykrywamy czy bohater sie zbliza, jak osiagnie odpowiednia odleglosc to potwory zaczynaja wykonywac atak
     (wilk jest wyjatkiem i zaczyna biec, a dopiero jak wie ze trafi to zaczyna atakowac)
    */
    for(auto &el : enemies_vector_)
    {
        if(el->can_attack_ && collision_->is_player_near (player_->return_hero (), el->return_enemy_sprite () , el->return_enemy_type ()))
        {
            //okreslamy tylkko w ktora strone bedzie atakowal
            if(player_->return_hero_x_position () < el->return_enemy_sprite ().getPosition ().x)
            {
                el->attack_right_=false;
            }
            else
            {
                el->attack_right_=true;
            }


            if(el->return_enemy_type ()==enemy_type::wolf)
            {
                //sprawdzamy czy jest w stanie trafić
                if(!el->attacking_ && !collision_->check_fighting_collision (player_->return_hero (), el->return_enemy_sprite(),el->return_enemy_type ()))
                {
                    el->wolf_running_=true;
                }
                else if (el->can_attack_ && !el->attacking_ && player_->hero_action_!=hero_action::dying)
                {
                    el->wolf_running_=false;
                    el->attacking_=true;
                    el->can_attack_=false;
                }
            }
            else
            {
                el->attacking_=true;
                el->can_attack_=false;
            }

        }

        /*
            sprawdzanie czy bohater zostal trafiony przez przeciwnika
            -golem zadaje 100hp
            -demon i szkielet 50hp
            -wilk 25hp ale atakuje najszybciej
        */
        if(el->attacking_ && !el->hited_hero_ && collision_->check_fighting_collision (player_->return_hero (), el->return_enemy_sprite (),el->return_enemy_type ())
                && el->can_deal_dmg_ )
        {
            el->hited_hero_ = true;
            if(el->return_enemy_type ()==enemy_type::golem)
            {
                player_->hp_-=100;
            }
            else if(el->return_enemy_type ()==enemy_type::wolf)
            {
                player_->hp_-=25;
            }
            else
            {
                player_->hp_-=50;
            }

        }
    }
}

void Game::check_enemy_hp_()
{
    /*
     sprawdzanie czy przeciwnicy umarli, jezeli tak to obiekty sa usuwane
     jezeli demon umarl (nasz BOSS) to gra sie konczy
    */
    for(size_t i=0; i<enemies_vector_.size (); i++)
    {
        if(enemies_vector_[i]->dead_==true)
        {
            if(enemies_vector_[i]->return_enemy_type ()==enemy_type::demon)
            {
                game_end_=true;
            }
            enemies_vector_.erase (enemies_vector_.begin ()+i);
        }

    }
}

void Game::updatePollEvents()
{
    sf::Event e;

    /*
     sprawdzanie wydarzen
     -zamykanie okna
     -rozpoczecie gry
     -klawisz funkcyjny F
    */
    while (this->window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
        {
            this->window->close();
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
        {
            this->window->close();
            this->music_.stop ();
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Space && !game_start_)
        {
            this->game_start_=true;
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::F )
        {
            for(size_t i = 0; i<platforms_vector_.size ();i++)
            {
                if(platforms_vector_[i]->interaction_ &&
                        collision_->check_fighting_collision (player_->return_hero (), platforms_vector_[i]->return_sprite_interaction (), enemy_type::none)
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
    /*
    Aktualizowanie wszystkich obiektow ktore tego wymagaja, ustawianie widoku, muzyki,
    funkcja ta wykonuje sie co petle
    */
    this->time_ = clock_.restart();              //restartuje zegar

    if(!first_loop_)
    {
        this->updatePollEvents();

        if(!game_end_)
        {
            this->hero_x_position_=player_->return_hero_x_position ();

            //ustawianie kamery
            if(hero_x_position_>=2880)
            {
                this->widok.setCenter (3600, window->getSize ().y/2);

                this->window->setView (widok);
            }
            else if(hero_x_position_>= window->getSize ().x/2.0f)
            {
                this->widok.setCenter (hero_x_position_, window->getSize ().y/2);

                this->window->setView (widok);
            }
            else if (widok.getCenter ().x != 0)
            {
                this->widok.setCenter (widok.getSize ().x /2, window->getSize ().y/2);
                this->window->setView (widok);
            }

            this->collision_->vector_collision_platforms_.clear ();

            for(const auto &el : platforms_vector_)
            {
                if(!el->damage_platform)
                {
                    collision_->copy_platforms (el->return_sprite ());
                }
            }

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
        //ustawianie muzyki przy dojsciu do bossa
        if(hero_x_position_>=2800 && !second_music_)
        {
            second_music_=true;
            set_music ();
        }
    }
    else
    {
        first_loop_=false;
    }

}

void Game::gamerender()
{
    /*
     rysowanie wszystkich elementow na scenie
    */
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

    if(!game_start_)
    {
        this->window->draw (sprite_start_);
    }
    if(game_end_)
    {
        this->window->draw (text_);
    }

    this->window->display();
}

bool Game::game_is_running() const
{
    return this->window->isOpen ();
}

