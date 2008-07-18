/* 
 * File:   player.h
 * Author: jernej
 * Desc: Includes player class definition
 *
 * Created on Ponedeljek, 14 julij 2008, 18:56
 * Modified: aljosa on Torek, 15 julij 2008, 12:25 (conflict resloving)
 *           aljosa on Petek, 18 julij 2008, 11:48; score moved to game session class(session.h)
 */


#ifndef __PLAYER_H
#define	__PLAYER_H

#include <iostream>
#include "levelbox.h"

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
      namespace GameClasses
      {
           /**********************************************************
           * PPlayer
           *
           * Represents player entity
           * --------------------------------------------------------
           * Aljosa 2008
           * ********************************************************/
          class PPlayer : public PLevelObject
          {
          private:
           //       int score;   
                  unsigned bombs;

          public:
                  // constructors
                  PPlayer();

                  // setters
                  void setBombs(unsigned _bombs);

                  // getters
              //    int getScore();
                  unsigned short getBombs();

                  // increase +1
               //   void incScore();
                  void incBombs();

                  // to override
                  void draw();
                  bool initialize();
                  void print();
          };
      }
}


#endif	/* _PLAYER_H */

