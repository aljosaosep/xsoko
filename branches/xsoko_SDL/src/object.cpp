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
 * File: object.cpp
 *
 * Summary:
 * Basic (abstract) class, every object, entity and related should be derived
 * from object.h
 * It is also a container
 * This file includes its implementation.
 *
 * Author: Aljosa Osep 2007
 * Modified:
*/

#include <iostream>
#include "object.h"
//#include "zip/zlib/zconf.in.h"

using namespace std;

namespace PacGame
{
      namespace GameClasses
      {
          // constructors
          PObject::PObject() 
          {
              root = NULL; // initiates linked list
          }  

  /*        PObject::PObject(float x, float y)
          {
              root = NULL;			 // initiates linked list
              position.setCoordinates(x, y);  // set vector coordinates	
          }*/


          PObject::~PObject()
          {
              releaseList();   // at destrution of class, release it's children from memory 
          }

          void PObject::print()
          {
              cout<<"=========== OBJECT INFO =============="<<endl;
//              this->position.printCoordinates();
              cout<<"======================================"<<endl;
          }

          // linked list related
          
          // adds object to lists head
          void PObject::add(PObject *obj)
          {
              node *newnode = new node;  // creates new node
              newnode->object = obj;     // attach object to node

              if(root == NULL)			 // if list is empty
                  newnode->next = NULL;  // new node is only one element
              else
                  newnode->next = root;  // otherwise, add element to head

              root = newnode;
          }
          
          
          // attaches new object to root; doesn't create new object
          void PObject::attachToRoot(PObject *obj)
          {
//              if(root->object == NULL)
                root->object = obj; 
          }

          // releases all list elements from memory
          void PObject::releaseList()
          {
              node *i = root;  // var points to root
              node *j = NULL;  // var used for delete element

              if(i!=NULL)	   // if list is not empty
              {
                  while(i!=NULL)   // while there are elements in list
                  {
                          j=i;
                          i=i->next;
                          delete[] j;  // delete element
                  }
                  Messages::infoMessage("List released");  // print out status
              }
          }

          // prints list into console
          void PObject::dumpList() const
          {
              for(node *i=root; i!=NULL; i=i->next)
              {
                      i->object->print();
              }
          }
          
          // functions returns first element in list, in soko, that is object appened to parent object
          PObject* PObject::returnFirstChild() const
          {
              return root == NULL ? NULL : root->object;
          }
          
          // removes first child, deletes it from memory; WARNING: it there are more children, they're lost!!!
          void PObject::releaseFirstChild()
          {
              delete [] root;  // delete object
              root = NULL;     // set pointer to NULL
          }
          
          void PObject::releaseFirstChildObject()
          {
              delete  root->object;
              root->object = NULL;
          }
  
          // removes first child, deletes it from memory; WARNING: it there are more children, they're lost!!!
          void PObject::unlinkFirstChild()
          {
              root->object = NULL;     // set pointer to NULL
          }
      }
}
