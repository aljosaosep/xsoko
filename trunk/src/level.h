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
#include "CommonStructures.h"
//#include "renderer/renderer.h"

using namespace PacGame::GameClasses;
using namespace PacGame::Functions;

// MATRIKA 1
#define FLOOR 0 
#define OW_FLOOR 1 // (POneWayFloor)
#define S_WALL 2 //  (PSolidWall)
#define U_WALL 3 // (PUnsolidWall)
#define TELEPORT 4 // (PTeleport)
#define BRIDGE 5 // (PBridge)
#define VOID 6 // (PVoid) 
#define CUBE_PLACE 7

// MATRIKA 2
#define NO_CHILD 0
#define PLAYER 1 // (PPlayer)
#define CUBE 2 // (PCube)
#define OW_CUBE_L 3 // (POnewayCube)
#define OW_C_CUBE_R 4 // (POnewayCube)
#define OW_CUBE_U 5 // (POnewayCube)
#define OW_CUBE_D 6 // (POnewayCube)
#define BOMB 7 // (PBomb)

// ID za smer enosmerne kocke  
#define LEFT 8
#define RIGHT 9
#define UP 10 
#define DOWN 11

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
                  void printLevelByType() const; // dumps level data insto console; prints type of level(wall, void, teleport, ...)
                  void printLevelByMeta() const; // same, but it prints meta data(what is on level block)
                  
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
