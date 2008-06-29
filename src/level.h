/*
 * Codename: xSoko
 * File: level.h
 *
 * Summary:
 * Includes level class definition, abstratct grid element def., and
 * several others level struct classes definitions
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Aljosa 2008
*/

#ifndef __LEVEL_H
#define __LEVEL_H

#include "object.h"
//#include "renderer/renderer.h"

using namespace PacGame::GameClasses;
//using namespace PacGame::RenderMaschine;

namespace PacGame
{

      namespace GameClasses
      {
              
               /**********************************************************
               * PLevel
               *
               * Represents a whole level
               * --------------------------------------------------------
               * Aljosa 2007 - 2008
               * ********************************************************/
              class PLevel : public PObject
              {
              private:
                  char *filename;
                  PObject* data[30][30]; 
                  unsigned width, height;
                  

              public:
                  PLevel(char *filename) : filename(filename),  width(0), height(0) {} // default constructor
                  // print
                  // todo: implement
                  void printLevelByType(); // dumps level data insto console; prints type of level(wall, void, teleport, ...)
                  void printLevelByMeta(); // same, but it prints meta data(what is on level block)
                  
                  // level data manipulation
                  // todo: implement
                  bool loadLevelFromFile(); // loads level from txt file into structure, stores level widthm height into class properties
                  bool saveStateToFile(char *filename);   // exports level state to file

                  // functions to override
                  // todo: implement
                  void draw();  // draws whole level
                  bool initialize(); // initiates level
                  void print(); // dumps level data into console
              };
      }
}

#endif
