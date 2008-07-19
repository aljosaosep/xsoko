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
             /* bool PPlayer::onMoveProcess(PDirection dir, PLevelObject* data[][30], int i, int j)
              {
                  switch(dir)
                  {
                      case Aliases::left:
                          data[i-1][j]->add(data[i][j]->returnFirstChild());
                          break;
                          
                      case Aliases::right:
                          break;  
                          
                      case Aliases::up:
                          break;
                          
                      case Aliases::down:
                          break;                        
                  }
                  return true;
              }*/
              
              void PPlayer::incBombs()
              {
                      bombs++;
              }

              // ===== FUNCTIONS TO OVERRIDE ===== //
              void PPlayer::draw() 
              {
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
