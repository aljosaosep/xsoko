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
          /********************************************
           * Constructor
           * Initiates lights and materials and camera
           ********************************************/
          PRenderer::PRenderer() //: cameraX(-10.0), cameraY(6.0), cameraZ(-25.0)
          {
              // light properties
              lightAmbient[0] = 0.3, lightAmbient[1] = 0.5, lightAmbient[2] = 0.8, lightAmbient[3] = 1.0; 
              lightDiffuse[0] = 0.25, lightDiffuse[1] = 0.25, lightDiffuse[2] = 0.25, lightDiffuse[3] = 1.0;
              lightPosition[0] = 0.0, lightPosition[1] = 0.0, lightPosition[2] = 1.0, lightPosition[3] = 1.0;   
              
              // material properties
           //   matAmbient[0] = 1.0, matAmbient[1] = 1.0, matAmbient[2] = 1.0, matAmbient[3] = 1.0;
           //   matDiffuse[0] = 1.0, matDiffuse[1] = 1.0, matDiffuse[2] = 1.0, matDiffuse[3] = 1.0;
              
              // camera
              this->cameraX = -10.0f; 
              this->cameraY = 6.0f; 
              this->cameraZ = -25.0;
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
           * Camera setters
           * 
           ********************************************/
          void PRenderer::setCameraX(float value)
          {
              this->cameraX = value;
          }
          
          void PRenderer::setCameraY(float value)
          {
              this->cameraY = value;
          }
          
          void PRenderer::setCameraZ(float value)
          {
              this->cameraZ = value;
          }
          
          /********************************************
           * Camera getters
           * 
           ********************************************/
          float PRenderer::getCameraX() const
          {
              return this->cameraX;
          }
          
          float PRenderer::getCameraY() const
          {
              return this->cameraY;
          }
          
          float PRenderer::getCameraZ() const
          {
              return this->cameraZ;
          }
          
          /********************************************
           * init()
           * Initiates OpenGL specific stuff
           ********************************************/
          bool PRenderer::init()
          {
              glEnable(GL_LIGHTING);
              
              glClearColor(0.0f, 0.0f, 0.0f, 0.0f);// Black Background
              glShadeModel(GL_SMOOTH);	// Enables Smooth Shading
              glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
              glDepthFunc(GL_LEQUAL);	// The Type Of Depth Test To Do
              glFrontFace(GL_CCW);   // counterclockwise polygons are out
              glClearDepth(1.0f); // Depth Buffer Setup
              glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations  
              
              // texture
              glEnable(GL_TEXTURE_2D);
              
              // material related
 //             glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
 //             glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
              
              // light related
              glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
              glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
              glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);                    
              glEnable(GL_LIGHT0);
              glEnable(GL_COLOR_MATERIAL);
            //  glEnable(GL_CULL_FACE); // do not calculate inside of polys
              
              // blending
              glEnable(GL_BLEND);
              glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
              
              return true;
          }

          /********************************************
           * drawCube()
           * Draws simple cube
           ********************************************/
          void PRenderer::drawCube(float x, float y, float size, float angle)
          {
                  glPushMatrix();
                    glTranslatef(x, y, 0.0);
                        glRotatef(angle, 1.0, 0.0, 0.0);
                        glRotatef(angle, 0.0, 1.0, 0.0);                                        
                        glRotatef(angle, 0.0, 0.0, 1.0);
                        glBegin(GL_QUADS);
                                // Front Face
                                glNormal3f( 0.0f, 0.0f, 1.0f);	
                                glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Left Of The Texture and Quad
                                glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Right Of The Texture and Quad
                                glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  size);	// Top Right Of The Texture and Quad
                                glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  size);	// Top Left Of The Texture and Quad
                                // Back Face
                                glNormal3f( 0.0f, 0.0f,-1.0f);
                                glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);	// Bottom Right Of The Texture and Quad
                                glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Right Of The Texture and Quad
                                glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Left Of The Texture and Quad
                                glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, -size);	// Bottom Left Of The Texture and Quad
                                // Top Face
                                glNormal3f( 0.0f, 1.0f, 0.0f);
                                glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Left Of The Texture and Quad
                                glTexCoord2f(0.0f, 0.0f); glVertex3f(-size,  size,  size);	// Bottom Left Of The Texture and Quad
                                glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size,  size);	// Bottom Right Of The Texture and Quad
                                glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Right Of The Texture and Quad
                                // Bottom Face
                                glNormal3f( 0.0f,-1.0f, 0.0f);	
                                glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);	// Top Right Of The Texture and Quad
                                glTexCoord2f(0.0f, 1.0f); glVertex3f( size, -size, -size);	// Top Left Of The Texture and Quad
                                glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Left Of The Texture and Quad
                                glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Right Of The Texture and Quad
                                // Right face
                                glNormal3f( 1.0f, 0.0f, 0.0f);	
                                glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);	// Bottom Right Of The Texture and Quad
                                glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Right Of The Texture and Quad
                                glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size,  size);	// Top Left Of The Texture and Quad
                                glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);	// Bottom Left Of The Texture and Quad
                                // Left Face
                                glNormal3f(-1.0f, 0.0f, 0.0f);	
                                glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);	// Bottom Left Of The Texture and Quad
                                glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);	// Bottom Right Of The Texture and Quad
                                glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size,  size);	// Top Right Of The Texture and Quad
                                glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Left Of The Texture and Quad
                        glEnd();
                  glPopMatrix();
          }

          /********************************************
           * drawFloor()
           * Draws 2D polygon, flat surface
           ********************************************/
          void PRenderer::drawFloor(float x, float y, float size)
          {
                 glPushMatrix();
                    glTranslatef(x, y, 0.0);
                        glBegin(GL_QUADS);
                                glNormal3f( 0.0f, 0.0f,-1.0f);
                                glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);	// Bottom Right Of The Texture and Quad
                                glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size, -size);	// Top Right Of The Texture and Quad
                                glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, -size);	// Top Left Of The Texture and Quad
                                glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, -size);	// Bottom Left Of The Texture and Quad

                        glEnd();
                  glPopMatrix();
          }
      }
}