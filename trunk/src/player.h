/* 
 * File:   player.h
 * Author: jernej
 *
 * Created on Ponedeljek, 14 julij 2008, 18:56
 */

#ifndef _PLAYER_H
#define	_PLAYER_H

#include <iostream>

#include "stdint.h"
#include "object.h"

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
    namespace GameClasses
    {
        class PPlayer
        {
          private:
            int score;
          public:
            PPlayer();
            void setBombs(uint8_t _bombs);
            int getScore();
              
            // to override
            void draw();
            bool initialize();
            void print();
            void onDeath();
          };
    }
}

#endif	/* _PLAYER_H */

