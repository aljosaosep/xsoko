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
 * File: player.cpp
 *
 * Summary:
 * Includes player methods implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 */

#include "object.h"
#include "player.h"

namespace PacGame
{
      namespace GameClasses
      {
          namespace GameObjects
          {
              PPlayer::PPlayer(PCore *core) //  constructor
              { 
                  this->core = core;
                  this->id = 1;
                  this->bombs = 0;
              } 
              
              PPlayer::PPlayer(int i, int j, PCore *core)
              {
                   this->i = i;
                   this->j = j;
                   this->realI = i;
                   this->realJ = j;
                   this->core = core;
                   this->id = 1;
                   this->bombs = 0;
              }

              // setters
              void PPlayer::setBombs(unsigned _bombs)
              {
                      bombs = _bombs;
              }

              // getters
              unsigned short PPlayer::getBombs()
              {
                      return bombs;
              }
              
         /*     short PPlayer::isPlayerMovePossible()
              {
                  return false;
              }*/

              // etc
              void PPlayer::incBombs()
              {
                      bombs++;
              }
              
              void PPlayer::decBombs()
              {
                  this->bombs--;
              }

              // ===== FUNCTIONS TO OVERRIDE ===== //
              void PPlayer::draw() 
              {
                  static float frame;
                  frame += 0.5;
                  if(frame > 39)
                    frame = 0;
                    glColor4f(1.0, 1.0, 0.7f, 0.8f);
                    //glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(6));
                    //this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
                    glPushMatrix();
                    
                    glTranslatef(-0.3f,0,1);
                    glScalef(0.05f,0.05f,0.05f);
                    
                    // rotate the object, so it faces the right direction
                    if(direction & PL_OBJECT_FACE_UP)
                    {
                            glRotatef(180, 0,0,1);
                    }else
                    if(direction & PL_OBJECT_FACE_RIGHT)
                    {
                            glRotatef(-90, 0,0,1);
                    }else
                    /*if(direction & PL_OBJECT_FACE_DOWN)
                    {
                            // no need to rotate
                    }else*/
                    if(direction & PL_OBJECT_FACE_LEFT)
                    {
                            glRotatef(90,  0,0,1);
                    }
                    
                    core->getResources()->getModelResource(6)->DrawFrame(frame);
                    glPopMatrix();
                      // TODO
              }
              
              bool PPlayer::animate(double time)
              {
                      //curFrame += 
                      
                      // if moving
                      //if(direction & PL_OBJECT_MOVE)
                      {
                              double moveOffset = 0.01*time; // speed = 0.1
                            
                                if(realI != (float)i)
                                {
                                        if(realI > (float)i)
                                        {
                                                realI -= moveOffset;
                                                if(realI <= (float)i)
                                                        realI = (float)i;
                                        }
                                        else
                                        {
                                                realI += moveOffset;
                                                if(realI >= (float)i)
                                                        realI = (float)i;
                                        }
                                }
                                
                                if(realJ != (float)j)
                                {
                                        if(realJ > (float)j)
                                        {
                                                realJ -=moveOffset;
                                                if(realJ <= (float)j)
                                                        realJ = (float)j;
                                        }
                                        else
                                        {
                                                realJ +=moveOffset;
                                                if(realJ >= (float)j)
                                                        realJ = (float)j;
                                        }
                                }
                        
                                
                                // check direction, change matrix position
                                /*if(direction & PL_OBJECT_FACE_UP)
                              {
                                      realJ -= moveOffset;
                                      if(realJ <= j)
                                      {
                                              realJ = j;
                                              direction = direction ^ PL_OBJECT_MOVE;
                                      }
                              }else
                              if(direction & PL_OBJECT_FACE_RIGHT)
                              {
                                      realI += moveOffset;
                                      if(realI >= i)
                                      {
                                              realI = i;
                                              direction = direction ^ PL_OBJECT_MOVE;
                                      }
                              }else
                              if(direction & PL_OBJECT_FACE_DOWN)
                              {
                                      realJ += moveOffset;
                                      if(realJ >= j)
                                      {
                                              realJ = j;
                                              direction = direction ^ PL_OBJECT_MOVE;
                                      }
                              }else
                              if(direction & PL_OBJECT_FACE_LEFT)
                              {
                                      realI-= moveOffset;
                                      if(realI <= i)
                                      {
                                              realI = i;
                                              direction = direction ^ PL_OBJECT_MOVE;
                                      }
                              }*/
                              
                      }
                      
                      
                       return true;
              }
              
              short PPlayer::isPlayerMovePossible(int direction)
              {
                      // player can't make a move, if he is curently moving from one position to the next
                      if(realI == i && realJ == j)
                                return 1;
                                
                        return 0;
              }
              
              void PPlayer::print()
              {
                  cout<<"|_PLYR";
              }              
          }
      }
}
