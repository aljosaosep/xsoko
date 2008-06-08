/*
 * Codename: xSoko
 * File: level.h
 *
 * Summary:
 * Includes level class implementation, abstratct grid element imp., and
 * several others level struct classes implementation
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Aljosa 2008
*/
#include <iostream>
#include "level.h"
#include "messages.h"

using namespace std;
using namespace PacGame::GameClasses;

// globals
//PMessages g_msg;  // globals are bad

namespace PacGame
{
          namespace GameClasses
          {
			  /*****************************************
			   PLevelBox methods
			   *****************************************/			  
                          void PLevelObject::setIndex(unsigned i, unsigned j) // index setter
			  {
				  this->i = i;
				  this->j = j;
			  }

			  void PLevelObject::setI(unsigned i)  // i index setter
			  {
				  this->i = i;
			  }

			  void PLevelObject::setJ(unsigned j)  // j index setter
			  {
				  this->j = j;
			  }

			  unsigned PLevelObject::getI()  // i index getter
			  {
				  return this->i;
			  }

			  unsigned PLevelObject::getJ()  // j index getter
			  {
				  return this->j;
			  }

			  void PLevelObject::getIndex(unsigned &i, unsigned &j)  // both index getter
			  {
				  i = this->i;
				  j = this->j;
			  }


                  /*        void PLevelBox::print()
			  {
				 // cout<<"\nInfo:\n Type:"<<(int)info.fieldType<<" Meta:"<<(int)info.fieldMeta<<endl;
				  cout<<"------------"<<endl;
				  cout<<"| Position:|"<<endl;
				  cout<<"| x: "<<positon.getCoordX()<<"   |"<<endl;
				  cout<<"| y: "<<position.getCoordY()<<"   |"<<endl;
				  cout<<"|----------|"<<endl;
				  //cout<<"| Type: "<<(int)info.fieldType<<"  |"<<endl;
				  //cout<<"| Meta: "<<(int)info.fieldMeta<<"  |"<<endl;
				  cout<<"------------"<<endl;
			  }*/


			  /*****************************************
			   PLevel methods
			   *****************************************/

		//	  	PLevelBox structureData[LEVEL_WIDTH][LEVEL_HEIGHT];

			  // setters
		/*	  void PLevel::setField(PLevelBox _box, unsigned short i, unsigned short j)
			  {
				  if((i<LEVEL_HEIGHT-1)&&(j<LEVEL_WIDTH-1))
					  structureData[i][j] = _box;
				  else
					  g_msg.errorIndexOutOfRange();

			  }

			  void PLevel::setFieldInfo(PBoxInfo _info, unsigned short i, unsigned short j)
			  {
				  if((i<LEVEL_HEIGHT-1)&&(j<LEVEL_WIDTH-1))
					  structureData[i][j].setInfo(_info);
				  else
					  g_msg.errorIndexOutOfRange();
			  }

			  void PLevel::setFieldType(uint8_t _type, unsigned short i, unsigned short j)
			  {
				  if((i<LEVEL_HEIGHT-1)&&(j<LEVEL_WIDTH-1))
					  structureData[i][j].setType(_type);
				  else
					  g_msg.errorIndexOutOfRange();
			  }

		      void PLevel::setFieldMeta(uint8_t _meta, unsigned short i, unsigned short j)
			  {
				  if((i<LEVEL_HEIGHT-1)&&(j<LEVEL_WIDTH-1))
					  structureData[i][j].setMeta(_meta); 
				  else
					  g_msg.errorIndexOutOfRange();
			  }

			  // getters
			  PLevelBox PLevel::getField(unsigned short i, unsigned short j)
			  {
				  if((i<LEVEL_HEIGHT-1)&&(j<LEVEL_WIDTH-1))
					  return structureData[i][j];
				  else
				  {
					  g_msg.errorIndexOutOfRange();
					  return structureData[0][0];
				  }
			  }

			  PBoxInfo PLevel::getFieldInfo(unsigned short i, unsigned short j)
			  {
				  if((i<LEVEL_HEIGHT-1)&&(j<LEVEL_WIDTH-1))
					  return structureData[i][j].getInfo();
				  else
				  {
					  g_msg.errorIndexOutOfRange();
					  return structureData[0][0].getInfo();
				  }
			  }

			  unsigned short PLevel::getFieldType(unsigned short i, unsigned short j)
			  {
				  if((i<LEVEL_HEIGHT-1)&&(j<LEVEL_WIDTH-1))
					  return (unsigned short)structureData[i][j].getType();
				  else
				  {
					  g_msg.errorIndexOutOfRange();
					  return 0;
				  }
			  }

			  unsigned short PLevel::getFieldMeta( unsigned short i, unsigned short j)
			  {
				  if((i<LEVEL_HEIGHT-1)&&(j<LEVEL_WIDTH-1))
					  return (unsigned short)structureData[i][j].getMeta();
				  else
				  {
					  g_msg.errorIndexOutOfRange();
					  return 0;
				  }
			  }

			  // print
			  void PLevel::printLevelByType()
			  {
				  cout<<"===== LEVEL BY TYPE ====="<<endl;
				  for(int i=0; i<LEVEL_WIDTH; i++)
				  {
					  for(int j=0; j<LEVEL_HEIGHT; j++)
					  {
						  cout<<(int)structureData[i][j].getType()<<"  ";
					  }
					  cout<<endl;
				  }
				  cout<<"========================"<<endl<<endl;

			  }

			  void PLevel::printLevelByMeta()
			  {
				  cout<<"===== LEVEL BY META ====="<<endl;
				  for(int i=0; i<LEVEL_WIDTH; i++)
				  {
					  for(int j=0; j<LEVEL_HEIGHT; j++)
					  {
						  cout<<(int)structureData[i][j].getMeta()<<"  ";
					  }
					  cout<<endl;
				  }
				  cout<<"========================"<<endl<<endl;
			  }*/

			  // ===== OBJECT FUNCTIONS TO OVERRIDE =====//
			  void PLevel::draw()
			  {
				  // TODO
			  }

                          bool PLevel::initialize()  // temporary random initialization (!!!!!!!!!!!!!!!)
			  {
				  // TODO
				/*  for(int i=0; i<LEVEL_WIDTH; i++)
				  {
					  for(int j=0; j<LEVEL_HEIGHT; j++)
					  {
						  structureData[i][j].setType(1);
					  }
					  cout<<endl;
				  }*/
				  return true;
			  }

                          void PLevel::print() 
			  {

			  }

		  }
}
