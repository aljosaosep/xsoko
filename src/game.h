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
 * File: game.h
 *
 * Summary:
 * Includes game core class definition
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 * Jernej October 5 2008
 */

#ifndef __GAME_H
#define __GAME_H

#include "messages.h"
#include "input.h"
#include "renderer/renderer.h"
#include "level.h"
#include "gui/gui.h"
#include "gui/window.h"

using namespace PacGame::RenderMaschine;

namespace PacGame
{
      namespace GameClasses
      {
            /**********************************************************
           * PGame
           *
           * Represents a whole window and game main functions
           * --------------------------------------------------------
           * Aljosa 2007
           * ********************************************************/
          class PGame
          {
          private:
              int windowWidth;
              int windowHeight;
              bool fullscreen;
              string windowTitle;

              PLevel *level;
              PPlayer *player;
              PCamera *camera;

              PInputSystem *input;
              double rotations_per_tick;
              bool levelLoaded;
              bool gameQuit;
              bool forceLevelQuit;
              //bool toggleMenu;

              //gui components
              //Gui &gui;
              Window* mainMenu;
              Window* gameMenu;

          private:
              // constructor
              PGame();
              // destructor
              ~PGame(){}

              //methods
              void prepareGui();
          public:
              bool initialize(int _width, int _height, string _title);
              void mainLoop();
              void quit();
              void setResolution(int width, int height, bool fullscreen);
              void terminate();

              void loadLevel(string levelPath);

              //getters
              static PGame& getInstance();
          };       
      }       
}

#endif
