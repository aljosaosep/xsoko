/*
  codename: Pac-Game
  Aljosa Osep 2007-2008
  ------------------
  ENTITIES.H

  Defines all entities in game.

*/

#ifndef __ENTITIES_H
#define __ENTITIES_H

#include <iostream>

#include "stdint.h"
#include "object.h"

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
          namespace GameClasses
          {
			  /**********************************************************
               * PEntity
			   *
               * Represents a every "living" entity in game
			   * Class is template
			   * --------------------------------------------------------
               * Aljosa 2007
               * ********************************************************/
			  class PEntity : public PObject
			  {
			  private:
				  // model
				  // almost empty for the moment, but it wont be long
			

			  public:
				  virtual void print()=0; // overloaded
				  virtual void onDeath()=0;  // method is called, when entity is destroyed e.g. killed

			  };

			   /**********************************************************
               * PPlayer
			   *
               * Represents player entity
			   * --------------------------------------------------------
               * Aljosa 2007
               * ********************************************************/
			  class PPlayer : public PEntity
			  {
			  private:
				  int score;   // not sure that will stay...

				  uint8_t bombs;
				//  uint8_t keys; // not needed anymore

			  public:
				  // constructors
				  PPlayer();
				//  PPlayer(uint8_t _bombs, uint8_t _keys); // fix; remove keys from here

				  // setters
			//	  void setScore(uint8_t _score);
				  void setBombs(uint8_t _bombs);
			//	  void setKeys(uint8_t _keys);

				  // getters

				  int getScore();
				  unsigned short getBombs();
			//	  unsigned short getKeys();

				  // increase +1
				  void incScore();
				  void incBombs();
			//	  void incKeys();

				  // to override
				  void draw();
				  bool initialize();
				  void print();
				  void onDeath();
			  };
          }
}

#endif
