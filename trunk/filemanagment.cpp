/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include "filemanager.h"

using namespace std;


namespace PacGame
{
          namespace InputOutputClasses
          {
			  PFileManager::PFileManager()
			  {
				  levelData.open("data/level.lvl", ios::binary);
				  if(!levelData.is_open())
					  cout<<"Error while opening level data"<<endl;
			  }

			  PFileManager::~PFileManager()
			  {
				  levelData.close();
			  }
		  }
}