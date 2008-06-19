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
//using namespace PacGame::GameClasses;
using namespace std;

namespace PacGame
{

  namespace RenderMaschine
  {

        /**********************************************************
        * PRenderer
        *
        * Class for drawing stuff
        * --------------------------------------------------------
        * Aljosa 2007
        * ********************************************************/
        class PRenderer
        {
        // TODO
        private:
        public:
                // constructor
                PRenderer();
//                PMessages msg;

                // render func
                void drawBackground();
                void drawSkyDome();
                void drawCube(float x, float y, float size);
                void drawFloor(float x, float y, float size);
        };

        /**********************************************************
         * PTexture
         *
         * Class for drawing stuff
         * --------------------------------------------------------
         * Aljosa 2007
         * ********************************************************/
        class PTexture
        {
        private:
                string filename;

                unsigned type; //  = GL_RGBA;
                PTextureImage texture;

        public:
                // constructor
            PTexture() {}
            PTexture(string _filename);  // does it work? 16.3.08
            PTexture(string _filename, string type, bool filter);
            ~PTexture();

            // variables
//            PMessages msg;

            // protoypes
            bool loadTGA();
            void generateTextureMipmap();
            void generateTextureLinear();
            bool makeTgaTexture(bool mipmap);

            // getters
            unsigned getTexID();

            // TODO:
            // separate TGA loading and texture generating... done
            // create mipmap tex generator and linear... done
            // create function, that loads and generates texture... done
            // move texture image variable to class and free texture in destructor... done
            // move loadTga to io.h and create Pio object in this object
    };
  }
}

#endif
