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
 * File: renderer.h
 *
 * Summary:
 * Includes level renderer classes definition
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa 2008
*/

#ifndef __RENDERER_H
#define __RENDERER_H

#include <stdio.h>
#include <string>
#include "../CommonStructures.h"
#include "../messages.h"

using namespace PacGame::Structures;

namespace PacGame
{

  namespace RenderMaschine
  {
      // TODO: indent code properly
    /*  #ifndef __VERTICES_DATA
      #define __VERTICES_DATA
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
     #endif*/

    /**********************************************************
    * PRenderer
    *
    * Class for drawing stuff
    * --------------------------------------------------------
    * Aljosa 2007-2008
    * ********************************************************/
    class PRenderer
    {
    private:
        // light properties
        float lightAmbient[4];
        float lightDiffuse[4];
        float lightPosition[4];

      //  GLfloat box[24][4];
      //  GLfloat texCoords[24][2];

        // material properties
     //   float matAmbient[4];
      //  float matDiffuse[4];

    public:
        // constructor
        PRenderer();

        // system functions
        bool init();
        void deinit();

        // getters
        float* getLightPosition();

        // functions that are drawing stuff
        void drawBackground();
        void drawSkyDome();
        void drawCube(float x, float y, float size);
        void drawFloor(float x, float y, float size);
    };
  }
}

#endif
