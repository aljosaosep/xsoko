/*
  codename: Pac-Game
  Aljosa Osep 2007
*/

#ifndef __FILEMANAGER_H
#define __FILEMANAGER_H

#include <iostream>
#include <fstream>
#include "../include/GL/glfw.h"

#include "level.h"

using namespace std;

namespace PacGame
{

          namespace InputOutputClasses
          {
             /**********************************************************
              * PFileManager
			  *
              * For reading data from file
			  * --------------------------------------------------------
              * Aljosa 2007
              * ********************************************************/
			  class PFileManager
			  {
			  public:
				  PFileManager();
				  ~PFileManager();
				 // bool openFile(char *filename);
				  PLevel getLevel(unsigned short index);
				 // void writeLevel

			  private:
				  ifstream levelData;

			  };
          }
}

#endif
