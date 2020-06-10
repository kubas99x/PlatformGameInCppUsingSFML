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
    };

enum class enemy_type
    {
    skeleton,

};

enum class enemy_action
{
    standing,
    walking,
    dying,

};

enum class platform_type
{
    grass,
    wood,
    rock,
    rock_with_gras,
    rock_pion,
    grass_pocz,


};

#endif // ENUM_CLASSES_H
