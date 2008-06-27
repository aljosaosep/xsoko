/*
  codename: Pac-Game
  Aljosa Osep 2007
 *
*/
#include "renderer.h"

namespace PacGame
{
          namespace RenderMaschine
          {
			  // constructor
			  PRenderer::PRenderer()
			  {
				  /*Messages::infoMessage("Invoking PacEngine renderer... ");*/
			  }

			  void PRenderer::drawCube(float x, float y, float size)
			  {
				  glPushMatrix();
				    glTranslatef(x, y, 0.0);
				  	glBegin(GL_QUADS);
				//	glColor3f(1.0, 1.0, 0.0);
						// Front Face
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Left Of The Texture and Quad
						glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  size);	// Top Left Of The Texture and Quad
						// Back Face
						glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Left Of The Texture and Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, -size);	// Bottom Left Of The Texture and Quad
						// Top Face
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Left Of The Texture and Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-size,  size,  size);	// Bottom Left Of The Texture and Quad
						glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size,  size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Right Of The Texture and Quad
						// Bottom Face
						glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f( size, -size, -size);	// Top Left Of The Texture and Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Left Of The Texture and Quad
						glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Right Of The Texture and Quad
						// Right face
						glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size,  size);	// Top Left Of The Texture and Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Left Of The Texture and Quad
						// Left Face
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);	// Bottom Left Of The Texture and Quad
						glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size,  size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Left Of The Texture and Quad
					glEnd();
				  glPopMatrix();
			  }

			  void PRenderer::drawFloor(float x, float y, float size)
			  {
				  	glPushMatrix();
				    glTranslatef(x, y, 0.0);
				  	glBegin(GL_QUADS);
						// Front Face
				/*		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Left Of The Texture and Quad
						glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  size);*/	// Top Left Of The Texture and Quad
						// Back Face
					glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Left Of The Texture and Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, -size);	// Bottom Left Of The Texture and Quad
						// Top Face
				/*		glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Left Of The Texture and Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-size,  size,  size);	// Bottom Left Of The Texture and Quad
						glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size,  size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Right Of The Texture and Quad
						// Bottom Face
						glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f( size, -size, -size);	// Top Left Of The Texture and Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Left Of The Texture and Quad
						glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Right Of The Texture and Quad
						// Right face
						glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size,  size);	// Top Left Of The Texture and Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Left Of The Texture and Quad
						// Left Face
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);	// Bottom Left Of The Texture and Quad
						glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Right Of The Texture and Quad
						glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size,  size);	// Top Right Of The Texture and Quad
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);*/	// Top Left Of The Texture and Quad
					glEnd();
				  glPopMatrix();

			  }

          }
}
