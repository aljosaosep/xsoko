
#include "object.h"

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
#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
//#include "messages.h"
#include "level.h"

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
          inline int PLevel::returnNumberFromFile(ifstream &file)
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
          inline bool PLevel::checkPosition(ifstream &file)
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
          inline PTeleport *PLevel::returnTeleport(int id)
          {
              for(unsigned i=0; i<teleports.size(); i++) // loops thorough vector
                  if(teleports[i]->getId() == id)  // if teleport's id matches id we're lookin' for
                      return teleports[i];  // then return it's address
         
              return NULL; // otherwise return NULL
          }
          
           /*****************************************************************
           * Function attaches object to another element in matrix
           * releases node from original element in matrix
           * and changes indexes
           *****************************************************************/          
          inline void PLevel::reattachNode(int i, int j, int i2, int j2, PLevelObject *obj)
          {
              data[i2][j2]->attachToRoot(data[i][j]->returnFirstChild());
              data[i][j]->unlinkFirstChild();
              obj->setIndex(i2, j2);
          }
          

           /*****************************************************************
           * Function checks in player has moved all cubes to their 
           * spaces
           *****************************************************************/ 
          inline bool PLevel::isLevelDone()
          {
              for(unsigned i=0; i<this->holds.size(); i++)  // we loop thorough all holders in level
              {
                  if(this->holds[i]->returnFirstChild()==NULL) // if hold has no child
                      return false;  // level cant be done!
                  else if((dynamic_cast<PLevelObject*>(this->holds[i]->returnFirstChild()))->getId() != 2) // if hold contains something else than cube
                      return false; // level cant be done either!
              }
              
              return true; // otherwise, player won :)
          }
          
           /*****************************************************************
           * Function checks if move is possible; if it is, processes it
           *****************************************************************/
          inline bool PLevel::checkAndApply(int i2, int j2, PLevelObject *obj, PDirection dir)
          {
              int i = obj->getI(), j = obj->getJ(); // gets object indexes
              // is move absolutely possible?
              if(data[i2][j2]->isPlayerMovePossible()==1)  // it is!
              {
                  reattachNode(i, j, i2, j2, obj);  // so we just do it ;)
                  return true;
              }
              
              else if(data[i2][j2]->isPlayerMovePossible()==3)  // teleport
              {
//                  PTeleport *srcTeleport = dynamic_cast<PTeleport*>(data[i2][j2]); // cast object to teleport, so we can use teleport methods
                  int it = (dynamic_cast<PTeleport*>(data[i2][j2]))->getChildTeleport()->getI(), // get id's of child teleport(our teleport destination)
                          jt = (dynamic_cast<PTeleport*>(data[i2][j2]))->getChildTeleport()->getJ();
                  
                  if(data[it][jt]->returnFirstChild()!=NULL) // if there is object alredy on teleport
                  {
                      if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[it][jt]->returnFirstChild())))  // try to move it
                      {
                          reattachNode(i, j, it, jt, obj);   // and then move player to teleport
                          return true;
                      }
                  }
                  else  // there is no object attached to teleport, that's ok
                  {
                      reattachNode(i, j, it, jt, obj);  // so we just move player to dest teleport ;)
                      return true;
                  }
              }

              else if(data[i2][j2]->isPlayerMovePossible()==2)  // move is conditionally possible; we check children
              {
                  if(data[i2][j2]->returnFirstChild() == NULL)  // move is possible since there are no children
                  {
                      reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                      return true;
                  }
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 2)  // na polju je kocka - poskusimo premaknit!
                  {
                      // koda za premik kocke
                      if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                      {
                          reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                          return true;                         
                      }
                  }
                  
              }
              
              else if(data[i2][j2]->isPlayerMovePossible()==6)  // move is conditionally possible; we check children; thid id cubeholder case
              {                                             // only diffrence between causal conditional move and move to cubeHolder is
                                                             // that in this case, after we move cube to cube holder, we check if level has been done
                  if(data[i2][j2]->returnFirstChild() == NULL)  // move is possible since there are no children
                  {
                      reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                      cout<<"ID: "<<dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())->getId()<<endl;
                      if(this->isLevelDone())
                          Messages::infoMessage("You won!!!!! :))))");
                      return true;
                  }
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 2)  // na polju je kocka - poskusimo premaknit!
                  {
                      // koda za premik kocke
                      if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                      {
                          reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                          cout<<"ID: "<<dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())->getId()<<endl;
                          if(this->isLevelDone())
                              Messages::infoMessage("You won!!!!! :))))");
                          return true;                         
                      }
                  }
                  
                  
              }
              
              else if(data[i2][j2]->isPlayerMovePossible()==5) // bridge!
              {
                  //// TODO
             /*     reattachNode(i, j, i2, j2, obj);   // move player to bridge
                  PVoid *praznina = new PVoid;       // create new void object
                  praznina->attachToRoot(NULL);  // attach player to void
                  
              //    data[i2][j2]->releaseFirstChild();   // drop player from bridge
                  delete data[i2][j2];  // delete bridge
                  data[i2][j2] = praznina;*/
                  
              }
              

          }
          
          // gameplay related
           /*****************************************************************
           * Function moves object to antoher field if it is possible;
           * successful move returns true, unsuccessfull false
           *****************************************************************/
         bool PLevel::moveObject(PDirection dir, PLevelObject *obj)
          {
                  switch(dir)
                  {
                      case Aliases::left:
                          if(!checkAndApply(obj->getI(), obj->getJ()-1, obj, Aliases::left))
                              return false;
                          break;
                          
                      case Aliases::right:
                          if(!checkAndApply(obj->getI(), obj->getJ()+1, obj, Aliases::right))
                              return false;
                          break;  
                          
                      case Aliases::up:
                          if(!(checkAndApply(obj->getI()-1, obj->getJ(), obj, Aliases::up)))
                                  return false;
                          break;
                          
                      case Aliases::down:
                          if(!(checkAndApply(obj->getI()+1, obj->getJ(), obj, Aliases::down)))
                              return false;                      
                          break;                        
                  }
                  return true;              
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
                                      this->holds.push_back(dynamic_cast<PCubeHolder*>(data[i][j])); // adds cuneHolder to holds array
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
                                  
                                  PTeleport *teleport = new PTeleport(i, j); // create object
                                //  cout<<"Tel id: "<<teleport->getI()<<' '<<teleport->getJ()<<endl;
                                  teleport->setId(num);                // set its id
                                  data[i][j] = teleport;               // attach it on level
                                  this->teleports.push_back(teleport); // push teleport info on vector
                              }
                              
                              switch(num)
                              {                                              
                                  case PLAYER:
                                      p = new PPlayer(i, j);
                                      this->player = dynamic_cast<PPlayer*>(p); // set class player pointer to player element
                                      data[i][j]->add(p);
                                      break;
                                      
                                  case CUBE:
                                      p = new PCube(i, j);
                                      data[i][j]->add(p);
                                      break;
                                      
                                  case OW_CUBE_L:
                                      p = new POnewayCube(Aliases::left, i, j);
                                      data[i][j]->add(p);
                                      break; 
                                      
                                  case OW_CUBE_R:
                                      p = new POnewayCube(Aliases::right, i, j);
                                      data[i][j]->add(p);
                                      break; 
                                      
                                  case OW_CUBE_U:
                                      p = new POnewayCube(Aliases::up, i, j);
                                      data[i][j]->add(p);
                                      break;  
                                      
                                  case OW_CUBE_D:
                                      p = new POnewayCube(Aliases::down, i, j);
                                      data[i][j]->add(p);
                                      break;
                                      
                                  case BOMB:
                                      p = new PBomb(i, j);
                                      data[i][j]->add(p);
                                      break; 
                                      
                                  default:   // in
                                      data[i][j]->add(NULL);
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
                    //      parentTeleport->add(childTeleport);  // attach them
                          parentTeleport->setChildTeleport(childTeleport);                      
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
           * Function returns pointer to player in level
           **************************************************************/
          PPlayer* PLevel::getPlayerHandle()
          {
              return this->player;
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
          
          
          short PLevel::isPlayerMovePossible() { return 0; }  // blind function, just for overwrtie; DO NOT attempt to implement it and escpecially,
                                                              // do not use it in LEVEL class context!
    }
}
