/*
  codename: Pac-Game
  Aljosa Osep 2007
*/

#include <cstdlib>
#include "game.h"
#include "entities.h"

// using namespace std;
using namespace PacGame::GameClasses;

int main(int argc, char *argv[])
{
    PGame pacgame;
    pacgame.setWindow(640, 480);

    pacgame.initGame();

    pacgame.mainLoop();

    PacGame::RenderMaschine::PRenderer renderer;

    /*
    PVector2D prvi(3.2, 3.2);
    PVector2D drugi(1.0, 1.0);
    PVector2D tretji(0.0, 0.0);
    tretji = prvi;
    tretji.printCoordinates();
    */

    system("pause");
    return 0;
}
