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
                    core->getResources()->getModelResource(6)->DrawFrame(frame);
                    glPopMatrix();
                      // TODO
              }
              
              void PPlayer::print()
              {
                  cout<<"|_PLYR";
              }              
          }
      }
}
