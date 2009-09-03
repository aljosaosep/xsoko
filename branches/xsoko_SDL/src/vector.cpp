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
 * Summary:
 * todo
 *
 * Author: Aljosa Osep 2008
 * Modified:
*/

#include "vector.h"

namespace PacGame
{
      namespace GameClasses
      {
          /********************************
           * vector 3D
           *
           ********************************/

          // setters
          void PVector3D::setCoordinates(float x, float y, float z)
          {
                  this->x = x;
                  this->y = y;
                  this->z = z;                  
          }

          void PVector3D::setCoordX(float x)
          {
                  this->x = x;
          }

          void PVector3D::setCoordY(float y)
          {
                  this->y = y;
          }
          
          void PVector3D::setCoordZ(float z)
          {
              this->z = z;
          }
          
          void PVector3D::setCoordinates(const PVector3D vec)
          {
              this->x = vec.x;
              this->y = vec.y;
              this->z = vec.z;
          }
          
          // getters
          float PVector3D::getCoordX()
          {
              return this->x;
          }

          float PVector3D::getCoordY()
          {
              return this->y;
          }
          
          float PVector3D::getCoordZ()
          {
              return this->z;
          }
          
          // print
          void PVector3D::printCoordinates()
          {
              cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<endl;              
          }
          
          // operators
          PVector3D PVector3D::operator= (const PVector3D vector)
          {
                  this->x = vector.x;
                  this->y = vector.y;
                  this->z = vector.z;

                  return *this;
          }
          
          PVector3D PVector3D::operator+ (const PVector3D vector)
          {
              this->x += vector.x;
              this->y += vector.y;
              this->z += vector.z;
              
              return *this;
          }
          
          PVector3D PVector3D::operator- (const PVector3D vector)
          {
              this->x -= vector.x;
              this->y -= vector.y;
              this->z -= vector.z;
              
              return *this;
          }
  
          PVector3D PVector3D::operator* (const PVector3D vector)
          {
              this->x *= vector.x;
              this->y *= vector.y;
              this->z *= vector.z;
              
              return *this;
          }
          
          PVector3D PVector3D::operator *(const float scalar)
          {
              this->x *= scalar;
              this->y *= scalar;
              this->z *= scalar;
              
              return *this;
          }

          PVector3D PVector3D::operator /(const float scalar)
          {
              this->x /= scalar;
              this->y /= scalar;
              this->z /= scalar;
              
              return *this;
          }
          
          
      }
}
