/* 
 * File:   core.h
 * Author: aljosa
 *
 * Created on August 26, 2008, 8:58 PM
 */

#ifndef _CORE_H
#define	_CORE_H

#include "renderer/renderer.h"
#include "resource.h"

namespace PacGame
{
    namespace GameClasses
    {
        class PCore
        {
        private:
            PRenderer *renderer; // renderer instance
            PResourceManager *resources;
            
        public:
            PCore(); // constructor
            ~PCore(); // destructor
            
            // init
            bool init();
            
            // getters
            PRenderer *getRenderer();
            PResourceManager *getResources();
            
            // release
            void release();
            
        };
    }
}

#endif	/* _CORE_H */
