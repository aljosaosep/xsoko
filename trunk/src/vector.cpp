/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include "vector.h"

namespace PacGame
{
          namespace GameClasses
          {

			  // constructors
			  PVector2D::PVector2D() {}

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
			      //PVector2D _tmpvec;

				  this->x = _vector.x;
				  this->y = _vector.y;

				  return *this;
				  //return _tmpvec;

			  }
          }
}