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

#include <sstream>
#include <string>
#include "level.h"
#include <iostream>
#include <fstream>
#include "messages.h"
#include "level.h"
#include "levelbox.h"

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
      namespace GameClasses
      {
 
           /*****************************************
           PLevel methods
           *****************************************/
          int PLevel::returnNumberFromFile(ifstream &file)
          {
              char buff[3];
              char c;
              file.get(c);
              if(!(c >= '0' && c <= '9'))
                  return -1;
              else
                  buff[0] = c;
                  
              file.get(c);
              
              if(c >= '0' && c <= '9')
              {
                  buff[1] = c;
                  buff[2] = '\0';
                  file.get();
              }
              else
              {
                  buff[1] = '\0';
              //    file.get();
              }
              
              return atoi(buff);
          }
          // level functions implementation goes here! ;)
          
          // function is work in progress, started by Aljosa june 29, 2008
          bool PLevel::loadLevelFromFile()
          {
              int m = 0, n = 0; // dimensions
              char c; // for reading single character in file
              ifstream level; // file handle
              level.open(this->filename.c_str());  // opens level
              if(!level.good())  // checks if file is properly open
                  return false;  // if it isn't, end routine
              
              // everything went ok so far
              Messages::infoMessage("Loading level data... please wait.");
              while(!level.eof()) // read line-by-line 'till the end
              {
                  // first, I read dimension
                  m = this->returnNumberFromFile(level);
                  n = this->returnNumberFromFile(level);
                  
                  int num = 0;  // numer that we get from file
                  // considering dimension, we read first matrix
                  for(int i=0; i<n; i++)
                  {
                      for(int j=0; j<m; j++)
                      {
                          num = returnNumberFromFile(level);
                          if(num!=-1)
                          {
                              switch(num)
                              {
                                  case FLOOR:
                                      data[i][j] = new PFloor;
                                      break;
                                      
                                  case OW_FLOOR:
                                      data[i][j] = new POnewayFloor;
                                      break;
                                      
                                  case S_WALL:
                                      data[i][j] = new PSolidWall;
                                      break;
                                      
                                  case U_WALL:
                                      data[i][j] = new PUnsolidWall;
                                      break; 
                                      
                                  case TELEPORT:
                                      data[i][j] = new PTeleport;
                                      break; 
                                      
                                  case BRIDGE:
                                      data[i][j] = new PBridge;
                                      break;  
                                      
                                  case VOID:
                                      data[i][j] = new PVoid;
                                      break;
                                      
                                  case CUBE_PLACE:
                                      data[i][j] = new PCubeHolder;
                                      break;                                       
                              }
                          }
                          else
                          {
                              Messages::errorMessage("Invalid level data.");
                              return false;
                          }
                      }
                  }
                  
                  // first matrix shoud be in memory by now.
                  level.get(c); // skip +
                  if(c!='+') // checks if so far is everything ok
                  {
                      Messages::errorMessage("Invalid level data.");
                      return false;                      
                  }
                  
                  level.get(); // skip newline

                  // we continue with second matrix
                  for(int i=0; i<n; i++)
                  {
                      for(int j=0; j<m; j++)
                      {
                          num = returnNumberFromFile(level);
                          if(num!=-1)
                          {
                              switch(num)
                              {
                                      
                               /*   case PLAYER:
                                   //   data[i][j] = new POnewayFloor;
                                      break;
                                      
                                  case CUBE:
                                      data[i][j].add()
                                      break;
                                      
                                  case U_WALL:
                                      data[i][j] = new PUnsolidWall;
                                      break; 
                                      
                                  case TELEPORT:
                                      data[i][j] = new PTeleport;
                                      break; 
                                      
                                  case BRIDGE:
                                      data[i][j] = new PBridge;
                                      break;  
                                      
                                  case VOID:
                                      data[i][j] = new PVoid;
                                      break;
                                      
                                  case CUBE_PLACE:
                                      data[i][j] = new PCubeHolder;
                                      break;  */                                     
                              }
                          }
                          else
                          {
                              Messages::errorMessage("Invalid level data.");
                              return false;
                          }
                      }
                  }              
                  

                  
                  break;   
              }
              
              Messages::infoMessage("Level data successfully loaded from file.");
              level.close();
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
              

             // test.add(&data[0][0]);
              return true; // everything went ok
          }
          
          // draws whole level
          void PLevel::draw()
          {
              
          }
          
          // dumps level data into console
          void PLevel::print()
          {
              
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
