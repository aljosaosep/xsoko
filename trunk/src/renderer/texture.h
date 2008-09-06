/* 
 * File:   texture.h
 * Author: aljosa
 *
 * Created on September 5, 2008, 11:46 AM
 */

#ifndef _TEXTURE_H
#define	_TEXTURE_H

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
         * PTexture
         *
         * Class for texture
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

            // protoypes
            bool loadTGA();
            void generateTextureMipmap();
            void generateTextureLinear();
            bool makeTgaTexture(bool mipmap);

            // getters
            unsigned getTexID();
            
            // setters
            void setPath(string filename);  
            void release();  // WARNING: TEXTURE RELEASE ISNT IMPLEMENTET AT THE MOMENT(SEP 08)
    };
  }
}


#endif	/* _TEXTURE_H */

