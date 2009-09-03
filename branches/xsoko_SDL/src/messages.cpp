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
 * File: messages.cpp
 *
 * Summary:
 * Includes message function implementation
 *
 * Author: Aljosa Osep 2008
 * Changes:
 * Jernej Haložan 2008
 * Aljosa 2008
*/

#include "messages.h"            
namespace PacGame
{
    namespace Messages 
    {
        /*******************************************
         * initMessage()
         * set isSucces true, if initialization went ok
         * otherwise false
         * text desribes what are you initialising
         *******************************************/
        void initMessage(string text, bool isSuccess)
        {
            isSuccess ? cout<<"Initializing "<<text<<" ........... OK"<<endl : cout<<"Initializing "<<text<<" ........... FAILED"<<endl;
        }

         /*******************************************
          * errorMesage()
          * If cause is known, pass error desc. 
          *******************************************/
        void errorMessage(string text) 
        {
            cout<<"Error: "<<text<<endl;
        }

         /*******************************************
         * errorIndexOutOfRange()
         * if it comes to index out of range error
         *******************************************/
        void errorIndexOutOfRange() 
        {
            cout<<"Error: index out of range!"<<endl;
        }

         /*******************************************
         * errorUnknown()
         * if cause in unknown, there is no description 
         * needed.
         *******************************************/
        void errorUnknown() 
        {
            cout<<"Error: unknown!"<<endl;
        }

         /*******************************************
         * infoMessage()
         * informs engine state about something
         * for debugging purposes
         *******************************************/
        void infoMessage(string text) 
        {
            cout<<"Info: "<<text<<endl;
        }

         /*******************************************
         * infoTexture()
         * informs that texture was loaded.
         *******************************************/
        void infoTexture(string text) 
        {
            cout<<"Info: Tga file "<<text<<" was successfully loaded."<<endl;
        }

         /*******************************************
         * mainTitleMessage()
         * fancy stuff :D
         *******************************************/
        void mainTitleMessage() 
        {
            cout<<"======================================"<<endl;
            cout<<"==        CODENAME: xSoko           =="<<endl;
            cout<<"==          Console output          =="<<endl;
            cout<<"======================================"<<endl;
            cout<<endl;
        }
    }
}
