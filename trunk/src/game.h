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
              PGameSession *session;  // pointer to current game class
              //PRenderer *renderer;
         //     PInputSystem input;

          public:
              // variables
              //PRenderer renderer;

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
              PRenderer *getRendererHandle();

              // setters
              void setWindow(int _width, int _height);
              void setWindowTitle(string _title);
            //  void setRenderer();
              
              
                  
              void loadSession(PGameSession *session);

              /*******************************************
               * processKey()
               * function prototype; function takes action 
               * based on key that is pressed
               * ----------------------------------
               * Jernej Skrabec
               * modified by Aljosa
               *******************************************/
              static void GLFWCALL processKey(int key, int action); 
          };       
      }       
}

#endif
