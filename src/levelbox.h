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
 * File: levelbox.h
 *
 * Summary:
 * Includes levelbox objects definition
 *
 * Author: Aljosa Osep 2008
*/

#ifndef __LEVELBOX_H
#define __LEVELBOX_H

#include "renderer/renderer.h"
#include "object.h"
#include "CommonStructures.h"
#include "core.h"

#ifdef _WINDOWS
	#undef VOID
#endif

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

// id's for object direction
#define PL_OBJECT_FACE_UP 1
#define PL_OBJECT_FACE_RIGHT 2
#define PL_OBJECT_FACE_DOWN 4
#define PL_OBJECT_FACE_LEFT 8
#define PL_OBJECT_MOVE 16

// movement speeds of objects
#define OBJECT_SPEED 4.0


using namespace PacGame::RenderMaschine;

namespace PacGame
{
      namespace GameClasses
      {
          namespace GameObjects
          {

               /**********************************************************
               * PFloor
               *
               * Represents a floor object
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PFloor : public PObject
              {
              private:
              public:
                  PFloor(PCore *core) { this->id = FLOOR; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible(int direction) ;
              };

               /**********************************************************
               * PSolidWall
               *
               * Represents a solid wall(unbreakable)
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PSolidWall : public PObject
              {
              private:
              public:
                  PSolidWall(PCore *core) { this->id = S_WALL; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible(int direction) ;
              };

               /**********************************************************
               * PUnsolidWall
               *
               * Represents a unsolid wall, that can be eliminated by bomb
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PUnsolidWall : public PObject
              {
              private:
              public:
                  PUnsolidWall(int i, int j,PCore *core) { this->i = i; this->j = j; realI = (float)i; realJ = (float)j; this->id = U_WALL; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible(int direction) ;
              };

               /**********************************************************
               * PTeleport
               *
               * Represents teleport object
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PTeleport : public PObject
              {
              private:
                  int teleport_id;
                  PTeleport *childTeleport;

              public:
                  // constructor
                  PTeleport(int id, PCore *core) : teleport_id(id) {  this->core = core; childTeleport = NULL; }
                  PTeleport(int i, int j, PCore *core, unsigned int o_id) { this->i=i; this->j = j; this->core = core; this->id = o_id; childTeleport = NULL; }

                  // setters
                  void setId(int id);
                  void setChildTeleport(PTeleport *child);

                  // getters
                  int getId();
                  PTeleport* getChildTeleport() const;

                  void draw();
                  void print();             
                  short isPlayerMovePossible(int direction) ;
              };

               /**********************************************************
               * PBridge
               *
               * Represents bridge object
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PBridge : public PObject
              {
              private:
              public:
                  PBridge(PCore *core) { this->id = BRIDGE; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible(int direction) ;
              };

               /**********************************************************
               * PVoid
               *
               * Represents empty space
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PVoid : public PObject
              {
              private:
              public:
                  PVoid() { this->id = VOID; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible(int direction) ;
              };

               /**********************************************************
               * PCube
               *
               * Represents moveable cube
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PCube : public PObject
              {
              private:
              public:
                  PCube(int i, int j, PCore *core) { this->i=i; this->j = j; realI = (float)i; realJ = (float)j; this->id=CUBE; this->core = core; }
                  void draw();
                  bool animate(double time);
                  void print();             
                  short isPlayerMovePossible(int direction); 
              };

               /**********************************************************
               * PCubeHolder
               *
               * Represents space for cube
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PCubeHolder : public PObject
              {
              private:
              public:
                  PCubeHolder(PCore *core)  { this->id = 4; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible(int direction) ;
              };

               /**********************************************************
               * POnewayFloor
               *
               * Represents floor where cube can be moved one way only
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class POnewayFloor : public PObject
              {
              private:
                  Aliases::PDirection dir; // tells in wich way os cube orientated
              public:
                  POnewayFloor(PCore *core, unsigned short id) { this->id = 1; this->core = core; this->id = id; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible(int direction) ;

                  // getters
                  Aliases::PDirection getDirection();

                  // setters
                  void  setDirection(Aliases::PDirection dir);
              };

               /**********************************************************
               * POnewayCube
               *
               * Represents cube that can be moved in only one way
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              // attention : id 
              // TODO!
              class POnewayCube : public PObject
              {
              private:
                  Aliases::PDirection dir; // tells in wich way os cube orientated

              public:            
                  POnewayCube(Aliases::PDirection dir, int i, int j, unsigned short id, PCore *core) : dir(dir) { this->i=i; this->j = j; realI = (float)i; realJ = (float)j; this->core = core; this->id=id; }
                  void draw();
                  bool animate(double time);
                  void print();        
                  short isPlayerMovePossible(int direction) ;

                  // getters
                  Aliases::PDirection getDirection();
              };

               /**********************************************************
               * PBomb
               *
               * Represents bomb that we pick up
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PBomb : public PObject
              {
              private:
              public:
                  PBomb(int i, int j, PCore *core){ this->i=i; this->j = j; realI = (float)i; realJ = (float)j; this->id = BOMB; this->core = core; }
                  void draw();
                  void print();
                  short isPlayerMovePossible(int direction) ;
              }; 

               /**********************************************************
               * PDetonatedBomb
               *
               * Represents bomb that can destroy unsolid wall
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PDetonatedBomb : public PObject
              {
              private:
              public:
                  PDetonatedBomb(){ this->id = D_BOMB;  }
                  void draw();
                  void print();
                  short isPlayerMovePossible(int direction) ;
              }; 
              
          }
      }
}

#endif

