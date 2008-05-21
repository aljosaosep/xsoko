/*
  codename: Pac-Game
  Aljosa Osep 2007
*/

#ifndef __OBJECT_H
#define __OBJECT_H

#include <string>
#include "CommonStructures.h"
#include "renderer.h"
#include "vector.h"
#include "messages.h"


using namespace PacGame::Structures;
using namespace PacGame::RenderMaschine;
using namespace PacGame::GameClasses;
using namespace std;


namespace PacGame
{
          namespace GameClasses
          {
                    /**********************************************************
                    * PObject
					*
					* Abstract class (!!!)
                    * Every drawed object should be drived from this class
					* --------------------------------------------------------
                    * Aljosa 2007
                    * ********************************************************/
					class PObject : public PVector2D
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
								 PObject(float x, float y, float i, float j);
								 ~PObject();

								 // setters
								 void setIndex(unsigned i, unsigned j);
								 void setI(unsigned i);
								 void setJ(unsigned j);

								 // getters
								 unsigned getI();
								 unsigned getJ();
								 void getIndex(unsigned &i, unsigned &j);

								 // linked list
								 void add(PObject *obj);
								 void dumpList() const;
								 void releaseList();

 
                                 // etc
                                 virtual void draw()=0;
                                 virtual bool initialize()=0;
                                 virtual void print();    // print into console    
							//	 string texFilename;
                     protected:	 
						//		 PTexture texture(string texFilename);
								unsigned i, j; // position in the matrix (x and y index)
								PMessages msg;
                    };
          }
}

#endif
