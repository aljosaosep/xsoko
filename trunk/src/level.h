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
#include "core.h"

using namespace PacGame::GameClasses;
using namespace PacGame::Functions;
using namespace PacGame::Aliases;
using namespace PacGame::RenderMaschine;


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
                  PLevelObject* data[30][30];        // actual level data
                  int second_matrix[30][30];        // presentation of second matrix with id
                  vector<PTeleport*> teleports; // vector of teleport pointers
                  unsigned width, height;       // level dimensions
                  PPlayer *player;              // player instance 
                  vector<PCubeHolder*> holds;           // vector contains all cube holders in level; it helps to determine when level is finished
                //  PRenderer *renderer;
                  PCore *gameCore;             // game core object
                  PResourceManager *resourceHandle; // shortcut to resources
                  bool endgameFlag;
                 
              public:
                  PLevel(string filename) : filename(filename),  width(0), height(0), player(NULL),  gameCore(new PCore), resourceHandle(this->gameCore->getResources()), endgameFlag(false) {} // default constructor
                  virtual ~PLevel();
                  
                  // print
                  void printLevelByType() const; // dumps level data insto console; prints type of level(wall, void, teleport, ...)
                  void printLevelByMeta() const; // same, but it prints meta data(what is on level block)
                  
                  // gameplay related
                  bool moveObject(PDirection dir, PLevelObject *obj);
                  inline bool checkAndApply(int i2, int j2, PLevelObject *obj, PDirection dir);
                  inline void reattachNode(int i, int j, int i2, int j2, PLevelObject *obj);
                  inline bool isLevelDone(); // checks if all cubes are in places
                  
                  // level data manipulation
                  bool loadLevelFromFile(); // loads level from txt file into structure, stores level widthm height into class properties
                  bool saveStateToFile(string filename);   // exports level state to file
                  void releaseLevel(); // released level from memory
                  
                  // level toolkit functions
                  inline int returnNumberFromFile(ifstream &file); // returns number from file and moves file pointer
                  inline bool checkPosition(ifstream &file); // checks if position is valid and moves file pointer
                  inline PTeleport* returnTeleport(int id); // returns teleports addres, that contains given id
                  PPlayer* getPlayerHandle();
               //   PRenderer* getRendererHandle();
                  
                  // setters
               //   void setRenderer(PRenderer *renderer);
                  
                  // getters
                  bool getEndgameFlag();

                  // functions to override
                  void draw();  // draws whole level
                  bool initialize(); // initiates level
                  void print(); // dumps level data into console
                  short isPlayerMovePossible();  // blind method
              };
      }
}

#endif
