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
            
            PRenderer *renderer; 
            PInputSystem *input;
            unsigned moves;
        //    bool isGameRunning;    
            double rotations_per_tick;
            
        public:
            // constructors
            PGameSession(PLevel *level, PInputSystem *input, PRenderer *renderer) : level(level), player(level->getPlayerHandle()), 
                                                                renderer(renderer), input(input), moves(0), /*isGameRunning(true),*/ rotations_per_tick(0.1) {}
            
            PGameSession() : level(NULL), player(NULL), renderer(NULL), input(NULL),  moves(0),/* isGameRunning(true),*/ rotations_per_tick(0.1)   {}
            
            // methods
            bool run();
            bool initialize();
            void mainLoop();
            PRenderer* getRendererHandle();
            
            // setters
            void setLevel(PLevel *level);
            void setScore(unsigned score);
            void setInput(PInputSystem *input);
            void setRenderer();
          //  void setGameEnd();
            
            // getters
            PLevel *getLevel() const;
            unsigned getScore() const; 
        };
    }
}



#endif	/* _SESSION_H */

