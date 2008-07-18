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


// using namespace std;
using namespace PacGame::GameClasses;

int main(int argc, char *argv[])
{
    PGame pacgame(640, 480, "xSoko project");

    if(!pacgame.initGame())
    {
        PacGame::Messages::initMessage("game", false); 
        return -1;
    }
    
    PLevel *test = new PLevel("data/testlevel.lvl");   
    PGameSession *testsession = new PGameSession(test);

    pacgame.loadSession(testsession);
    pacgame.run();

  /*  test.loadLevelFromFile();
    test.print();
    test.printLevelByMeta();*/
  //  system("pause");
    return 0;
}