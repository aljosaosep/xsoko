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
              unsigned i, j;     // represents indexes of element on level matrix
              PTexture texture;  // represents texture of object
              unsigned short id; // number, that represents object in file

          public:
            //  PLevelObject() : i(0), j(0), id(0) {}// constructors
           //   PLevelObject(unsigned short id) : id(id) {}                
            //  PLevelObject(unsigned i, unsigned j) : i(i), j(j) {}
           //   PLevelObject(unsigned i, unsigned j, unsigned short id) : i(i), j(j), id(id) {}

              // setters
              void setIndex(unsigned i, unsigned j);
              void setI(unsigned i);
              void setJ(unsigned j);

              // getters
              unsigned getI() const;
              unsigned getJ() const;
              void getIndex(unsigned &i, unsigned &j);
              unsigned short getId() const;

              // virtual functions to override
              virtual void draw()=0;        // code that draws object
              virtual bool initialize()=0;  // code that initiates objects properties
              virtual void print()=0;       // object's console dump
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
              void draw();
              bool initalize();
              void print();
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
              bool initalize();
              void print();
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
              bool initalize();
              void print();
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
          public:
              PTeleport() {}
              void draw();
              bool initialize();
              void print();
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
              bool initalize();
              void print();
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
              bool initalize();
              void print();
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
              bool initalize();
              void print();
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
              bool initalize();
              void print();
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
              bool initalize();
              void print();
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
          public:
              void draw();
              bool initalize();
              void print();
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
              bool initalize();
              void print();
          };
      }
}

#endif

