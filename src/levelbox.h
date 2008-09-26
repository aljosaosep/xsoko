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
#define OW_CUBE_L 3 // (POnewayCube)
#define OW_CUBE_R 4 // (POnewayCube)
#define OW_CUBE_U 5 // (POnewayCube)
#define OW_CUBE_D 6 // (POnewayCube)
#define BOMB 7 // (PBomb)
#define U_WALL 8 // (PUnsolidWall)

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


using namespace PacGame::RenderMaschine;

namespace PacGame
{
      namespace GameClasses
      {
          namespace GameObjects
          {
               /**********************************************************
               * PLevelObject
               *
               * Represents a single level struct
               * All object, that are on level, should be derived from this
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/
              class PLevelObject : public PObject  
              {
              protected:
                  int i, j;     // represents indexes of element on level matrix
                  unsigned short id; // number, that represents object in file
                  PCore *core;

              public:
                  PLevelObject() : i(0), j(0), id(0) {}// constructors          
                  PLevelObject(unsigned i, unsigned j) : i(i), j(j) {}


                  // setters
                  void setIndex(int i, int j);
                  void setI(int i);
                  void setJ(int j);

                  // getters
                  int getI() const;
                  int getJ() const;
                  unsigned short getId() const;

                  // virtual functions to override
                  virtual void draw()=0;        // code that draws object
                  bool initialize() { return true; }  // override
                  virtual void print()=0;       // object's console dump            
                  virtual short isPlayerMovePossible()=0;
              };

               /**********************************************************
               * PFloor
               *
               * Represents a floor object
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PFloor : public PLevelObject
              {
              private:
              public:
                  PFloor(PCore *core) { this->id = 0; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible() ;
              };

               /**********************************************************
               * PSolidWall
               *
               * Represents a solid wall(unbreakable)
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PSolidWall : public PLevelObject
              {
              private:
              public:
                  PSolidWall(PCore *core) { this->id = 1; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible() ;
              };

               /**********************************************************
               * PUnsolidWall
               *
               * Represents a unsolid wall, that can be eliminated by bomb
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PUnsolidWall : public PLevelObject
              {
              private:
              public:
                  PUnsolidWall(PCore *core) { this->id = 8; this->core = core; }
                  void draw();
                  void print();              
                  short isPlayerMovePossible() ;
              };

               /**********************************************************
               * PTeleport
               *
               * Represents teleport object
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PTeleport : public PLevelObject
              {
              private:
                  int teleport_id;
                  PTeleport *childTeleport;

              public:
                  // constructor
                  PTeleport(int id, PCore *core) : teleport_id(id) {  this->core = core; }
                  PTeleport(int i, int j, PCore *core, unsigned int o_id) { this->i=i; this->j = j; this->core = core; this->id = o_id; }

                  // setters
                  void setId(int id);
                  void setChildTeleport(PTeleport *child);

                  // getters
                  int getId();
                  PTeleport* getChildTeleport() const;

                  void draw();
                  void print();             
                  short isPlayerMovePossible() ;
              };

               /**********************************************************
               * PBridge
               *
               * Represents bridge object
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PBridge : public PLevelObject
              {
              private:
              public:
                  PBridge(PCore *core) { this->id = 2; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible() ;
              };

               /**********************************************************
               * PVoid
               *
               * Represents empty space
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PVoid : public PLevelObject
              {
              private:
              public:
                  PVoid() { this->id = 3; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible() ;
              };

               /**********************************************************
               * PCube
               *
               * Represents moveable cube
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PCube : public PLevelObject
              {
              private:
              public:
                  PCube(int i, int j, PCore *core) { this->i=i; this->j = j; this->id=2; this->core = core; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible(); //  { return 0; }
              };

               /**********************************************************
               * PCubeHolder
               *
               * Represents space for cube
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PCubeHolder : public PLevelObject
              {
              private:
              public:
                  PCubeHolder(PCore *core)  { this->id = 4; this->core = core; }
                  void draw();
                  void print();              
                  short isPlayerMovePossible() ;
              };

               /**********************************************************
               * POnewayFloor
               *
               * Represents floor where cube can be moved one way only
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class POnewayFloor : public PLevelObject
              {
              private:
                  Aliases::PDirection dir; // tells in wich way os cube orientated
              public:
                  POnewayFloor(PCore *core, unsigned short id) { this->id = 1; this->core = core; this->id = id; }
                  void draw();
                  void print();             
                  short isPlayerMovePossible() ;

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
              class POnewayCube : public PLevelObject
              {
              private:
                  Aliases::PDirection dir; // tells in wich way os cube orientated

              public:            
                  POnewayCube(Aliases::PDirection dir, int i, int j, unsigned short id, PCore *core) : dir(dir) { this->i=i; this->j = j; this->core = core; this->id=id; }
                  void draw();
                  void print();        
                  short isPlayerMovePossible();

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
              class PBomb : public PLevelObject
              {
              private:
              public:
                  PBomb(int i, int j, PCore *core){ this->i=i; this->j = j; this->id = 7; this->core = core; }
                  void draw();
                  void print();
                  short isPlayerMovePossible();
              }; 

               /**********************************************************
               * PDetonaedBomb
               *
               * Represents bomb that can destroy unsolid wall
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/ 
              class PDetonatedBomb : public PLevelObject
              {
              private:
              public:
                  PDetonatedBomb(PCore *core){ this->id = 9; this->core = core; }
                  void draw();
                  void print();
                  short isPlayerMovePossible();
              }; 
              
          }
      }
}

#endif

