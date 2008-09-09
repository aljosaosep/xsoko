
#include "vector.h"

/*
 * codename: xSoko
 *
 * Summary:
 * todo
 *
 * Author: Aljosa Osep 2007
 * Modified:
*/
#include "vector.h"

namespace PacGame
{
      namespace GameClasses
      {
          /********************************
           * vector 2D
           *
           ********************************/
          // constructors
          PVector2D::PVector2D() 
          {
              this->setCoordinates(0.0, 0.0);
          }

          PVector2D::PVector2D(float _x, float _y)
          {
                  x = _x;
                  y = _y;
          }

          // setters
          void PVector2D::setCoordinates(float _x, float _y)
          {
                  x = _x;
                  y = _y;
          }

          void PVector2D::setCoordX(float _x)
          {
                  x = _x;
          }

          void PVector2D::setCoordY(float _y)
          {
                  y = _y;
          }

          // getters
          float PVector2D::getCoordX()
          {
                  return x;
          }

          float PVector2D::getCoordY()
          {
                  return y;
          }
          void PVector2D::getCoordinates(float &_x, float &_y)
          {
                  _x = x;
                  _y = y;
          }

          // print
          void PVector2D::printCoordinates()
          {
              cout<<"\nCoordinates:\n x:"<<x<<" y:"<<y<<endl;
          }

          // operators overloading
          // addition
/*	  PVector2D PVector2D::operator + (PVector2D _vector)
          {
                  PVector2D _tmpvec;
                  _tmpvec.x = x + _vector.x;
                  _tmpvec.y = y + _vector.y;

                  return _tmpvec;
          }

          // substraction
          PVector2D PVector2D::operator - (PVector2D _vector)
          {
                  PVector2D _tmpvec;
                  _tmpvec.x = x - _vector.x;
                  _tmpvec.y = y - _vector.y;

                  return _tmpvec;
          }

          // substraction
          PVector2D PVector2D::operator * (PVector2D _vector)
          {
                  PVector2D _tmpvec;
                  _tmpvec.x = x * _vector.x;
                  _tmpvec.y = y * _vector.y;

                  return _tmpvec;
          }

          // division
          PVector2D PVector2D::operator / (PVector2D _vector)
          {
                  PVector2D _tmpvec;
                  _tmpvec.x = x / _vector.x;
                  _tmpvec.y = y / _vector.y;

                  return _tmpvec;
          }*/

          // PVector2D &operator = (const PVector2D &_vector)
          PVector2D PVector2D::operator = (const PVector2D _vector)
          {
                  this->x = _vector.x;
                  this->y = _vector.y;

                  return *this;
          }
          
          
          
          /********************************
           * vector 3D
           *
           ********************************/
          PVector3D::PVector3D() 
          {
              this->setCoordinates(0.0, 0.0, 0.0);
          }  // default constructor
          
          PVector3D::PVector3D(float _x, float _y, float _z)
          {
              this->x = _x;
              this->y = _y;
              this->z = _z;
          }
          
          // setters
          void PVector3D::setCoordZ(float _z)
          {
              this->z = _z;
          }
          
          void PVector3D::setCoordinates(float _x, float _y, float _z)
          {
              this->x = _x;
              this->y = _y;
              this->z = _z;
          }
          
          void PVector3D::setCoordinates(const PVector3D _vec)
          {
              this->x = _vec.x;
              this->y = _vec.y;
              this->z = _vec.z;
          }
          
          // getters
          float PVector3D::getCoordZ()
          {
              return this->z;
          }
          
          // print
          void PVector3D::printCoordinates()
          {
              cout<<"\nCoordinates:\n x:"<<x<<" y:"<<y<<" z:"<<z<<endl;              
          }
          
          // operators
          PVector3D PVector3D::operator= (const PVector3D _vector)
          {
                  this->x = _vector.x;
                  this->y = _vector.y;
                  this->z = _vector.z;

                  return *this;
          }
          
          PVector3D PVector3D::operator+ (const PVector3D _vector)
          {
              this->x += _vector.x;
              this->y += _vector.y;
              this->z += _vector.z;
              
              return *this;
          }
          
          PVector3D PVector3D::operator- (const PVector3D _vector)
          {
              this->x -= _vector.x;
              this->y -= _vector.y;
              this->z -= _vector.z;
              
              return *this;
          }
  
          PVector3D PVector3D::operator* (const PVector3D _vector)
          {
              this->x *= _vector.x;
              this->y *= _vector.y;
              this->z *= _vector.z;
              
              return *this;
          }
          
          PVector3D PVector3D::operator *(const float scalar)
          {
              this->x *= scalar;
              this->y *= scalar;
              this->z *= scalar;
              
              return *this;
          }
          
      }
}
