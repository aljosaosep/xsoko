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
               PObject(float x, float y);
                                                       
               virtual ~PObject();
               // linked list
               void add(PObject *obj);
               void dumpList() const;
               void releaseList();
               PObject* returnFirstChild() const;

               // etc
               virtual void draw()=0;
               virtual bool initialize()=0;
               virtual void print();    // print into console    
                                                //	 string texFilename;
           protected:
               // PTexture texture(string texFilename);
               PVector2D position;  // position of object in OpenGL space, z coord is ignored
           };
      }
}

#endif
