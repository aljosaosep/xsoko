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
            PacGame::RenderMaschine::PRenderer renderer; 
            PInputSystem *input;
            
        public:
            PGameSession(PLevel *level, PInputSystem *input) : level(level), player(level->getPlayerHandle()), input(input) 
            {
          //      input.setLevel(level);
            }
            
            PGameSession() : level(NULL), player(NULL), input(NULL)  {}
            
            bool run();
            bool initialize();
            void mainLoop();
            
            // setters
            void setLevel(PLevel *level);
            void setScore(unsigned score);
            
            // getters
            PLevel *getLevel() const;
            unsigned getScore() const; 
        };
    }
}



#endif	/* _SESSION_H */
