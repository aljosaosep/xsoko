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
 */

#ifndef __GAME_H
#define __GAME_H

#include <GL/glfw.h>
#include <stdio.h>
#include "renderer/renderer.h"
#include "messages.h"

//using PacGame::RenderMaschine;

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

          public:
                  // variables
                  PMessages msg;
                  PacGame::RenderMaschine::PRenderer renderer;

                  // prototypes
                  // constructors
                  PGame();
                  PGame(int _width, int _height, string _title);

                  // destructor
                  ~PGame();

                  // other
                  bool initGame();
                  void mainLoop();
                  void renderGame();
                  void terminateGLFW();

                  // setters
                  void setWindow(int _width, int _height);
                  void setWindowTitle(string _title);

          };       
      }
      
        /**********************************************************
       * Outside-of-class-functions
       *
       * For input, since GLFW callback functions takes 
       * function pointer as argument
       * --------------------------------------------------------
       * Jernej Skrabec 2008
       * ********************************************************/
       void GLFWCALL processKey(int key, int action); // processKey function prototype; function takes action based on key that is pressed  
}

#endif
