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
using namespace PacGame::Aliases;

namespace PacGame
{
      namespace GameClasses
      {
          namespace GameObjects
          {
               /**********************************************************
               * PPlayer
               *
               * Represents player entity
               * --------------------------------------------------------
               * Aljosa 2008
               * ********************************************************/
              class PPlayer : public PObject
              {
              private:
           //       int score;   
                  unsigned bombs;
                  
                  float curFrame;
                  int firstFrame, lastFrame;

              public:
                  // constructors
                  PPlayer(PCore *core);
                  PPlayer(int i, int j, PCore *core);

                  // setters
                  void setBombs(unsigned _bombs);

                  // getters
                  unsigned short getBombs();

                  // increase +1
                  void incBombs();
                  // decrease -1
                  void decBombs(); 

                  // to override
                  void draw(float x, float y);
                  void print();
                  
                  // movement and animation
                  bool animate(double time);

                  short isPlayerMovePossible(int direction);
                  
              };              
          }
      }
}

#endif	/* _PLAYER_H */

