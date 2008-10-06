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
 * File:   particle.h
 * Author: aljosa
 * 
 * desc: basic class for particle effects
 *
 * Created on October 5, 2008, 11:11 AM
 */

#ifndef __PARTICLE_H
#define	__PARTICLE_H

#define MAX_PARTICLES 100

#include "../vector.h"
#include <cstdio>
#include <ctime>

using namespace PacGame::GameClasses;

namespace PacGame
{
    namespace RenderMaschine
    {
        class PParticleEngine
        {
        protected:
            // one-particle structure
            struct particle
            {
                bool active;            // is particle active
                float life;             // how much life is particle got
                float fade;             // fade variable
                float r, g, b;          // color
                PVector3D position;     // particle position
                PVector3D vector;       // direction and speed vector
                PVector3D gravity;      // particle gravity
            };
            
            float slowdown;
            float xpseed, yspeed;
            float delay;
            float zoom;
            
            particle particles[MAX_PARTICLES];      // particle list
            
        public:
            PParticleEngine();          // constructor
            
            void init();                // initialization
            
            bool process();             // process - main particle function
        };
        
    }
}


#endif	/* _PARTICLE_H */

