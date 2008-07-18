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

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
//#include <typeinfo>
#include <iomanip>
#include "messages.h"
#include "level.h"
//#include "levelbox.h"

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
      namespace GameClasses
      {
 
           /*****************************************
           PLevel methods
           *****************************************/
          
          /*****************************************************************
           * Function reads two-digit number from stream pointer current
           * position and skips one character, it is suitable for our
           * level format only.
           *****************************************************************/
          int PLevel::returnNumberFromFile(ifstream &file)
          {
              char buff[3]; // char buffer for our number, before it is being parsed into integer
              char c;       // strage for single character
              file.get(c);  // we read first digit
              if(!(c >= '0' && c <= '9')) // if it isn't a digit, we return an error
                  return -1;
              else
                  buff[0] = c; // otherwise, we store it into buffer
                  
              file.get(c); // we read next character
              
              if(c >= '0' && c <= '9') // if it is a digit ...
              {
                  buff[1] = c;  // we also store it into buffer
                  buff[2] = '\0'; // and then we close string, because we need two-digit numbers only
                  file.get();  // we skip one character(space)
              }
              else // if second character isn't digit
                  buff[1] = '\0';  // we just close string
 
              return atoi(buff);  // we return number read from file, parsed into integer
          }
  
          /*****************************************************************
           * Function validates level format with checking + sign
           * position.
           *****************************************************************/
          bool PLevel::checkPosition(ifstream &file)
          {
              char c; // single character buffer
              file.get(c); // read +  sign

              if(c!='+') // checks if our position is valid
              {
                  Messages::errorMessage("Invalid level data."); 
                  return false;                      
              }

              file.get(); // skip newline
              return true; // position is ok
          }

           /*****************************************************************
           * Function loops through level and finds teleport with
           * given id. It returns pointer to that teleport.
           *****************************************************************/
          PTeleport *PLevel::returnTeleport(int id)
          {
              for(unsigned i=0; i<teleports.size(); i++) // loops thorough vector
                  if(teleports[i]->getId() == id)  // if teleport's id matches id we're lookin' for
                      return teleports[i];  // then return it's address
         
              return NULL; // otherwise return NULL
          }
          
          // level functions implementation goes here! ;)
          
          /**************************************************************
           * Function reads file data form file, given by filename 
           * variable into level class
           **************************************************************/
          // function is work in progress, started by Aljosa june 29, 2008
          bool PLevel::loadLevelFromFile()
          {
              int tmsize; // teleport matrix size
              PObject *p = NULL; // our pobject pointer; for creating dynamic objects
              ifstream level; // file handle
              level.open(this->filename.c_str());  // opens level
              
              if(!level.good())  // checks if file is properly open
              {
                  Messages::errorMessage("Level data is in invalid format ot there is not level data at all!");
                  return false;  // if it isn't, end routine
              }
              
              // everything went ok so far
              Messages::infoMessage("Loading level data... please wait.");
              while(!level.eof()) // we read file 'till the end
              {
                  // first read dimension
                  height = this->returnNumberFromFile(level); // dimensions are first two numbers
                  width = this->returnNumberFromFile(level);
                  
                  int num = 0;  // number that we get from file
                  
                  // considering dimension, we read first matrix
                  for(unsigned i=0; i<width; i++)  
                  {
                      for(unsigned j=0; j<height; j++)
                      {
                          num = returnNumberFromFile(level);  // we read number from file and store it into num
                          
                          if(num!=-1)  // we check if data is valid
                          {
                              switch(num)  // if it is, we create suitable object
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
                          else  // if it isn't, we return error
                          {
                              Messages::errorMessage("Invalid level data.");
                              return false;
                          }
                      }
                  }
                  
                  // first matrix shoud be in memory by now.
                  if(!checkPosition(level))
                      return false;

                  // we continue with second matrix
                  for(unsigned i=0; i<width; i++)
                  {
                      for(unsigned j=0; j<height; j++)
                      {
                          num = returnNumberFromFile(level);
                          if(num!=-1)
                          {
                              if(num >= 11) // if it is > 11, then it is an teleport id
                              {
                                  PTeleport *teleport = new PTeleport; // create object
                                  teleport->setId(num);                // set its id
                                  data[i][j] = teleport;               // attach it on level
                                  this->teleports.push_back(teleport); // push teleport info on vector
                              }
                              
                              switch(num)
                              {                                              
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

                  // second matrix should be in memory by now
                  // now validate
                  if(!checkPosition(level))
                      return false;
                  
                  // validation went ok; now we read teleport relationship matrix
                  tmsize = returnNumberFromFile(level);
                  for(int i=0; i<tmsize; i++)
                  {
                      PTeleport *childTeleport;  // teleprot we're attaching
                      PTeleport *parentTeleport; // parent teleport

                      parentTeleport = returnTeleport(returnNumberFromFile(level)); // get parent teleport
                      childTeleport = returnTeleport(returnNumberFromFile(level));  // get child teleport

                      if(parentTeleport!=NULL && childTeleport!=NULL)  // if teleports has been found
                      {
                          parentTeleport->add(childTeleport);  // attach them
                          cout<<"Teleport "<<childTeleport->getId()<<" attached to teleport "<<parentTeleport->getId()<<endl;
                      }
                      else
                      {
                          Messages::errorMessage("Invalid level data.");
                          return false;
                      }
                  }
                  teleports.clear(); // clear teleport vector, since they are by now in memory and no longer needed
                  break;   
              }
              
              Messages::infoMessage("Level data successfully loaded from file.");
              level.close();
              return true; // everything went ok
          }
          
          /**************************************************************
           * Function initiates level
           * work in progress
           **************************************************************/
          bool PLevel::initialize()
          {
              //data = new
              if(!this->loadLevelFromFile())
              {
                  Messages::errorMessage("Level loading from file failed.");
                  return 0;
              }
              // by now, matrix should be initialized with proper classes, if it went ok this far
              
              // temporary, dump state
              this->print();
              

             // test.add(&data[0][0]);
              return true; // everything went ok
          }
          
          /**************************************************************
           * Function draws level with OpenGL into a window
           **************************************************************/
          void PLevel::draw()
          {
              
          }
          
          /**************************************************************
           * Function dumps level data into console
           * consider it as an alternative render function :D
           **************************************************************/
          void PLevel::print()
          {
              cout<<endl;
              for(unsigned i=0; i<this->width; i++)
              {
                  cout<<setfill('-')<<setw(73)<<"-"<<endl;  // prints line

                  for(unsigned j=0; j<this->height; j++)
                  {
                      PObject *obj = data[i][j]->returnFirstChild(); 
                      if(obj!=NULL) // if there is boject binded
                          obj->print(); // prints it
                      else
                          data[i][j]->print();  // otherwise, print object
                  }
                  cout<<'|'<<endl;
              }
              cout<<setfill('-')<<setw(73)<<"-"<<endl;  // prints line
              cout<<endl;  
          }
     
          /**************************************************************
           * Function dumps level data into console
           * prints type of level(wall, void, teleport, ...) 
           **************************************************************/        
          void PLevel::printLevelByType() const
          {
              cout<<endl;
              for(unsigned i=0; i<this->width; i++)
              {
                  for(unsigned j=0; j<this->height; j++)
                      data[i][j]->print(); // prints objects info
                  cout<<'|'<<endl;
              }
              cout<<endl;
          }
          
          /**************************************************************
           * Function dumps level data into console
           * prints meta data(what is on level block)
           **************************************************************/  
          void PLevel::printLevelByMeta() const
          {
              cout<<endl;
              for(unsigned i=0; i<this->width; i++)
              {
                  for(unsigned j=0; j<this->height; j++)
                  {
                      PObject *obj = data[i][j]->returnFirstChild(); 
                      if(obj!=NULL) // if there is boject binded
                          obj->print(); // prints it
                      else
                          cout<<"|     "; // otherwise, print empty
                  }
                  cout<<'|'<<endl;
              }
              cout<<endl;            
          }
          
           /**************************************************************
           * releaseLevel()
           * clear all level data from memory
           **************************************************************/          
          void PLevel::releaseLevel()
          {
              for(unsigned i=0; i<width; i++)  
              {
                  for(unsigned j=0; j<height; j++)
                  {
                      delete data[i][j];
                      data[i][j] = NULL; 
                  }
              }
              Messages::infoMessage("Level data successfully released from memory.");              
          }
 
          /**************************************************************
           * Destructor
           * clear all level data from memory
           **************************************************************/ 
          PLevel::~PLevel()
          {
              this->releaseLevel();
          }
    }
}
