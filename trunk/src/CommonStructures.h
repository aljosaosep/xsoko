/*
 * Codename: xSoko
 * File: commonStructures.h
 *
 * Summary:
 * contains functions and structures, that aren't file-specific
 * e.g generic stuff
 *
 * Author: Aljosa Osep 2007-2008
 * Modified:
*/

#ifndef __COMMON_STRUCTURES_H
#define __COMMON_STRUCTURES_H

#include <GL/glfw.h>
#include <sstream>

using namespace std;

namespace PacGame
{
      namespace Aliases
      {
          enum PDirection
          {
              left, right, up, down
          };
      }

      namespace Structures
      {
          // structure used to describe bomb state, when bomb is dropped
          struct PDroppedBomb
          {
              double dropTime;  // time bomb has been dropped
              int i, j;  // index of bomb

              PDroppedBomb(int i, int j) : dropTime(glfwGetTime()), i(i), j(j) {}  // constructor
          };
      }
      
      namespace Functions
      {
          /*********************************
           * toString()
           * "borrowed" from Marjan Mernik
           **********************************/
          template <typename T>
          inline string toString(const T& t)
          {
              stringstream ss;
              ss<<t;
              return ss.str();
          }         
      }
}

#endif
