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
 * Codename: xSoko
 * File: object.h
 *
 * Summary:
 * Basic (abstract) class, every object, entity and related should be derived
 * from object.h
 * It is also a container
 *
 * Author: Aljosa Osep 2007
 * Modified:
*/

#ifndef __OBJECT_H
#define __OBJECT_H

#include <string>
#include "CommonStructures.h"
#include "renderer/renderer.h"
#include "vector.h"
#include "core.h"
#include "messages.h"

using namespace PacGame::Structures;
using namespace PacGame::RenderMaschine;
using namespace PacGame::GameClasses;
using namespace PacGame::Messages;
using namespace std;

namespace PacGame
{
      namespace GameClasses
      {
            /**********************************************************
            * PObject
            *
            * Abstract class 
            * Every object should be drived from this class
            * --------------------------------------------------------
            * Aljosa 2007 - 2008
            * ********************************************************/
           class PObject 
           {
           private:
               struct node  // linked list structure
               {
                   PObject *object;
                   node *next;
               };



               node *root; // root of linked list
           public:

               enum PMaterial {
                   AMBIENT, DIFFUSE, SPECULAR
               };

               // constructors
             //  PObject();
               PObject() :  root(NULL) ,  i(0), j(0), realI(0), realJ(0),direction(0),id(0),  containsActiveBomb(0), materialsSet(0) {}// constructors
               PObject(int i, int j) : root(NULL) , i(i), j(j), realI((float)i),realJ((float)j),direction(0),containsActiveBomb(0), materialsSet(0) {}

                  // setters
               void setIndex(int i, int j);
               void setI(int i);
               void setJ(int j);
               void setRealI(float realI);
               void setRealJ(float realJ);
               void toogleBombActivity();

               // getters
               int getI() const;
               int getJ() const;
               float getRealI() const;
               float getRealJ() const;
               bool isActiveBomb() const;
               unsigned short getId() const;

               // animation objects
               virtual void moveObject(int direction);
               virtual bool animate(double time){return false;};

               // virtual functions to override
               virtual void draw()=0;        // code that draws object
               bool initialize() { return true; }  // override
               virtual void print()=0;       // object's console dump

               // IsPlayerMovePossible
               // return values:
               // 0 - no move possible
               // 1 - move possible
               // 2 - the object in the way must first be moved
               // 4 - pick up object, pbomb
               // 8 - teleport
               virtual short isPlayerMovePossible(int direction)=0;



               void setMaterial(PMaterial material, float r, float g, float b, float a);
               void setMaterialShininess(float s);
               void setMaterialSet();

               // destructor
               virtual ~PObject();

               //// low-level func
               // linked list
               void add(PObject *obj);  // attaches another object to this object 
               void attachToRoot(PObject *obj); // attaches new object to root; doesn't create new object
               void dumpList() const;   // dumps children data into console
               void releaseList();      // releases this objects children from memory
               PObject* returnFirstChild() const;  // returns first child
               void releaseFirstChild(); // releases first child from memory; WARNING: if there are more children, others are lost!
               void releaseFirstChildObject();
               void unlinkFirstChild();  // destroys connection with first child; WARNING: if there are more children, others are lost!
               
           protected:
                  int i, j;     // represents indexes of element on level matrix
                  float realI, realJ;   // real coordinates, for smooth movement

                  // direction that the object is facing
                  // 5 important bits
                  // bit 1: direction up, PL_OBJECT_FACE_UP
                  // bit 2: direction right, PL_OBJECT_FACE_RIGHT
                  // bit 4: direction down, PL_OBJECT_FACE_DOWN
                  // bit 8: direction left, PL_OBJECT_FACE_LEFT
                  // bit 16: movement bit, set when the object is moving, PL_OBJECT_MOVE
                  // other bits can be used for special animation
                  int direction;

                  unsigned short id; // number, that represents object in file
                  bool containsActiveBomb;
                  PCore *core;

                  bool materialsSet;
                  float materialAmbient[4];
                  float materialDiffuse[4];
                  float materialSpecular[4];
                  float materialShinines;
           };
      }
}

#endif
