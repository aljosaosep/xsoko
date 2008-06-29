/*
 * Codename: xSoko
 * File: level.h
 *
 * Summary:
 * Includes level class implementation, abstratct grid element imp., and
 * several others level struct classes implementation
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Aljosa 2008
*/
#include <iostream>
#include "messages.h"
#include "level.h"
#include "levelbox.h"

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
      namespace GameClasses
      {
           /*****************************************
           PLevel methods
           *****************************************/
          // level functions implementation goes here! ;)
          // function is work in progress, started by Aljosa june 29, 2008
          bool PLevel::initialize()
          {
              //data = new
              if(/*!this->loadLevelFromFile()*/1)
              {
                  Messages::errorMessage("Level loading from file failed.");
                  return 0;
              }
              
              data[0][0] = new PTeleport;
          }
    }
}
