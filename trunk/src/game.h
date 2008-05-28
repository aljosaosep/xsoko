/*
  codename: Pac-Game
  Aljosa Osep 2007
*/

#ifndef __GAME_H
#define __GAME_H

//#include "../include/GL/glfw.h"
#include <GL/glfw.h>
#include <stdio.h>
#include "renderer.h"
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
				  const char *altWindowTitle; 
                                  
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
}

#endif