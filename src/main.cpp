/* 
 * Codename: xSoko
 * File: main.cpp
 *
 * Summary:
 * Game entry point
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 */

#include <cstdlib>
#include "level.h"
#include "game.h"
#include "messages.h"
#include "input.h"
#include "renderer/renderer.h"


// using namespace std;
using namespace PacGame::GameClasses;
using namespace PacGame::RenderMaschine;

int main(int argc, char *argv[])
{
    // game and window creation
    PGame pacgame(640, 480, "xSoko project");
 
    // game initialization
    if(!pacgame.initGame())
    {
        PacGame::Messages::initMessage("game", false); 
        return -1;
    }
    
    // level object
    PLevel *test = new PLevel("data/testlevel.lvl");
    /*test->initialize();
    if (test->saveStateToFile("test.txt"))
    {
        cout << "Zapis stopnje v datoteko uspel!" << endl;
    } else {
        cout << "Napaka pri zapisu stopnje v datoteko!" << endl;
    }*/
    // renderer object
//    PRenderer *renderer = new PRenderer;
    
    // input object
    PInputSystem input(test); 

    // make session
    PGameSession *testsession = new PGameSession(test, &input);

    // loads session
    pacgame.loadSession(testsession);

    // run game
    pacgame.run();

    return 0;
}
