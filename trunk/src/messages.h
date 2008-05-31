/*
 * Codename: xSoko
 * File: messages.h
 *
 * Summary:
 * Includes PMessage class implementation
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Jernej Haložan 2008
*/

#ifndef __MESSAGES_H
#define __MESSAGES_H

#include <iostream>
#include <string>
using namespace std;

namespace PacGame
{
    namespace GameClasses
    {
        class PMessages
        {
	public:
            void initMessage(string text, bool isSuccess)
            {
                if(isSuccess)
                    cout<<"Initializing "<<text<<" ........... OK"<<endl;
                else
                    cout<<"Initializing "<<text<<" ........... FAILED"<<endl;
            }

            void errorMessage(string text)
            {
                cout<<"Error: "<<text<<endl;
            }

            void errorIndexOutOfRange()
            {
                cout<<"Error: index out of range!"<<endl;
            }

            void errorUnknown()
            {
                cout<<"Error: unknown!"<<endl;
            }


            void infoMessage(string text)
            {
                cout<<"Info: "<<text<<endl;
            }

            void infoTexture(string text)
            {
                cout<<"Info: Tga file "<<text<<" was successfully loaded."<<endl;
            }

            void mainTitleMessage()
            {
                cout<<"======================================"<<endl;
                cout<<"==        CODENAME: xSoko           =="<<endl;
                cout<<"==          Console output          =="<<endl;
                cout<<"======================================"<<endl;
                cout<<endl;
            }
        };
    }
}

#endif
