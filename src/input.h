/* 
 * File:   input.h
 * Author: aljosa
 *
 * Input class; provides interface for interaction
 * with input devices
 *
 * Created on July 20, 2008, 5:50 PM
 */

#ifndef __INPUT_H
#define	__INPUT_H

#include <GL/glfw.h>
#include "level.h"

namespace PacGame
{
    namespace GameClasses
    {
        class PInputSystem
        {
        private: 
            PLevel *level;    // level object
            
        public:
            
            // constructors
            PInputSystem(PLevel *level) : level(level) { }
            PInputSystem() : level(NULL){ }
            
            // process function
            void process();
            
            // setters
            void setLevel(PLevel *level);
            
            // getters
            PLevel* getLevel() const;
        }; 
    }
}

#endif	/* _INPUT_H */

