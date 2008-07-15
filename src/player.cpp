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
              int PPlayer::getScore()
              {
                      return score;
              }

              unsigned short PPlayer::getBombs()
              {
                      return bombs;
              }

              // etc
              void PPlayer::incScore()
              {
                      score++;
              }

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
