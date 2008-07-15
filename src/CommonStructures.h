/*
 * Codename: xSoko
 * File: commonStructures.h
 *
 * Summary:
 * contains functions and structures, that aren't file-specific
 * e.g generic stuff
 *
 * Author: Aljosa Osep 2007-2008
 * Modified:
*/

#ifndef __COMMON_STRUCTURES_H
#define __COMMON_STRUCTURES_H

#include <GL/glfw.h>
#include <sstream>

using namespace std;

namespace PacGame
{
      namespace Aliases
      {
          enum PDirection
          {
              left, right, up, down
          };
        
      }

      namespace Structures
      {
            /**********************************************************
             * PTextureImage
             *
             * Holds data for texture
             * --------------------------------------------------------
             * Aljosa 2007
             *********************************************************/
            struct PTextureImage								
            {
                GLubyte	*imageData;						// data 
                unsigned	bpp;							// Image Color Depth In Bits Per Pixel.
                unsigned	width;							// Image Width
                unsigned	height;							// Image Height
                unsigned	texID;							// Texture ID Used To Select A Texture
            };
      }
      
      namespace Functions
      {
          /*********************************
           * toString()
           * "borrowed" from Marjan Mernik
           **********************************/
          template <typename T>
          inline string toString(const T& t)
          {
              stringstream ss;
              ss<<t;
              return ss.str();
          }         
      }
}

#endif
