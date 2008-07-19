/* 
 * File:   session.h
 * Author: aljosa
 *
 * Created on July 18, 2008, 11:42 AM
 */

#include "level.h"
#include "renderer/renderer.h"

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
            
        public:
            PGameSession(PLevel *level) : level(level), player(level->getPlayerHandle()) {}
            PGameSession() : level(NULL), player(NULL)  {}
            
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

