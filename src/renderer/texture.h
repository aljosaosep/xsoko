/* 
 * File:   texture.h
 * Author: aljosa
 *
 * Mdified on September 5, 2008, 11:46 AM
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
            string filename;   // texture filename

            GLubyte *imageData;	// data 
            unsigned bpp;		// Image Color Depth In Bits Per Pixel
            unsigned width;		// Image Width
            unsigned height;		// Image Height
            unsigned texID;	
            unsigned type;   // texture type: GL_RGB or GL_RGBA
            
        public:
            // constructor
            PTexture() {}
            PTexture(string _filename);  
            PTexture(string _filename, string type, bool filter);
            ~PTexture();

            // protoypes
            bool loadTGA();
            void generateTextureMipmap();
            void generateTextureLinear();
            bool makeTgaTexture(bool mipmap);

            // getters
            unsigned getId();
            string getFilename() const;
            
            // setters
            void setPath(string filename);  
            void release();  
    };
  }
}

#endif	/* _TEXTURE_H */

