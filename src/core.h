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
