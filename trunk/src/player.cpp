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
              PPlayer::PPlayer(PCore *core) //  constructor
              { 
                  this->core = core;
                  this->id = 1;
              } 
              
              PPlayer::PPlayer(int i, int j, PCore *core)
              {
                   this->i = i;
                   this->j = j;
                   this->core = core;
                   this->id = 1;
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

              // ===== FUNCTIONS TO OVERRIDE ===== //
              void PPlayer::draw() 
              {
                    glColor4f(1.0, 1.0, 0.7, 0.8);
                    glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(6));
                    this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, 0.0);
                      // TODO
              }
              
              void PPlayer::print()
              {
                  cout<<"|_PLYR";
              }
      }
}
