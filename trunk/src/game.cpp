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
#include <AL/alut.h>6

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
          
          // input
           /*******************************************
           * processKey()
           * function implementation; function takes action 
           * based on key that is pressed
           * ------------------------------------
           * Jernej Skrabec 08
           * modified Aljosa 08
           *******************************************/   
         /* void GLFWCALL PGame::processKey(int key, int action)
          {   

          }*/

          // methods
          void PGame::loadSession(PGameSession *session)
          {
              this->session = session;
          }
          
        /*  void PGame::setRenderer()
          {
              this->session->getRendererHandle()
          }*/
          
        /*  PRenderer* PGame::getRendererHandle()
          {
              return this->session->getRendererHandle();
          }*/
          
          bool PGame::run()
          {
              return this->session->run();
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
