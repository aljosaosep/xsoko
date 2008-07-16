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

#include <string>
#include <vector>
#include "object.h"
#include "CommonStructures.h"
#include "player.h"
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
#define OW_CUBE_R 4 // (POnewayCube)
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
               * Represents a whole level, including its data
               * --------------------------------------------------------
               * Aljosa 2007 - 2008
               * ********************************************************/
              class PLevel : public PObject
              {
              private:
                  string filename;              // level filename
                  PObject* data[30][30];        // actual level data
                  vector<PTeleport*> teleports; // vector of teleport pointers
                  unsigned width, height;       // level dimensions
                 
              public:
                  PLevel(string filename) : filename(filename),  width(0), height(0) {} // default constructor
                  virtual ~PLevel() {};
                  
                  // print
                  void printLevelByType() const; // dumps level data insto console; prints type of level(wall, void, teleport, ...)
                  void printLevelByMeta() const; // same, but it prints meta data(what is on level block)
                  
                  // level data manipulation
                  bool loadLevelFromFile(); // loads level from txt file into structure, stores level widthm height into class properties
                  bool saveStateToFile(char *filename);   // exports level state to file
                  
                  // level toolkit functions
                  int returnNumberFromFile(ifstream &file);
                  bool checkPosition(ifstream &file); // checks if position is valid and moves file pointer
                  PTeleport *returnTeleport(int id);

                  // functions to override
                  // todo: implement
                  void draw();  // draws whole level
                  bool initialize(); // initiates level
                  void print(); // dumps level data into console
              };
      }
}

#endif
