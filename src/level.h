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
              // Aljosa:
              // levelBox is obsolete
              // here comes definitions of classes for level structs
              // e.g. Teleport, Wall, Floor, Cube, ...
              /**********************************************************
               * PLevelBox
               *
               * Represents a single level struct
               * --------------------------------------------------------
               * Aljosa 2007
               * ********************************************************/
		/*	  class PLevelBox : public PObject
			  {
			  private:
				 // uint8_t fieldType;   // uint8_t: 0-255, more than enough ;)
				 // uint8_t filedMeta;
				  PBoxInfo info;

				  // texture
			  public:
				  // constructors
				  PLevelBox();
				  PLevelBox(PBoxInfo inf);
				  PLevelBox(float x, float y, uint8_t type, uint8_t meta);

				  // setters
				  void setType(uint8_t type);
				  void setMeta(uint8_t meta);
				  void setInfo(PBoxInfo inf);
				  void setInfo(uint8_t type, uint8_t meta);

				  // getters
				  void getInfo(uint8_t &type, uint8_t &meta);
				  PBoxInfo getInfo();
				  int getType();
				  int getMeta();

				  // etc


				  // virtual functions to override
				  void draw();
				  bool initialize();
				  void print();
			  };*/

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
