#include "new_enemies.h"
#include "iostream"
new_enemies::new_enemies()
{

}

new_enemies::new_enemies(const enemy_type &type ,float pos_x, float pos_y ,float distance, float time)
{
    this->init_variables ();
    this->walk_distance_ = distance;
    this->waiting_time_start_ = time;
    this->enemy_type_=type;
    this->start_position_x_=pos_x;
    this->start_position_y_=pos_y;
    this->download_textures ();
    this->set_animations ();
    this->set_enemy ();
    this->set_sound_effects ();

}

void new_enemies::init_variables()
{
    this->enemy_step_dying_=0;
    this->enemy_step_standing_=0;
    this->enemy_step_attack_=0;
    this->enemy_step_walking_=0;
    this->was_attacked_ = false;
    this->dead_ = false;
    this->moving_left_ = false;
    this->attacking_ = false;
    this->can_attack_ = true;
    this->hited_hero_ = false;
    this->wolf_running_ = false;
    this->enemy_frame_time_ = 0;
}


void new_enemies::set_sound_effects()
{
    sound.setLoop (false);
    if(enemy_type_==enemy_type::demon)
    {
    buffer.emplace_back(load_sound_effect ("music/demon_dying.wav"));
    buffer.emplace_back(load_sound_effect ("music/zianie_ogniem1.wav"));
    }
    if(enemy_type_==enemy_type::skeleton)
    {
    buffer.emplace_back(load_sound_effect ("music/skeleton_dying.wav"));
    }
    if(enemy_type_==enemy_type::golem)
    {
    buffer.emplace_back(load_sound_effect ("music/golem_dying.wav"));
    }

}

void new_enemies::download_textures()
{
    if(enemy_type_==enemy_type::skeleton)
    {
        texture_.emplace_back(get_textures("textures/skeleton_standing.png"));              //0
        texture_.emplace_back(get_textures("textures/skeleton_standing_left.png"));        //1
        texture_.emplace_back(get_textures("textures/skeleton_die.png"));                   //2
        texture_.emplace_back(get_textures ("textures/skeleton_attack_left.png"));         //3
        texture_.emplace_back(get_textures ("textures/skeleton_attack.png"));               //4
    }
    if(enemy_type_==enemy_type::wolf)
    {
        texture_.emplace_back(get_textures ("textures/wolf_standing.png"));
        texture_.emplace_back(get_textures ("textures/wolf_standing_left.png"));
        texture_.emplace_back(get_textures ("textures/wolf_death.png"));
        texture_.emplace_back(get_textures ("textures/wolf_attack_left.png"));         //3
        texture_.emplace_back(get_textures ("textures/wolf_attack.png"));               //4
        texture_.emplace_back(get_textures ("textures/wolf_run.png"));             //5
        texture_.emplace_back(get_textures ("textures/wolf_run_left.png"));             //6
    }
    if(enemy_type_==enemy_type::golem)
    {
        texture_.emplace_back(get_textures("textures/golem_standing.png"));              //0
        texture_.emplace_back(get_textures("textures/golem_standing_left.png"));        //1
        texture_.emplace_back(get_textures ("textures/golem_death.png"));                //2
        texture_.emplace_back(get_textures ("textures/golem_attack_left.png"));         //3
        texture_.emplace_back(get_textures ("textures/golem_attack.png"));               //4
        texture_.emplace_back(get_textures ("textures/golem_walking.png"));             //5
        texture_.emplace_back(get_textures ("textures/golem_walking_left.png"));             //6
    }
    if(enemy_type_==enemy_type::demon)
    {
        texture_.emplace_back(get_textures("textures/demon_standing.png"));              //0
        texture_.emplace_back(get_textures("textures/demon_standing_left.png"));        //1
        texture_.emplace_back(get_textures ("textures/demon_death.png"));                //2
        texture_.emplace_back(get_textures ("textures/demon_attack_left.png"));         //3
        texture_.emplace_back(get_textures ("textures/demon_attack.png"));               //4
        texture_.emplace_back(get_textures ("textures/health_bar_enemy.png"));           //5
    }
}

void new_enemies::set_enemy()
{

    enemy_sprite_.setTexture (texture_[0]);
    enemy_sprite_.setTextureRect (animations_[enemy_action::standing][0]);
    enemy_sprite_.setPosition (start_position_x_, start_position_y_);
    distance_=walk_distance_;
    waiting_time_=waiting_time_start_;

    switch (enemy_type_)
    {
    case enemy_type::skeleton:
    {
        enemy_action_=enemy_action::standing;
        enemy_sprite_.setScale (3.5,3.5);
        move_left=true;
        hp_=100;
        waiting_for_attack_=3;
        velocity_=200;
        break;
    }
    case enemy_type::wolf:
    {
        enemy_action_=enemy_action::standing_left;
        enemy_sprite_.setScale (3,3);
        move_left=true;
        hp_=50;
        waiting_for_attack_=waiting_time_start_;
        velocity_=450;
        break;
    }
    case enemy_type::golem:
    {
        enemy_action_=enemy_action::standing;
        enemy_sprite_.setScale (3,3);
        move_left=true;
        hp_=150;
        waiting_for_attack_=3;
        velocity_=150;
        break;
    }
    case enemy_type::demon:
    {
        enemy_action_=enemy_action::standing;
        enemy_sprite_.setScale (2,2);
        move_left=true;
        hp_=50;
        waiting_for_attack_=3;
        health_bar_.setTexture (texture_[5]);
        health_bar_.setTextureRect (health_animations_[0]);
        health_bar_.setScale (4,4);
        health_bar_.setPosition (3870,0);
        velocity_=800;
        break;
    }
    default:
        break;
    }

}
void new_enemies::set_animations()
{
    if(enemy_type_==enemy_type::skeleton)
    {
        std::vector <sf::IntRect> tmp_vector;
        for(int i=0; i<24*11; i+=24)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,24,36));
        }
        animations_.emplace(enemy_action::standing,tmp_vector);

        tmp_vector.clear ();
        for(int i=0; i<24*11; i+=24)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,22,36));
        }
        animations_.emplace(enemy_action::standing_left,tmp_vector);

        tmp_vector.clear ();
        for(int i=0; i<33*16; i+=33)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,34,32));

        }
        animations_.emplace(enemy_action::dying,tmp_vector);

        tmp_vector.clear ();
        int height = 36;
        tmp_vector.emplace_back(sf::IntRect(2,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(46,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(90,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(123,0,30,height));
        tmp_vector.emplace_back(sf::IntRect(160,0,33,height));
        tmp_vector.emplace_back(sf::IntRect(200,0,34,height));
        tmp_vector.emplace_back(sf::IntRect(244,0,33,height));
        tmp_vector.emplace_back(sf::IntRect(288,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(332,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(373,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(415,0,40,height));
        tmp_vector.emplace_back(sf::IntRect(468,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(510,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(554,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(595,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(680,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(723,0,35,height));

        animations_.emplace(enemy_action::attack_left,tmp_vector);

        tmp_vector.clear ();
        tmp_vector.emplace_back(sf::IntRect(2,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(45,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(88,0,23,height));
        tmp_vector.emplace_back(sf::IntRect(133,0,30,height));
        tmp_vector.emplace_back(sf::IntRect(175,0,33,height));
        tmp_vector.emplace_back(sf::IntRect(215,0,34,height));
        tmp_vector.emplace_back(sf::IntRect(257,0,33,height));
        tmp_vector.emplace_back(sf::IntRect(303,0,40,height));
        tmp_vector.emplace_back(sf::IntRect(353,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(394,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(437,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(481,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(524,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(565,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(607,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(646,0,35,height));
        tmp_vector.emplace_back(sf::IntRect(690,0,35,height));

        animations_.emplace(enemy_action::attack,tmp_vector);
    }

    if(enemy_type_==enemy_type::wolf)
    {
        std::vector <sf::IntRect> tmp_vector;

        for(int i=13; i<64*12; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,15,40,30));
        }
        animations_.emplace(enemy_action::standing,tmp_vector);

        tmp_vector.clear ();
        for(int i=15; i<64*12; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,15,40,30));
        }
        animations_.emplace(enemy_action::standing_left,tmp_vector);

        tmp_vector.clear ();
        for(int i=7; i<64*18; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,15,40,30));
        }
        animations_.emplace(enemy_action::dying, tmp_vector);

        tmp_vector.clear ();
        for(int i=9; i<64*16; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,15,40,30));
        }
        animations_.emplace(enemy_action::attack_left, tmp_vector);

        tmp_vector.clear ();
        for(int i=13; i<64*16; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,15,40,30));
        }
        animations_.emplace(enemy_action::attack, tmp_vector);

        tmp_vector.clear ();
        for(int i=11; i<64*8; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,15,40,30));
        }
        animations_.emplace(enemy_action::walking_left, tmp_vector);

        tmp_vector.clear ();
        for(int i=13; i<64*8; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,15,40,30));
        }
        animations_.emplace(enemy_action::walking, tmp_vector);

    }

    if(enemy_type_==enemy_type::golem)
    {
        std::vector <sf::IntRect> tmp_vector;

        for(int i=15; i<64*12; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,55,45));
        }
        animations_.emplace(enemy_action::standing,tmp_vector);

        tmp_vector.clear ();
        for(int i=10; i<64*12; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,55,45));
        }
        animations_.emplace(enemy_action::standing_left,tmp_vector);

        tmp_vector.clear ();
        for(int i=15; i<64*28; i+=64)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,55,45));
        }
        animations_.emplace(enemy_action::dying,tmp_vector);

        tmp_vector.clear ();
        for(int i=20; i<80*16; i+=80)
        {
            if(i==420)
                i-=10;
            tmp_vector.emplace_back(sf::IntRect(i,0,60,45));
            if(i==430)
                i+=10;
        }
        animations_.emplace(enemy_action::attack_left,tmp_vector);

        tmp_vector.clear ();
        for(int i=0; i<80*16; i+=80)
        {

            tmp_vector.emplace_back(sf::IntRect(i,0,60,45));

        }
        animations_.emplace(enemy_action::attack,tmp_vector);

        tmp_vector.clear ();
        for(int i=15; i<65*7; i+=65)
        {

            tmp_vector.emplace_back(sf::IntRect(i,0,55,45));

        }
        animations_.emplace(enemy_action::walking,tmp_vector);

        tmp_vector.clear ();
        for(int i=10; i<65*7; i+=65)
        {

            tmp_vector.emplace_back(sf::IntRect(i,0,55,45));

        }
        animations_.emplace(enemy_action::walking_left,tmp_vector);
    }
    if(enemy_type_==enemy_type::demon)
    {
        std::vector <sf::IntRect> tmp_vector;

        for(int i=0; i<160*6; i+=160)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,160,180));
        }
        animations_.emplace(enemy_action::standing,tmp_vector);

        tmp_vector.clear ();
        for(int i=0; i<160*6; i+=160)
        {
            tmp_vector.emplace_back(sf::IntRect(i,0,160,180));
        }
        animations_.emplace(enemy_action::standing_left,tmp_vector);

        tmp_vector.clear ();
        for(int i=70; i<230*11; i+=230)
        {
            if(i<1400)
            {
                tmp_vector.emplace_back(sf::IntRect(i,25,200,160));
            }
            else
            {
                tmp_vector.emplace_back(sf::IntRect(i,5,200,180));
            }
        }
        animations_.emplace(enemy_action::attack_left,tmp_vector);

        tmp_vector.clear ();
        for(int i=30; i<240*11; i+=240)
        {
            if(i==1230)
                i-=20;
            tmp_vector.emplace_back(sf::IntRect(i,5,200,180));

        }
        animations_.emplace(enemy_action::attack,tmp_vector);

        tmp_vector.clear ();
        for(int i=20; i<150*10; i+=150)
        {
            if(i==320)
                i+=10;
            if(i==1080)
                i-=20;
            if(i==1210)
                i-=10;
            if(i==1350)
                i-=25;
            if(i==1500)
                i-=40;
            tmp_vector.emplace_back(sf::IntRect(i,0,150,140));
        }
        tmp_vector.emplace_back(sf::IntRect(1820,0,90,140));
        tmp_vector.emplace_back(sf::IntRect(1913,0,90,140));
        tmp_vector.emplace_back(sf::IntRect(1820,0,90,140));
        tmp_vector.emplace_back(sf::IntRect(2000,0,90,140));
        tmp_vector.emplace_back(sf::IntRect(2090,0,90,140));
        tmp_vector.emplace_back(sf::IntRect(1820,0,90,140));
        tmp_vector.emplace_back(sf::IntRect(2197,0,60,140));
        tmp_vector.emplace_back(sf::IntRect(2260,0,70,140));
        tmp_vector.emplace_back(sf::IntRect(2340,0,70,140));
        tmp_vector.emplace_back(sf::IntRect(2410,0,60,140));
        tmp_vector.emplace_back(sf::IntRect(2470,0,64,140));
        tmp_vector.emplace_back(sf::IntRect(2534,0,62,140));
        tmp_vector.emplace_back(sf::IntRect(2598,0,62,140));
        tmp_vector.emplace_back(sf::IntRect(2660,0,63,140));
        tmp_vector.emplace_back(sf::IntRect(2724,0,61,140));
        tmp_vector.emplace_back(sf::IntRect(2785,0,50,140));
        tmp_vector.emplace_back(sf::IntRect(2840,0,50,140));
        tmp_vector.emplace_back(sf::IntRect(2897,0,50,140));
        tmp_vector.emplace_back(sf::IntRect(2956,0,55,140));
        tmp_vector.emplace_back(sf::IntRect(3011,0,80,140));
        tmp_vector.emplace_back(sf::IntRect(3111,0,60,140));
        tmp_vector.emplace_back(sf::IntRect(3183,0,60,140));
        tmp_vector.emplace_back(sf::IntRect(3255,0,60,140));
        tmp_vector.emplace_back(sf::IntRect(3313,0,60,140));

        animations_.emplace(enemy_action::dying,tmp_vector);
        for(size_t i = 2; i<90 ; i+=10)
        {
            health_animations_.emplace_back(sf::IntRect(36, i, 109, 10));
        }
    }
}



void new_enemies::update_enemy_frame()
{
    enemy_frame_time_+=time_.asSeconds ();
    if(enemy_type_==enemy_type::demon)
    {
        if(enemy_frame_time_>=1.0f/6.0f && (enemy_action_==enemy_action::standing || enemy_action_==enemy_action::standing_left ))
        {
            enemy_step_standing_++;
            enemy_frame_time_=0;
            enemy_animation_change_=true;
        }
    }
    else
    {
        if(enemy_frame_time_>=1.0f/13.0f && (enemy_action_==enemy_action::standing || enemy_action_==enemy_action::standing_left ))
        {
            enemy_step_standing_++;
            enemy_frame_time_=0;
            enemy_animation_change_=true;
        }
    }
    if(enemy_frame_time_>=1.0f/8.0f && enemy_action_==enemy_action::dying )
    {
        enemy_step_dying_++;
        enemy_frame_time_=0;
        enemy_animation_change_=true;
    }
    if(enemy_frame_time_>=1.0f/8.0f && (enemy_action_==enemy_action::attack_left || enemy_action_==enemy_action::attack) )
    {
        enemy_step_attack_++;
        enemy_frame_time_=0;
        enemy_animation_change_=true;
        if(enemy_type_==enemy_type::golem)
        {
            if(enemy_step_attack_>=9 && enemy_step_attack_<=13)
            {
                can_deal_dmg_=true;
            }
            else
            {
                can_deal_dmg_=false;
            }
        }
        else
        {
            if(enemy_step_attack_>=6 && enemy_step_attack_<=12)
            {
                can_deal_dmg_=true;
            }
            else
            {
                can_deal_dmg_=false;
            }
        }
    }
    if((enemy_frame_time_>=1.0f/5.0f && (enemy_action_==enemy_action::walking || enemy_action_==enemy_action::walking_left)&&enemy_type_!=enemy_type::wolf)
            || (enemy_frame_time_>=1.0f/10.0f && (enemy_action_==enemy_action::walking || enemy_action_==enemy_action::walking_left)&&enemy_type_==enemy_type::wolf))
    {
        enemy_step_walking_++;
        enemy_frame_time_=0;
        enemy_animation_change_=true;
    }
}
void new_enemies::choose_enemy_animation()
{
    if(this->enemy_animation_change_)
    {
        if(enemy_action_==enemy_action::standing)
        {
            if(this->enemy_step_standing_>=animations_[enemy_action::standing].size ()-1)
            {
                enemy_step_standing_=0;
            }
            this->enemy_sprite_.setTexture (texture_[0]);
            this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::standing][this->enemy_step_standing_]);
        }

        if(enemy_action_==enemy_action::standing_left)
        {
            if(this->enemy_step_standing_>=animations_[enemy_action::standing_left].size ()-1)
            {
                enemy_step_standing_=0;
            }
            this->enemy_sprite_.setTexture (texture_[1]);
            this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::standing_left][this->enemy_step_standing_]);
        }

        if(enemy_action_==enemy_action::dying)
        {
            if(this->enemy_step_dying_>=animations_[enemy_action::dying].size ()-1)
            {
                this->dead_=true;
            }
            this->enemy_sprite_.setTexture (texture_[2]);
            if(enemy_type_==enemy_type::wolf)
            {
                this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::dying][animations_[enemy_action::dying].size ()-1 -this->enemy_step_dying_]);
            }
            else
            {
                this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::dying][this->enemy_step_dying_]);
            }
        }
        if(enemy_action_==enemy_action::walking)
        {
            if(this->enemy_step_walking_>=animations_[enemy_action::walking].size ()-1)
            {
                enemy_step_walking_=0;
            }
            this->enemy_sprite_.setTexture (texture_[5]);
            this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::walking][this->enemy_step_walking_]);
        }
        if(enemy_action_==enemy_action::walking_left)
        {
            if(this->enemy_step_walking_>=animations_[enemy_action::walking_left].size ()-1)
            {
                enemy_step_walking_=0;
            }
            this->enemy_sprite_.setTexture (texture_[6]);
            this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::walking_left][this->animations_[enemy_action::walking_left].size ()- 1 -this->enemy_step_walking_]);
        }
        if(enemy_action_==enemy_action::attack_left)
        {
            if(this->enemy_step_attack_>=animations_[enemy_action::attack_left].size ()-1)
            {
                enemy_step_attack_=0;
                attacking_ = false;
                can_deal_dmg_=false;
                if(enemy_type_==enemy_type::demon)
                {
                    enemy_sprite_.move (100,0);
                }
            }
            this->enemy_sprite_.setTexture (texture_[3]);
            if(enemy_type_==enemy_type::demon)
            {
                this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::attack_left][this->enemy_step_attack_]);
            }
            else
            {
                this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::attack_left][animations_[enemy_action::attack_left].size ()-1 - this->enemy_step_attack_]);
            }
        }
        if(enemy_action_==enemy_action::attack)
        {
            if(this->enemy_step_attack_>=animations_[enemy_action::attack].size ()-1)
            {
                enemy_step_attack_=0;
                attacking_ = false;
                can_deal_dmg_=false;
                if(enemy_type_==enemy_type::demon)
                {
                    enemy_sprite_.move (-50,0);
                }
            }
            this->enemy_sprite_.setTexture (texture_[4]);
            if(enemy_type_==enemy_type::demon)
            {
                this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::attack_left][animations_[enemy_action::attack_left].size ()-1 - this->enemy_step_attack_]);
            }
            else
            {
                this->enemy_sprite_.setTextureRect (this->animations_[enemy_action::attack][this->enemy_step_attack_]);
            }

        }
    }
    enemy_animation_change_=false;
}

void new_enemies::move_enemy()
{
    if(!attacking_)
    {
        if(waiting_time_<=0)
        {
            if(move_left)
            {
                if(enemy_type_==enemy_type::skeleton || enemy_type_==enemy_type::demon)
                {
                    enemy_action_=enemy_action::standing_left;
                }
                else
                {
                    enemy_action_=enemy_action::walking_left;
                }

                enemy_sprite_.move (-0.25*velocity_*time_.asSeconds (),0);
                distance_-=0.25*velocity_*time_.asSeconds ();
                if(distance_<=0)
                {
                    distance_=walk_distance_;
                    waiting_time_=waiting_time_start_;
                    move_left=false;
                    enemy_action_=enemy_action::standing_left;
                }
            }
            else
            {
                if(enemy_type_==enemy_type::skeleton || enemy_type_==enemy_type::demon)
                {
                    enemy_action_=enemy_action::standing;
                }
                else
                {
                    enemy_action_=enemy_action::walking;
                }
                enemy_sprite_.move (0.25*velocity_*time_.asSeconds (),0);
                distance_-=0.25*velocity_*time_.asSeconds ();
                if(distance_<=0)
                {
                    distance_=walk_distance_;
                    waiting_time_=waiting_time_start_;
                    move_left=true;
                    enemy_action_=enemy_action::standing;
                }
            }
        }
    }

}

void new_enemies::move_wolf()
{
    if(wolf_running_)
    {

        if(!attack_right_ && distance_>0)
        {
            enemy_action_=enemy_action::walking_left;
            enemy_sprite_.move (-0.5*velocity_*time_.asSeconds (),0);
            distance_-=0.5*velocity_*time_.asSeconds ();
        }
        else if(distance_<=walk_distance_ && attack_right_)
        {
            enemy_action_=enemy_action::walking;
            enemy_sprite_.move (0.5*velocity_*time_.asSeconds (),0);
            distance_+=0.5*velocity_*time_.asSeconds ();
        }
    }
    else if (attacking_ )
    {
        waiting_for_attack_-=time_.asSeconds ();
        if(waiting_for_attack_<=0 && enemy_action_!=enemy_action::attack_left && enemy_action_!=enemy_action::attack)
        {
            can_attack_=true;
            hited_hero_=false;
            if(!attack_right_)
            {
                enemy_action_=enemy_action::attack_left;
            }
            else
            {
                enemy_action_=enemy_action::attack;
            }
        }
    }
    else if(!attacking_ && !wolf_running_)
    {
        enemy_action_=enemy_action::standing_left;
        waiting_for_attack_=waiting_time_start_;
    }
}
void new_enemies::attack_stuff()
{
    waiting_for_attack_-=time_.asSeconds ();
    if(waiting_for_attack_<=0)
    {
        hited_hero_ = false;
        can_attack_=true;
        if(enemy_type_==enemy_type::demon)
        {
            waiting_for_attack_=5;
        }
        else
        {
            waiting_for_attack_=3;
        }
    }
}



void new_enemies::check_hp()
{
    if(this->hp_<=0 && enemy_action_!=enemy_action::dying)
    {
        if(enemy_type_==enemy_type::demon || enemy_type_==enemy_type::skeleton)
        {
            sound.setBuffer (buffer[0]);
            sound.play ();
        }
        enemy_action_=enemy_action::dying;
        can_deal_dmg_=false;
    }
    if(enemy_type_==enemy_type::demon)
    {
        switch(hp_)
        {
        case(400):
        {
            health_bar_.setTextureRect (health_animations_[0]);
            break;
        }
        case(350):
        {
            health_bar_.setTextureRect (health_animations_[1]);
            break;
        }
        case(300):
        {
            health_bar_.setTextureRect (health_animations_[2]);
            break;
        }
        case(250):
        {
            health_bar_.setTextureRect (health_animations_[3]);
            break;
        }
        case(200):
        {
            health_bar_.setTextureRect (health_animations_[4]);
            break;
        }
        case(150):
        {
            health_bar_.setTextureRect (health_animations_[5]);
            break;
        }
        case(100):
        {
            health_bar_.setTextureRect (health_animations_[6]);
            break;
        }
        case(50):
        {
            health_bar_.setTextureRect (health_animations_[7]);
            break;
        }
        case(0):
        {
            health_bar_.setTextureRect (health_animations_[8]);
            break;
        }
        default:
        {
            break;
        }

        }
    }
}



void new_enemies::update_enemy()
{
    this->time_=clock.restart ();
    waiting_time_-=time_.asSeconds ();

    this->update_enemy_frame ();
    this->choose_enemy_animation ();


    if((enemy_type_ == enemy_type::skeleton || enemy_type_ == enemy_type::golem || enemy_type_==enemy_type::demon) && enemy_action_!=enemy_action::dying)
    {
        this->move_enemy ();
        if(attacking_ )
        {
            if(attack_right_ && enemy_action_!= enemy_action::attack )
            {
                this->enemy_action_= enemy_action::attack;
                if(enemy_type_==enemy_type::demon)
                {
                    sound.setBuffer (buffer[1]);
                    sound.play ();
                    enemy_sprite_.move (50,0);
                }
            }
            else if (!attack_right_ && enemy_action_!= enemy_action::attack_left )
            {
                this->enemy_action_=enemy_action::attack_left;
                if(enemy_type_==enemy_type::demon)
                {
                    sound.setBuffer (buffer[1]);
                    sound.play ();
                    enemy_sprite_.move (-100,0);
                }
            }
        }
        if(!can_attack_ && !attacking_ )
        {
            sound.stop ();
            attack_stuff ();
        }
    }
    else if (enemy_type_==enemy_type::wolf)
    {
        this->move_wolf ();

    }


    this->check_hp ();

}
enemy_type new_enemies::return_enemy_type()
{
    return enemy_type_;
}

sf::Sprite new_enemies::return_enemy_sprite()
{
    return enemy_sprite_;
}

void new_enemies::render(sf::RenderWindow &window)
{
    window.draw (enemy_sprite_);
    if(enemy_type_==enemy_type::demon)
    {
        window.draw(health_bar_);
    }
}


