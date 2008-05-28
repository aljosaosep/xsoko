/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include <iostream>
#include "object.h"

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

			  PObject::PObject(float x, float y)
			  {
				  root = NULL;			 // initiates linked list
			      setCoordinates(x, y);  // set vector coordinates	
			  }

			  /*PObject::PObject(float x, float y, float i, float j)
			  {
				  root = NULL; // initiates linked list
				  setCoordinates(x, y); // set vector coordinates
				  this->i = i;   // set i index
				  this->j = j;   // set j index
			  }*/

			  PObject::~PObject()
			  {
				  releaseList();   // at destrution of class, release it's children from memory 
			  }

			  void PObject::setIndex(unsigned i, unsigned j) // index setter
			  {
				  this->i = i;
				  this->j = j;
			  }

			  void PObject::setI(unsigned i)  // i index setter
			  {
				  this->i = i;
			  }

			  void PObject::setJ(unsigned j)  // j index setter
			  {
				  this->j = j;
			  }

			  unsigned PObject::getI()  // i index getter
			  {
				  return this->i;
			  }

			  unsigned PObject::getJ()  // j index getter
			  {
				  return this->j;
			  }

			  void PObject::getIndex(unsigned &i, unsigned &j)  // both index getter
			  {
				  i = this->i;
				  j = this->j;
			  }

			  void PObject::print()
			  {
				  cout<<"=========== OBJECT INFO =============="<<endl;
				  cout<<"x: "<<this->x<<endl;
				  cout<<"y: "<<this->y<<endl;
				  cout<<"i: "<<this->i<<endl;
				  cout<<"j: "<<this->j<<endl;
				  cout<<"======================================"<<endl;
			  }

			  // linked list related
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
					  msg.infoMessage("List released");  // print out status
				  }
				  
			  }

			  void PObject::dumpList() const
			  {
			//	  this->print():
				  for(node *i=root; i!=NULL; i=i->next)
				  {
					  i->object->print();
				  }
			  }
          }
}
