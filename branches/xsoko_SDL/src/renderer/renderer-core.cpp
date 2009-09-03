/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep, Jernej Skrabec, Jernej Halozan 2008 <aljosa.osep@gmail.com, jernej.skrabec@gmail.com, jernej.halozan@gmail.com>
 * 
 * xSoko project is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * xSoko project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Codename: xSoko
 * File: renderer.cpp
 *
 * Summary:
 * Includes renderer core implementation
 *
 * Author: Aljosa Osep 2008
*/

#include "renderer.h"

namespace PacGame
{
      namespace RenderMaschine
      {

      		  GLfloat box[] = {
				// FRONT
				-0.5f, -0.5f,  0.5f,
				 0.5f, -0.5f,  0.5f,
				-0.5f,  0.5f,  0.5f,
				 0.5f,  0.5f,  0.5f,

				// BACK
				-0.5f, -0.5f, -0.5f,
				-0.5f,  0.5f, -0.5f,
				 0.5f, -0.5f, -0.5f,
				 0.5f,  0.5f, -0.5f,

				// LEFT
				-0.5f, -0.5f,  0.5f,
				-0.5f,  0.5f,  0.5f,
				-0.5f, -0.5f, -0.5f,
				-0.5f,  0.5f, -0.5f,

				// RIGHT
				 0.5f, -0.5f, -0.5f,
				 0.5f,  0.5f, -0.5f,
				 0.5f, -0.5f,  0.5f,
				 0.5f,  0.5f,  0.5f,

				// TOP
				-0.5f,  0.5f,  0.5f,
				 0.5f,  0.5f,  0.5f,
				 -0.5f,  0.5f, -0.5f,
				 0.5f,  0.5f, -0.5f,

				// BOTTOM
				-0.5f, -0.5f,  0.5f,
				-0.5f, -0.5f, -0.5f,
				 0.5f, -0.5f,  0.5f,
				 0.5f, -0.5f, -0.5f,
			};

			GLfloat texCoords[] = {
				// FRONT
				 0.0f, 0.0f,
				 1.0f, 0.0f,
				 0.0f, 1.0f,
				 1.0f, 1.0f,

				// BACK
				 1.0f, 0.0f,
				 1.0f, 1.0f,
				 0.0f, 0.0f,
				 0.0f, 1.0f,

				// LEFT
				 1.0f, 0.0f,
				 1.0f, 1.0f,
				 0.0f, 0.0f,
				 0.0f, 1.0f,

				// RIGHT
				 1.0f, 0.0f,
				 1.0f, 1.0f,
				 0.0f, 0.0f,
				 0.0f, 1.0f,

				// TOP
				 0.0f, 0.0f,
				 1.0f, 0.0f,
				 0.0f, 1.0f,
				 1.0f, 1.0f,

				// BOTTOM
				 1.0f, 0.0f,
				 1.0f, 1.0f,
				 0.0f, 0.0f,
				 0.0f, 1.0f
                        };

          /********************************************
           * Constructor
           * Initiates lights and materials and camera
           ********************************************/
          PRenderer::PRenderer() //: cameraX(-10.0), cameraY(6.0), cameraZ(-25.0)
          {
              // light properties
              lightAmbient[0] = 0.1f, lightAmbient[1] = 0.1f, lightAmbient[2] = 0.1f, lightAmbient[3] = 1.0f; 
              lightDiffuse[0] = 1.0f, lightDiffuse[1] = 1.0f, lightDiffuse[2] = 1.0f, lightDiffuse[3] = 1.0f;
              lightPosition[0] = 1.0f, lightPosition[1] = 1.0f, lightPosition[2] = 0.0f, lightPosition[3] = 1.0f;   
              
              // material properties
         //     matAmbient[0] = 1.0, matAmbient[1] = 1.0, matAmbient[2] = 1.0, matAmbient[3] = 1.0;
         //     matDiffuse[0] = 1.0, matDiffuse[1] = 1.0, matDiffuse[2] = 1.0, matDiffuse[3] = 1.0;
              
              // camera
//              this->cameraX = -10.0f; 
//              this->cameraY = 6.0f; 
 //             this->cameraZ = -25.0;
          }
          
           /********************************************
           * light getters
           * 
           ********************************************/
          float* PRenderer::getLightPosition() 
          {
              return this->lightPosition;  
          }
          
          
          /********************************************
           * init()
           * Initiates OpenGL specific stuff
           ********************************************/
          bool PRenderer::init()
          {

             glClearColor(0.0f, 0.0f, 0.0f, 0.0f);// Black Background
              glShadeModel(GL_SMOOTH);  // Enables Smooth Shading
              glEnable(GL_DEPTH_TEST);  // Enables Depth Testing
              glDepthFunc(GL_LEQUAL);   // The Type Of Depth Test To Do
              glFrontFace(GL_CCW);   // counterclockwise polygons are out
              glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);        // Really Nice Perspective Calculations

              // texture
              glEnable(GL_TEXTURE_2D);

              // light related
              glEnable(GL_LIGHTING);
              glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
              glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
              glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
              glEnable(GL_LIGHT0);


              glEnable(GL_COLOR_MATERIAL);
             // glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
             // glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);

             // glEnable(GL_CULL_FACE); // do not calculate inside of polys
   //           glCullFace(GL_BACK);


              // blending
              glEnable(GL_BLEND);
              glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

              glEnableClientState(GL_VERTEX_ARRAY);
              glEnableClientState(GL_TEXTURE_COORD_ARRAY);

              return true;

          }
          
          void PRenderer::deinit()
          {
              glDisable(GL_LIGHTING);
              glDisable(GL_DEPTH_TEST);	// Enables Depth Testing
              glDisable(GL_TEXTURE_2D);
              glDisable(GL_COLOR_MATERIAL);
              glDisable(GL_BLEND);
          }

          /********************************************
           * drawCube()
           * Draws simple cube
           ********************************************/
          void PRenderer::drawCube(float x, float y, float size)
          {
              glEnable(GL_CULL_FACE);

             glCullFace(GL_BACK);
              glVertexPointer(3, GL_FLOAT, 0, box);
              glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
                  glPushMatrix();
                    glTranslatef(x, y, 0.0);
			// FRONT AND BACK
			glNormal3f(0.0f, 0.0f, 1.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			/*glNormal3f(0.0f, 0.0f, -1.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 4, 4); */

			// LEFT AND RIGHT
                        glNormal3f(-1.0f, 0.0f, 0.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);

			// TOP AND BOTTOM
			glNormal3f(0.0f, 1.0f, 0.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
			glNormal3f(0.0f, -1.0f, 0.0f);
                        glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
                  glPopMatrix();
                  glDisable(GL_CULL_FACE);
          }

          /********************************************
           * drawFloor()
           * Draws 2D polygon, flat surface
           ********************************************/
          void PRenderer::drawFloor(float x, float y, float size)
          {
              glEnable(GL_CULL_FACE);
              glCullFace(GL_FRONT);
                 glVertexPointer(3, GL_FLOAT, 0, box);
              glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
              glPushMatrix();
                    glTranslatef(x, y, 0.0);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
              glPopMatrix();
              glDisable(GL_CULL_FACE);
          }
      }
}
