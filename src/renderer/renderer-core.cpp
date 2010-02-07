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
             /* lightAmbient[0] = 0.8f, lightAmbient[1] = 0.7f, lightAmbient[2] = 0.9f, lightAmbient[3] = 0.7f;
              lightDiffuse[0] = 0.9f, lightDiffuse[1] = 0.8f, lightDiffuse[2] = 1.0f, lightDiffuse[3] = 0.8f;
              lightSpecular[0] = 1.0f, lightSpecular[1] = 1.0f, lightSpecular[2] = 1.0f, lightSpecular[3] = 1.0f;
 */

                            lightAmbient[0] = 1.0f, lightAmbient[1] = 1.0f, lightAmbient[2] = 1.0f, lightAmbient[3] = 1.0f;
              lightDiffuse[0] =1.0f, lightDiffuse[1] =1.0f, lightDiffuse[2] = 1.0f, lightDiffuse[3] = 1.0f;
              lightSpecular[0] = 1.0f, lightSpecular[1] = 1.0f, lightSpecular[2] = 1.0f, lightSpecular[3] = 1.0f;

              lightPosition[0] = 50.0f, lightPosition[1] = 50.0f, lightPosition[2] = -30.0f, lightPosition[3] = 0.0f;


              g_materialDiffuse[0] = 1.0f, g_materialDiffuse[1] = 1.0f, g_materialDiffuse[2] = 1.0f, g_materialDiffuse[3] = 1.0f;
              g_materialAmbient[0] = 1.0f, g_materialAmbient[1] = 0.0f, g_materialAmbient[2] = 0.0f, g_materialAmbient[3] = 1.0f;
              g_materialSpecular[0] = 1.0f, g_materialSpecular[1] = 1.0f, g_materialSpecular[2] = 1.0f, g_materialSpecular[3] = 1.0f;
              
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
              glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
              glEnable(GL_LIGHT0);


              // global material
              glEnable(GL_COLOR_MATERIAL);
             // glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
              glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 200.0);

              glMaterialfv(GL_FRONT, GL_AMBIENT, g_materialAmbient);
              glMaterialfv(GL_FRONT, GL_DIFFUSE, g_materialDiffuse);
              glMaterialfv(GL_FRONT, GL_SPECULAR, g_materialSpecular);

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
          void PRenderer::drawCube(float x, float y, float size, float *color, int texID)
          {
              glColor4f(color[0], color[1], color[2], color[3]); // color of cube
              glBindTexture(GL_TEXTURE_2D, texID); // texture

             glEnable(GL_CULL_FACE);

             glCullFace(GL_BACK);
              glVertexPointer(3, GL_FLOAT, 0, box);
              glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
                  glPushMatrix();
                    glTranslatef(x, y, 0.0);
                    glScalef(size, size, size);
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
           * drawSkyCube()
           * Draws simple cube
           ********************************************/
          void PRenderer::drawSkyCube(float x, float y, float z, float size, int textures[6])
          {
             glColor4f(1.0, 1.0, 1.0, 1.0); // color of cube
            // glBindTexture(GL_TEXTURE_2D, texID); // texture
              glDisable(GL_LIGHTING);

            // glEnable(GL_CULL_FACE);

           //  glCullFace(GL_BACK);


              glVertexPointer(3, GL_FLOAT, 0, box);
              glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
                  glPushMatrix();
                    
                    glTranslatef(x, y, z);
                    glScalef(size, size, size);

			// FRONT AND BACK
                        glBindTexture(GL_TEXTURE_2D, textures[0]);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                        glBindTexture(GL_TEXTURE_2D, textures[1]);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

			// LEFT AND RIGHT
                        glBindTexture(GL_TEXTURE_2D, textures[2]);
                        glNormal3f(-1.0f, 0.0f, 0.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);

                        glBindTexture(GL_TEXTURE_2D, textures[3]);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);

			// TOP AND BOTTOM
                        glBindTexture(GL_TEXTURE_2D, textures[4]);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);

                        glBindTexture(GL_TEXTURE_2D, textures[5]);
			glNormal3f(0.0f, -1.0f, 0.0f);
                        glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);

                  glPopMatrix();

                 // glDisable(GL_CULL_FACE);
                  glEnable(GL_LIGHTING);
          }

          /********************************************
           * drawFloor()
           * Draws 2D polygon, flat surface
           ********************************************/
          void PRenderer::drawFloor(float x, float y, float size, float *color, int texID)
          {
              glColor4f(color[0], color[1], color[2], color[3]); // color of floor
              glBindTexture(GL_TEXTURE_2D, texID); // texture

            //  glEnable(GL_COLOR_MATERIAL);

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

          void PRenderer::drawLightwaveModel(float x, float y, float z, /*PacGame::LWFormat::*/LWObject *lwo) {
                VECTOR* pt;
                POLYGON* ply = lwo->plys;

             /*   glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
           //     glDisable(GL_BLEND);
           //     glDisable(GL_TEXTURE_2D);

                glEnable(GL_COLOR_MATERIAL);
         //     glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;*/


                glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);

                glMaterialfv(GL_FRONT, GL_AMBIENT, g_materialAmbient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, g_materialDiffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, g_materialSpecular);

                glPushMatrix();
                glTranslatef(x, y, z);

 

                for(int i=0; i<lwo->numpolygons; i++)
                {
                    glBegin(GL_POLYGON);
                    // določanje barve posameznega lica


                        glColor3ub((GLubyte)lwo->srfs[ply->srfID].red,
                        (GLubyte)lwo->srfs[ply->srfID].green,
                        (GLubyte)lwo->srfs[ply->srfID].blue);

                 //   glColor4f(0.0f, 0.0f ,0.0f, 1.0);


                    // material setup
                 //   glMaterialfv( GL_FRONT, GL_AMBIENT, lwo->srfs[ply->srfID].material.m_ambient );
                //    glMaterialfv( GL_FRONT, GL_DIFFUSE, lwo->srfs[ply->srfID].material.m_diffuse );
                //    glMaterialfv( GL_FRONT, GL_SPECULAR, lwo->srfs[ply->srfID].material.m_specular );
                //    glMaterialfv( GL_FRONT, GL_EMISSION, m_pMaterials[materialIndex].m_emissive );
                //    glMaterialf( GL_FRONT, GL_SHININESS, lwo->srfs[ply->srfID].material.m_shininess );


                    // izris posameznega oglišča
                    glNormal3f(ply->nx,ply->ny,ply->nz);
                    pt = &lwo->pts[ply->p[0]];

                    glNormal3f(pt->px,pt->py,pt->pz); // podatki o normali oglišča
                    glVertex3f(pt->x,pt->y,pt->z); // podatki o koordinatah točke
                    // podatki o ogljiščih p[1] in p[2]
                    glNormal3f(lwo->pts[ply->p[1]].px,lwo->pts[ply->p[1]].py ,lwo->pts[ply->p[1]].pz);
                    glVertex3f(lwo->pts[ply->p[1]].x,lwo->pts[ply->p[1]].y ,lwo->pts[ply->p[1]].z);

                    glNormal3f(lwo->pts[ply->p[2]].px,lwo->pts[ply->p[2]].py ,lwo->pts[ply->p[2]].pz);
                    glVertex3f(lwo->pts[ply->p[2]].x,lwo->pts[ply->p[2]].y ,lwo->pts[ply->p[2]].z);



                    // Ali imamo več kot tri oglišča?
                    if(ply->numverts == 4) {
                    // podatki o oglišču p[3]
                        glNormal3f(lwo->pts[ply->p[3]].px,lwo->pts[ply->p[3]].py ,lwo->pts[ply->p[3]].pz);
                        glVertex3f(lwo->pts[ply->p[3]].x,lwo->pts[ply->p[3]].y ,lwo->pts[ply->p[3]].z);
                    }
                glEnd();
                ply++; // naslednje lice
                }

                glPopMatrix();

               // glEnable(GL_BLEND);
               // glEnable(GL_TEXTURE_2D);
          }
      }
}
