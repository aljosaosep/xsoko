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
           class PObject //: public PVector2D
           {
           private:
               struct node  // linked list structure
               {
                   PObject *object;
                   node *next;
               };

               node *root; // root of linked list
           public:
               // constructors
               PObject();
//               PObject(float x, float y);
                                                       
               virtual ~PObject();
               // linked list
               void add(PObject *obj);  // attaches another object to this object 
               void attachToRoot(PObject *obj); // attaches new object to root; doesn't create new object
          //     void attachToHead(PObject *obj); // attaches object to head
               void dumpList() const;   // dumps children data into console
               void releaseList();      // releases this objects children from memory
               PObject* returnFirstChild() const;  // returns first child
               void releaseFirstChild(); // releases first child from memory; WARNING: if there are more children, others are lost!
               void releaseFirstChildObject();
               void unlinkFirstChild();  // destroys connection with first child; WARNING: if there are more children, others are lost!
               
               // etc
               virtual void draw()=0;
               virtual bool initialize()=0;
               virtual void print();    // print into console    
                                                //	 string texFilename;
           protected:
//               PVector2D position;  // position of object in OpenGL space, z coord is ignored
           };
      }
}

#endif
