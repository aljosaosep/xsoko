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
              PPlayer::PPlayer(PRenderer *renderer) //  constructor
              { 
                  this->renderer = renderer;
              } 
              
              PPlayer::PPlayer(int i, int j, PRenderer *renderer)
              {
                   this->i = i;
                   this->j = j;
                   this->renderer = renderer;                  
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
                    glBindTexture(GL_TEXTURE_2D, this->renderer->playerTex->getTexID());
                    this->renderer->drawCube(0.0, 0.0, 1.0, 0.0);
                      // TODO
              }

              bool PPlayer::initialize()
              {
                      // TODO
                      return 0;
              }

              void PPlayer::print()
              {
                  cout<<"|_PLYR";
              }
      }
}
