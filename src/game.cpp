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
 * File: game.cpp
 *
 * Summary:
 * Includes game core implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 */

#include "game.h"
#include <AL/alut.h>

using namespace PacGame;

namespace PacGame
{
      namespace GameClasses
      {
          // construcotrs
          PGame::PGame() 
          {
                  windowTitle = "xSoko";
          }

          PGame::PGame(int _width, int _height, string _title) 
          {
                  windowWidth = _width;
                  windowHeight = _height;
                  windowTitle = _title;
                  
                  alutInit (NULL, NULL); // inicializacija ALUT in OpenAL API
                  alGetError(); // počisti napake
          }

          // destructor
          PGame::~PGame()
          {
                  terminateGLFW();
                  alutExit ();
          }

          // methods
          void PGame::loadSession(PGameSession *session)
          {
              this->session = session;
          }
          
          bool PGame::run()
          {
              //TODO: fix this
              this->session->mainLoop();
              return true;
          }
          
          // setters
          void PGame::setWindow(int _width, int _height)
          {
               windowWidth = _width;   
               windowHeight = _height;
          }

          void PGame::setWindowTitle(string _title)
          {
               windowTitle = _title;
          }

          void PGame::terminateGLFW()
          {
               Messages::infoMessage("Termination, destroying glfw...");
               glfwTerminate();
          }
      }
}
