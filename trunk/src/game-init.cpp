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
 * File: game-funcinit.cpp
 *
 * Summary:
 * Includes engine initialization methods implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 * Jernej Skrabec June 19 2008
 */

#include "game.h"

namespace PacGame
{
      namespace GameClasses
      {
          // other
          bool PGame::initGame()
          {
              Messages::mainTitleMessage();

              if (!glfwInit())  // is GLFW initialization successful?
              {
                  Messages::errorMessage("OpenGL/glfw initialization failed."); // in case, it is not
                  terminateGLFW(); // terminate glfw and return false
                  return false;
              }

              Messages::initMessage("GLFW", true); // prints out that initialization was success

              // 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
              if (!glfwOpenWindow(windowWidth, windowHeight, 8, 8, 8, 8, 24, 0, GLFW_WINDOW)) // attemps to open window
              {
                  Messages::errorMessage("OpenGL window creation failed.");  // failed
                  terminateGLFW();
                  return false;
              }

              Messages::initMessage("OpenGL window", true);  // prints out success

              glfwSetWindowTitle(this->windowTitle.c_str()); // temporary

          // set the projection matrix to a normal frustum with a max depth of 50
    /*          glMatrixMode(GL_PROJECTION);
              glLoadIdentity();
              float aspectRatio = ((float)windowHeight) / windowWidth;
              glFrustum(.5, -.5, -.5 * aspectRatio, .5 * aspectRatio, 1, 50);
              glMatrixMode(GL_MODELVIEW);*/

              glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
              glLoadIdentity();                                                         // Reset The Projection Matrix
              // Calculate The Aspect Ratio Of The Window
              gluPerspective(45.0f,(float)windowWidth/(float)windowHeight,0.1f,100.0f);
              glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
              glLoadIdentity();

              // initiates renderer
           /*   if(!this->getRendererHandle()->init())
                  return false;*/

//                      glfwSetKeyCallback(&PacGame::GameClasses::PGame::processKey); // sets keyboard input callback
              Messages::initMessage("Game", true);
              return true;
          }
      }
}
