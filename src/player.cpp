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
              PPlayer::PPlayer() {} // default constructor

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
                    glColor3f(1.0, 1.0, 0.7);
                    this->renderer.drawCube(0.0, 0.0, 1.0, 0.0);
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
              
              void PPlayer::drawToConsole()
              {
                  cout<<"-o-";
              }
      }
}
