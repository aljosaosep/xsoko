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


#include "game.h"

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
          }

          // destructor
          PGame::~PGame()
          {
                  terminateGLFW();
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
          void GLFWCALL PGame::processKey(int key, int action)
          {   
              if(action == GLFW_PRESS) // was key pressed? (two possible actions; press and release - we are interested only in press)
              {
                  // determine which was pressed and take proper action.
                  switch(key)
                  {
                      case GLFW_KEY_UP:  // KEYUP
                          Messages::infoMessage("Key up pressed.");
                          break;

                      case GLFW_KEY_DOWN:   // KEYDOWN
                          Messages::infoMessage("Key DOWN pressed.");
                          break;

                      case GLFW_KEY_LEFT:   // KEYLEFT
                          //this->session->getLevel()->
                          Messages::infoMessage("Key left pressed.");
                          break;        

                      case GLFW_KEY_RIGHT:    // KEYRIGHT
                          Messages::infoMessage("Key right pressed.");
                          break;

                      case GLFW_KEY_ESC:    // KEY ESCAPE
                          Messages::infoMessage("Esc key pressed, quitting...");
                          break;

                      default:
                          Messages::infoMessage("Unknown Key pressed.");
                          break;
                  }
             }
          }

          // methods
          void PGame::loadSession(PGameSession *session)
          {
              this->session = session;
          }
          
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
