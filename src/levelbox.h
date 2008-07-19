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


using namespace PacGame::RenderMaschine;

namespace PacGame
{
      namespace GameClasses
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
              PTexture texture;  // represents texture of object
              unsigned short id; // number, that represents object in file

          public:
              PLevelObject() : i(0), j(0), id(0) {}// constructors
           //   PLevelObject(unsigned short id) : id(id) {}                
              PLevelObject(unsigned i, unsigned j) : i(i), j(j) {}
           //   PLevelObject(unsigned i, unsigned j, unsigned short id) : i(i), j(j), id(id) {}
             

              // setters
              void setIndex(int i, int j);
      /*        void setI(unsigned i);
              void setJ(unsigned j);*/

              // getters
              int getI() const;
              int getJ() const;
              //void getIndex(unsigned &i, unsigned &j);
              unsigned short getId() const;

              // virtual functions to override
              virtual void draw()=0;        // code that draws object
              virtual bool initialize()=0;  // code that initiates objects properties
              virtual void print()=0;       // object's console dump
              virtual short isPlayerMovePossible() = 0;
              
              
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
              PFloor() {}
              void draw();
              bool initialize();
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
              void draw();
              bool initialize();
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
              void draw();
              bool initialize();
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
              
          public:
              PTeleport() {}
              PTeleport(int id) : teleport_id(id) {}
              
              // setters
              void setId(int id);
              
              // getters
              int getId();
              
              void draw();
              bool initialize();
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
              void draw();
              bool initialize();
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
              void draw();
              bool initialize();
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
              void draw();
              bool initialize();
              void print();
              short isPlayerMovePossible()  { return 0; }
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
              void draw();
              bool initialize();
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
          public:
              void draw();
              bool initialize();
              void print();
              short isPlayerMovePossible() ;
          };

           /**********************************************************
           * POnewayCube
           *
           * Represents cube that can be moved in only one way
           * --------------------------------------------------------
           * Aljosa 2008
           * ********************************************************/ 
          class POnewayCube : public PLevelObject
          {
          private:
              Aliases::PDirection dir; // tells in wich way os cube orientated
              
          public:
              POnewayCube(Aliases::PDirection dir) : dir(dir) {}
           //   POnewayCube() {}
              void draw();
              bool initialize();
              void print();
              short isPlayerMovePossible()  { return 0; }
          };

           /**********************************************************
           * PBomb
           *
           * Represents bomb that can destroy unsolid wall
           * --------------------------------------------------------
           * Aljosa 2008
           * ********************************************************/ 
          class PBomb : public PLevelObject
          {
          private:
          public:
              void draw();
              bool initialize();
              void print();
              short isPlayerMovePossible()  { return 0; }
          };
          
          /**********************************************************
           * PNoData
           *
           * Represents blind child, means that element doens't have data
           * --------------------------------------------------------
           * Aljosa 2008
           * ********************************************************/ 
  /*        class PNoData : public PLevelObject
          {
          private:
          public:
              void draw() {}
              bool initialize() { return true; }
              void print();
          };*/
          
          /**********************************************************
           * PData
           *
           * Represents object, that hold only data
           * one way of use: binds teleport id
           * --------------------------------------------------------
           * Aljosa 2008
           * ********************************************************/ 
        //  template<class T>
          class PData : public PLevelObject
          {
          private:
              int data;
          public:
              PData(int data) : data(data) {}
              
              // getter
              int getData()  { return data; }
              void draw() {}
              bool initialize() {return true;}
              short isPlayerMovePossible() ;
              void print()
              {
                  cout<<"|DAT"<<this->data;
              }
          };
      }
}

#endif

