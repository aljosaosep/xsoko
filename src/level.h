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
#include <deque>
#include "object.h"
#include "CommonStructures.h"
#include "player.h"
#include "core.h"
#include "gui/fonts.h"

using namespace PacGame::GameClasses::GameObjects;
using namespace PacGame::Functions;
using namespace PacGame::Aliases;
using namespace PacGame::RenderMaschine;


// MATRIKA 1
#define FLOOR 0 
#define S_WALL 1 //  (PSolidWall)
#define BRIDGE 2 // (PBridge)
#define VOID 3 // (PVoid) 
#define CUBE_PLACE 4
#define OW_FLOOR_L 5 // (POneWayFloor)
#define OW_FLOOR_R 6 // (POneWayFloor)
#define OW_FLOOR_U 7 // (POneWayFloor)
#define OW_FLOOR_D 8 // (POneWayFloor)
#define TELEPORT 9 // (PTeleport)


// MATRIKA 2
#define NO_CHILD 0
#define PLAYER 1 // (PPlayer)
#define CUBE 2 // (PCube) 
#define OW_CUBE_L 6 // (POnewayCube)
#define OW_CUBE_R 10 // (POnewayCube)
#define OW_CUBE_U 14 // (POnewayCube)
#define OW_CUBE_D 18 // (POnewayCube)
#define BOMB 4 // (PBomb)
#define U_WALL 8 // (PUnsolidWall)
#define D_BOMB 12 // (PDetonatedBomb)

// id's of resourcev for objects
#define FLOOR_RES 0
#define S_WALL_RES 1 
#define BRIDGE_RES 2 
#define CUBE_PLACE_RES 3
#define OW_FLOOR_RES 4
#define TELEPORT_RES 5
#define PLAYER_RES 6
#define CUBE_RES 7
#define OW_CUBE_RES 8
#define BOMB_RES 9
#define U_WALL_RES 10

// skybox
#define SKY_RES_TOP 11
#define SKY_RES_BOTTOM 12
#define SKY_RES_LEFT 13
#define SKY_RES_RIGHT 14
#define SKY_RES_FRONT 15
#define SKY_RES_BACK 16

// button flag values
#define KB_LEFT 1
#define KB_RIGHT 2
#define KB_UP 4
#define KB_DOWN 8


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
              class PLevel //: public PObject
              {
              private:
                  string filename;                   // level filename
                  PObject* data[30][30];        // actual level data
                  int second_matrix[30][30];         // presentation of second matrix with id
                  vector<PTeleport*> teleports;      // vector of teleport pointers
                  unsigned width, height;            // level dimensions
                  PPlayer *player;                   // player instance 
                  vector<PCubeHolder*> holds;        // vector contains all cube holders in level; it helps to determine when level is finished
                  PCore *gameCore;                   // game core object
                  PResourceManager *resourceHandle;  // shortcut to resources
                  bool endgameFlag;
                  //bool timestopped;
                  Font *fnt;
                  double starttime;
                  double time;
                  int moves;
                  int button_flags;
                  
           //       PDirection lastDirection;  // direction player is facing according to last move
                  
                  vector<PDroppedBomb*> bombs;   // list of currently dropped bombs
                 
              public:
                  PLevel(string filename);
                  virtual ~PLevel();
                  
                  // print
                  void printLevelByType() const; // dumps level data insto console; prints type of level(wall, void, teleport, ...)
                  void printLevelByMeta() const; // same, but it prints meta data(what is on level block)
                  
                  // gameplay related
                  bool moveObject(PDirection dir, PObject *obj);
                  void activateFloor(int i, int j);
                  bool checkMoveTo(int toI, int toJ, PObject *obj, PDirection dir);
                  inline void reattachNode(int i, int j, int i2, int j2, PObject *obj);
                  inline bool isLevelDone(); // checks if all cubes are in places
                  void setButtonFlag(int flag);
                  void resetButtonFlag(int flag);
                  
                  // level data manipulation
                  bool reloadLevel();
                  bool loadLevelFromFile(string Filename); // loads level from txt file into structure, stores level widthm height into class properties
                  bool saveStateToFile(string filename);   // exports level state to file
                  void releaseLevel(); // released level from memory
                  bool reset();
                  
                  // level toolkit functions
                  inline int returnNumberFromFile(ifstream &file); // returns number from file and moves file pointer
                  inline bool checkPosition(ifstream &file); // checks if position is valid and moves file pointer
                  inline PTeleport* returnTeleport(int id); // returns teleports addres, that contains given id
                  PPlayer* getPlayerHandle();
                  PCore* getGameCoreHandle();
                  
                  // getters
                  bool getEndgameFlag();
                  //unsigned getWidth();
                  //unsigned getHeight();
                  
                  // bomb related
                  bool addDroppedBomb(int i, int j);
                  void checkAndApplyBombBlast(int i, int j);
                  void processBombs(double current_time);

                  void adjustCameraAtTeleport(int it, int jt, PObject *obj, PDirection dir);

                  // functions to override
                  void draw();  // draws whole level
                  void animate(double time); // animates moving objects
                  bool initialize(); // initiates level
                  void print(); // dumps level data into console
              };
      }
}

#endif
