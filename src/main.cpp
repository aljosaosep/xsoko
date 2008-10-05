/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep, Jernej Skrabec, Jernej Halozan 2008 <aljosa.osep@gmail.com, jernej.skrabec@gmail.com, jernej.halozan@gmail.com>
 * 
 * xSoko project is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * xSoko project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
 * Jernej October 5 2008
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
    //PLevel *test = new PLevel("data/testlevel.lvl");
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
    //PInputSystem input(test); 

    // make session
    //PGameSession *testsession = new PGameSession(test, &input);

    // loads session
    pacgame.loadSession(new PGuiSession(640,480));

    // run game
    pacgame.run();

    return 0;
}
