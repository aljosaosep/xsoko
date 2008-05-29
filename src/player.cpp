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

#include "entities.h"

namespace PacGame
{
      namespace GameClasses
      {
              PPlayer::PPlayer() {} // default constructor

              // setters
              void PPlayer::setBombs(uint8_t _bombs)
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
                      return (unsigned short)bombs;
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
              void PPlayer::onDeath()
              {
                      // TODO
              }

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
                      // TODO
                      cout<<"==== PLAYER INFO ===="<<endl;
                      cout<<"Bombs:" <<getBombs()<<endl;
                      cout<<"Score:" <<getScore()<<endl;
                      cout<<"====================="<<endl;
              }
      }
}
