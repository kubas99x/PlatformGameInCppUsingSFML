#include "game.h"



int main()
{
    Game game;

    while(game.game_is_running ())
    {
        //Game update (events itp.
        game.update();
        //rysowanie
        game.gamerender();
    }

    //does it works?
    //and now?
    return 0;
}
