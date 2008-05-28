/*
  codename: Pac-Game
  Aljosa Osep 2007
*/

#ifndef __MESSAGES_H
#define __MESSAGES_H

#include <iostream>

using namespace std;

namespace PacGame
{
          namespace GameClasses
          {
                    /**********************************************************
                    * PMessages
					*
                    * For writing states into console
					* --------------------------------------------------------
                    * Aljosa 2007
                    * ********************************************************/
                    class PMessages
                    {
					public:
						void initMessage(char *string, bool isSuccess)
						{
							if(isSuccess)
								cout<<"Initializing "<<string<<" ........... OK"<<endl;
							else
								cout<<"Initializing "<<string<<" ........... FAILED"<<endl;
						}

						void errorMessage(char *string)
						{
							cout<<"Error: "<<string<<endl;
						}

						void errorIndexOutOfRange()
						{
							cout<<"Error: index out of range!"<<endl;
						}

						void errorUnknown()
						{
							cout<<"Error: unknown!"<<endl;
						}


						void infoMessage(char *string)
						{
							cout<<"Info: "<<string<<endl;
						}

						void infoTexture(const char *string)
						{
							cout<<"Info: Tga file "<<string<<" was successfully loaded."<<endl;
						}

						void mainTitleMessage()
						{
							cout<<"======================================"<<endl;
							cout<<"==        CODENAME: PACGAME         =="<<endl;
							cout<<"==          Console output          =="<<endl;
							cout<<"==         (c) Aljosa 2007          =="<<endl;
							cout<<"======================================"<<endl;
							cout<<endl;
						}
                    };
          }
}

#endif
