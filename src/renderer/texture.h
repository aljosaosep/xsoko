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
 * File:   texture.h
 * Author: aljosa
 *
 * Mdified on September 5, 2008, 11:46 AM
 */

#ifndef _TEXTURE_H
#define	_TEXTURE_H

#include <GL/glfw.h>
#include <cstdio>
#include <cstring> // for memcmp() func
#include <string>
#include <cstdlib>
#include "../CommonStructures.h"
#include "../messages.h"

using namespace std;
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

