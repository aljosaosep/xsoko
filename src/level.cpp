/*
 * Codename: xSoko
 * File: level.h
 *
 * Summary:
 * Includes level class implementation, abstratct grid element imp., and
 * several others level struct classes implementation
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Aljosa 2008
*/
#include <iostream>
#include "level.h"
#include "messages.h"

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
      namespace GameClasses
      {
          /*****************************************
           PLevelBox methods
           *****************************************/			  
          void PLevelObject::setIndex(unsigned i, unsigned j) // index setter
          {
                  this->i = i;
                  this->j = j;
          }

          void PLevelObject::setI(unsigned i)  // i index setter
          {
                  this->i = i;
          }

          void PLevelObject::setJ(unsigned j)  // j index setter
          {
                  this->j = j;
          }

          unsigned PLevelObject::getI() const  // i index getter
          {
                  return this->i;
          }

          unsigned PLevelObject::getJ() const  // j index getter
          {
                  return this->j;
          }
          
          unsigned short PLevelObject::getId() const
          {
              return id;
          }

          void PLevelObject::getIndex(unsigned &i, unsigned &j)  // both index getter
          {
                  i = this->i;
                  j = this->j;
          }
          
           /*****************************************
           PLevel methods
           *****************************************/
           // level functions implementation goes here! ;)
    }
}
