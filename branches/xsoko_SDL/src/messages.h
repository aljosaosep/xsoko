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
 * File: messages.h
 *
 * Summary:
 * Includes message function prototypes
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
    namespace Messages
    {
        // error/status console messages prototypes
        void initMessage(string text, bool isSuccess);  // init; isSuccess must be true in case that initialization is good
        void errorMessage(string text); // error message
        void errorIndexOutOfRange();  // index out of range error message
        void errorUnknown(); // unknown error
        void infoMessage(string text);  // info; for debugging
        void infoTexture(string text);
        void mainTitleMessage();
    }
}

#endif
