#include "game.h"


int main()
{
    Game game;

    while(game.game_is_running ())
    {
        //Game update
        game.update();

        //rysowanie
        game.gamerender();
    }

    return 0;
}
