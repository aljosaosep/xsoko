/*
  codename: Pac-Game
  Aljosa Osep 2007
*/

#ifndef __COMMON_STRUCTURES_H
#define __COMMON_STRUCTURES_H

#include <GL/glfw.h>
#include "stdint.h"




namespace PacGame
{
		  namespace Aliases
		  {

			  // TODO: change&fix for XSoko purpuses
			  enum fieldType
			  {
		/*		  empty = 0,
				  wall = 1,
				  solid = 2,
				  fast = 3,
				  slow = 4,
				  teleport = 5,
				  door = 6*/
			  };

			  enum fieldMeta
			  {
			/*	  food = 0,
				  enemyHorror = 1,
				  timeStopper = 2,
				  shotgun = 3,
				  bomb = 4,
				  key = 5,
				  playerStart = 6,
				  enemyStart = 7*/
			  };
		  }

          namespace Structures
          {
					/**********************************************************
                    * PPosition2D
					*
                    * Represents a point on the surface
					* --------------------------------------------------------
                    * Aljosa 2007
                    * ********************************************************/
                 /*   struct PPosition2D
                    {
                            float x;
                            float y;
                    }; */

					/**********************************************************
                    * PBoxInfo
					*
                    * Holds data for every element in level
					* --------------------------------------------------------
                    * Aljosa 2007
                    * ********************************************************/
                    // obsolete
					/*struct PBoxInfo
					{
							uint8_t fieldType; // type of field(wall, floor, ...)  // uint8_t: 0-255, more than enough ;)
							uint8_t fieldMeta; // type of object on field
					};*/

					/**********************************************************
                    * PTextureImage
					*
                    * Holds data for texture
					* --------------------------------------------------------
                    * Aljosa 2007
                    * ********************************************************/
					struct	PTextureImage								
					{
							GLubyte		*imageData;						// data 
							unsigned	bpp;							// Image Color Depth In Bits Per Pixel.
							unsigned	width;							// Image Width
							unsigned	height;							// Image Height
							unsigned	texID;							// Texture ID Used To Select A Texture
					};
          }

}

#endif
