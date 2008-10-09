/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep, Jernej Skrabec, Jernej Halozan 2008 <aljosa.osep@gmail.com, jernej.skrabec@gmail.com, jernej.halozan@gmail.com>
 * 
 * xSoko project is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * xSoko project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * codename: xSoko
 *
 * Author: Aljosa Osep 2007
 * Modified:
*/

#ifndef __VECTOR_H
#define __VECTOR_H

#include <iostream>

using namespace std;

namespace PacGame
{
      namespace GameClasses
      {
           /**********************************************************
           * PVector
           * TODO: more summary
           * --------------------------------------------------------
           * Aljosa 2007 - 2008
           * ********************************************************/
          class PVector3D
          {
          protected:
                  float x, y, z;  // x and y position in the space
                  
          public:
                  // constructors
                  PVector3D() : x(0), y(0), z(0) {} 
                  PVector3D(float x, float y, float z) : x(x), y(y), z(z) {} 
                  PVector3D(const PVector3D &vec) : x(vec.x), y(vec.y), z(vec.z) {}   // copy constructor

                  // setters
                  void setCoordinates(float x, float y, float z);
                  void setCoordinates(const PVector3D vec);
                  void setCoordX(float x);
                  void setCoordY(float y);
                  void setCoordZ(float z);                  

                  // getters
                  float getCoordX();
                  float getCoordY();
                  float getCoordZ();                  

                  // print
                  virtual void printCoordinates();

                  // operators
                  PVector3D operator = (PVector3D vector);
                  
		  PVector3D operator + (PVector3D vector);
                  PVector3D operator - (PVector3D vector);
                  PVector3D operator * (PVector3D vector);
                  PVector3D operator * (const float scalar);
                  PVector3D operator / (const float scalar);

          };

      }
}

#endif
