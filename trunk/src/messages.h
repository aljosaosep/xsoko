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
