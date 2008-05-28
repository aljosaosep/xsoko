/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include "game.h"



namespace PacGame
{
          namespace GameClasses
          {
			  float angle = 0.0;
			  void PGame::renderGame()
			  {
				  // reset view matrix
				  glLoadIdentity();


			  
				  // temp
				  glTranslatef(-1.0, -2.0, -20.0);
				  glRotatef(angle, 1.0, 1.0, 0.0);
				//  glDisable(GL_TEXTURE_2D);
				//  glEnable(GL_LIGHTING);
				  renderer.drawCube(0.0, 0.0, 1.0);
			//	  renderer.drawFloor(0.0, -1.0, 1.0);
				  angle+=0.03;
			  }
          }
}