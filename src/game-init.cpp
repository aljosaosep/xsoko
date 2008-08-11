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
                      if (!glfwOpenWindow(windowWidth, windowHeight, 5, 6, 5, 0, 0, 0, GLFW_WINDOW)) // attemps to open window
                      {
                            Messages::errorMessage("OpenGL window creation failed.");  // failed
                            terminateGLFW();
                            return false;
                      }

                      Messages::initMessage("OpenGL window", true);  // prints out success

                      glfwSetWindowTitle(this->windowTitle.c_str()); // temporary

                  // set the projection matrix to a normal frustum with a max depth of 50
                      glMatrixMode(GL_PROJECTION);
                      glLoadIdentity();
                      float aspectRatio = ((float)windowHeight) / windowWidth;
                      glFrustum(.5, -.5, -.5 * aspectRatio, .5 * aspectRatio, 1, 50);
                      glMatrixMode(GL_MODELVIEW);

                      // OpenGL specific
                      glEnable(GL_TEXTURE_2D);
                    //  RenderMaschine::PTexture textura("data/test.tga");
                    //  if(!textura.makeTgaTexture(true))
                    //      return false;
                      
                     // glBindTexture(GL_TEXTURE_2D, textura.getTexId());
                      
                      
                      
                      // light related
                     glEnable(GL_DEPTH_TEST);
                     glEnable(GL_LIGHTING);
                     glEnable(GL_LIGHT0);
                     glEnable(GL_COLOR_MATERIAL);
                      

//                      glfwSetKeyCallback(&PacGame::GameClasses::PGame::processKey); // sets keyboard input callback
                      Messages::initMessage("Game", true);
                      return true;
              }
      }
}
