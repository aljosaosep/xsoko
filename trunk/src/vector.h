/*
 * codename: xSoko
 *
 * Author: Aljosa Osep 2007
 * Modified:
*/

#ifndef __VECTOR_2D_H
#define __VECTOR_2D_H

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
                  virtual void printCoordinates();

                  // operators
/*		  PVector2D operator + (PVector2D _vector);
                  PVector2D operator - (PVector2D _vector);
                  PVector2D operator * (PVector2D _vector);
                  PVector2D operator / (PVector2D _vector);*/

                  PVector2D operator = (PVector2D _vector);


        //	  PVector2D operator ++ (PVector2D _vector);
                 // PVector2D operator^ (PVector2D _vector); // dot product

          };
          
          class PVector3D : public PVector2D
          {
          private:
              float z;
              
          public:
             // constructors
                  PVector3D();
                  PVector3D(float _x, float _y, float _z);
                 // PVector2D(const PVector2D &vec);  // copy constructor

                  // setters
                  void setCoordinates(float _x, float _y, float _z);
                  void setCoordinates(const PVector3D _vec);
                  void setCoordZ(float _z);

                  // getters
                  float getCoordZ();

                  // print
                  void printCoordinates();
                  
                  // operators
                  PVector3D operator = (PVector3D _vector);
                  
		  PVector3D operator + (PVector3D _vector);
                  PVector3D operator - (PVector3D _vector);
                  PVector3D operator * (PVector3D _vector);
                  PVector3D operator * (const float scalar);
         //         PVector2D operator / (PVector2D _vector);
          };
      }
}

#endif
