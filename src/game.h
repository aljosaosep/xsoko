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

          public:
              // variables
              PacGame::RenderMaschine::PRenderer renderer;

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
