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
#ifdef _WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include <GL/gl.h>


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



#include "object.h"
#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "level.h"
#include "renderer/particle.h"
#include "CommonStructures.h"

using namespace std;
using namespace PacGame::GameClasses::GameObjects;

namespace PacGame
{
      namespace GameClasses
      {

          /*****************************************
           PLevel constructors
           *****************************************/

          PLevel::PLevel(string filename) :
            filename(filename),  width(0), height(0), player(NULL), gameCore(new PCore),
            resourceHandle(gameCore->getResources()), endgameFlag(false), fnt(new Font("font"))
          {
              fnt->setColor(255,255,0);
              fnt->setSize(15);
          }
 
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
                  buff[1] = '\0';  // terminate string
 
              return atoi(buff);  // return number read from file, integer
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
              
              if(data[i][j]->getId()==BRIDGE)
              {
                  if(obj->getId() == 1)
                  {
                      if(data[i][j]->isActiveBomb()){
                          for(unsigned int k=0;k<bombs.size();k++)
                              if(bombs[k]->i == i && bombs[k]->j == j){
                                  delete bombs[k];
                                  bombs.erase(bombs.begin()+k);
                              }
                      }
                      delete data[i][j];
                      data[i][j] = new PVoid;
                  }
              }
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

                  else if(((dynamic_cast<PLevelObject*>(this->holds[i]->returnFirstChild()))->getId() < 2) 
                          || ((dynamic_cast<PLevelObject*>(this->holds[i]->returnFirstChild()))->getId() >6))
                      return false; // on this holder there is no valid cubes (valid cubes has id's: 2-normal, 3...6-oneway cubes)
              }
              
              return true; // otherwise, player won :)
          }
          
           /*****************************************************************
           * Function checks if move is possible; if it is, processes it
           *****************************************************************/
          inline bool PLevel::checkAndApply(int i2, int j2, PLevelObject *obj, PDirection dir)
          {
            //  int delta_i = 0, delta_j = 0; // for camera rotation at teleport event
              // i2 and j2 are indexes of field, we re checking; so if on field with idexes i2 and j2 is empty
              // (has nothing attached to it), then we move our object(obj) to i2, j2
              
              // checks if indexes are valible; it prevents index-out-of-range error
              if((unsigned)i2 >  (this->width-1)|| i2<0 || (unsigned)j2 > (this->height-1) || j2<0)
              {
                  Messages::errorIndexOutOfRange();
                  return false;
              }
              
              int i = obj->getI(), j = obj->getJ(); // gets source object indexes, object, that we're moving
//              cout<<"indexes: "<<i<<' '<<j<<endl;
              
              // is move absolutely possible?
              if(data[i2][j2]->isPlayerMovePossible()==1)  // it is!
              {
//                  cout<<"move possible = 1: direct reattach"<<endl;
                  reattachNode(i, j, i2, j2, obj);  // so we just do it ;) we move object from indexes i, j to i2, j2
                  return true;
              }
              
              //////// TELEPORT
              else if(data[i2][j2]->isPlayerMovePossible()==3)  
              {
//                  cout<<"Teleport: "<<endl;
                  // it - I index of dest teleport
                  // jt-  J index of dest teleport
                  int it = (dynamic_cast<PTeleport*>(data[i2][j2]))->getChildTeleport()->getI(), 
                      jt = (dynamic_cast<PTeleport*>(data[i2][j2]))->getChildTeleport()->getJ();
                  
//                  cout<<"Child Teleport indexes: "<<it<<' '<<jt<<endl;
                  
                  
                  if(data[it][jt]->returnFirstChild()!=NULL) // if there is object alredy on teleport
                  {
                      // code prevents crashing, if player attempts to teleport object to tepelport, where is
                      // player currently located
                      if(dynamic_cast<PLevelObject*>(data[it][jt]->returnFirstChild())->getId() == 1)
                          return false;
                      
//                      cout<<"First Teleport child not null! Attempting to move: ... "<<it<<' '<<jt<<endl;
                      // if obj is player, attempt to move obj at dest teleport
                      if( (obj->getId() == 1 ) && this->moveObject(dir, dynamic_cast<PLevelObject*>(data[it][jt]->returnFirstChild())))  // try to move it
                      {
                          adjustCameraAtTeleport(it, jt, obj, dir);
                          
                          reattachNode(i, j, it, jt, obj);   //  then move player to teleport
                          return true;
                      }
                  }
                  else  // there is no object attached to teleport, that's ok
                  {
                      if(obj->getId() == 1) // check if it is player
                        adjustCameraAtTeleport(it, jt, obj, dir);
                     
 //                     cout<<"Cool, no object on teleport, so beam me up scotty!"<<it<<' '<<jt<<endl;
                      reattachNode(i, j, it, jt, obj);  // so we just move player to dest teleport ;)
                      return true;
                  }
              }  /// END OF TELEPORT SECTION

              // CONDITIONALLY POSSIBLE MOVES
              else if(data[i2][j2]->isPlayerMovePossible()==2  && (!data[i2][j2]->isActiveBomb()))  // move is conditionally possible; we check children
              {
  //                cout<<"Conditially possible move."<<endl;
                  if(data[i2][j2]->returnFirstChild() == NULL)  // move is possible since there are no children
                  {
  //                    cout<<"It seems that dest has no children, so I will directly reattach node."<<endl;
                      reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                      return true;
                  }
                  
                  // case, there is normal cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 2 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  {
  //                    cout<<"Hell, there is someting there, attempting to move..."<<endl;
                      // CUBE-MOVE CODE GOES HERE
                      if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                      {
  //                        cout<<"Obj moved, now I am reattaching..."<<endl;
                          reattachNode(i, j, i2, j2, obj);   // it is, we move object
                          return true;   
                      }
                  }  
                  
                  // case, there is oneway cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 3 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  { 
//                      cout<<"Hell, there is someting there, oneway cube, attempting to move..."<<endl;
                      if(dynamic_cast<POnewayCube*>(data[i2][j2]->returnFirstChild())->getDirection()==dir)
                      {
                          // CUBE-MOVE CODE GOES HERE
                          if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                          {
//                            cout<<"Obj moved, now I am reattaching..."<<endl;
                              reattachNode(i, j, i2, j2, obj);   // it is, we move object
                              return true;   
                          }
                      }
                  } 
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 4) // there is a bomb
                  {
                    //  cout<<"idproblem"<<endl;
                      if(obj->getId()==1) // is object a player ?
                      {
                      //    data[i2][j2]->releaseFirstChild(); // release picking bomb object
                      //    data[i2][j2]->unlinkFirstChild();
                          data[i2][j2]->releaseFirstChildObject();
                          this->player->incBombs();  // increase bombs
                          reattachNode(i, j, i2, j2, obj);   // move
                          cout<<"St. bomb:"<<this->player->getBombs()<<endl;
                          return true;
                      }
                  }
              }    
          /*    else if(1)
              {
              Aliases::PDirection dirrr = dynamic_cast<POnewayFloor*>(data[i2][j2])->getDirection();
              cout<<"stupid"<<endl;
              }*/

              // CONDITIONALLY POSSIBLE MOVE - ONEWAY FLOOR    //TODO:    FFIIIXX
              else if((data[i2][j2]->isPlayerMovePossible()==5) && (dir ==  (dynamic_cast<POnewayFloor*>(data[i2][j2])->getDirection())))  // move is conditionally possible; we check children
              {
                  if(data[i2][j2]->returnFirstChild() == NULL)  // move is possible since there are no children
                  {
                      reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                      return true;
                  }
                  
                  // case, there is normal cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 2 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  {
                      // CUBE-MOVE CODE GOES HERE
                      if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                      {
                          reattachNode(i, j, i2, j2, obj);   // it is, we move object
                          return true;   
                      }
                  }  
                  
                  // case, there is oneway cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 3 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  { 
                      if(dynamic_cast<POnewayCube*>(data[i2][j2]->returnFirstChild())->getDirection()==dir)
                      {
                          // CUBE-MOVE CODE GOES HERE
                          if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                          {

                              reattachNode(i, j, i2, j2, obj);   // it is, we move object
                              return true;   
                          }
                      }
                  } 
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 4) // there is a bomb
                  {
                    //  cout<<"idproblem"<<endl;
                      if(obj->getId()==1) // is object a player ?
                      {
                      //    data[i2][j2]->releaseFirstChild(); // release picking bomb object
                          data[i2][j2]->releaseList();
                          this->player->incBombs();  // increase bombs
                          reattachNode(i, j, i2, j2, obj);   // move
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
                      if(this->isLevelDone())
                      {
                          this->endgameFlag = true;
                          Messages::infoMessage("You won!!!!! :))))");
                      }
                      return true;
                  }
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 2 && (obj->getId()==1))  // na polju je kocka - poskusimo premaknit!
                  {
                      // koda za premik kocke
                      if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                      {
                          reattachNode(i, j, i2, j2, obj);   // so we do it ;)
                          if(this->isLevelDone())
                          {
                              this->endgameFlag = true;
                              Messages::infoMessage("You won!!!!! :))))");
                          }
                          return true;                         
                      }
                  } // case, there is oneway cube
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 3 && (obj->getId()==1))  // there is cube on the field, we attemt to move it
                                                                                                              // but we can move it only, if obj is player(do it has id=1)
                  {
                      cout<<"Hell, there is someting there, oneway cube, attempting to move..."<<endl;
                      if(dynamic_cast<POnewayCube*>(data[i2][j2]->returnFirstChild())->getDirection()==dir)
                      {
                          // CUBE-MOVE CODE GOES HERE
                          if(this->moveObject(dir, dynamic_cast<PLevelObject*>(data[i2][j2]->returnFirstChild())))
                          {
                            cout<<"Obj moved, now I am reattaching..."<<endl;
                              reattachNode(i, j, i2, j2, obj);   // it is, we move object
                              return true;
                          }
                      }
                  }
                  else if(data[i2][j2]->returnFirstChild()->isPlayerMovePossible() == 4) // there is a bomb
                  {
                    //  cout<<"idproblem"<<endl;
                      if(obj->getId()==1) // is object a player ?
                      {
                      //    data[i2][j2]->unlinkFirstChild();
                          data[i2][j2]->releaseFirstChildObject(); // release picking bomb object
                          this->player->incBombs();  // increase bombs
                          reattachNode(i, j, i2, j2, obj);   // move
                          cout<<"St. bomb:"<<this->player->getBombs()<<endl;
                          return true;
                      }
                  }
              }

              
              // is there empty space?
          //    else if(data[i2][j2]->returnFirstChild()==NULL)
        //      {
                  // yes! game over, haha!
              /*    cout<<"Is not a bug, you fall into space - or you pushed cube into space, so it's game over!!!! :p"<<endl;
                  data[i][j]->attachToRoot(NULL);  // we make cube or player vanish
                 // delete [] this->player;   // todo: delete player obj without segmentation fault!
                  this->endgameFlag = true;  // and we make game end */

      //        }
              
              return false; // to avoid warning
          }

          // gameplay related
           /*****************************************************************
           * Function moves object to antoher field if it is possible;
           * successful move returns true, unsuccessfull false
           *****************************************************************/
         bool PLevel::moveObject(PDirection dir, PLevelObject *obj)
          {
                  int toI, toJ, dirFacing;
                  switch(dir)
                  {
                        //set destination and direction
                      case Aliases::left:
                              toI = obj->getI();
                              toJ = obj->getJ()-1;
                              dirFacing = PL_OBJECT_FACE_LEFT;
                          break;
                          
                      case Aliases::right:
                              toI = obj->getI();
                              toJ = obj->getJ()+1;
                              dirFacing = PL_OBJECT_FACE_RIGHT;
                          break;  
                          
                      case Aliases::up:    
                              toI = obj->getI()-1;
                              toJ = obj->getJ();
                              dirFacing = PL_OBJECT_FACE_UP;
                          break;
                          
                      case Aliases::down:              
                              toI = obj->getI()+1;
                              toJ = obj->getJ();
                              dirFacing = PL_OBJECT_FACE_DOWN;   
                          break;                        
                  }
                  if(checkMoveTo(toI, toJ, obj, dir))
                  {
                        obj->moveObject(dirFacing);
                        reattachNode(obj->getI(), obj->getJ(), toI, toJ, obj);
                        moves++;
                        return true;
                 }else
                        return false;              
          }
          
          bool PLevel::checkMoveTo(int toI, int toJ,PLevelObject* obj, PDirection dir)
          {
                // check if the move is within level bounds
               if((unsigned)toI >  (this->width-1)|| toI<0 || (unsigned)toJ > (this->height-1) || toJ<0)
              {
                  Messages::errorIndexOutOfRange();
                  return false;
              }
              // if there is no way we could move there
               if(data[toI][toJ]->isPlayerMovePossible() == 0)  
                  return false;
                
                // if the space is empty, move freely
              if(data[toI][toJ]->isPlayerMovePossible() == 1)  
                  return true;
                  
                  // if the default PLevelObject method is used, then it is a problem
              if(data[toI][toJ]->isPlayerMovePossible() == -1)
              {
                      cout<<"!!! default isPlayerMovePossible used !!!"<<endl;
                      return false;
              }  
          }
          
          void activateFloor(int i, int j)
          {
                  
          }
          
          // level functions implementation goes here! ;)
          
          /**************************************************************
           * Function reads file data form file, given by filename 
           * variable into level class
           **************************************************************/
          // function is work in progress, started by Aljosa june 29, 2008
          bool PLevel::reloadLevel()
          {
              int tmsize; // teleport matrix size
              PObject *p = NULL; // our pobject pointer; for creating dynamic objects
              ifstream level; // file handle
              level.open(this->filename.c_str(), ios::in);  // opens level
              
              
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
                              // teleport case
                              if(num >= 9) // if it is > 11, then it is an teleport id
                              {
                                  data[i][j] = new PTeleport(i, j, this->gameCore, num); // create object
                                  
                                  if((resourceHandle->getTextureResource(TELEPORT_RES))==NULL)  // texture isn't in memory yet?
                                      resourceHandle->loadTextureResource(TELEPORT_RES, "test.tga");  // load it!

                                  (dynamic_cast<PTeleport*>(data[i][j]))->setId(num);                // set its id
                            //      (dynamic_cast<PTeleport*>(data[i][j]))->
                              //    data[i][j] = teleport;               // attach it on level
                                  this->teleports.push_back(dynamic_cast<PTeleport*>(data[i][j])); // push teleport info on vector
                              }
                              
                              switch(num)  // if it is, we create suitable object
                              {
                                  case FLOOR:
                                      data[i][j] = new PFloor(this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                            resourceHandle->loadTextureResource(FLOOR_RES, "floor.tga");  // load it!
                                      
                                      break;
                                      
                             /*     case OW_FLOOR:
                                      data[i][j] = new POnewayFloor(this->gameCore);
                                      break;*/
                                      
                                  case S_WALL:
                                      data[i][j] = new PSolidWall(this->gameCore);   
                                      if((resourceHandle->getTextureResource(S_WALL_RES))==NULL)
                                          resourceHandle->loadTextureResource(S_WALL_RES, "wall.tga"); 

                                      break;
                                      
                                  case BRIDGE:
                                      data[i][j] = new PBridge(this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(BRIDGE_RES))==NULL)  // texture isn't in memory yet?
                                            resourceHandle->loadTextureResource(BRIDGE_RES, "bridge.tga");  // load it!
                                      
                                      break;  
                                      
                                  case VOID:
                                      data[i][j] = new PVoid;
                                      break;
                                      
                                  case CUBE_PLACE:
                                      data[i][j] = new PCubeHolder(this->gameCore);
                                      this->holds.push_back(dynamic_cast<PCubeHolder*>(data[i][j])); // adds cuneHolder to holds array
                                      if((resourceHandle->getTextureResource(CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(CUBE_RES, "crate.tga");  // load it!
                                      break;    
                                      
                                  case OW_FLOOR_L:
                                      data[i][j] = new POnewayFloor(this->gameCore, 5);
                                      dynamic_cast<POnewayFloor*>(data[i][j])->setDirection(Aliases::left);
                                   //   data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_FLOOR_RES, "onewayfloor.tga");  // load it!
                                      
                                  //    second_matrix[i][j] = 8;
                                 //     data[i][j]->add(NULL);
                                      break;
                                      
                                  case OW_FLOOR_R:
                                      data[i][j] = new POnewayFloor(this->gameCore, 6);
                                      dynamic_cast<POnewayFloor*>(data[i][j])->setDirection(Aliases::right);
                                  //    data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_FLOOR_RES, "onewayfloor.tga");  // load it!
                                      
                                  //    second_matrix[i][j] = 9;
                                 //     data[i][j]->add(NULL);
                                      break;
                                      
                                      
                                  case OW_FLOOR_U:
                                      data[i][j] = new POnewayFloor(this->gameCore, 7);
                                      dynamic_cast<POnewayFloor*>(data[i][j])->setDirection(Aliases::up);
                                  //    data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_FLOOR_RES, "onewayfloor.tga");  // load it!
                                      
                                 //     second_matrix[i][j] = 10;
                                 //     data[i][j]->add(NULL);
                                      break;
                                      
                                  case OW_FLOOR_D:
                                      data[i][j] = new POnewayFloor(this->gameCore, 8);
                                      dynamic_cast<POnewayFloor*>(data[i][j])->setDirection(Aliases::down);
                                 //     data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_FLOOR_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_FLOOR_RES, "onewayfloor.tga");  // load it!
                                      
                                //      second_matrix[i][j] = 11;
                                //      data[i][j]->add(NULL);
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

                              
                              switch(num)
                              {                                              
                                  case PLAYER:
                                      p = new PPlayer(i, j, this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(PLAYER_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(PLAYER_RES, "player.tga");  // load it!
                                      if((resourceHandle->getModelResource(PLAYER_RES)) == NULL) // model isn't in memory yet?
                                      {
                                          resourceHandle->loadModelResource(PLAYER_RES, "data/player.md2"); // load it!
                                          resourceHandle->getModelResource(PLAYER_RES)->SetTexture(resourceHandle->getTextureTesourceId(PLAYER_RES)); // set the texture
                                       }
                                      
                                      this->player = dynamic_cast<PPlayer*>(p); // set class player pointer to player element
                                      data[i][j]->add(p);
                                      second_matrix[i][j] = PLAYER;
                                      
                                      break;
                                      
                                  case CUBE:
                                      p = new PCube(i, j, this->gameCore);
                                      
                                      if((resourceHandle->getTextureResource(CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(CUBE_RES, "crate.tga");  // load it!

                                      data[i][j]->add(p);
                                      second_matrix[i][j] = CUBE;
                                      break;
                                      
                                  case OW_CUBE_L:
                                      p = new POnewayCube(Aliases::left, i, j, 3, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "onewaycube.tga");  // load it!
                                      
                                      second_matrix[i][j] = OW_CUBE_L;
                                      break; 
                                      
                                  case OW_CUBE_R:
                                      p = new POnewayCube(Aliases::right, i, j, 4, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "onewaycube.tga");  // load it!
                                      
                                      second_matrix[i][j] = OW_CUBE_R;
                                      break; 
                                      
                                  case OW_CUBE_U:
                                      p = new POnewayCube(Aliases::up, i, j, 5, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "onewaycube.tga");  // load it!
                                      
                                      second_matrix[i][j] = OW_CUBE_U;
                                      break;  
                                      
                                  case OW_CUBE_D:
                                      p = new POnewayCube(Aliases::down, i, j, 6, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "onewaycube.tga");  // load it!
                                      
                                      second_matrix[i][j] = OW_CUBE_D;
                                      break;
                                      
                                  case BOMB:
                                      p = new PBomb(i, j, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(BOMB_RES))==NULL)  // texture isn't in memory yet?
                                               resourceHandle->loadTextureResource(BOMB_RES, "bomb.tga");  // load it!
                                      
                                      second_matrix[i][j] = BOMB;
                                      break; 
                                      
                                  case U_WALL:
                                      p = new PUnsolidWall(i,j,this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(U_WALL_RES))==NULL)
                                          resourceHandle->loadTextureResource(U_WALL_RES, "unsolidwall.tga"); 
                                      
                                      second_matrix[i][j] = U_WALL;
                                      break; 

                                      
                                  default:   // in
                                      data[i][j]->add(NULL);
                                      second_matrix[i][j] = 0;
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
                      int tmp_i = parentTeleport->getI();
                      int tmp_j = parentTeleport->getJ();
                      second_matrix[tmp_i][tmp_j] = parentTeleport->getId();
                      
                      
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
                  
                  // camera setup
                  
                  // set the camera position
                 gameCore->getCamera()->fitCameraToLevel(width, height);
                  // rotate the camera above the player
                  gameCore->getCamera()->rotateViewX( 0.5f * (player->getJ() - ((int)width-1)/2));
                  gameCore->getCamera()->rotateViewY( 0.5f * (player->getI() - ((int)height-1)/2));
                  
                  // teleports.clear(); // clear teleport vector, since they are by now in memory and no longer needed
                  break;   
              }
              
              Messages::infoMessage("Level data successfully loaded from file.");
              level.close();
              return true; // everything went ok
          }
          
          bool PLevel::saveStateToFile(string file_name)
          {
              
              // cout << "test" << endl;
              ofstream file (file_name.c_str());
              if (file.is_open()) {
                  
                  file << this->width << " " << this->height << endl; // 1st matrix dimension
                  
                  // write 1st matrix data to file
                  for (unsigned i=0; i<this->width; i++)
                  {
                      for (unsigned j=0; j<this->height; j++) {
                          file << data[i][j]->getId() << " ";
                      }
                      file << endl;
                  }
                  
                  file << "+" << endl;
                  
                  for (unsigned i=0; i<this->width; i++)
                  {
                      for (unsigned j=0; j<this->height; j++) {
                          file << second_matrix[i][j] << " ";
                      }
                      file << endl;
                  }
                  
                  file << "+" << endl;
                  
                  file << teleports.size() << endl;
                  
                  for(int i=0; i<(int)teleports.size(); i++)
                  {
                      PTeleport* tmp = teleports.at(i);
                      PTeleport* child = tmp->getChildTeleport();

                      file << tmp->getId() << " " << child->getId() << endl;
                  }
                  
                  file.close();
                  return true;
                  
              } else {
                  cout << "NAPAKA: datoteke ni mogoče ustvariti!" << endl;
                  return false;
              }
              
          }
          
          /**************************************************************
           * Function which reset level data 
           **************************************************************/
          bool PLevel::reset()
          {
              releaseLevel();
              teleports.clear();
              holds.clear();
              endgameFlag = false;
              moves = 0;
              return reloadLevel();
          }
          
           /**************************************************************
           * Function returns pointer to player in level
           **************************************************************/
          PPlayer* PLevel::getPlayerHandle()
          {
              return this->player;
          }
  
          /**************************************************************
           * Function returns pointer to renderer object
           **************************************************************/
          bool PLevel::getEndgameFlag()
          {
              return this->endgameFlag;
          }
          
          
          /**************************************************************
           * Function initiates level
           * work in progress
           **************************************************************/
          bool PLevel::initialize()
          {
              //data = new
              if(!this->reloadLevel())
              {
                  Messages::errorMessage("Level loading from file failed.");
                  return 0;
              }
              // by now, matrix should be initialized with proper classes, if it went ok this far
              
              // try to initialize core
              if(!this->gameCore->init())
              {
                  this->gameCore->release();
                  Messages::initMessage("Game core", false);
              }
              else
                  Messages::initMessage("Game core", true);
              
              // temporary, dump state
              this->print();

              starttime = glfwGetTime();
              moves = 0;
              return true; // everything went ok
          }
          
          /**************************************************************
           * Function draws level with OpenGL into a window
           **************************************************************/
          void PLevel::draw()
          {
              glEnable(GL_LIGHTING);
              glPushMatrix();
                  for(unsigned i=0; i<this->width; i++)
                  {
                      for(unsigned j=0; j<this->height; j++)
                      {
                          PLevelObject *obj = (PLevelObject*) data[i][j]->returnFirstChild(); 
                          if(obj!=NULL) // if there is boject binded
                          {
                              glPushMatrix();
                              glTranslatef(obj->getRealI(), obj->getRealJ(), 0.0);
                              obj->draw(); // prints it
                              
                              glPopMatrix();
                              if (static_cast<PLevelObject*>(obj)->getId() == PLAYER) // if child is player, draw also paren
                              {
                                   glPushMatrix();
                                   glTranslatef(float(i),float(j),0.0);
                                  data[i][j]->draw();
                                  glPopMatrix();
                              }
                          }
                          else
                              if(data[i][j]!=NULL)
                              {
                                  glPushMatrix();
                                  glTranslatef((float)i, (float)j, 0.0);
                                  data[i][j]->draw();  // otherwise, print object
                                  glPopMatrix();
                              }
                          
                          // draw activated bombs, if there are any
                          if(this->bombs.size()>0)
                          {
                              for(unsigned i=0; i<bombs.size(); i++)
                              {
                                  
                                  glPushMatrix();
                                  glTranslatef((float)this->bombs[i]->i, (float)this->bombs[i]->j, 0.0);
                                  glColor3f(1.0, 0.0, 0.0);
                                  glBindTexture(GL_TEXTURE_2D, this->resourceHandle->getTextureTesourceId(BOMB_RES));
                                  this->gameCore->getRenderer()->drawCube(0.0, 0.0, 0.5);
                                  glPopMatrix();
                              }
                          }
                      }
                  }
              glPopMatrix();
              glDisable(GL_LIGHTING);

              //Change mode for text
              glMatrixMode(GL_PROJECTION);  // Change Matrix Mode to Projection
              glLoadIdentity();             // Reset View
              glOrtho(0, 800, 0, 600, 0, 100);
              glMatrixMode(GL_MODELVIEW);   // Change Projection to Matrix Mode
              glLoadIdentity();

              glTranslatef(0, 600, -0.5);

              if(!endgameFlag)
                  time = glfwGetTime();
              fnt->writeText(10,-30,"Elapsed time: "+Functions::toString<int>((int)(time-starttime)));
              fnt->writeText(170,-30,"Moves: "+Functions::toString<int>(moves));
          }
          /****************************************
           * animates the objects on the field
           * **************************************/
          void PLevel::animate(double time)
          {
                  for(unsigned i=0; i<this->width; i++)
                  {
                      for(unsigned j=0; j<this->height; j++)
                      {
                              PLevelObject *obj = (PLevelObject*) data[i][j]->returnFirstChild(); 
                              if(obj != NULL)
                              {
                                obj->animate(time);
                                }
                      }
                      
              }
          }
          
          bool PLevel::loadLevelFromFile(string filename){
              this->filename = filename;
              this->endgameFlag = false;
              starttime = glfwGetTime();
              return reset();
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
                      PLevelObject *obj = dynamic_cast<PLevelObject*>(data[i][j]->returnFirstChild()); 
                      if(obj!=NULL) // if there is boject binded
                      {
                          obj->print(); // prints it
                     //     cout<<"ACTIVE BOMB: "<<obj->isActiveBomb()<<false;
                      }
                      else
                          if(data[i][j]!=NULL)
                            
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
              delete player;
              Messages::infoMessage("Level data successfully released from memory.");              
          }
          
          
          unsigned PLevel::getWidth()
          {
              return this->width;
          }
          
          unsigned PLevel::getHeight()
          {
              return this->height;
          }
          
           /**************************************************************
           * Dropped Bombs
           * functions manages them
           **************************************************************/ 
          void PLevel::processBombs(double current_time)
          {
                if(this->bombs.size() != 0)  // are there any bombs to trigger?
                {
                    // get addres of bomb that was released first(is first in the list)
                    PDroppedBomb* firstDroppedBomb = this->bombs[0];
                    // apparently they are!
                    if(int(current_time-firstDroppedBomb->dropTime+0.5) == 3)  // is it time to trigger bomb yet?
                    {    
                        // check bomb surrounding fields
                        this->checkAndApplyBombBlast(firstDroppedBomb->i-1, firstDroppedBomb->j);
                        this->checkAndApplyBombBlast(firstDroppedBomb->i+1, firstDroppedBomb->j);
                        this->checkAndApplyBombBlast(firstDroppedBomb->i, firstDroppedBomb->j-1);
                        this->checkAndApplyBombBlast(firstDroppedBomb->i, firstDroppedBomb->j+1);
                        
                        // remove first dropped bomb
                        delete bombs[0];
                        this->bombs.erase(this->bombs.begin());
                        data[firstDroppedBomb->i][firstDroppedBomb->j]->toogleBombActivity();
                    }
                }              
          }
          
          bool PLevel::addDroppedBomb(int i, int j)
          {
              if(!data[i][j]->isActiveBomb())
              {
                  cout<<"I can attach bomb here ;)"<<endl;
            //      data[i][j]->attachToRoot(new PacGame::GameClasses::GameObjects::PDetonatedBomb());
                  data[i][j]->toogleBombActivity();
                  this->bombs.push_back(new PDroppedBomb(i, j));
                  return true;
              }
              return false;
          }
          
          void PLevel::checkAndApplyBombBlast(int i, int j)
          {
       //       PacGame::RenderMaschine::PParticleEngine particle(i*2.0, j*2.0, -10.0);
        //      (10.05, -11.4, 29.3);
        //      particle.process(100);
              if((unsigned)i >  (this->width-1)|| i<0 || (unsigned)j > (this->height-1) || j<0)
              {
                  Messages::errorIndexOutOfRange();
                  return;
              }
              if(data[i][j]->returnFirstChild() != NULL)
              {
                  
                  if((dynamic_cast<PLevelObject*>(this->data[i][j]->returnFirstChild())->getId())==U_WALL)  // is there unsolidWall ?
                  {
                      data[i][j]->releaseFirstChildObject();
                  } 
              }
          }

          void PLevel::adjustCameraAtTeleport(int it, int jt, PLevelObject *obj, PDirection dir)
          {
              int delta_i = (int)this->data[it][jt]->getI() - (int)obj->getI()  ;
              int delta_j = (int)this->data[it][jt]->getJ() - (int)obj->getJ()  ; // 0.5

              switch (dir)
              {
                  case Aliases::up:
                      delta_i ++;
                      break;

                  case Aliases::down:
                      delta_i --;
                      break;

                  case Aliases::left:
                      delta_j ++;
                      break;

                  case Aliases::right:
                      delta_j --;
                      break;
              }

              this->gameCore->getCamera()->rotateViewX(0.5,  delta_j );
              this->gameCore->getCamera()->rotateViewY(0.5, -delta_i );
          }
          
          
          ///// temporary?
          PCore* PLevel::getGameCoreHandle()
          {
              return this->gameCore;
          }
 
          /**************************************************************
           * Destructor
           * clear all level data from memory
           **************************************************************/ 
          PLevel::~PLevel()
          {
              this->gameCore->deinit();
              this->releaseLevel();
              delete fnt;
          }
          
          
          short PLevel::isPlayerMovePossible() { return 0; }  // blind function, just for overwrtie; DO NOT attempt to implement it and escpecially,
                                                              // do not use it in LEVEL class context!
    }
}
