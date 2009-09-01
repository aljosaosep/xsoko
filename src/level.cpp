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
                  if(obj->getId() == PLAYER)
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

                  else if(((dynamic_cast<PLevelObject*>(this->holds[i]->returnFirstChild()))->getId() & CUBE) == 0)
                      return false; // on this holder there is no valid cubes (valid cubes have the CUBE bits set
              
              }
              
              return true; // otherwise, player won :)
          }
          
          /******************************************************************
           *  setButtonFlag
           *  resetButtonFlag
           * 
           * The set function sets the button flag and reset releases it.
           * This way we can remember whih buttons are down and which up.
           ******************************************************************/
           void PLevel::setButtonFlag(int flag)
           {
                   button_flags = flag | button_flags;
                   if((button_flags ^ flag) == 0) // the status of button_flags before adding this flag
                   {
                           switch(flag)
                           {
                                case KB_UP:
                                        this->moveObject(Aliases::up, this->getPlayerHandle());
                                        break;
                                case KB_LEFT:
                                        this->moveObject(Aliases::left, this->getPlayerHandle());
                                        break;
                                case KB_DOWN:
                                        this->moveObject(Aliases::down, this->getPlayerHandle());
                                        break;
                                case KB_RIGHT:
                                        this->moveObject(Aliases::right, this->getPlayerHandle());
                                        break;
                        }
                   }
           }
           
           void PLevel::resetButtonFlag(int flag)
           {
                   button_flags = button_flags &  (!flag);
           }

          // gameplay related
           /*****************************************************************
           * moveObject
           * Checks object, his current position and his
           * destination, to try to move it. 
           * A successful move return true, otherwise it returns false.
           *****************************************************************/
         bool PLevel::moveObject(PDirection dir, PLevelObject *obj)
          {
                  int toI, toJ, dirFacing;
                
                  // first the object itself must be movable
                  if(obj->isPlayerMovePossible(dir) == 0)
                  {
                        return false;  
                  }
                  
                  // cant move in a direction the floor does not allow
                  short floor_id = data[obj->getI()][obj->getJ()]->getId();
                  // check if its a one way floor
                  if((floor_id == 5) || (floor_id == 6) || (floor_id == 7) || (floor_id == 8))
                  {
                          // check if the direction doesn't match
                          if(static_cast<POnewayFloor*>(data[obj->getI()][obj->getJ()])->getDirection() != dir )
                                return false;
                  }
                  
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
                  // the object can be moved in the wanted direction
                  if(checkMoveTo(toI, toJ, obj, dir))
                  {
                        obj->moveObject(dirFacing | PL_OBJECT_MOVE);
                        reattachNode(obj->getI(), obj->getJ(), toI, toJ, obj);
                        moves++;
                        return true;
                 }else
                 {
                         // the object can't be moved, it will just turn in the wanted direction 
                        obj->moveObject(dirFacing);
                        return false; 
                } 
          }
          
          /***********************************************
           * chechMoveTo
           * Checks the destination of an object.
           * Tries to clear the path by moving 
           * cubes.
           * Returns true if its free, false if there is something
           * in the way.
           * **********************************************/
          bool PLevel::checkMoveTo(int toI, int toJ,PLevelObject* obj, PDirection dir)
          {
              
                  
                // check if the move is within level bounds
               if((unsigned)toI >  (this->width-1)|| toI<0 || (unsigned)toJ > (this->height-1) || toJ<0)
              {
                  Messages::errorIndexOutOfRange();
                  return false;
              }
              short is_move_possible = data[toI][toJ]->isPlayerMovePossible(dir);
              
                // if the default PLevelObject method is used, then it is a problem
              if(is_move_possible == -1)
              {
                      cout<<"!!! default isPlayerMovePossible used !!!"<<endl;
                      return false;
              }
              
              // if there is no way we could move there
               if(is_move_possible == 0)  
                  return false;
                  
               // if the space is empty, move freely
              if(is_move_possible & 1)  
                  return true;
                
                // we have teleport, object move, and pick up left
                // we can have all three or just one of them
                // if one succeeds, but then next fails, the one that succeeded
                // needs to be undone 
                
                // we stat with move and pick up, since these are the easyest to undo
                // teleport is left for last, so we never need to undo it
                
                PLevelObject* moved_object = NULL;
                // first an object must be moved
                if(is_move_possible & 2)
                {
                        // only player is capable of moving other objects
                        if(obj->getId() == PLAYER)
                        {
                                moved_object =  (PLevelObject*)data[toI][toJ]->returnFirstChild();
                                // if we can't move the object, we can stop right here
                                if( !moveObject(dir, moved_object) )
                                        return false;
                                
                                
                        }else
                                return false;
                }
                
                bool picked_up = false;
                 // we have a bomb, or other pickup object
                if(is_move_possible & 4)
                {
                        // only player can pick up objects
                        if(obj->getId() == PLAYER)
                        {
                                 picked_up = true;
                                   data[toI][toJ]->releaseFirstChildObject();
                                this->player->incBombs();  // increase bombs
                         }else
                                return false;
                        // no need to undo any moving, if we couldn't pick it up, we couldn't have moved it either
                }
                
                // its a teleport
                if(is_move_possible & 8)
                {
                        
                        // we get the destination coordinates
                        int it = (static_cast<PTeleport*>(data[toI][toJ]))->getChildTeleport()->getI(), 
                                jt = (static_cast<PTeleport*>(data[toI][toJ]))->getChildTeleport()->getJ();
                        
                        
                        
                        // the object at the other side
                        PLevelObject* otherObject = static_cast<PLevelObject*>(data[it][jt]->returnFirstChild());
                        
                        // no object, can teleport safely
                        if(otherObject == NULL)
                        {
                                return true;
                        }else // we have to try and move the object on the other side in the appropriate direction
                        if(obj->getId() == PLAYER) // only player can move objects
                        {
                                if(moveObject(dir,otherObject))
                                {
                                        return true;
                                }
                                        
                                // UNDO
                                // If the player couldn't have moved the object on the other side of the teleport,
                                // than any moving from before needs to be undone
                                
                                if(moved_object != NULL)
                                {
                                         reattachNode(moved_object->getI(), moved_object->getJ(), toI, toJ, moved_object);
                                }
                                
                                        
                        }
                        
                        return false;
                        
                }
                return true;
          }
          
          /***************************************
           * activateFloor
           * The function activates special 
           * floors like teleport or cube holders.
           * *************************************/
          void PLevel::activateFloor(int i, int j)
          {
                  short floor_id = data[i][j]->getId();
                  // do we have a teleport to activate
                  if(floor_id >= 9)
                  {
                                int cameraAdjustX, cameraAdjustY;
                  
                  
                          // we get the destination teleport, and the object to teleport
                           PTeleport* destination = static_cast<PTeleport*>(data[i][j])->getChildTeleport();
                           PLevelObject* object = static_cast<PLevelObject*>(data[i][j]->returnFirstChild());
                           
                           destination->attachToRoot(data[i][j]->returnFirstChild());
                           data[i][j]->unlinkFirstChild();
                           int it = destination->getI(),
                                jt =destination->getJ();
                                
                            cameraAdjustX = jt - object->getJ();   
                            cameraAdjustY = - it + object->getI();
                                
                           object->setIndex(it, jt);
                           object->setRealI((float)it);
                           object->setRealJ((float)jt);
                          // PDirection dir = Aliases::left;
                          // adjustCameraAtTeleport(it, jt, object, dir);
                          // adjust the camera
                          gameCore->getCamera()->rotateViewX((float)cameraAdjustX*0.5);
                        gameCore->getCamera()->rotateViewY((float)cameraAdjustY*0.5);
                           
                  }else
                  if(floor_id == CUBE_PLACE)// if we put a cube in its place
                  {
                          if(this->isLevelDone())
                          {
                              this->endgameFlag = true;
                              Messages::infoMessage("You won!!!!! :))))");
                          }
                  }else
                  if(((PLevelObject*) data[i][j]->returnFirstChild())->getId() == PLAYER) // if the child object is a player
                  {
                        if(button_flags != 0)// if we are holding down the button, we want still to move the player
                        {
                                // check which button is still held down, and apply that movement
                                if(button_flags & KB_UP)
                                {
                                        this->moveObject(Aliases::up, this->getPlayerHandle());
                                }else
                                if(button_flags & KB_LEFT)
                                {
                                        this->moveObject(Aliases::left, this->getPlayerHandle());
                                 }else
                                 if(button_flags & KB_DOWN)
                                 {
                                                this->moveObject(Aliases::down, this->getPlayerHandle());
                                 }else
                                  if(button_flags & KB_RIGHT)
                                   { 
                                                this->moveObject(Aliases::right, this->getPlayerHandle());
                                  }
                        }
                  }
                  
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
                                      
                                  case 3://OW_CUBE_L:
                                      p = new POnewayCube(Aliases::left, i, j, OW_CUBE_L, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "onewaycube.tga");  // load it!
                                      
                                      second_matrix[i][j] = OW_CUBE_L;
                                      break; 
                                      
                                  case 4://OW_CUBE_R:
                                      p = new POnewayCube(Aliases::right, i, j, OW_CUBE_R, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "onewaycube.tga");  // load it!
                                      
                                      second_matrix[i][j] = OW_CUBE_R;
                                      break; 
                                      
                                  case 5://OW_CUBE_U:
                                      p = new POnewayCube(Aliases::up, i, j, OW_CUBE_U, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "onewaycube.tga");  // load it!
                                      
                                      second_matrix[i][j] = OW_CUBE_U;
                                      break;  
                                      
                                  case 6://OW_CUBE_D:
                                      p = new POnewayCube(Aliases::down, i, j, OW_CUBE_D, this->gameCore);
                                      data[i][j]->add(p);
                                      
                                      if((resourceHandle->getTextureResource(OW_CUBE_RES))==NULL)  // texture isn't in memory yet?
                                          resourceHandle->loadTextureResource(OW_CUBE_RES, "onewaycube.tga");  // load it!
                                      
                                      second_matrix[i][j] = OW_CUBE_D;
                                      break;
                                      
                                  case 7://BOMB:
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
              button_flags = 0;
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
                              // if child is player or movable cube, draw also parent
                              if ((static_cast<PLevelObject*>(obj)->getId() & (PLAYER | CUBE)) != 0) 
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
              /*glMatrixMode(GL_PROJECTION);  // Change Matrix Mode to Projection
              glLoadIdentity();             // Reset View
              glOrtho(0, 800, 0, 600, 0, 100);
              glMatrixMode(GL_MODELVIEW);   // Change Projection to Matrix Mode
              glLoadIdentity();

              glTranslatef(0, 600, -0.5);

              if(!endgameFlag)
                  time = glfwGetTime();
              fnt->writeTextAbs(10,-30,"Elapsed time: "+Functions::toString<int>((int)(time-starttime)));
              fnt->writeTextAbs(170,-30,"Moves: "+Functions::toString<int>(moves));*/
          }
          /****************************************
           * animate
           * Animates the objects on the field.
           * When they are done moving it activates
           * the floor underneath them.
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
                                        if(obj->animate(time))
                                                activateFloor(i,j);
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
						data[firstDroppedBomb->i][firstDroppedBomb->j]->toogleBombActivity();
                        delete bombs[0];
                        this->bombs.erase(this->bombs.begin());
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
          
          
    }
}
