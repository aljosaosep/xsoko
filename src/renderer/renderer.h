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

#include <GL/glfw.h>
#include <stdio.h>
#include <string>
#include "../CommonStructures.h"
#include "../messages.h"

using namespace PacGame::Structures;

namespace PacGame
{

  namespace RenderMaschine
  { 
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

        // material properties
      //  float matAmbient[4];
      //  float matDiffuse[4];

        // camera
        float cameraX;
        float cameraY; 
        float cameraZ;

    public:
        // constructor
        PRenderer();

        // system functions
        bool init();

        // getters
        float getCameraX() const;
        float getCameraY() const;
        float getCameraZ() const;
        float* getLightPosition();

        // setters
        void setCameraX(float value);
        void setCameraY(float value);            
        void setCameraZ(float value);

        // functions that are drawing stuff
        void drawBackground();
        void drawSkyDome();
        void drawCube(float x, float y, float size, float angle);
        void drawFloor(float x, float y, float size);
    };
  }
}

#endif
