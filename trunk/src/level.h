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

#include "stdint.h"
#include "object.h"
#include "renderer/renderer.h"

using namespace PacGame::GameClasses;
using namespace PacGame::RenderMaschine;

namespace PacGame
{

      namespace GameClasses
      {
               /**********************************************************
               * PLevel
               *
               * Represents a single level struct
               * All object, that are on level, should be derived from this
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/
              class PLevelObject : public PObject  // derived from PObject
              {
              protected:
                  unsigned i, j;     // represents indexes of element on level matrix
                  PTexture texture;  // represents texture of object
                  unsigned short id; // number, that represents object in file
                  
              public:
                //  PLevelObject() : i(0), j(0), id(0) {}// constructors
                  PLevelObject(unsigned short id) : id(id) {}                
                //  PLevelObject(unsigned i, unsigned j) : i(i), j(j) {}
                  PLevelObject(unsigned i, unsigned j, unsigned short id) : i(i), j(j), id(id) {}
                  
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
                  virtual void draw()=0;   // code that draws object
                  virtual bool initialize()=0;  // code that initiates objects properties
                  virtual void print()=0;  // object's console dump
              };
              
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
                  PObject *data;    // level data
                  unsigned width, height;

              public:
                  PLevel() : data(NULL), width(0), height(0) {} // default constructor
                  // print
                  // todo: implement
                  void printLevelByType(); // dumps level data insto console; prints type of level(wall, void, teleport, ...)
                  void printLevelByMeta(); // same, but it prints meta data(what is on level block)
                  
                  // level data manipulation
                  // todo: implement
                  bool loadLevelFromFile(char *filename); // loads level from txt file into structure, stores level widthm height into class properties
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
