/* 
 * File:   session.h
 * Author: aljosa
 *
 * Created on July 18, 2008, 11:42 AM
 */

#include "level.h"
#include "renderer/renderer.h"
#include "input.h"

#ifndef __SESSION_H
#define	__SESSION_H

using namespace PacGame::RenderMaschine;

namespace PacGame
{
    namespace GameClasses
    {
        class PGameSession
        {
        private:
            PLevel *level; 
            PPlayer *player;           
            unsigned score;
            
            PInputSystem *input;
            unsigned moves;  
            double rotations_per_tick;
            
        public:
            // constructors
            PGameSession(PLevel *level, PInputSystem *input) : level(level), input(input), moves(0),  rotations_per_tick(0.1) {}
            PGameSession() : level(NULL), player(NULL), input(NULL),  moves(0),rotations_per_tick(0.1)   {}
            
            // methods
            bool run();
            bool initialize();
            void mainLoop();
            
            // setters
            void setLevel(PLevel *level);
            void setScore(unsigned score);
            void setInput(PInputSystem *input);
            
            // getters
            PLevel *getLevel() const;
            unsigned getScore() const; 
        };
    }
}



#endif	/* _SESSION_H */

