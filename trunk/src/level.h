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

using namespace PacGame::GameClasses;

namespace PacGame
{

      namespace GameClasses
      {
               /**********************************************************
               * PLevel
               *
               * Represents a whole level
               * --------------------------------------------------------
               * Aljosa 2007
               * ********************************************************/
              class PLevel : public PObject
              {
              private:
            //	  PLevelBox structureData[LEVEL_HEIGHT][LEVEL_WIDTH]; // obsolete

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

                      // virtual functions to override
                      void draw();
                      bool initialize();
                      void print();
              };
      }
}

#endif
