/* 
 * File:   core.h
 * Author: aljosa
 *
 * Created on August 26, 2008, 8:58 PM
 */

#ifndef __CORE_H
#define	__CORE_H

#include "renderer/renderer.h"
#include "resource.h"
#include "camera.h"

namespace PacGame
{
    namespace GameClasses
    {
        class PCore
        {
        private:
            PRenderer *renderer; // renderer instance
            PResourceManager *resources;
            PCamera *camera;
            
        public:
            PCore(); // constructor
            ~PCore(); // destructor
            
            // init
            bool init();
            
            // getters
            PRenderer *getRenderer();
            PResourceManager *getResources();
            PCamera *getCamera();
            
            // release
            void release();
            
        };
    }
}

#endif	/* _CORE_H */
