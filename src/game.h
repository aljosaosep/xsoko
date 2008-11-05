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
#include "session.h"
#include "input.h"
#include "renderer/renderer.h"

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
              int windowWidth, windowHeight;
              string windowTitle;
             // PLevel *currentLevel;  
              PGuiSession *session;  // pointer to current game class

          public:
              // variables

              // prototypes
              // constructors
              PGame();
              PGame(int _width, int _height, string _title);

              // destructor
              ~PGame();

              // other
              bool run();
              bool initGame();
              void terminateGLFW();

              // setters
              void setWindow(int _width, int _height);
              void setWindowTitle(string _title);
            //  void setRenderer();
                  
              void loadSession(PGuiSession *session);

              /*******************************************
               * processKey()
               * function prototype; function takes action 
               * based on key that is pressed
               * ----------------------------------
               * Jernej Skrabec
               * modified by Aljosa
               *******************************************/
        //      static void GLFWCALL processKey(int key, int action); 
          };       
      }       
}

#endif
