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

#include "levelbox.h"


#include "object.h"


#include <sstream>
#include <string>
// #include "level.h"
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
              PObject *p = NULL;
              ifstream level; // file handle
              level.open(this->filename.c_str());  // opens level
              if(!level.good())  // checks if file is properly open
              {
                  Messages::errorMessage("Level data is in invalid format ot there is not level data at all!");
                  return false;  // if it isn't, end routine
              }
              
              // everything went ok so far
              Messages::infoMessage("Loading level data... please wait.");
              while(!level.eof()) // read line-by-line 'till the end
              {
                  // first, I read dimension
                  m = height = this->returnNumberFromFile(level);
                  n = width = this->returnNumberFromFile(level);
                  
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
                  
                  PNoData *noData = new PNoData;  // one object for all fields with no data

                  // we continue with second matrix
                  for(int i=0; i<n; i++)
                  {
                      for(int j=0; j<m; j++)
                      {
                          num = returnNumberFromFile(level);
                          if(num!=-1)
                          {
                              if(num >= 11) // if it is > 11, then it is an teleport id
                              {
                                      p = new PData(num);
                                      data[i][j]->add(p);                                
                              }
                              
                              switch(num)
                              {
                                  case NO_CHILD:
                                   //   p = new PNoData;
                                      data[i][j]->add(noData);
                                      break;                                      
                                      
                                  case PLAYER:
                                      p = new PPlayer;
                                      data[i][j]->add(p);
                                      break;
                                      
                                  case CUBE:
                                      p = new PCube;
                                      data[i][j]->add(p);
                                      break;
                                      
                                  case OW_CUBE_L:
                                      p = new POnewayCube(Aliases::left);
                                      data[i][j]->add(p);
                                      break; 
                                      
                                  case OW_CUBE_R:
                                      p = new POnewayCube(Aliases::right);
                                      data[i][j]->add(p);
                                      break; 
                                      
                                  case OW_CUBE_U:
                                      p = new POnewayCube(Aliases::up);
                                      data[i][j]->add(p);
                                      break;  
                                      
                                  case OW_CUBE_D:
                                      p = new POnewayCube(Aliases::down);
                                      data[i][j]->add(p);
                                      break;
                                      
                                  case BOMB:
                                      p = new PBomb;
                                      data[i][j]->add(p);
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
              cout<<"Level by type:"<<endl;
              this->printLevelByType();
              cout<<"Level by meta:"<<endl;
              this->printLevelByMeta();
              
          }
     
     
          // dumps level data insto console; prints type of level(wall, void, teleport, ...)          
          void PLevel::printLevelByType() const
          {
              cout<<endl;
              for(unsigned i=0; i<this->width; i++)
              {
                  for(unsigned j=0; j<this->height; j++)
                      data[i][j]->print();
                  cout<<'|'<<endl;
              }
              cout<<endl;
          }
          // dumps level data insto console;  prints meta data(what is on level block)
          void PLevel::printLevelByMeta() const
          {
              cout<<endl;
              for(unsigned i=0; i<this->width; i++)
              {
                  for(unsigned j=0; j<this->height; j++)
                      data[i][j]->returnFirstChild()->print();
                  cout<<'|'<<endl;
              }
              cout<<endl;            
          }
    }
}
