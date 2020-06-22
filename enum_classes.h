#ifndef ENUM_CLASSES_H
#define ENUM_CLASSES_H

enum class hero_action
    {
        standing,
        standing_left,
        walking,
        walking_left,
        jumping,
        falling,
        attack1,
        attack1_left,
        dying,
        spin_attack,
        spin_attack_left,
    };

enum class enemy_type
    {
    skeleton,
    wolf,

};

enum class enemy_action
{
    standing,
    standing_left,
    walking,
    dying,
    attack,
    attack_left,

};

enum class platform_type
{
    grass,
    wood,
    rock,
    rock_with_gras,
    rock_pion,
    grass_pocz,
    spikes,


};

#endif // ENUM_CLASSES_H
