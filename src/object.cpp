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

using namespace std;

namespace PacGame
{
      namespace GameClasses
      {
            /*****************************************
            PLevelBox methods
            *****************************************/
            void PObject::setIndex(int i, int j) // index setter
            {
                this->i = i;
                this->j = j;
            }

            void PObject::setI(int i)  // i index setter
            {
                this->i = i;
            }

            void PObject::setJ(int j)  // j index setter
            {
                this->j = j;
            }


            void PObject::setRealI(float realI)
            {
                this->realI = realI;
            }

            void PObject::setRealJ(float realJ)
            {
                this->realJ = realJ;
            }

            void PObject::toogleBombActivity()
            {
                this->containsActiveBomb = !this->containsActiveBomb;
            }

            int PObject::getI() const  // i index getter
            {
                return this->i;
            }

            int PObject::getJ() const  // j index getter
            {
                return this->j;
            }

            float PObject::getRealI() const  // i index getter
            {
                return this->realI;
            }

            float PObject::getRealJ() const  // j index getter
            {
                return this->realJ;
            }

            bool PObject::isActiveBomb() const
            {
                return this->containsActiveBomb;
            }

            unsigned short PObject::getId() const
            {
                return id;
            }


            void PObject::moveObject(int direction)
            {
                 // set the direction of the object and the move bit
                 this->direction = direction;
            }

            void PObject::print()
            {
                cout<<this->id<<' ';
            }


            PObject::~PObject()
            {
                releaseList();   // at destrution of class, release it's children from memory
            }

          
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
                  //Messages::infoMessage("List released");  // print out status
              }
          }

          // prints list into console
          /*void PObject::dumpList() const
          {
              for(node *i=root; i!=NULL; i=i->next)
              {
                      i->object->print();
              }
          }*/
          
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

          void PObject::setMaterial(PMaterial material, float r, float g, float b, float a)
          {
              float *propList = NULL;

              if (material == DIFFUSE)
                  propList = this->materialDiffuse;
              else if (material == AMBIENT)
                  propList = this->materialAmbient;
              else if (material == SPECULAR)
                  propList = this->materialSpecular;
              else return;

              // we have material's properties pointer, so set the properties
              propList[0] = r;
              propList[1] = g;
              propList[2] = b;
              propList[3] = a;
          }

          void PObject::setMaterialShininess(float s)
          {
              this->materialShinines = s;
          }

          void PObject::setMaterialSet() {
              this->materialsSet = true;
          }

          void PObject::draw(float x, float y) {
              if (this->materialsSet) {
                  glMaterialfv(GL_FRONT, GL_AMBIENT, this->materialDiffuse);
                  glMaterialfv(GL_FRONT, GL_DIFFUSE, this->materialAmbient);
                  glMaterialfv(GL_FRONT, GL_SPECULAR, this->materialSpecular);

                  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, this->materialShinines);
              }
          }
      }
}
