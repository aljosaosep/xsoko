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

#define NUM_PARTICLES 3000

#include "../vector.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
//#include <GL/glfw.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <cmath>

#define MAX_PARTICLES 1000

using namespace std;
using namespace PacGame::GameClasses;

namespace PacGame
{
    namespace RenderMaschine
    {
        typedef struct Particle {
            bool active;
            float life;
            float fade;

            float r, g, b;

            PVector3D pos;
            PVector3D dir;
            PVector3D grav;
        };

        class PParticleEffect {
        protected:
            float slowdown; // spawn ratio (?)
            float xspeed, yspeed; // direction of the "tail"
            float zoom;

            unsigned int col;
            unsigned int delay;
            unsigned int loop;

            Particle particles[MAX_PARTICLES];

            int numParticles;
            
            PVector3D position;

        public:
            PParticleEffect(const PVector3D &pos);
            virtual void init() = 0;
            virtual void draw() = 0;

            
        };

        class PParticleExplosion : PParticleEffect {

        public:
            PParticleExplosion(const PVector3D &pos);

            void init();
            void draw();

            int getNumParticles();

        };
  
        
    }
}


#endif	/* _PARTICLE_H */

