/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include <iostream>
#include "level.h"
#include "messages.h"

using namespace std;
using namespace PacGame::GameClasses;

// globals
PMessages g_msg;

namespace PacGame
{
          namespace GameClasses
          {

			  /*****************************************
			   PLevelBox methods
			   *****************************************/
			  // constructors
			  PLevelBox::PLevelBox() {}

			  PLevelBox::PLevelBox(PBoxInfo inf)
			  {
				  info = inf;
			  }

			  PLevelBox::PLevelBox(float x, float y, uint8_t type, uint8_t meta)
			  {
				  setCoordinates(x, y);
				  setInfo(type, meta);
			  }

			  // setters
			  void PLevelBox::setType(uint8_t type)
			  {
				  info.fieldType = type;
			  }

			  void PLevelBox::setMeta(uint8_t meta)
			  {
				  info.fieldMeta = meta;
			  }

			  void PLevelBox::setInfo(PBoxInfo inf)
			  {
				  info = inf;
			  }

			  void PLevelBox::setInfo(uint8_t type, uint8_t meta)
			  {
				  	info.fieldType = type;
					info.fieldMeta = meta;
			  }

			  // getters
			  void PLevelBox::getInfo(uint8_t &type, uint8_t &meta)
			  {
				  type = info.fieldType;
				  meta = info.fieldMeta;
			  }

			  PBoxInfo PLevelBox::getInfo()
			  {
				  return info;
			  }

			  int PLevelBox::getType()
			  {
				  return (int)info.fieldType;
			  }

			  int PLevelBox::getMeta()
			  {
				  return (int)info.fieldMeta;
			  }


			  // ===== OBJECT FUNCTIONS TO OVERRIDE =====//
			  void PLevelBox::draw()
			  {
				  // TODO
			  }

              bool PLevelBox::initialize()
			  {
				  // TODO
				  return true;
			  }

              void PLevelBox::print()
			  {
				 // cout<<"\nInfo:\n Type:"<<(int)info.fieldType<<" Meta:"<<(int)info.fieldMeta<<endl;
				  cout<<"------------"<<endl;
				  cout<<"| Position:|"<<endl;
				  cout<<"| x: "<<getCoordX()<<"   |"<<endl;
				  cout<<"| y: "<<getCoordY()<<"   |"<<endl;
				  cout<<"|----------|"<<endl;
				  cout<<"| Type: "<<(int)info.fieldType<<"  |"<<endl;
				  cout<<"| Meta: "<<(int)info.fieldMeta<<"  |"<<endl;
				  cout<<"------------"<<endl;
			  }


			  /*****************************************
			   PLevel methods
			   *****************************************/

		//	  	PLevelBox structureData[LEVEL_WIDTH][LEVEL_HEIGHT];

			  // setters
			  void PLevel::setField(PLevelBox _box, unsigned short i, unsigned short j)
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
			  }

			  // ===== OBJECT FUNCTIONS TO OVERRIDE =====//
			  void PLevel::draw()
			  {
				  // TODO
			  }

              bool PLevel::initialize()  // temporary random initialization (!!!!!!!!!!!!!!!)
			  {
				  // TODO
				  for(int i=0; i<LEVEL_WIDTH; i++)
				  {
					  for(int j=0; j<LEVEL_HEIGHT; j++)
					  {
						  structureData[i][j].setType(1);
					  }
					  cout<<endl;
				  }
				  return true;
			  }

              void PLevel::print() 
			  {

			  }

		  }
}
