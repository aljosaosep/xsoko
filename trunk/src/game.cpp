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

using namespace PacGame;

namespace PacGame
{
           /**********************************************************
           * Outside-of-class-functions
           *
           * For input, since GLFW callback functions takes 
           * function pointer as argument
           * --------------------------------------------------------
           * Jernej Skrabec 2008
           * Aljosa Osep 2008
           * ********************************************************/
    
           /*******************************************
           * processKey()
           * function implementation; function takes action 
           * based on key that is pressed
           *******************************************/
          void GLFWCALL processKey( int key, int action )
          {
              /*
               * TODO:
               * * determine which key is pressed(up, down, left, right)
               * * call suficient function, that takes proper action
               * * exit key should be also processed
               */
              
             /* if(key == GLFW_KEY_SPACE)
                zoom();*/
          }
                          
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

			  // other
			  void PGame::mainLoop()
			  {
				  Messages::infoMessage("Entering main loop...");
				    // the time of the previous frame
//				  double old_time = glfwGetTime();   // ne brisat! se bo nucal!
				  // this just loops as long as the program runs
                                  
				  while(1)
				  {
	
					  // calculate time elapsed, and the amount by which stuff rotates
				//	  double current_time = glfwGetTime(),
				//		  delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
				//	  old_time = current_time;

					 // clear the buffer
					 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					 // draw the figure
					 renderGame();
					 // swap back and front buffers
					 glfwSwapBuffers();
	
				  }
			  }
                          
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
