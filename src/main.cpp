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
#ifdef _WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include "game.h"

using namespace PacGame::GameClasses;

#ifdef _WINDOWS
int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
    PGame &game = PGame::getInstance();
 
    // game initialization
    if(game.initialize(800, 600, "xSoko project"))
    {
        game.mainLoop();
        game.terminate();
    }
    
    return 0;
}
