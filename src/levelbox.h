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

#include "level.h"

namespace PacGame
{

      namespace GameClasses
      {
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
                  void initalize();
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
                  void initalize();
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
                  void initalize();
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
                  void draw();
                  void initalize();
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
                  void initalize();
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
                  void initalize();
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
                  void initalize();
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
                  void initalize();
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
                  void initalize();
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
                  void initalize();
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
                  void initalize();
                  void print();
              };
      }
}

#endif

