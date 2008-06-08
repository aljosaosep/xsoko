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
#include "renderer.h"

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
              class PLevelObject : public PObject
              {
              protected:
                  unsigned i, j;     // represents indexes of element on level matrix
                  PTexture texture;
                  
              public:
                  PLevelObject() : i(0), j(0) {}// constructors
                  PLevelObject(unsigned i, unsigned j) : i(i), j(j) {}
                  
                  // setters
                  void setIndex(unsigned i, unsigned j);
                  void setI(unsigned i);
                  void setJ(unsigned j);

                  // getters
                  unsigned getI();
                  unsigned getJ();
                  void getIndex(unsigned &i, unsigned &j);

                  // virtual functions to override
                  void draw();
                  bool initialize();
                  virtual void print();
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
            //	  PLevelBox structureData[LEVEL_HEIGHT][LEVEL_WIDTH]; // obsolete
                  PObject *data;    // level data

              public:
                      // print
                      void printLevelByType(); // todo: rename and implement
                      void printLevelByMeta();

                      // setters
                      // todo: rename, change, implement
                    /*  void setField(PLevelBox _box, unsigned short i, unsigned short j);
                      void setFieldInfo(PBoxInfo _info, unsigned short i, unsigned short j);
                      void setFieldType(uint8_t _type, unsigned short i, unsigned short j);
                      void setFieldMeta(uint8_t _meta, unsigned short i, unsigned short j);*/

                      // getters
                      // todo: rename, change, implement
                    /*  PLevelBox getField(unsigned short i, unsigned short j);
                      PBoxInfo getFieldInfo(unsigned short i, unsigned short j);
                      unsigned short getFieldType(unsigned short i, unsigned short j);
                      unsigned short getFieldMeta( unsigned short i, unsigned short j);*/

                      // functions to override
                      void draw();
                      bool initialize();
                      void print();
              };
      }
}

#endif
