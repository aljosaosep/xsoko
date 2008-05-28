/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include "game.h"



namespace PacGame
{
          namespace GameClasses
          {
			  // other
			  bool PGame::initGame()
			  {
				  msg.mainTitleMessage();

				  if (!glfwInit())  // is GLFW initialization successful?
				  {
//					msg.errorMessage("OpenGL/glfw initialization failed."); // in case, it is not
					terminateGLFW(); // terminate glfw and return false
					return false;
				  }

				  msg.initMessage("GLFW", true); // prints out that initialization was success

					// 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
				  if (!glfwOpenWindow(windowWidth, windowHeight, 5, 6, 5, 0, 0, 0, GLFW_WINDOW)) // attemps to open window
				  {
//					msg.errorMessage("OpenGL window creation failed.");  // failed
					terminateGLFW();
					return false;
				  }

				  msg.initMessage("OpenGL window", true);  // prints out success

				  glfwSetWindowTitle(altWindowTitle); // temporary
 
			      // set the projection matrix to a normal frustum with a max depth of 50
				  glMatrixMode(GL_PROJECTION);
				  glLoadIdentity();
				  float aspectRatio = ((float)windowHeight) / windowWidth;
				  glFrustum(.5, -.5, -.5 * aspectRatio, .5 * aspectRatio, 1, 50);
				  glMatrixMode(GL_MODELVIEW);

				  // OpenGL specific
				  glEnable(GL_TEXTURE_2D);
				 // PTextureImage texture;
				  RenderMaschine::PTexture textura("data/test.tga");
				  if(!textura.makeTgaTexture(true))
                                      return false;


				  msg.initMessage("Game", true);
				  return true;
			  }

          }
}
