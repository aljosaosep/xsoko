/*
 * codename: xSoko
 *
 * Author: Aljosa Osep 2007
 * Modified:
*/

#ifndef __VECTOR_2D_H
#define __VECTOR_2D_H

#include <iostream>

//using namespace PacGame::Structures;
//using namespace PacGame::GameClasses;
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
			  class PVector2D
			  {
			  protected:
				  float x, y;  // x and y position in the space
			  public:
				  // constructors
				  PVector2D();
				  PVector2D(float _x, float _y);
				 // PVector2D(const PVector2D &vec);  // copy constructor

				  // setters
				  void setCoordinates(float _x, float _y);
				  void setCoordX(float _x);
				  void setCoordY(float _y);

				  // getters
				  float getCoordX();
				  float getCoordY();
				  void getCoordinates(float &_x, float &_y);

				  // print
				  void printCoordinates();

				  // operators
		/*		  PVector2D operator + (PVector2D _vector);
				  PVector2D operator - (PVector2D _vector);
				  PVector2D operator * (PVector2D _vector);
				  PVector2D operator / (PVector2D _vector);*/

				  PVector2D operator = (PVector2D _vector);


			//	  PVector2D operator ++ (PVector2D _vector);
				 // PVector2D operator^ (PVector2D _vector); // dot product
				  
			  };		
          }
}

#endif
