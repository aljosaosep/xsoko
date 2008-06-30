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
#include "messages.h"
#include "level.h"
#include "levelbox.h"
#include "object.h"

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
      namespace GameClasses
      {
           /*****************************************
           PLevel methods
           *****************************************/
          // level functions implementation goes here! ;)
          
          // function is work in progress, started by Aljosa june 29, 2008
          bool PLevel::loadLevelFromFile()
          {
              
              return true; // everything went ok
          }
          
          // function is work in progress, started by Aljosa june 29, 2008
          bool PLevel::initialize()
          {
              //data = new
              if(!this->loadLevelFromFile())
              {
                  Messages::errorMessage("Level loading from file failed.");
                  return 0;
              }
              // by now, matrix should be initialized with proper classes, if it went ok this far
              
       /*       data[0][0] = new PTeleport;
              data[0][1] = new PTeleport;
              
              data[0][0]->add(data[0][1]);
              //data[0][0]->
              
              PTeleport *oce = new PTeleport;
              PTeleport *sin = new PTeleport;
              
              oce->add(data[0][0]);*/
             // test.add(&data[0][0]);
              return true; // everything went ok
          }
          // dumps level data insto console; prints type of level(wall, void, teleport, ...)          
          void PLevel::printLevelByType() const
          {
              for(unsigned i=0; i<this->width; i++)
              {
                  for(unsigned j=0; j<this->height; j++)
                      data[i][j]->print();
                  cout<<endl;
              }
          }
          // dumps level data insto console;  prints meta data(what is on level block)
          void PLevel::printLevelByMeta() const
          {
              for(unsigned i=0; i<this->width; i++)
              {
                  for(unsigned j=0; j<this->height; j++);
                   //   data[i][j]->returnFirstChild()->print();  // print it's child; // zakaj ne dela?!?
                  cout<<endl;
              }              
          }
    }
}
