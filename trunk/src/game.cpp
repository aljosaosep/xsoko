/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include "game.h"



namespace PacGame
{
          namespace GameClasses
          {
			  // construcotrs
			  PGame::PGame() 
			  {
				  windowTitle = "defaultGame - PacEngine";
				  altWindowTitle = windowTitle.c_str();
			  }

			  PGame::PGame(int _width, int _height, string _title) 
			  {
				  windowWidth = _width;
				  windowHeight = _height;
				  windowTitle = _title;
				  altWindowTitle = windowTitle.c_str();
				  // hehe !
//				  strcpy(_title, windowTitle);  // PICKU MATER U PUFUKANIH WINISH ITAK _NIC_ NE DELA, CELO STRCPY!!!!
			  }

			  // destructor
			  PGame::~PGame()
			  {
				  terminateGLFW();
			  }

			  // other
			  void PGame::mainLoop()
			  {
				  msg.infoMessage("Entering main loop...");
				    // the time of the previous frame
				  double old_time = glfwGetTime();
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
//				  strcpy(windowTitle, _title);
			  }

			  void PGame::terminateGLFW()
			  {
				  msg.infoMessage("Termination, destroying glfw...");
				  glfwTerminate();
			  }
          }
}